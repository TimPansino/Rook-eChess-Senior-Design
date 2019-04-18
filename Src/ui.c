char pawnPromote(void) {
    char s[100];

    Print("Promote to...");
    Scan(s);
    while (strlen(s) != 1) {
        Print("Error. Only 1 character allowed.");
        Print("Promote to...");
        Scan(s);
    }

    return s[0];
}