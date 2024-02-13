#include "ui.h"
#include <stdlib.h>

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "../styles/ashes/style_ashes.h"
#include "../styles/bluish/style_bluish.h"
#include "../styles/candy/style_candy.h"
#include "../styles/cherry/style_cherry.h"
#include "../styles/cyber/style_cyber.h"
#include "../styles/dark/style_dark.h"
#include "../styles/enefete/style_enefete.h"
#include "../styles/jungle/style_jungle.h"
#include "../styles/lavanda/style_lavanda.h"
#include "../styles/sunny/style_sunny.h"
#include "../styles/terminal/style_terminal.h"

void set_ui(Ui *ui) {
	ui->w_king = LoadTexture("assets/textures/white_king.png");
	ui->w_queen = LoadTexture("assets/textures/white_queen.png");
	ui->w_rook = LoadTexture("assets/textures/white_rook.png");
	ui->w_bishop = LoadTexture("assets/textures/white_bishop.png");
	ui->w_knight = LoadTexture("assets/textures/white_knight.png");
	ui->w_pawn = LoadTexture("assets/textures/white_pawn.png");

	ui->b_king = LoadTexture("assets/textures/black_king.png");
	ui->b_queen = LoadTexture("assets/textures/black_queen.png");
	ui->b_rook = LoadTexture("assets/textures/black_rook.png");
	ui->b_bishop = LoadTexture("assets/textures/black_bishop.png");
	ui->b_knight = LoadTexture("assets/textures/black_knight.png");
	ui->b_pawn = LoadTexture("assets/textures/black_pawn.png");

	ui->move_sound = LoadSound("assets/sounds/move.wav");
	ui->capture_sound = LoadSound("assets/sounds/capture.wav");

	ui->end.x = 50;
	ui->end.y = 50;
	ui->end.width = 800;
	ui->end.height = 800;

	ui->options = false;
	ui->rotation = true;
	ui->perspective = true;
	ui->sound = true;
	ui->coordinate = true;
	ui->new_game = false;
	ui->start_game = false;
	ui->game_type = 0;
	ui->style = 4;
	ui->quit = false;

	GuiLoadStyleCyber();
	GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
}

void close_ui(Ui *ui) {
	UnloadTexture(ui->w_king);
	UnloadTexture(ui->w_queen);
	UnloadTexture(ui->w_rook);
	UnloadTexture(ui->w_bishop);
	UnloadTexture(ui->w_knight);
	UnloadTexture(ui->w_pawn);
	UnloadTexture(ui->b_king);
	UnloadTexture(ui->b_queen);
	UnloadTexture(ui->b_rook);
	UnloadTexture(ui->b_bishop);
	UnloadTexture(ui->b_knight);
	UnloadTexture(ui->b_pawn);

	UnloadSound(ui->move_sound);
	UnloadSound(ui->capture_sound);
	free(ui);
}

void set_style(Ui *ui) {
	ui->style = (ui->style + 1) % 12;
	switch(ui->style) {
		case 0:
			GuiLoadStyleAshes();
			break;
		case 1:
			GuiLoadStyleBluish();
			break;
		case 2:
			GuiLoadStyleCandy();
			break;
		case 3:
			GuiLoadStyleCherry();
			break;
		case 4:
			GuiLoadStyleCyber();
			break;
		case 5:
			GuiLoadStyleDark();
			break;
		case 6:
			GuiLoadStyleDefault();
			break;
		case 7:
			GuiLoadStyleEnefete();
			break;
		case 8:
			GuiLoadStyleJungle();
			break;
		case 9:
			GuiLoadStyleLavanda();
			break;
		case 10:
			GuiLoadStyleSunny();
			break;
		case 11:
			GuiLoadStyleTerminal();
			break;
	}
	GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
}

void draw_coordinate(Ui *ui, bool side) {
	if(ui->coordinate) {
		int j;
		for(int i = 1; i < 9; i++) {
			if(side) j = 9 - i;
			else j = i;
			GuiDrawText(TextFormat("%c", 48 + j), (Rectangle){20, 100 * i - 5, 20, 20}, 1, GetColor(GuiGetStyle(DEFAULT, LINE_COLOR)));
			GuiDrawText(TextFormat("%c", 73 - j), (Rectangle){100 * i - 5, 860, 20, 20}, 1, GetColor(GuiGetStyle(DEFAULT, LINE_COLOR)));
		}
	}
}

