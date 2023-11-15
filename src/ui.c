#include "ui.h"

void set_ui(Ui *ui) {
    ui -> w_king = LoadTexture("assets/textures/white_king.png");
    ui -> w_queen = LoadTexture("assets/textures/white_queen.png");
    ui -> w_rook = LoadTexture("assets/textures/white_rook.png");
    ui -> w_bishop = LoadTexture("assets/textures/white_bishop.png");
    ui -> w_knight = LoadTexture("assets/textures/white_knight.png");
    ui -> w_pawn = LoadTexture("assets/textures/white_pawn.png");

    ui -> b_king = LoadTexture("assets/textures/black_king.png");
    ui -> b_queen = LoadTexture("assets/textures/black_queen.png");
    ui -> b_rook = LoadTexture("assets/textures/black_rook.png");
    ui -> b_bishop = LoadTexture("assets/textures/black_bishop.png");
    ui -> b_knight = LoadTexture("assets/textures/black_knight.png");
    ui -> b_pawn = LoadTexture("assets/textures/black_pawn.png");

    ui -> move_sound = LoadSound("assets/sounds/move.wav");
    ui -> capture_sound = LoadSound("assets/sounds/capture.wav");

    ui -> button1.x = 925;
    ui -> button1.y = 150;
    ui -> button1.width = 200;
    ui -> button1.height = 50;

    ui -> button2.x = 925;
    ui -> button2.y = 250;
    ui -> button2.width = 200;
    ui -> button2.height = 50;

    ui -> button3.x = 925;
    ui -> button3.y = 350;
    ui -> button3.width = 200;
    ui -> button3.height = 50;

    ui -> button4.x = 925;
    ui -> button4.y = 450;
    ui -> button4.width = 200;
    ui -> button4.height = 50;

    ui -> button5.x = 925;
    ui -> button5.y = 700;
    ui -> button5.width = 200;
    ui -> button5.height = 50;

    ui -> end.x = 50;
    ui -> end.y = 50;
    ui -> end.width = 800;
    ui -> end.height = 800;

    ui -> options = false;
    ui -> rotation = true;
    ui -> perspective = true;
    ui -> sound = true;
    ui -> coordinate = true;
    ui -> newgame = false;
}

void draw_coordinate(Ui *ui, bool side) {
    if(ui -> coordinate) {
        int j;
        for(int i = 1; i < 9; i++) {
            if(side) j = 9 - i;
            else j = i;
            DrawText(TextFormat("%c", 48 + j), 20, 100 * i - 5, 20, TEXT_COLOR);
            DrawText(TextFormat("%c", 73 - j), 100 * i - 5, 860, 20, TEXT_COLOR);
        }
    }
}

void draw_board(Ui *ui, char position[8][8], int possible[8][8], int x, int y, bool side) {
    int m, n;
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
            switch (position[i][j]) {
                case 'K':
                    DrawTexture(ui -> w_king, m * 100 + 50, n * 100 + 50, WHITE);
                    break;
                case 'Q':
                    DrawTexture(ui -> w_queen, m * 100 + 50, n * 100 + 50, WHITE);
                    break;
                case 'R':
                    DrawTexture(ui -> w_rook, m * 100 + 50, n * 100 + 50, WHITE);
                    break;
                case 'B':
                    DrawTexture(ui -> w_bishop, m * 100 + 50, n * 100 + 50, WHITE);
                    break;
                case 'N':
                    DrawTexture(ui -> w_knight, m * 100 + 50, n * 100 + 50, WHITE);
                    break;
                case 'P':
                    DrawTexture(ui -> w_pawn, m * 100 + 50, n * 100 + 50, WHITE);
                    break;
                case 'k':
                    DrawTexture(ui -> b_king, m * 100 + 50, n * 100 + 50, WHITE);
                    break;
                case 'q':
                    DrawTexture(ui -> b_queen, m * 100 + 50, n * 100 + 50, WHITE);
                    break;
                case 'r':
                    DrawTexture(ui -> b_rook, m * 100 + 50, n * 100 + 50, WHITE);
                    break;
                case 'b':
                    DrawTexture(ui -> b_bishop, m * 100 + 50, n * 100 + 50, WHITE);
                    break;
                case 'n':
                    DrawTexture(ui -> b_knight, m * 100 + 50, n * 100 + 50, WHITE);
                    break;
                case 'p':
                    DrawTexture(ui -> b_pawn, m * 100 + 50, n * 100 + 50, WHITE);
                    break;
            }
            if(possible[i][j])
                DrawCircle(100 * (m + 1), 100 * (n + 1), 25, P_SQUARE); 
        }
    }
}

