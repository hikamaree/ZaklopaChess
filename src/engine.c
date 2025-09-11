#include "engine.h"
#include "chess.h"
#include <limits.h>
#include <pthread.h>
#include <string.h>

typedef struct {
    Chess* chess;
    char best_move[5];
    int done;
} EngineTask;

static EngineTask engine_task;
static pthread_t engine_thread;

int pawn_table[64] = {
	0,   0,   0,   0,   0,   0,   0,   0,
	50,  50,  50,  50,  50,  50,  50,  50,
	10,  10,  20,  30,  30,  20,  10,  10,
	0,   0,   0,  20,  20,   0,   0,   0,
	0,   0,   0, -20, -20,   0,   0,   0,
	10, -10, -20,   0,   0, -20, -10,  10,
	10,  20,  20, -20, -20,  20,  20,  10,
	0,   0,   0,   0,   0,   0,   0,   0
};

int knight_table[64] = {
	-50, -40, -30, -30, -30, -30, -40, -50,
	-40, -20,   0,   0,   0,   0, -20, -40,
	-30,   0,  10,  15,  15,  10,   0, -30,
	-30,   0,  15,  20,  20,  15,   0, -30,
	-30,   0,  15,  20,  20,  15,   0, -30,
	-30,   0,  10,  15,  15,  10,   0, -30,
	-40, -20,   0,   0,   0,   0, -20, -40,
	-50, -40, -30, -30, -30, -30, -40, -50
};

int bishop_table[64] = {
	-20, -10, -10, -10, -10, -10, -10, -20,
	-10,   0,   0,   0,   0,   0,   0, -10,
	-10,   0,   5,  10,  10,   5,   0, -10,
	-10,   0,   5,  10,  10,   5,   0, -10,
	-10,   0,   5,  10,  10,   5,   0, -10,
	-10,   0,   5,  10,  10,   5,   0, -10,
	-10,   0,   0,   0,   0,   0,   0, -10,
	-20, -10, -10, -10, -10, -10, -10, -20
};

int rook_table[64] = {
	0,   0,   0,   0,   0,   0,   0,   0,
	0,   0,   0,   0,   0,   0,   0,   0,
	0,   0,   0,   0,   0,   0,   0,   0,
	0,   0,   0,   0,   0,   0,   0,   0,
	0,   0,   0,   0,   0,   0,   0,   0,
	0,   0,   0,   0,   0,   0,   0,   0,
	0,   0,   0,   0,   0,   0,   0,   0,
	0,   0,   0,   0,   0,   0,   0,   0
};

int queen_table[64] = {
	-20, -10, -10,  -5,  -5, -10, -10, -20,
	-10,   0,   0,   0,   0,   0,   0, -10,
	-10,   0,   5,   5,   5,   5,   0, -10,
	-5,    0,   5,   5,   5,   5,   0,  -5,
	0,     0,   5,   5,   5,   5,   0,  -5,
	-10,   5,   5,   5,   5,   5,   0, -10,
	-10,   0,   5,   0,   0,   0,   0, -10,
	-20, -10, -10,  -5,  -5, -10, -10, -20
};

int king_table[64] = {
	-30, -40, -40, -50, -50, -40, -40, -30,
	-30, -40, -40, -50, -50, -40, -40, -30,
	-30, -40, -40, -50, -50, -40, -40, -30,
	-30, -40, -40, -50, -50, -40, -40, -30,
	-20, -30, -30, -40, -40, -30, -30, -20,
	-10, -20, -20, -20, -20, -20, -20, -10,
	20,  20,   0,   0,   0,   0,  20,  20,
	20,  30,   10,  0,   0,  10,  30,  20
};