void draw_board(Ui *ui, Chess* chess, bool side) {
	int m, n;
	int x = chess->x;
	int y = chess->y;
	if(!side) {
		x = 7 - x;
		y = 7 - y;
	}
	for(int i = 0; i < 8; i++) {
		for(int j = 0; j < 8; j++) {
			if(side) {
				m = j;
				n = i;
			}
			else {
				m = 7 - j;
				n = 7 - i;
			}
			if(n == x && m == y)
				DrawRectangle(100 * m + 50, 100 * n + 50, 100, 100, S_SQUARE);
			else {
				if((i + j + 1) % 2) {
					DrawRectangle(100 * m + 50, 100 * n + 50, 100, 100, W_SQUARE);
				}
				else {
					DrawRectangle(100 * m + 50, 100 * n + 50, 100, 100, B_SQUARE);
				}
			}
			switch (chess->position[i][j]) {
				case 'K':
					DrawTexture(ui->w_king, m * 100 + 50, n * 100 + 50, WHITE);
					break;
				case 'Q':
					DrawTexture(ui->w_queen, m * 100 + 50, n * 100 + 50, WHITE);
					break;
				case 'R':
					DrawTexture(ui->w_rook, m * 100 + 50, n * 100 + 50, WHITE);
					break;
				case 'B':
					DrawTexture(ui->w_bishop, m * 100 + 50, n * 100 + 50, WHITE);
					break;
				case 'N':
					DrawTexture(ui->w_knight, m * 100 + 50, n * 100 + 50, WHITE);
					break;
				case 'P':
					DrawTexture(ui->w_pawn, m * 100 + 50, n * 100 + 50, WHITE);
					break;
				case 'k':
					DrawTexture(ui->b_king, m * 100 + 50, n * 100 + 50, WHITE);
					break;
				case 'q':
					DrawTexture(ui->b_queen, m * 100 + 50, n * 100 + 50, WHITE);
					break;
				case 'r':
					DrawTexture(ui->b_rook, m * 100 + 50, n * 100 + 50, WHITE);
					break;
				case 'b':
					DrawTexture(ui->b_bishop, m * 100 + 50, n * 100 + 50, WHITE);
					break;
				case 'n':
					DrawTexture(ui->b_knight, m * 100 + 50, n * 100 + 50, WHITE);
					break;
				case 'p':
					DrawTexture(ui->b_pawn, m * 100 + 50, n * 100 + 50, WHITE);
					break;
			}
			if(chess->possible[i][j])
				DrawCircle(100 * (m + 1), 100 * (n + 1), 25, P_SQUARE); 
		}
	}
}

