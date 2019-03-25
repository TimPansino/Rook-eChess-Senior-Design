#ifndef AI_H
#define AI_H
#include "defs.h"
#include "data.h"
#include "protos.h"

// Functions
void aiInit(int user_side);
void aiMakeMove(char* s);
void aiParseCommand(char* s);

#endif
