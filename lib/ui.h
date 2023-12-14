#ifndef UI_H
#define UI_H

#include <raylib.h>
#include <stdlib.h>

#include "chess.h"
#include "engine.h"

#define B_SQUARE (Color){ 110, 109, 107, 255 }
#define W_SQUARE (Color){ 144, 143, 141, 255 }
#define S_SQUARE (Color){ 117, 144, 161, 255 }
#define P_SQUARE (Color){ 0, 0, 0, 64 }
#define END_SCREEN (Color){ 0, 0, 0, 64 }

#if defined(PLATFORM_WEB)
#define WEB 1
#else
#define WEB 0
#endif

typedef struct {
	bool options;
	bool rotation;
	bool perspective;
	bool sound;
	bool coordinate;
	bool new_game;
	int game_type;
	int style;

	Texture2D w_king;
	Texture2D w_queen;
	Texture2D w_rook;
	Texture2D w_bishop;
	Texture2D w_knight;
	Texture2D w_pawn;
	Texture2D b_king;
	Texture2D b_queen;
	Texture2D b_rook;
	Texture2D b_bishop;
	Texture2D b_knight;
	Texture2D b_pawn;

	Sound move_sound;
	Sound capture_sound;

	Rectangle end;
} Ui;

void set_ui(Ui *ui);
void render(Chess *chess, Engine *engine);
#endif
