#ifndef UI_HPP
#define UI_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

using namespace sf;

class Ui {
    private:
    Color background_color;
    Color text_color;
    Color button_color;
    Color inactive_button_color;
    Color black_square_color;
    Color white_square_color;
    Color selected_square_color;
    Color possible_square_color;

    Font font;
    Text text;

    Text text_pause;
    RectangleShape button_pause;

    Text text_newgame;
    Text text_options;
    Text text_quit;
    Text text_resume;
    RectangleShape button_newgame;
    RectangleShape button_options;
    RectangleShape button_quit;
    RectangleShape button_resume;

    Text label_rotation;
    Text label_sound;
    Text label_perspective;
    Text label_coordinate;
    Text text_rotation;
    Text text_sound;
    Text text_perspective;
    Text text_coordinate;
    Text text_ok;
    RectangleShape button_rotation;
    RectangleShape button_sound;
    RectangleShape button_perspective;
    RectangleShape button_coordinate;
    RectangleShape button_ok;

    Text winner;
    RectangleShape pause;

    bool sound;
    bool rotation;
    bool perspective;
    bool coordinate;
    bool newgame;
    bool options_menu;
    bool side;

    Texture white_pawn;
    Texture black_pawn;
    Texture white_knight;
    Texture black_knight;
    Texture white_bishop;
    Texture black_bishop;
    Texture white_rook;
    Texture black_rook;
    Texture white_queen;
    Texture black_queen;
    Texture white_king;
    Texture black_king;
    Sprite piece;

    CircleShape possible_square;
    RectangleShape selected_square;
    RectangleShape white_square;
    RectangleShape black_square;

    SoundBuffer move;
    SoundBuffer capture;
    Sound sound_effect;

    void draw_coordinate(RenderTarget& window, bool side);
    void draw_board(RenderTarget& window, char position[8][8], int possible[8][8], int x, int y);
    void menu(RenderTarget& window);
    bool clicked(RectangleShape button, int mouse_x, int mouse_y);

    void update_rotation();
    void update_sound();
    void update_perspective();
    void update_coordinate();

    public:
    bool paused;
    bool playing;
    Ui();
    void draw(RenderTarget& window, char position[8][8], int possible[8][8], int x, int y, bool turn);
    void input(int mouse_x, int mouse_y, int *x, int *y, bool turn);
    void play_sound(bool capture);
    bool start_game();
    void end_game(int mate);
};

#endif