void draw_menu(Ui *ui) {
	if(ui->options) {
		DrawText("ROTATION", 925, 130, 20, GetColor(GuiGetStyle(DEFAULT, LINE_COLOR)));
		if(GuiButton((Rectangle){925, 150, 200, 50}, ui->rotation ? "ON" : "OFF")) {
			ui->rotation = !ui->rotation;
		}
		DrawText("PERSPECTIVE", 925, 230, 20, GetColor(GuiGetStyle(DEFAULT, LINE_COLOR)));
		if(GuiButton((Rectangle){925, 250, 200, 50}, ui->perspective ? "WHITE" : "BLACK")) {
			ui->perspective = !ui->perspective;
		}
		DrawText("COORDINATE", 925, 330, 20, GetColor(GuiGetStyle(DEFAULT, LINE_COLOR)));
		if(GuiButton((Rectangle){925, 350, 200, 50}, ui->coordinate ? "ON" : "OFF")) {
			ui->coordinate = !ui->coordinate;
		}
		DrawText("SOUND", 925, 430, 20, GetColor(GuiGetStyle(DEFAULT, LINE_COLOR)));
		if(GuiButton((Rectangle){925, 450, 200, 50}, ui->sound ? "ON" : "OFF")) {
			ui->sound = !ui->sound;
		}

		char style[12][10] = {"ASHES", "BLUISH", "CANDY", "CHERRY", "CYBER", "DARK", "DEFAULT", "ENEFETE", "JUNGLE", "LAVANDA", "SUNNY", "TERMINAL"};
		DrawText("STYLE", 925, 530, 20, GetColor(GuiGetStyle(DEFAULT, LINE_COLOR)));
		if(GuiButton((Rectangle){925, 550, 200, 50}, style[ui->style])) {
			set_style(ui);
		}
		if(GuiButton((Rectangle){925, 700, 200, 50}, "OK")) {
			ui->options = !ui->options;
		}
	}
	else if(ui->new_game){
		if(GuiButton((Rectangle){925, 150, 200, 50}, "SOLO")) {
			ui->start_game = true;
			ui->new_game = false;
			ui->game_type = 1;
		}
		if(GuiButton((Rectangle){925, 250, 200, 50}, "ENGINE")) {
			ui->start_game = true;
			ui->new_game = false;
			ui->game_type = 2;
		}
		if(GuiButton((Rectangle){925, 350, 200, 50}, "ONLINE")) {
			ui->start_game = true;
			ui->new_game = false;
			ui->game_type = 3;
		}
		if(GuiButton((Rectangle){925, 700, 200, 50}, "CANCEL")) {
			ui->new_game = false;
		}
	}
	else {
		if(GuiButton((Rectangle){925, 150, 200, 50}, "NEW GAME")) {
			ui->new_game = !ui->new_game;
		}
		if(GuiButton((Rectangle){925, 250, 200, 50}, "OPTIONS")) {
			ui->options = !ui->options;
		}
		if(!WEB) {
			if(GuiButton((Rectangle){925, 700, 200, 50}, "QUIT")) {
				ui->quit = true;
			}
		}
	}
}

void draw_end(Ui *ui, int mate) {
	if(mate)
		DrawRectangleRec(ui->end, END_SCREEN);
	switch (mate) {
		case 1:
			DrawText("STALEMATE DRAW", 255, 430, 40, WHITE);
			break;
		case 2:
			DrawText("CHECKMATE WHITE WON", 200, 430, 40, WHITE);
			break;
		case 3:
			DrawText("CHECKMATE BLACK WON", 200, 430, 40, WHITE);
			break;
	}
}

void draw(Ui *ui, Chess *chess) {
	bool side = (ui->rotation && chess->turn) || (!ui->rotation && ui->perspective);
	ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
	BeginDrawing();
	draw_board(ui, chess, side);
	draw_coordinate(ui, side);
	draw_menu(ui);
	draw_end(ui, chess->mate);
	EndDrawing();
}

void play_sound(Ui *ui, bool capture) {
	if(ui->sound) {
		if(capture)
			PlaySound(ui->capture_sound);
		else
			PlaySound(ui->move_sound);
	}
}

void mouse_input(Ui *ui, Chess *chess, Vector2 coordinate) {
	int x, y;
	bool side = (ui->rotation && chess->turn) || (!ui->rotation && ui->perspective);

	x = (coordinate.y - 50) / 100;
	y = (coordinate.x - 50) / 100;
	if(x >= 0 && x < 8 && y >= 0 && y < 8) {
		if(!side) {
			x = 7 - x;
			y = 7 - y;
		}
	}
	else {
		x = -1;
		y = -1;
	}

	if(x != -1 && y != -1) {
		play(chess, x, y);
		if(chess->moved) {
			play_sound(ui, chess->capture);
		}
	}
}

void render(Chess* chess) {
	InitWindow(1200, 900, "ZaklopaChess");
	SetTargetFPS(60);
	InitAudioDevice();

	Ui *ui = (Ui*)calloc(1, sizeof(Ui));
	set_ui(ui);

	while (!WindowShouldClose() && !ui->quit) {
		if(ui->start_game){
			new_game(chess);
			if(ui->game_type == 2 || ui->game_type == 3) {
				ui->rotation = false;
			}
			ui->start_game = false;
		}
		// bice jednog dana
		/*if(!chess->turn && ui->game_type == 2) { 
			calculate(chess);
		}*/
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			mouse_input(ui, chess, GetMousePosition());
		}
		else if(IsGestureDetected(GESTURE_TAP)) {
			mouse_input(ui, chess, GetTouchPosition(0));
		}
		draw(ui, chess);
	}
	close_ui(ui);
	CloseAudioDevice();
	CloseWindow();
}
