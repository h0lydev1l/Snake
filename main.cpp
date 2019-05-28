#include <iostream>
#include <SFML/Graphics.hpp>
#include "SnakeBoard.h"
#include "GameView.h"

int main()
{
    srand( time( NULL ) );

    int x0=50;
    int y0=50;

    int fieldLenght=20;
    int windowWidth=1000;
    int windowHeight=700;


    SnakeBoard Snake(30,30);
    sf::RenderWindow window(sf::VideoMode(windowWidth,windowHeight), "Snake");
    GameView game(Snake,x0,y0,fieldLenght);
    game.loadTextures();
    game.play(window);
    return 0;
}
