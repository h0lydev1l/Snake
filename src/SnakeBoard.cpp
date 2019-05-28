//
// Created by Adrian on 27.05.2019.
//

#include "SnakeBoard.h"


SnakeBoard::SnakeBoard(int width, int height)
{
    boardWidth = width;
    boardHeight = height;
    setBoard();
    addSnake();
}

void SnakeBoard::setBoard()
{
    for (int idx_y = 0; idx_y < boardHeight; idx_y++) {
        for (int idx_x = 0; idx_x < boardWidth; idx_x++)
        {
            board[idx_y][idx_x]={false,false};
        }
    }
}

bool SnakeBoard::isWall()
{
    if(snakePosition[0].x<0 or snakePosition[0].x>=boardWidth or snakePosition[0].y<0 or snakePosition[0].y>=boardHeight)
        return true;
    else
        return false;
}

bool SnakeBoard::canMove(int x, int y)
{
    if(x==snakePosition[1].x and y==snakePosition[1].y)
        return false;
    if(x<0 or x>=boardWidth or y<0 or y>=boardHeight)
    {
        state=FINISHED_LOSS;
        return false;
    }
    else
        return true;
}

void SnakeBoard::addSnake()
{
    int y=boardWidth/2;
    int x=boardHeight/2;
    Position begin={x,y};
    snakePosition.push_back(begin);
    Position t1={16,15};
    snakePosition.push_back(t1);
    Position t2={17,15};
    snakePosition.push_back(t2);
    Position t3={18,15};
    snakePosition.push_back(t3);
    updateBoard();
}

bool SnakeBoard::isHitted(int x, int y)
{
    for(std::size_t i=1; i<snakePosition.size();i++)
    {
        if(x==snakePosition[i].x and y==snakePosition[i].y)
        {
                state=FINISHED_LOSS;
                return true;
        }
    }
    return false;
}

void SnakeBoard::moveSnake()
{
    if(state==STOPPED)
        return;
    if(state==FINISHED_LOSS)
        return;
    if(state==FINISHED_WIN)
        return;
    if(emptyFields==0)
        state=FINISHED_WIN;
    if(kierunek==UP)
    {
        Position new_pos=snakePosition[0];
        new_pos.y--;
        if(canMove(snakePosition[0].x,new_pos.y)==true and isHitted(snakePosition[0].x,new_pos.y)==false)
        {
            snakePosition.push_front(new_pos);
            if(isCollected(snakePosition[0].x,snakePosition[0].y)==false)
                snakePosition.pop_back();
        }
        else
            {
                kierunek=DOWN;
            }
    }
    if(kierunek==DOWN)
    {
        Position new_pos=snakePosition[0];
        new_pos.y++;
        if(canMove(snakePosition[0].x,new_pos.y)==true and isHitted(snakePosition[0].x,new_pos.y)==false)
        {
            snakePosition.push_front(new_pos);
            if(isCollected(snakePosition[0].x,snakePosition[0].y)==false)
                snakePosition.pop_back();
        }
        else
            {
                kierunek=UP;
            }
    }
    if(kierunek==LEFT)
    {
        Position new_pos=snakePosition[0];
        new_pos.x--;
        if(canMove(new_pos.x,snakePosition[0].y)==true and isHitted(new_pos.x,snakePosition[0].y)==false)
        {
            snakePosition.push_front(new_pos);
            if(isCollected(snakePosition[0].x,snakePosition[0].y)==false)
                snakePosition.pop_back();
        }
        else
            {
                kierunek=RIGHT;
            }
    }
    if(kierunek==RIGHT)
    {
        Position new_pos=snakePosition[0];
        new_pos.x++;
        if(canMove(new_pos.x,snakePosition[0].y)==true and isHitted(new_pos.x,snakePosition[0].y)==false)
        {
            snakePosition.push_front(new_pos);
            if(isCollected(snakePosition[0].x,snakePosition[0].y)==false)
                snakePosition.pop_back();
        }
        else
            {
                kierunek=LEFT;
            }
    }
    updateBoard();
}

void SnakeBoard::updateBoard()
{
    std::cout<<snakePosition.size()<<std::endl;
    for(std::size_t i = 0; i<snakePosition.size(); i++)
    {
        board[snakePosition[i].y][snakePosition[i].x].isSnake=true;
        if(board[snakePosition[i].y][snakePosition[i].x].isSnake==true and board[snakePosition[i].y][snakePosition[i].x].isApple==true)
        {
            board[snakePosition[i].y][snakePosition[i].x].isApple=false;
        }
        else
            board[snakePosition[snakePosition.size()].y][snakePosition[snakePosition.size()].x].isSnake=false;
    }
}

int SnakeBoard::getBoardWidth()
{
    return boardWidth;
}

int SnakeBoard::getBoardHeight()
{
    return boardHeight;
}

bool SnakeBoard::isSnake(int x, int y)
{
    if(board[y][x].isSnake==true)
        return true;
    else
        return false;
}

void SnakeBoard::changeDirection(direction new_direction)
{
    kierunek=new_direction;
}

bool SnakeBoard::isCollected(int xd, int yd)
{
    if(snakePosition[0].x==xd and snakePosition[0].y==yd and board[yd][xd].isApple==true)
        {
            appleChecker=0;
            emptyFields--;
            return true;
        }
    else return false;
}

void SnakeBoard::generateApple()
{
    if(state==FINISHED_LOSS or state==FINISHED_WIN or state==STOPPED)
        return;
    for(int checker=1; checker<2; checker++)
    {
        int rand_x=(( std::rand() % boardWidth) + 0 );
        int rand_y=(( std::rand() % boardHeight) + 0 );
        if(board[rand_y][rand_x].isSnake==false)
            {
                board[rand_y][rand_x].isApple=true;
                appleChecker=1;
            }
        else
            checker--;
    }
}

void SnakeBoard::debug_display()
{
    std::string display;
    for (int idx_y = 0; idx_y<boardHeight; idx_y++)
    {
        for (int idx_x = 0; idx_x<boardWidth; idx_x++) {
            display+="[";
            if (board[idx_y][idx_x].isSnake==1)
                display+="S";
            else
                display+=".";
            if (board[idx_y][idx_x].isApple==1)
                display+="a";
            else
                display+=".";
            display+="] ";
        } display+= "\n";
    }
    std::cout << display << std::endl;
}

