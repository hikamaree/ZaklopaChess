#include "ui.h"

int main() {
	Chess chess;
	new_game(&chess);

	Engine engine;
	set_engine(&engine, &chess);

	render(&chess, &engine);
	return 0;
}
