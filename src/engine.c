#include "engine.h"
#include "chess.h"
#include <limits.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    Chess *chess;
    int dubina;
    int alfa;
    int beta;
    bool max_igrac;
    int rezultat;
} ThreadArgs;

#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))

int evaluate(Square** board);
int minimax(Chess *chess, int dubina, int alfa, int beta, bool max_igrac);
void* minimax_thread(void* arg);
void calculate(Chess* chess);

int evaluate(Square** board) {
    int score = 0;
    int piece_value[] = {
        ['P'] = 100,
		['N'] = 320,
		['B'] = 330,
		['R'] = 500,
		['Q'] = 900,
		['K'] = 20000,
        ['p'] = -100,
		['n'] = -320,
		['b'] = -330,
		['r'] = -500,
		['q'] = -900,
		['k'] = -20000
    };
    
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            score += piece_value[board[i][j]];
        }
    }

    return score;
}

void* minimax_thread(void* arg) {
    ThreadArgs *args = (ThreadArgs*)arg;
    args->rezultat = minimax(args->chess, args->dubina, args->alfa, args->beta, args->max_igrac);
    return NULL;
}

int minimax(Chess *chess, int dubina, int alfa, int beta, bool max_igrac) {
    if (dubina <= 0 || chess->mate) {
        return evaluate(chess->board);
    }

    int num_threads = 0;
    pthread_t threads[256];
    ThreadArgs thread_args[256];

    if (max_igrac) {
        int max_eval = INT_MIN;

        for (int x = 0; x < 8; x++) {
            for (int y = 0; y < 8; y++) {
                if (chess->board[x][y] != 0) {
                    Chess *c = copy_chess(chess);
                    for (int x1 = 0; x1 < 8; x1++) {
                        for (int y1 = 0; y1 < 8; y1++) {
                            if (chess->moves[x1][y1]) {
                                Chess *c1 = copy_chess(c);
                                move_piece(c1, x1, y1);

                                thread_args[num_threads].chess = c1;
                                thread_args[num_threads].dubina = dubina - 1;
                                thread_args[num_threads].alfa = alfa;
                                thread_args[num_threads].beta = beta;
                                thread_args[num_threads].max_igrac = false;

                                pthread_create(&threads[num_threads], NULL, minimax_thread, &thread_args[num_threads]);
                                num_threads++;

                                /*if (num_threads >= 64) {*/
                                /*    break;*/
                                /*}*/
                            }
                        }
                    }
                }
            }
        }

        for (int i = 0; i < num_threads; i++) {
            pthread_join(threads[i], NULL);
            int eval = thread_args[i].rezultat;
            max_eval = (eval > max_eval) ? eval : max_eval;
            alfa = (eval > alfa) ? eval : alfa;
            if (beta <= alfa) {
                break;
            }
        }

        return max_eval;
    } else {
        int min_eval = INT_MAX;

        for (int x = 0; x < 8; x++) {
            for (int y = 0; y < 8; y++) {
                if (chess->board[x][y] != 0) {
                    Chess *c = copy_chess(chess);
                    for (int x1 = 0; x1 < 8; x1++) {
                        for (int y1 = 0; y1 < 8; y1++) {
                            if (chess->moves[x1][y1]) {
                                Chess *c1 = copy_chess(c);
                                move_piece(c1, x1, y1);

                                thread_args[num_threads].chess = c1;
                                thread_args[num_threads].dubina = dubina - 1;
                                thread_args[num_threads].alfa = alfa;
                                thread_args[num_threads].beta = beta;
                                thread_args[num_threads].max_igrac = true;

                                pthread_create(&threads[num_threads], NULL, minimax_thread, &thread_args[num_threads]);
                                num_threads++;

                                /*if (num_threads >= 64) {*/
                                /*    break;*/
                                /*}*/
                            }
                        }
                    }
                }
            }
        }

        for (int i = 0; i < num_threads; i++) {
            pthread_join(threads[i], NULL);
            int eval = thread_args[i].rezultat;
            min_eval = (eval < min_eval) ? eval : min_eval;
            beta = (eval < beta) ? eval : beta;
            if (beta <= alfa) {
                break;
            }
        }

        return min_eval;
    }
}

void calculate(Chess* chess) {
	int eval = !chess->turn ? INT_MAX : INT_MIN;
	char move[5];
	int dubina = 5;
	for(int x = 0; x < 8; x++) {
		for(int y = 0; y < 8; y++) {
			if((chess->turn && white(chess->board[x][y])) || (!chess->turn && black(chess->board[x][y]))) {
				Chess* c = copy_chess(chess);
				select_piece(c, x, y);
				for(int x1 = 0; x1 < 8; x1++){
					for(int y1 = 0; y1 < 8; y1++) {
						if(c->moves[x1][y1]) {
							Chess *c1 = copy_chess(c);
							move_piece(c1, x1, y1);
							int tmp = minimax(c1, dubina - 1, INT_MIN, INT_MAX, !chess->turn);
							if((chess->turn && eval < tmp) || (!chess->turn && eval > tmp)) {
								eval = tmp;
								memcpy(move, c1->move, 5);
							}
						}
					}
				}
			}
		}
	}
	play_move(chess, move);
}
