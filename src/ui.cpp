#include "ui.hpp"

Ui::Ui() {
    if (!font.loadFromFile("assets/font/Exo2.ttf"))
        std::cout << "Failed to open Exo2.ttf" << std::endl;

    newgame = false;
    playing = false;
    paused = false;
    rotation = true;
    sound = true;
    perspective = true;
    coordinate = true;
    options_menu = false;

    background_color = Color(0x1A1B26FF);
    text_color = Color(0xC0CAF5FF);
    button_color = Color(0x292E42FF);
    inactive_button_color = Color(0x16161EFF);
    black_square_color = Color(0x6E6D6BFF);
    white_square_color = Color(0x908F8DFF);
    selected_square_color = Color(0x7590A1FF);
    possible_square_color = Color(0x00000040);

    text.setFont(font);
    text.setCharacterSize(20);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(text_color);

    // PAUSE
    button_pause.setSize(Vector2f(200.f, 50.f));
    button_pause.setFillColor(button_color);
    button_pause.setPosition(Vector2f(925.f, 750.f));
    text_pause.setFont(font);
    text_pause.setCharacterSize(20);
    text_pause.setStyle(sf::Text::Bold);
    text_pause.setFillColor(text_color);
    text_pause.setString("PAUSE");
    text_pause.setPosition(Vector2f(990.f, 762.f));

    // NEW GAME
    button_newgame.setSize(Vector2f(200.f, 50.f));
    button_newgame.setFillColor(button_color);
    button_newgame.setPosition(Vector2f(925.f, 150.f));
    text_newgame.setFont(font);
    text_newgame.setCharacterSize(20);
    text_newgame.setStyle(sf::Text::Bold);
    text_newgame.setFillColor(text_color);
    text_newgame.setString("NEW GAME");
    text_newgame.setPosition(Vector2f(970.f, 162.f));

    // OPTIONS
    button_options.setSize(Vector2f(200.f, 50.f));
    button_options.setFillColor(button_color);
    button_options.setPosition(Vector2f(925.f, 250.f));
    text_options.setFont(font);
    text_options.setCharacterSize(20);
    text_options.setStyle(sf::Text::Bold);
    text_options.setFillColor(text_color);
    text_options.setString("OPTIONS");
    text_options.setPosition(Vector2f(980.f, 262.f));

    // QUIT
    button_quit.setSize(Vector2f(200.f, 50.f));
    button_quit.setFillColor(button_color);
    button_quit.setPosition(Vector2f(925.f, 350.f));
    text_quit.setFont(font);
    text_quit.setCharacterSize(20);
    text_quit.setStyle(sf::Text::Bold);
    text_quit.setFillColor(text_color);
    text_quit.setString("QUIT");
    text_quit.setPosition(Vector2f(1000.f, 362.f));

    // RESUME
    button_resume.setSize(Vector2f(200.f, 50.f));
    button_resume.setFillColor(button_color);
    button_resume.setPosition(Vector2f(925.f, 750.f));
    text_resume.setFont(font);
    text_resume.setCharacterSize(20);
    text_resume.setStyle(Text::Bold);
    text_resume.setFillColor(text_color);
    text_resume.setString("RESUME");
    text_resume.setPosition(Vector2f(980.f, 762.f));

    // ROTATION
    button_rotation.setSize(Vector2f(200.f, 50.f));
    button_rotation.setFillColor(button_color);
    button_rotation.setPosition(Vector2f(925.f, 150.f));
    label_rotation.setFont(font);
    label_rotation.setCharacterSize(16);
    label_rotation.setStyle(sf::Text::Bold);
    label_rotation.setFillColor(text_color);
    label_rotation.setString("ROTATION");
    label_rotation.setPosition(Vector2f(925.f, 130.f));
    text_rotation.setFont(font);
    text_rotation.setCharacterSize(20);
    text_rotation.setStyle(Text::Bold);
    text_rotation.setString("ON");
    text_rotation.setFillColor(text_color);
    text_rotation.setPosition(Vector2f(1010.f, 162.f));

    // SOUND
    button_sound.setSize(Vector2f(200.f, 50.f));
    button_sound.setFillColor(button_color);
    button_sound.setPosition(Vector2f(925.f, 350.f));
    label_sound.setFont(font);
    label_sound.setCharacterSize(16);
    label_sound.setStyle(sf::Text::Bold);
    label_sound.setFillColor(text_color);
    label_sound.setString("SOUND");
    label_sound.setPosition(Vector2f(925.f, 330.f));
    text_sound.setFont(font);
    text_sound.setCharacterSize(20);
    text_sound.setStyle(Text::Bold);
    text_sound.setString("ON");
    text_sound.setFillColor(text_color);
    text_sound.setPosition(Vector2f(1010.f, 362.f));

    // PERSPECTIVE
    button_perspective.setSize(Vector2f(200.f, 50.f));
    button_perspective.setFillColor(inactive_button_color);
    button_perspective.setPosition(Vector2f(925.f, 250.f));
    label_perspective.setFont(font);
    label_perspective.setCharacterSize(16);
    label_perspective.setStyle(sf::Text::Bold);
    label_perspective.setFillColor(text_color);
    label_perspective.setString("PERSPECTIVE");
    label_perspective.setPosition(Vector2f(925.f, 230.f));
    text_perspective.setFont(font);
    text_perspective.setCharacterSize(20);
    text_perspective.setStyle(Text::Bold);
    text_perspective.setString("WHITE");
    text_perspective.setFillColor(text_color);
    text_perspective.setPosition(Vector2f(990.f, 262.f));

    // COORDINATE
    button_coordinate.setSize(Vector2f(200.f, 50.f));
    button_coordinate.setFillColor(button_color);
    button_coordinate.setPosition(Vector2f(925.f, 450.f));
    label_coordinate.setFont(font);
    label_coordinate.setCharacterSize(16);
    label_coordinate.setStyle(sf::Text::Bold);
    label_coordinate.setFillColor(text_color);
    label_coordinate.setString("COORDINATE");
    label_coordinate.setPosition(Vector2f(925.f, 430.f));
    text_coordinate.setFont(font);
    text_coordinate.setCharacterSize(20);
    text_coordinate.setStyle(Text::Bold);
    text_coordinate.setString("ON");
    text_coordinate.setFillColor(text_color);
    text_coordinate.setPosition(Vector2f(1010.f, 462.f));

    // OK
    button_ok.setSize(Vector2f(200.f, 50.f));
    button_ok.setFillColor(button_color);
    button_ok.setPosition(Vector2f(925.f, 750.f));
    text_ok.setFont(font);
    text_ok.setCharacterSize(20);
    text_ok.setStyle(Text::Bold);
    text_ok.setFillColor(text_color);
    text_ok.setString("OK");
    text_ok.setPosition(Vector2f(1010.f, 762.f));

    // WINNER
    winner.setFont(font);
    winner.setCharacterSize(40);
    winner.setStyle(sf::Text::Bold);
    winner.setFillColor(text_color);

    // DIM BOARD
    pause.setSize(Vector2f(800.f, 800.f));
    pause.setFillColor(Color(0x00404080));
    pause.setPosition(Vector2f(50.f, 50.f));

    // BOARD
    white_square.setSize(Vector2f(100.f, 100.f));
    white_square.setFillColor(white_square_color);
    black_square.setSize(Vector2f(100.f, 100.f));
    black_square.setFillColor(black_square_color);
    possible_square.setRadius(25.f);
    possible_square.setFillColor(possible_square_color);
    selected_square.setSize(Vector2f(100.0f, 100.0f));
    selected_square.setFillColor(selected_square_color);

    // PAWN
    if (!white_pawn.loadFromFile("assets/textures/white_pawn.png"))
        std::cout << "Failed to open white_pawn.png" << std::endl;
    if (!black_pawn.loadFromFile("assets/textures/black_pawn.png"))
        std::cout << "Failed to open black_pawn.png" << std::endl;

    // KNIGHT
    if (!white_knight.loadFromFile("assets/textures/white_knight.png"))
        std::cout << "Failed to open white_knight.png" << std::endl;
    if (!black_knight.loadFromFile("assets/textures/black_knight.png"))
        std::cout << "Failed to open black_knight.png" << std::endl;

    // BISHOP
    if (!white_bishop.loadFromFile("assets/textures/white_bishop.png"))
        std::cout << "Failed to open white_bishop.png" << std::endl;
    if (!black_bishop.loadFromFile("assets/textures/black_bishop.png"))
        std::cout << "Failed to open black_bishop.png" << std::endl;

    // ROOK
    if (!white_rook.loadFromFile("assets/textures/white_rook.png"))
        std::cout << "Failed to open white_rook.png" << std::endl;
    if (!black_rook.loadFromFile("assets/textures/black_rook.png"))
        std::cout << "Failed to open black_rook.png" << std::endl;

    // QUEEN
    if (!white_queen.loadFromFile("assets/textures/white_queen.png"))
        std::cout << "Failed to open white_queen.png" << std::endl;
    if (!black_queen.loadFromFile("assets/textures/black_queen.png"))
        std::cout << "Failed to open black_queen.png" << std::endl;

    // KING
    if (!white_king.loadFromFile("assets/textures/white_king.png"))
        std::cout << "Failed to open white_king.png" << std::endl;
    if (!black_king.loadFromFile("assets/textures/black_king.png"))
        std::cout << "Failed to open black_king.png" << std::endl;

    // SOUND
    if (!move.loadFromFile("assets/sounds/move.flac"))
        std::cout << "Failed to open move.flac" << std::endl;
    if (!capture.loadFromFile("assets/sounds/capture.flac"))
        std::cout << "Failed to open capture.flac" << std::endl;
}

