#ifndef ENGINE_H
#define ENGINE_H

#include <stdlib.h>
#include "chess.h"

typedef struct {
	Chess *chess;
	char *move;
	float eval;
} Engine;

void set_engine(Engine* engine, Chess* chess);
char* get_move(Chess *chess);

#endif
