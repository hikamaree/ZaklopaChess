#include "chess.h"
#include "ui.h"

int main() {
	Chess *chess = init_chess();
	render(chess);
	delete_chess(chess);
	return 0;
}
