#include "ui.h"

int main() {
	Chess chess;
	new_game(&chess);

	render(&chess);
	return 0;
}