int evaluate(Square** board) {
    int score = 0;
    int piece_value[128] = {
        ['P'] = 100, ['N'] = 320, ['B'] = 330, ['R'] = 500, ['Q'] = 900, ['K'] = INT_MAX,
        ['p'] = -100, ['n'] = -320, ['b'] = -330, ['r'] = -500, ['q'] = -900, ['k'] = INT_MIN
    };

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            char p = board[i][j];
            if (p == 0) continue;

            int idx = i * 8 + j;
            score += piece_value[(int)p];

            switch(p) {
                case 'P': score += pawn_table[idx]; break;
                case 'p': score -= pawn_table[63 - idx]; break;
                case 'N': score += knight_table[idx]; break;
                case 'n': score -= knight_table[63 - idx]; break;
                case 'B': score += bishop_table[idx]; break;
                case 'b': score -= bishop_table[63 - idx]; break;
                case 'R': score += rook_table[idx]; break;
                case 'r': score -= rook_table[63 - idx]; break;
                case 'Q': score += queen_table[idx]; break;
                case 'q': score -= queen_table[63 - idx]; break;
                case 'K': score += king_table[idx]; break;
                case 'k': score -= king_table[63 - idx]; break;
            }
        }
    }

    return score;
}

int minimaxAB(Chess *chess, int dubina, int alfa, int beta, bool max_igrac) {
	if (dubina == 0 || chess->mate) {
		return evaluate(chess->board);
	}

	int best_eval = max_igrac ? INT_MIN : INT_MAX;

	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {
			if ((chess->turn && white(chess->board[x][y])) ||
				(!chess->turn && black(chess->board[x][y]))) {

				Chess *c = copy_chess(chess);
				select_piece(c, x, y);

				for (int x1 = 0; x1 < 8; x1++) {
					for (int y1 = 0; y1 < 8; y1++) {
						if (c->moves[x1][y1]) {
							Chess *c1 = copy_chess(c);
							move_piece(c1, x1, y1);

							int eval = minimaxAB(c1, dubina - 1, alfa, beta, !max_igrac);

							free_chess(c1);

							if (max_igrac) {
								if (eval > best_eval) best_eval = eval;
								if (eval > alfa) alfa = eval;
							} else {
								if (eval < best_eval) best_eval = eval;
								if (eval < beta) beta = eval;
							}

							if (beta <= alfa) {
								free_chess(c);
								return best_eval;
							}
						}
					}
				}

				free_chess(c);
			}
		}
	}

	if (best_eval == (max_igrac ? INT_MIN : INT_MAX)) {
		return evaluate(chess->board);
	}

	return best_eval;
}

static void* engine_thread_func(void* arg) {
    EngineTask* task = (EngineTask*)arg;
    int depth = 5;
    int best_eval = task->chess->turn ? INT_MIN : INT_MAX;
    char move[5] = {0};

    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            if ((task->chess->turn && white(task->chess->board[x][y])) ||
                (!task->chess->turn && black(task->chess->board[x][y]))) {

                Chess* c = copy_chess(task->chess);
                select_piece(c, x, y);

                for (int x1 = 0; x1 < 8; x1++) {
                    for (int y1 = 0; y1 < 8; y1++) {
                        if (c->moves[x1][y1]) {
                            Chess* c1 = copy_chess(c);
                            move_piece(c1, x1, y1);

                            int eval = minimaxAB(c1, depth - 1, INT_MIN, INT_MAX, !task->chess->turn);

                            if ((task->chess->turn && eval > best_eval) ||
                                (!task->chess->turn && eval < best_eval)) {
                                best_eval = eval;
                                memcpy(move, c1->move, 5);
                            }

                            free_chess(c1);
                        }
                    }
                }

                free_chess(c);
            }
        }
    }

    memcpy(task->best_move, move, 5);
    task->done = 1;
    return NULL;
}

void engine_start(Chess* chess) {
    if (engine_task.done == 0) {
        engine_task.chess = copy_chess(chess);
        engine_task.done = -1;
        pthread_create(&engine_thread, NULL, engine_thread_func, &engine_task);
        pthread_detach(engine_thread);
    } else if(engine_task.done == 1) {
        play_move(chess, engine_task.best_move);
        engine_task.done = 0;
	}
}
