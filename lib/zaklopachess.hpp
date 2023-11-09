#ifndef ZAKLOPACHESS_HPP
#define ZAKLOPACHESS_HPP

#include <SFML/Graphics.hpp>
#include "game.hpp"
#include "ui.hpp"

class ZaklopaChess {
private:
    Game game;
    Ui ui;

    void input(int x, int y);
    void paly_online();
public:
    void play();
};

#endif
