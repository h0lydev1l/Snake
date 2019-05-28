#include "GameView.h"

#include "SnakeBoard.h"

#include <iostream>

GameView::GameView(SnakeBoard &Snake, int x0, int y0, int lenght):board(Snake)
{
    board_width=board.getBoardWidth();
    board_height=board.getBoardHeight();
    field_lenght=lenght;
    GameView::x0=x0;
    GameView::y0=y0;
}

void GameView::play(sf::RenderWindow &window)
{
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed)
                {

                if (event.key.code == sf::Keyboard::W)
                    {
                        board.changeDirection(UP);
                    }
                if (event.key.code == sf::Keyboard::A)
                    {
                        board.changeDirection(LEFT);
                    }
                if (event.key.code == sf::Keyboard::S)
                    {
                        board.changeDirection(DOWN);
                    }
                if (event.key.code == sf::Keyboard::D)
                    {
                        board.changeDirection(RIGHT);
                    }
                if (event.key.code == sf::Keyboard::PageUp)
                    {
                        if(speeder>1)
                            {
                                speeder--;
                            }
                    }
                if (event.key.code == sf::Keyboard::PageDown)
                    {
                        if(speeder<5)
                            {
                             speeder++;
                            }
                    }
                }
            if (event.type == sf::Event::MouseButtonPressed)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        if (event.mouseButton.x >= 684 and event.mouseButton.x <= 968 and event.mouseButton.y >= 184 and event.mouseButton.y <= 282)
                        {
                            if(board.state==STOPPED)
                                {
                                    board.state=RUNNING;
                                }
                        }
                        if (event.mouseButton.x >= 684 and event.mouseButton.x <= 968 and event.mouseButton.y >= 306 and event.mouseButton.y <= 404)
                        {
                            event.type = sf::Event::Closed;
                        }
                        if (event.mouseButton.x >= 684 and event.mouseButton.x <= 968 and event.mouseButton.y >= 425 and event.mouseButton.y <= 523)
                        {
                            board.state=STOPPED;
                            board.snakePosition.clear();
                            board.setBoard();
                            board.addSnake();
                            board.updateBoard();
                            board.appleChecker=0;
                            board.kierunek=LEFT;
                            speeder=5;
                            moveTimer=0;
                            appleTimer=0;
                        }
                    }
                }
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        drawBackground(window);
        drawBoard(window);
        drawText(window, 710, 560);
        if(board.state==FINISHED_LOSS)
            drawLose(window);
        if(board.state==FINISHED_WIN)
            drawWin(window);
        window.display();

        sf::Clock Clock;
        sf::Time elapsed;
        double time;
        int mainTimer=0;
        while(mainTimer==0)
            {
                elapsed=Clock.getElapsedTime();
                time=elapsed.asSeconds();
                time=time/1;
                if(time>0.1)
                    {
                        mainTimer++;
                        moveTimer++;
                        if(board.appleChecker==0)
                            appleTimer++;
                    }
                    if(moveTimer>=speeder)
                    {
                        board.moveSnake();
                        moveTimer=0;
                    }
                    if(appleTimer>=20)
                    {
                        board.generateApple();
                        mainTimer=0;
                        appleTimer=0;
                    }
            }

    }

}


void GameView::drawBoard(sf::RenderWindow &window)
{
    for (int idx_y = 0; idx_y<board_height; idx_y++)
    {
        for (int idx_x = 0; idx_x<board_width; idx_x++)
        {
            if(board.isSnake(idx_x,idx_y)==true)
            {
                drawSnake(window, idx_x,idx_y);
            }
            if(board.snakePosition[0].x==idx_x and board.snakePosition[0].y==idx_y)
            {
                drawHead(window, idx_x, idx_y);
            }
            if(board.board[idx_y][idx_x].isApple==true)
            {
                drawApple(window, idx_x,idx_y);
            }
            if(board.board[idx_y][idx_x].isApple==0 and board.board[idx_y][idx_x].isSnake==0)
            {
                drawEmpty(window,idx_x,idx_y);
            }
        }
    }
}

void GameView::drawHead(sf::RenderWindow &window, int idx_x, int idx_y)
{
    pole2.setPointCount(4);
    pole2.setPoint(0, sf::Vector2f(x0+idx_x*field_lenght,y0+idx_y*field_lenght));
    pole2.setPoint(1, sf::Vector2f(x0+field_lenght+idx_x*field_lenght-1,y0+idx_y*field_lenght));
    pole2.setPoint(2, sf::Vector2f(x0+field_lenght+idx_x*field_lenght-1,y0+field_lenght+idx_y*field_lenght-1));
    pole2.setPoint(3, sf::Vector2f(x0+idx_x*field_lenght,y0+field_lenght+idx_y*field_lenght-1));
    pole2.setTexture(&head);
    if(board.kierunek==UP or board.kierunek==DOWN)
        pole2.setTexture(&head2);
        else
            pole2.setTexture(&head);
    window.draw(pole2);
}