void Ui::play_sound(bool c) {
    if(sound) {
        if (c)
            sound_effect.setBuffer(capture);
        else
            sound_effect.setBuffer(move);
        sound_effect.play();
    }
}

void Ui::draw_coordinate(RenderTarget& window, bool side) {
    int j;
    for(int i = 1; i < 9; i++) {
        if(side) j = 9 - i;
        else j = i;
        text.setString(std::to_string(j));
        text.setPosition(Vector2f(20.f, i * 100.f - 10.f));
        window.draw(text);
        std::string letter(1, 73 - j);
        text.setString(letter);
        text.setPosition(Vector2f(i * 100.f - 5.f, 860.f));
        window.draw(text);
    }
}

void Ui::draw_board(sf::RenderTarget& window, char position[8][8], int possible[8][8], int x, int y) {
    int m, n;
    if(!side) {
        x = 7 - x;
        y = 7 - y;
    }
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if(i == x && j == y) {
                selected_square.setPosition(Vector2f(100.f * j + 50.f, 100.f * i + 50.f));
                window.draw(selected_square);
            }
            else {
                if((i + j + 1) % 2) {
                    white_square.setPosition(Vector2f(100.f * j + 50.f, 100.f * i + 50.f));
                    window.draw(white_square);
                }
                else {
                    black_square.setPosition(Vector2f(100.f * j + 50.f, 100.f * i + 50.f));
                    window.draw(black_square);
                }
            }
        }
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
            switch (position[i][j]) {
                case 'K':
                    piece.setTexture(white_king);
                    break;
                case 'Q':
                    piece.setTexture(white_queen);
                    break;
                case 'R':
                    piece.setTexture(white_rook);
                    break;
                case 'B':
                    piece.setTexture(white_bishop);
                    break;
                case 'N':
                    piece.setTexture(white_knight);
                    break;
                case 'P':
                    piece.setTexture(white_pawn);
                    break;
                case 'k':
                    piece.setTexture(black_king);
                    break;
                case 'q':
                    piece.setTexture(black_queen);
                    break;
                case 'r':
                    piece.setTexture(black_rook);
                    break;
                case 'b':
                    piece.setTexture(black_bishop);
                    break;
                case 'n':
                    piece.setTexture(black_knight);
                    break;
                case 'p':
                    piece.setTexture(black_pawn);
                    break;
            }
            if(isalpha(position[i][j])) {
                piece.setPosition(Vector2f(m * 100.f + 50.f, n * 100.f + 50.f));
                window.draw(piece);
            }
            if(possible[i][j]) {
                possible_square.setPosition(Vector2f(100.f * m + 75.f, 100.f * n + 75.f));
                window.draw(possible_square);
            }
        }
    }
}

