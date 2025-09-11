#include "chess.h"
#include "ui.h"

int main() {
	Chess *chess = init_chess();
	run(chess);
	free_chess(chess);
	return 0;
}