void draw_menu(Ui *ui) {
    if(ui -> options) {
        DrawText("ROTATION", 925, 130, 20, TEXT_COLOR);
        DrawRectangleRec(ui -> button1, BUTTON);
        DrawText(ui -> rotation ? "ON" : "OFF", 1010, 165, 20, TEXT_COLOR);

        DrawText("PERSPECTIVE", 925, 230, 20, TEXT_COLOR);
        if(ui -> rotation)
            DrawRectangleRec(ui -> button2, BUTTON_D);
        else
            DrawRectangleRec(ui -> button2, BUTTON);
        DrawText(ui -> perspective ? "WHITE" : "BLACK", 990, 265, 20, TEXT_COLOR);

        DrawText("COORDINATE", 925, 330, 20, TEXT_COLOR);
        DrawRectangleRec(ui -> button3, BUTTON);
        DrawText(ui -> coordinate ? "ON" : "OFF", 1010, 365, 20, TEXT_COLOR);

        DrawText("SOUND", 925, 430, 20, TEXT_COLOR);
        DrawRectangleRec(ui -> button4, BUTTON);
        DrawText(ui -> sound ? "ON" : "OFF", 1010, 465, 20, TEXT_COLOR);

        DrawRectangleRec(ui -> button5, BUTTON);
        DrawText("OK", 1010, 715, 20, TEXT_COLOR);
    }
    else {
        DrawRectangleRec(ui -> button1, BUTTON);
        DrawText("NEW GAME", 970, 165, 20, TEXT_COLOR);

        DrawRectangleRec(ui -> button2, BUTTON);
        DrawText("OPTIONS", 980, 265, 20, TEXT_COLOR);
        if(!WEB) {
            DrawRectangleRec(ui -> button3, BUTTON);
            DrawText("QUIT", 1000, 365, 20, TEXT_COLOR);
        }
    }
}

void draw_end(Ui *ui, int mate) {
    if(mate)
        DrawRectangleRec(ui -> end, END_SCREEN);
    switch (mate) {
        case 1:
            DrawText("STALEMATE DRAW", 255, 430, 40, TEXT_COLOR);
            break;
        case 2:
            DrawText("CHECKMATE WHITE WON", 200, 430, 40, TEXT_COLOR);
            break;
        case 3:
            DrawText("CHECKMATE BLACK WON", 200, 430, 40, TEXT_COLOR);
            break;
    }
}

void draw(Ui *ui, char position[8][8], int possible[8][8], int x, int y, bool turn, int mate) {
    bool side = (ui -> rotation && turn) || (!ui -> rotation && ui -> perspective);
    ClearBackground(BACKGROUND);
    BeginDrawing();
    draw_board(ui, position, possible, x, y, side);
    draw_coordinate(ui, side);
    draw_menu(ui);
    draw_end(ui, mate);
    EndDrawing();
}

void input(Ui *ui, int *x, int *y, bool turn) {
    bool side = (ui -> rotation && turn) || (!ui -> rotation && ui -> perspective);
    Vector2 mouse = GetMousePosition();
    if(ui -> options) {
        if(CheckCollisionPointRec(mouse, ui -> button1))
            ui -> rotation = !ui -> rotation;
        if(CheckCollisionPointRec(mouse, ui -> button2))
            ui -> perspective = !ui -> perspective;
        if(CheckCollisionPointRec(mouse, ui -> button3))
            ui -> coordinate = !ui -> coordinate;
        if(CheckCollisionPointRec(mouse, ui -> button4))
            ui -> sound = !ui -> sound;
        if(CheckCollisionPointRec(mouse, ui -> button5))
            ui -> options = false;
    }
    else {
        if(CheckCollisionPointRec(mouse, ui -> button1))
            ui -> newgame = true;
        if(CheckCollisionPointRec(mouse, ui -> button2))
            ui -> options = true;
        if(!WEB && CheckCollisionPointRec(mouse, ui -> button3)) {
            close_ui(ui);
            exit(0);
        }
    }
    *x = (mouse.y - 50) / 100;
    *y = (mouse.x - 50) / 100;
    if(*x >= 0 && *x < 8 && *y >= 0 && *y < 8) {
        if(!side) {
            *x = 7 - *x;
            *y = 7 - *y;
        }
    }
    else {
        *x = -1;
        *y = -1;
    }
}

void play_sound(Ui *ui, bool capture) {
    if(ui -> sound) {
        if(capture)
            PlaySound(ui -> capture_sound);
        else
            PlaySound(ui -> move_sound);
    }
}

void close_ui(Ui *ui) {
    UnloadTexture(ui -> w_king);
    UnloadTexture(ui -> w_queen);
    UnloadTexture(ui -> w_rook);
    UnloadTexture(ui -> w_bishop);
    UnloadTexture(ui -> w_knight);
    UnloadTexture(ui -> w_pawn);
    UnloadTexture(ui -> b_king);
    UnloadTexture(ui -> b_queen);
    UnloadTexture(ui -> b_rook);
    UnloadTexture(ui -> b_bishop);
    UnloadTexture(ui -> b_knight);
    UnloadTexture(ui -> b_pawn);

    UnloadSound(ui -> move_sound);
    UnloadSound(ui -> capture_sound);
}
