/*
 *	DATA.H
 *	Tom Kerrigan's Simple Chess Program (TSCP)
 *
 *	Copyright 1997 Tom Kerrigan
 */

#ifndef DATA_H_
#define DATA_H_

extern int color[64];
extern int piece[64];
extern int side;
extern int xside;
extern int castle;
extern int ep;
extern int fifty;
extern int hash;
extern int ply;
extern int hply;
extern gen_t gen_dat[GEN_STACK];
extern int first_move[MAX_PLY];
extern int history[64][64];
extern hist_t hist_dat[HIST_STACK];
extern int max_time;
extern int max_depth;
extern int start_time;
extern int stop_time;
extern int nodes;
extern move pv[MAX_PLY][MAX_PLY];
extern int pv_length[MAX_PLY];
extern BOOL follow_pv;
extern int hash_piece[2][6][64];
extern int hash_side;
extern int hash_ep[64];
extern int mailbox[120];
extern int mailbox64[64];
extern BOOL slide[6];
extern int offsets[6];
extern int offset[6][8];
extern int castle_mask[64];
extern char piece_char[6];
extern int init_color[64];
extern int init_piece[64];

#endif /* DATA_H_ */
