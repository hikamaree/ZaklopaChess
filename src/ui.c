#include "ui.h"
#include "chess.h"
#include "client.h"
#include "server.h"
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
	ui->online_menu = false;
	ui->enter_ip = false;
	ui->start_game = false;
	ui->game_type = 0;
	ui->style = 4;
	ui->quit = false;

	GuiLoadStyleCyber();
	GuiSetStyle(DEFAULT, TEXT_SIZE, 20);

	ui->client_data = (ClientData*)malloc(sizeof(ClientData));
	memcpy (ui->client_data->ip_address, "127.0.0.1", 10 * sizeof(char));
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
	free(ui->client_data);
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
			switch (chess->board[i][j]) {
				case WHITE_KING:
					DrawTexture(ui->w_king, m * 100 + 50, n * 100 + 50, WHITE);
					break;
				case WHITE_QUEEN:
					DrawTexture(ui->w_queen, m * 100 + 50, n * 100 + 50, WHITE);
					break;
				case WHITE_ROOK:
					DrawTexture(ui->w_rook, m * 100 + 50, n * 100 + 50, WHITE);
					break;
				case WHITE_BISHOP:
					DrawTexture(ui->w_bishop, m * 100 + 50, n * 100 + 50, WHITE);
					break;
				case WHITE_KNIGHT:
					DrawTexture(ui->w_knight, m * 100 + 50, n * 100 + 50, WHITE);
					break;
				case WHITE_PAWN:
					DrawTexture(ui->w_pawn, m * 100 + 50, n * 100 + 50, WHITE);
					break;
				case BLACK_KING:
					DrawTexture(ui->b_king, m * 100 + 50, n * 100 + 50, WHITE);
					break;
				case BLACK_QUEEN:
					DrawTexture(ui->b_queen, m * 100 + 50, n * 100 + 50, WHITE);
					break;
				case BLACK_ROOK:
					DrawTexture(ui->b_rook, m * 100 + 50, n * 100 + 50, WHITE);
					break;
				case BLACK_BISHOP:
					DrawTexture(ui->b_bishop, m * 100 + 50, n * 100 + 50, WHITE);
					break;
				case BLACK_KNIGHT:
					DrawTexture(ui->b_knight, m * 100 + 50, n * 100 + 50, WHITE);
					break;
				case BLACK_PAWN:
					DrawTexture(ui->b_pawn, m * 100 + 50, n * 100 + 50, WHITE);
					break;
				case EMPTY:
					break;
			}
			if(chess->moves[i][j])
				DrawCircle(100 * (m + 1), 100 * (n + 1), 25, P_SQUARE); 
		}
	}
}

void resign(Ui *ui, Chess* chess) {
	if(ui->game_type != 0) {
		if(GuiButton((Rectangle){925, 350, 200, 50}, "RESIGN")) {
			if(chess->turn && ui->game_type != 0) {
				chess->mate = 3;
			}
			else if(ui->game_type != 0) {
				chess->mate = 2;
			}
			ui->game_type = 0;
		}
		//drugi igrac treba da skonta da je ovaj predao
		/*if(ui->game_type == 3) {
			disconnect(*(ui->client_data));
		}*/
	}
}

void draw_menu(Ui *ui, Chess* chess) {
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
	else if(ui->online_menu) {
		if(GuiButton((Rectangle){925, 150, 200, 50}, "HOST GAME")) {
			ui->start_game = true;
			ui->new_game = false;
			ui->online_menu = false;
			ui->rotation = false;
			ui->game_type = 3;
			//ovde treba da se nekako startuje server
			enable_server();
			memcpy (ui->client_data->ip_address, "127.0.0.1", 10 * sizeof(char));
			connect_to_server(ui->client_data);
			ui->perspective = ui->client_data->color;
		}
		if (GuiTextBox((Rectangle){925, 250, 200, 50}, ui->client_data->ip_address, 32, ui->enter_ip)) {
			ui->enter_ip = !ui->enter_ip;
		}
		if(GuiButton((Rectangle){925, 350, 200, 50}, "CONNECT")) {
			ui->start_game = true;
			ui->new_game = false;
			ui->online_menu = false;
			ui->rotation = false;
			ui->game_type = 3;
			connect_to_server(ui->client_data);
			ui->perspective = ui->client_data->color;
		}
		if(GuiButton((Rectangle){925, 700, 200, 50}, "CANCEL")) {
			ui->online_menu = false;
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
			ui->rotation = false;
			ui->game_type = 2;
		}
		if(GuiButton((Rectangle){925, 350, 200, 50}, "ONLINE")) {
			ui->online_menu = !ui->online_menu;
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
		resign(ui, chess);
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
			DrawText("DRAW", 400, 430, 40, WHITE);
			break;
		case 2:
			DrawText("WHITE WON", 330, 430, 40, WHITE);
			break;
		case 3:
			DrawText("BLACK WON", 330, 430, 40, WHITE);
			break;
	}
}

void draw(Ui *ui, Chess *chess) {
	bool side = (ui->rotation && chess->turn) || (!ui->rotation && ui->perspective);
	ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
	BeginDrawing();
	draw_board(ui, chess, side);
	draw_coordinate(ui, side);
	draw_menu(ui, chess);
	draw_end(ui, chess->mate);
	EndDrawing();
}

void play_sound(Ui *ui, bool capture) {
	if(ui->sound) {
		if(capture) {
			PlaySound(ui->capture_sound);
		}
		else {
			PlaySound(ui->move_sound);
		}
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

void handle_solo_game(Ui* ui, Chess* chess) {
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		mouse_input(ui, chess, GetMousePosition());
	}
}

void handle_engine_game(Ui* ui, Chess* chess) {
	// bice jednog dana
	/*if(!chess->turn && ui->game_type == 2) { 
	  calculate(chess);
	  }*/
	return;
}

void handle_online_game(Ui* ui, Chess* chess) {
	if(chess->moved) {
		send_move(*ui->client_data, chess->move);
	}
	if(chess->turn == ui->client_data->color) {
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			mouse_input(ui, chess, GetMousePosition());
		}
	}
}

void handle_game(Ui* ui, Chess* chess) {
	if(ui->start_game){
		new_game(chess);
		ui->start_game = false;
	}
	switch(ui->game_type) {
		case 1:
			handle_solo_game(ui, chess);
			break;
		case 2:
			handle_engine_game(ui, chess);
			break;
		case 3:
			handle_online_game(ui, chess);
			break;
		default:
			break;
	}
}

void render(Chess* chess) {
	SetTraceLogLevel(LOG_ERROR);
	InitWindow(1200, 900, "ZaklopaChess");
	SetTargetFPS(60);
	InitAudioDevice();

	Ui *ui = (Ui*)calloc(1, sizeof(Ui));
	set_ui(ui);
	ui->client_data->chess = chess;

	while(!ui->quit) {
		handle_game(ui, chess);
		draw(ui, chess);
	}
	close_ui(ui);
	CloseAudioDevice();
	CloseWindow();
}
