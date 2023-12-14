#include "engine.h"

void set_engine(Engine* engine, Chess* chess) {
	engine->chess = chess;
	engine->move = (char*)malloc(5 * sizeof(char));
	engine->eval = 0;
}

bool possible(Chess* chess);

char *engine_move(Chess* chess) {
//	if(possible())
	return NULL;
}