void Ui::menu(RenderTarget& window) {
    window.draw(pause);
    if(options_menu) {
        window.draw(label_rotation);
        window.draw(button_rotation);
        window.draw(text_rotation);

        window.draw(label_sound);
        window.draw(button_sound);
        window.draw(text_sound);

        window.draw(label_perspective);
        window.draw(button_perspective);
        window.draw(text_perspective);

        window.draw(label_coordinate);
        window.draw(button_coordinate);
        window.draw(text_coordinate);

        window.draw(button_ok);
        window.draw(text_ok);

        if(!playing) {
            window.draw(winner);
        }
    }
    else {
        window.draw(button_newgame);
        window.draw(text_newgame);

        window.draw(button_options);
        window.draw(text_options);

        window.draw(button_quit);
        window.draw(text_quit);

        if(paused) {
            window.draw(button_resume);
            window.draw(text_resume);
        }

        if(!playing) {
            window.draw(winner);
        }
    }
}

void Ui::draw(RenderTarget& window, char position[8][8], int possible[8][8], int x, int y, bool turn) {
    side = (turn && rotation) || (!rotation && perspective);
    window.clear(background_color);
    draw_board(window, position, possible, x, y);
    if(coordinate)
        draw_coordinate(window, side);
    if(!playing || paused) {
        menu(window);
    }
    else {
        window.draw(button_pause);
        window.draw(text_pause);
    }
}

