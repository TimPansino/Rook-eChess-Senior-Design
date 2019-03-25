#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include <sys/timeb.h>

#include "ai.h"
#include "defs.h"
#include "data.h"
#include "protos.h"

void Print(const char* format, ...);

BOOL ftime_ok;
int computer_side;
int m;
int post;

void aiInit(int user_side) {
	post = 0;
	ftime_ok = FALSE;

	init_board();
	gen();
	init_board();
	open_book();
	gen();

	computer_side = EMPTY;
	max_time = 1 << 25;
	max_depth = 4;

	if (user_side == LIGHT) {
		aiParseCommand("white");
	}
	else if (user_side == DARK) {
		aiParseCommand("black");
	}
}

void aiMakeMove(char* s) {
    if (side == computer_side) {
        think(post);
        if (!pv[0][0].u) {
            computer_side = EMPTY;
        }
        strcpy(s, move_str(pv[0][0].b));
        makemove(pv[0][0].b);
        ply = 0;
        gen();
        print_result();
    }
}

void aiParseCommand(char* s) {
    if (!strcmp(s, "xboard"))
        return;
    if (!strcmp(s, "new")) {
        init_board();
        gen();
        computer_side = DARK;
        return;
    }
    //if (!strcmp(s, "quit"))
    if (!strcmp(s, "force")) {
        computer_side = EMPTY;
        return;
    }
    if (!strcmp(s, "white")) {
        side = LIGHT;
        xside = DARK;
        gen();
        computer_side = DARK;
        return;
    }
    if (!strcmp(s, "black")) {
        side = DARK;
        xside = LIGHT;
        gen();
        computer_side = LIGHT;
        return;
    }
    /*if (!strcmp(command, "st")) {
        sscanf(line, "st %d", &max_time);
        max_time *= 1000;
        max_depth = 32;
    }
    if (!strcmp(command, "sd")) {
        sscanf(line, "sd %d", &max_depth);
        max_time = 1 << 25;
    }
    if (!strcmp(command, "time")) {
        sscanf(line, "time %d", &max_time);
        max_time *= 10;
        max_time /= 30;
        max_depth = 32;
    } */
    if (!strcmp(s, "go")) {
        computer_side = side;
        return;
    }
    if (!strcmp(s, "hint")) {
        think(0);
        Print("Hint: %s\n", move_str(pv[0][0].b));
        return;

    }
    if (!strcmp(s, "undo")) {
        if (!hply)
            return;
        takeback();
        ply = 0;
        gen();
        return;
    }
    if (!strcmp(s, "remove")) {
        if (hply < 2)
            return;
        takeback();
        takeback();
        ply = 0;
        gen();
        return;
    }
    if (!strcmp(s, "post")) {
        post = 2;
        return;
    }
    if (!strcmp(s, "nopost")) {
        post = 0;
        return;
    }
    m = parse_move(s);
    if (m == -1 || !makemove(gen_dat[m].m.b))
    {
        Print("Error: Move not accepted.\n");
    }
    else {
        ply = 0;
        gen();
        print_result();
    }
}


char *move_str(move_bytes m)
{
    static char str[6];

    char c;

    if (m.bits & 32) {
        switch (m.promote) {
            case KNIGHT:
                c = 'n';
                break;
            case BISHOP:
                c = 'b';
                break;
            case ROOK:
                c = 'r';
                break;
            default:
                c = 'q';
                break;
        }
        sprintf(str, "%c%d%c%d%c",
                COL(m.from) + 'a',
                8 - ROW(m.from),
                COL(m.to) + 'a',
                8 - ROW(m.to),
                c);
    }
    else
        sprintf(str, "%c%d%c%d",
                COL(m.from) + 'a',
                8 - ROW(m.from),
                COL(m.to) + 'a',
                8 - ROW(m.to));
    return str;
}

/* print_board() prints the board */

void print_board()
{
    int i;

    Print("\n8 ");
    for (i = 0; i < 64; ++i) {
        switch (color[i]) {
            case EMPTY:
                Print(" .");
                break;
            case LIGHT:
                Print(" %c", piece_char[piece[i]]);
                break;
            case DARK:
                Print(" %c", piece_char[piece[i]] + ('a' - 'A'));
                break;
        }
        if ((i + 1) % 8 == 0 && i != 63)
            Print("\n%d ", 7 - ROW(i));
    }
    Print("\n\n   a b c d e f g h\n\n");
}

int get_ms()
{
    struct timeb timebuffer;
    //ftime(&timebuffer);
    if (timebuffer.millitm != 0)
        ftime_ok = TRUE;
    return (timebuffer.time * 1000) + timebuffer.millitm;
}

