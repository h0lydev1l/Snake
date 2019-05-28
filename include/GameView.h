#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include "SnakeBoard.h"
#include "SFML/Graphics.hpp"

class GameView
{
    public:
        GameView(SnakeBoard &Snake, int x0, int y0, int lenght);
        void drawBoard(sf::RenderWindow &window);
        void play(sf::RenderWindow &window);
        void loadTextures();

    private:
        SnakeBoard board;
        int board_width;
        int board_height;
        int field_lenght;
        int x0;
        int y0;
        int speeder=5;
        int moveTimer=0;
        int appleTimer=0;
        void drawHead(sf::RenderWindow &window, int x, int y);
        void drawSnake(sf::RenderWindow &window, int x, int y);
        void drawEmpty(sf::RenderWindow &window, int x, int y);
        void drawApple(sf::RenderWindow &window, int x, int y);
        void drawBackground(sf::RenderWindow &window);
        void drawText(sf::RenderWindow &window, int x, int y);
        void drawWin(sf::RenderWindow &window);
        void drawLose(sf::RenderWindow &window);
        sf::ConvexShape pole;
        sf::ConvexShape bg;
        sf::ConvexShape pole1;
        sf::ConvexShape pole2;
        sf::Texture backgrnd;
        sf::Texture apple;
        sf::Texture empty;
        sf::Texture snake;
        sf::Texture head;
        sf::Texture head2;
        sf::Text speed;
        sf::Texture win;
        sf::Texture lose;
        sf::Font font;





};

#endif // GAMEVIEW_H