void Ui::input(int mouse_x, int mouse_y, int *x, int *y, bool turn) {
    if(!playing || paused) {
        if(options_menu) {
            if(clicked(button_rotation, mouse_x, mouse_y))
                update_rotation();
            else if(clicked(button_sound, mouse_x, mouse_y))
                update_sound();
            else if(clicked(button_perspective, mouse_x, mouse_y))
                update_perspective();
            else if(clicked(button_coordinate, mouse_x, mouse_y))
                update_coordinate();
            else if(clicked(button_ok, mouse_x, mouse_y))
                options_menu = false;
        }
        else {
            if(clicked(button_newgame, mouse_x, mouse_y))
                newgame = true;
            else if(clicked(button_options, mouse_x, mouse_y))
                options_menu = true;
            else if(clicked(button_quit, mouse_x, mouse_y))
                exit(0);
            else if(clicked(button_resume, mouse_x, mouse_y))
                paused = false;
        }
    }
    else {
        if(clicked(button_pause, mouse_x, mouse_y))
            paused = true;
        int x1 = (mouse_y - 50) / 100;
        int y1 = (mouse_x - 50) / 100;
        if(x1 >= 0 && x1 < 8 && y1 >= 0 && y1 < 8) {
            if(side) {
                *x = x1;
                *y = y1;
            }
            if(!side) {
                *x = 7 - x1;
                *y = 7 - y1;
            }
        }
    }
}

bool Ui::clicked(RectangleShape button, int mouse_x, int mouse_y) {
    if(button.getPosition().x < mouse_x && mouse_x < button.getPosition().x + button.getSize().x &&
            button.getPosition().y < mouse_y && mouse_y < button.getPosition().y + button.getSize().y) {
        return true;
    }
    return false;
}

void Ui::update_rotation() {
    rotation = !rotation;
    if(rotation) {
        text_rotation.setString("ON");
        text_rotation.setPosition(Vector2f(1010.f, 162.f));
        button_perspective.setFillColor(inactive_button_color);
    }
    else {
        text_rotation.setString("OFF");
        text_rotation.setPosition(Vector2f(1005.f, 162.f));
        button_perspective.setFillColor(button_color);
    }

}

void Ui::update_sound() {
    sound = !sound;
    if(sound) {
        text_sound.setString("ON");
        text_sound.setPosition(Vector2f(1010.f, 362.f));
    }
    else {
        text_sound.setString("OFF");
        text_sound.setPosition(Vector2f(1005.f, 362.f));
    }
}

void Ui::update_perspective() {
    perspective = !perspective;
    if(perspective)
        text_perspective.setString("WHITE");
    else
        text_perspective.setString("BLACK");
}

void Ui::update_coordinate() {
    coordinate = !coordinate;
    if(coordinate) {
        text_coordinate.setString("ON");
        text_coordinate.setPosition(Vector2f(1010.f, 462.f));
    }
    else {
        text_coordinate.setString("OFF");
        text_coordinate.setPosition(Vector2f(1005.f, 462.f));
    }
}

bool Ui::start_game() {
    if(newgame) {
        playing = true;
        paused = false;
        newgame = false;
        return true;
    }
    return false;
}

void Ui::end_game(int mate) {
    if(mate) playing = false;
    switch (mate) {
        case 1:
            winner.setString("STALEMATE DRAW");
            winner.setPosition(Vector2f(275.f, 422.f));
            break;
        case 2:
            winner.setString("CHECKMATE WHITE WON");
            winner.setPosition(Vector2f(215.f, 422.f));
            break;
        case 3:
            winner.setString("CHECKMATE BLACK WON");
            winner.setPosition(Vector2f(215.f, 422.f));
            break;
    }
}