int parse_move(char *s)
{
    int from, to, i;

    /* make sure the string looks like a move */
    if (s[0] < 'a' || s[0] > 'h' ||
            s[1] < '0' || s[1] > '9' ||
            s[2] < 'a' || s[2] > 'h' ||
            s[3] < '0' || s[3] > '9')
        return -1;

    from = s[0] - 'a';
    from += 8 * (8 - (s[1] - '0'));
    to = s[2] - 'a';
    to += 8 * (8 - (s[3] - '0'));

    for (i = 0; i < first_move[1]; ++i)
        if (gen_dat[i].m.b.from == from && gen_dat[i].m.b.to == to) {

            /* if the move is a promotion, handle the promotion piece;
               assume that the promotion moves occur consecutively in
               gen_dat. */
            if (gen_dat[i].m.b.bits & 32)
                switch (s[4]) {
                    case 'N':
                    case 'n':
                        return i;
                    case 'B':
                    case 'b':
                        return i + 1;
                    case 'R':
                    case 'r':
                        return i + 2;
                    default:  /* assume it's a queen */
                        return i + 3;
                }
            return i;
        }

    /* didn't find the move */
    return -1;
}

/* print_result() checks to see if the game is over, and if so,
   prints the result. */

void print_result()
{
    int i;

    /* is there a legal move? */
    for (i = 0; i < first_move[1]; ++i)
        if (makemove(gen_dat[i].m.b)) {
            takeback();
            break;
        }
    if (i == first_move[1]) {
        if (in_check(side)) {
            if (side == LIGHT)
                Print("0-1 {Black mates}\n");
            else
                Print("1-0 {White mates}\n");
        }
        else
            Print("1/2-1/2 {Stalemate}\n");
    }
    else if (reps() == 2)
        Print("1/2-1/2 {Draw by repetition}\n");
    else if (fifty >= 100)
        Print("1/2-1/2 {Draw by fifty move rule}\n");
}


/* bench: This is a little benchmark code that calculates how many
   nodes per second TSCP searches.
   It sets the position to move 17 of Bobby Fischer vs. J. Sherwin,
   New Jersey State Open Championship, 9/2/1957.
   Then it searches five ply three times. It calculates nodes per
   second from the best time. */

int bench_color[64] = {
    6, 1, 1, 6, 6, 1, 1, 6,
    1, 6, 6, 6, 6, 1, 1, 1,
    6, 1, 6, 1, 1, 6, 1, 6,
    6, 6, 6, 1, 6, 6, 0, 6,
    6, 6, 1, 0, 6, 6, 6, 6,
    6, 6, 0, 6, 6, 6, 0, 6,
    0, 0, 0, 6, 6, 0, 0, 0,
    0, 6, 0, 6, 0, 6, 0, 6
};

int bench_piece[64] = {
    6, 3, 2, 6, 6, 3, 5, 6,
    0, 6, 6, 6, 6, 0, 0, 0,
    6, 0, 6, 4, 0, 6, 1, 6,
    6, 6, 6, 1, 6, 6, 1, 6,
    6, 6, 0, 0, 6, 6, 6, 6,
    6, 6, 0, 6, 6, 6, 0, 6,
    0, 0, 4, 6, 6, 0, 2, 0,
    3, 6, 2, 6, 3, 6, 5, 6
};

void bench()
{
    int i;
    int t[3];
    double nps;

    /* setting the position to a non-initial position confuses the opening
       book code. */
    close_book();

    for (i = 0; i < 64; ++i) {
        color[i] = bench_color[i];
        piece[i] = bench_piece[i];
    }
    side = LIGHT;
    xside = DARK;
    castle = 0;
    ep = -1;
    fifty = 0;
    ply = 0;
    hply = 0;
    set_hash();
    print_board();
    max_time = 1 << 25;
    max_depth = 5;
    for (i = 0; i < 3; ++i) {
        think(1);
        t[i] = get_ms() - start_time;
        Print("Time: %d ms\n", t[i]);
    }
    if (t[1] < t[0])
        t[0] = t[1];
    if (t[2] < t[0])
        t[0] = t[2];
    Print("\n");
    Print("Nodes: %d\n", nodes);
    Print("Best time: %d ms\n", t[0]);
    if (!ftime_ok) {
        Print("\n");
        Print("Your compiler's ftime() function is apparently only accurate\n");
        Print("to the second. Please change the get_ms() function in main.c\n");
        Print("to make it more accurate.\n");
        Print("\n");
        return;
    }
    if (t[0] == 0) {
        Print("(invalid)\n");
        return;
    }
    nps = (double)nodes / (double)t[0];
    nps *= 1000.0;

    /* Score: 1.000 = my Athlon XP 2000+ */
    // printf("Nodes per second: %d (Score: %.3f)\n", (int)nps, (float)nps/243169.0);

    init_board();
    open_book();
    gen();
}
