//
// Created by Adrian on 27.05.2019.
//

#ifndef SNAKE_BACKEND_SNAKEBOARD_H
#define SNAKE_BACKEND_SNAKEBOARD_H

#include <string>
#include <iostream>
#include <deque>
struct Field
{
    bool isSnake;
    bool isApple;
};

struct Position
{
    int x;
    int y;
};

enum direction {UP, DOWN, LEFT, RIGHT};
enum GameState {RUNNING, FINISHED_WIN, FINISHED_LOSS,STOPPED};
enum GameDifficulty {NORMAL, HARD};



class SnakeBoard
{
public:
    SnakeBoard(int width, int height);
    int getBoardWidth();
    int getBoardHeight();
    bool isSnake(int x, int y);
    Field board[100][100];
    std::deque<Position>snakePosition;
    void changeDirection(direction new_direction);
    void moveSnake();
    void debug_display();
    int appleChecker=0;
    int emptyFields=900;
//private:
    int boardWidth;
    int boardHeight;
    GameState state=STOPPED;
    GameDifficulty difficulty=NORMAL;
    direction kierunek=LEFT;
    void setBoard();
    void updateBoard();
    bool isWall();
    bool canMove(int x, int y);
    bool isHitted(int x, int y);
    bool isCollected(int x, int y);
    void addSnake();
    void generateApple();
};

#endif //SNAKE_BACKEND_SNAKEBOARD_H
