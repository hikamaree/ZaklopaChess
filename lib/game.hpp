#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "../lib/board.hpp"
#include "../lib/king.hpp"
#include "../lib/queen.hpp"
#include "../lib/rook.hpp"
#include "../lib/bishop.hpp"
#include "../lib/knight.hpp"
#include "../lib/pawn.hpp"

struct Game {
    char position[8][8];
    int possible[8][8];

    Board board;
    King king;
    Queen queen;
    Rook rook;
    Bishop bishop;
    Knight knight;
    Pawn pawn;

    bool turn;
    int enpassant;
    int selected_x;
    int selected_y;
    sf::CircleShape circle;
    sf::RectangleShape square;

    void reset_game();
    void reset_possible();
    void update_enpassant(int x, int y);
    void promotion(int x, int y);

    void draw_possible(sf::RenderTarget& window, int x, int y);
    void draw_selected(sf::RenderTarget& window, int x, int y);

    void calc_moves();
    void calc_pawn();
    void calc_knight();
    void calc_bishop();
    void calc_rook();
    void calc_queen();
    void calc_king();

    public:
    Game();
    void move(int x, int y);
    void draw(sf::RenderTarget& window);
};