void GameView::drawSnake(sf::RenderWindow &window, int idx_x, int idx_y)
{
    pole.setPointCount(4);
    pole.setPoint(0, sf::Vector2f(x0+idx_x*field_lenght,y0+idx_y*field_lenght));
    pole.setPoint(1, sf::Vector2f(x0+field_lenght+idx_x*field_lenght-1,y0+idx_y*field_lenght));
    pole.setPoint(2, sf::Vector2f(x0+field_lenght+idx_x*field_lenght-1,y0+field_lenght+idx_y*field_lenght-1));
    pole.setPoint(3, sf::Vector2f(x0+idx_x*field_lenght,y0+field_lenght+idx_y*field_lenght-1));
    pole.setTexture(&snake);
    window.draw(pole);
}

void GameView::drawEmpty(sf::RenderWindow &window, int idx_x, int idx_y)
{
    pole.setPointCount(4);
    pole.setPoint(0, sf::Vector2f(x0+idx_x*field_lenght,y0+idx_y*field_lenght));
    pole.setPoint(1, sf::Vector2f(x0+field_lenght+idx_x*field_lenght-1,y0+idx_y*field_lenght));
    pole.setPoint(2, sf::Vector2f(x0+field_lenght+idx_x*field_lenght-1,y0+field_lenght+idx_y*field_lenght-1));
    pole.setPoint(3, sf::Vector2f(x0+idx_x*field_lenght,y0+field_lenght+idx_y*field_lenght-1));
    pole.setTexture(&empty);
    window.draw(pole);
}

void GameView::drawApple(sf::RenderWindow &window, int idx_x, int idx_y)
{
    pole.setPointCount(4);
    pole.setPoint(0, sf::Vector2f(x0+idx_x*field_lenght,y0+idx_y*field_lenght));
    pole.setPoint(1, sf::Vector2f(x0+field_lenght+idx_x*field_lenght-1,y0+idx_y*field_lenght));
    pole.setPoint(2, sf::Vector2f(x0+field_lenght+idx_x*field_lenght-1,y0+field_lenght+idx_y*field_lenght-1));
    pole.setPoint(3, sf::Vector2f(x0+idx_x*field_lenght,y0+field_lenght+idx_y*field_lenght-1));
    pole.setTexture(&apple);
    window.draw(pole);
}

void GameView::drawBackground(sf::RenderWindow &window)
{
    bg.setPointCount(4);
    bg.setPoint(0, sf::Vector2f(0,0));
    bg.setPoint(1, sf::Vector2f(1000,0));
    bg.setPoint(2, sf::Vector2f(1000,700));
    bg.setPoint(3, sf::Vector2f(0, 700));
    bg.setTexture(&backgrnd);
    window.draw(bg);
}

void GameView::drawText(sf::RenderWindow &window, int x, int y)
{
    int spd=6-speeder;
    speed.setString("SPEED: "+std::to_string(spd));
    speed.setFont(font);
    speed.setCharacterSize(60);
    speed.setFillColor(sf::Color::White);
    speed.setPosition(x,y);
    window.draw(speed);
}

void GameView::drawLose(sf::RenderWindow &window)
{
    pole1.setPointCount(4);
    pole1.setPoint(0, sf::Vector2f(100,185));
    pole1.setPoint(1, sf::Vector2f(600,185));
    pole1.setPoint(2, sf::Vector2f(600,485));
    pole1.setPoint(3, sf::Vector2f(100,485));
    pole1.setTexture(&lose);
    window.draw(pole1);
}

void GameView::drawWin(sf::RenderWindow &window)
{
    pole1.setPointCount(4);
    pole1.setPoint(0, sf::Vector2f(100,185));
    pole1.setPoint(1, sf::Vector2f(600,185));
    pole1.setPoint(2, sf::Vector2f(600,485));
    pole1.setPoint(3, sf::Vector2f(100,485));
    pole1.setTexture(&win);
    window.draw(pole1);
}

void GameView::loadTextures()
{
    font.loadFromFile("image/Madonnina.otf");
    backgrnd.loadFromFile("image/background.png");
    apple.loadFromFile("image/apple.png");
    empty.loadFromFile("image/empty.png");
    snake.loadFromFile("image/snake.png");
    win.loadFromFile("image/wingame.png");
    lose.loadFromFile("image/endgame.png");
    head.loadFromFile("image/head.png");
    head2.loadFromFile("image/head2.png");
}
