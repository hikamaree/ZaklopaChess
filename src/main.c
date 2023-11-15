#include "chess.h"
#include "ui.h"
void mouse_input(Ui *ui, Chess *chess) {
    int x, y;
    input(ui, &x, &y, chess -> turn);
    if(ui -> newgame){
        new_game(chess);
        ui -> newgame = false;
    }
    if(x != -1) {
        play(chess, x, y);
        if(chess -> moved) {
            play_sound(ui, chess -> capture);
        }
    }
}

int main() {
    InitWindow(1200, 900, "ZaklopaChess");
    SetTargetFPS(60);
    InitAudioDevice();

    Chess chess;
    new_game(&chess);

    Ui ui;
    set_ui(&ui);

    while (!WindowShouldClose()) {

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || GetTouchPointCount()) {
            mouse_input(&ui, &chess);
        }
        draw(&ui, chess.position, chess.possible, chess.x, chess.y, chess.turn, chess.mate);
    }

    close_ui(&ui);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
