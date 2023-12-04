#include <iostream>
#include <string>
#include <vector>
#include "board.hpp"
#include "pieces.hpp"

/*-------------------------------THREAT FUNCTIONS-------------------------------*/
/*Created these functions to setUnderAttack of the pieces accordingly. For every
Piece, I check where the piece can attack and i set the isUnderAttack variable
of that Piece to true.*/

void Board::threatOfPawn(int x, int y)
{
    if(myBoard[x][y].getColor() == "White") /*If pawn is white*/
    {
        if(x+1 < 8 && y+1 < 8)  /*Right corner*/
        {
            if(myBoard[x+1][y+1].getColor() != "White") /*If attacking point is not white*/
                myBoard[x+1][y+1].setUnderAttack(true);
        }
        if(x-1 >= 0 && y+1 < 8) /*Left corner*/
        {
            if(myBoard[x-1][y+1].getColor() != "White") /*If attacking point is not white*/
                myBoard[x-1][y+1].setUnderAttack(true);  
        }

    }
    else if(myBoard[x][y].getColor() == "Black")    /*If pawn is black*/
    {
        if(x+1 < 8 && y-1 >= 0) /*Left corner*/
        {
            if(myBoard[x+1][y-1].getColor() != "Black") /*If attacking point is not black*/
                myBoard[x+1][y-1].setUnderAttack(true);
        }
        if(x-1 >= 0 && y-1 >= 0) /*Right corner*/
        {
            if(myBoard[x-1][y-1].getColor() != "Black") /*If attacking point is not black*/
                myBoard[x-1][y-1].setUnderAttack(true);
        }
           
    }
}
void Board::threatOfRook(int x, int y)
{
    if(myBoard[x][y].getColor() == "White")
    {
        for(int i = x + 1, j = y; i < 8; i++)   /*From R to right*/
        {
            if(myBoard[i][j].getColor() == "White")    /*If there is a teammate piece*/
                break;
            if(myBoard[i][j].getColor() == "Black") /*If there is a opponent piece*/
            {
                myBoard[i][j].setUnderAttack(true);
                break;
            }
            else                                        
                myBoard[i][j].setUnderAttack(true); /*If it is an empty piece*/
        }
        for(int i = x - 1, j = y; i >= 0; i--)  /*From R to left*/
        {
            if(myBoard[i][j].getColor() == "White")    /*If there is a teammate piece*/
                break;
            if(myBoard[i][j].getColor() == "Black") /*If there is a opponent piece*/
            {
                myBoard[i][j].setUnderAttack(true);
                break;
            }
            else                                        
                myBoard[i][j].setUnderAttack(true); /*If it is an empty piece*/
        }
        for(int i = x, j = y + 1; j < 8; j++)   /*From R to up*/
        {
            if(myBoard[i][j].getColor() == "White")    /*If there is a teammate piece*/
                break;
            if(myBoard[i][j].getColor() == "Black") /*If there is a opponent piece*/
            {
                myBoard[i][j].setUnderAttack(true);
                break;
            }
            else                                        
                myBoard[i][j].setUnderAttack(true); /*If it is an empty piece*/
        }
        for(int i = x, j = y - 1; j >= 0; j--)   /*From R to down*/
        {
            if(myBoard[i][j].getColor() == "White")    /*If there is a teammate piece*/
                break;
            if(myBoard[i][j].getColor() == "Black") /*If there is a opponent piece*/
            {
                myBoard[i][j].setUnderAttack(true);
                break;
            }
            else                                        
                myBoard[i][j].setUnderAttack(true); /*If it is an empty piece*/
        }

    }
    else if(myBoard[x][y].getColor() == "Black")
    {
         for(int i = x + 1, j = y; i < 8; i++)   /*From R to right*/
        {
            if(myBoard[i][j].getColor() == "Black")    /*If there is a teammate piece*/
                break;
            if(myBoard[i][j].getColor() == "White") /*If there is a opponent piece*/
            {
                myBoard[i][j].setUnderAttack(true);
                break;
            }
            else                                        
                myBoard[i][j].setUnderAttack(true); /*If it is an empty piece*/
        }
        for(int i = x - 1, j = y; i >= 0; i--)  /*From R to left*/
        {
            if(myBoard[i][j].getColor() == "Black")    /*If there is a teammate piece*/
                break;
            if(myBoard[i][j].getColor() == "White") /*If there is a opponent piece*/
            {
                myBoard[i][j].setUnderAttack(true);
                break;
            }
            else                                        
                myBoard[i][j].setUnderAttack(true); /*If it is an empty piece*/
        }
        for(int i = x, j = y + 1; j < 8; j++)   /*From R to up*/
        {
            if(myBoard[i][j].getColor() == "Black")    /*If there is a teammate piece*/
                break;
            if(myBoard[i][j].getColor() == "White") /*If there is a opponent piece*/
            {
                myBoard[i][j].setUnderAttack(true);
                break;
            }
            else                                        
                myBoard[i][j].setUnderAttack(true); /*If it is an empty piece*/
        }
        for(int i = x, j = y - 1; j >= 0; j--)   /*From R to down*/
        {
            if(myBoard[i][j].getColor() == "Black")    /*If there is a teammate piece*/
                break;
            if(myBoard[i][j].getColor() == "White") /*If there is a opponent piece*/
            {
                myBoard[i][j].setUnderAttack(true);
                break;
            }
            else                                        
                myBoard[i][j].setUnderAttack(true); /*If it is an empty piece*/
        }
    }
}
void Board::threatOfKnight(int x, int y)
{
    if(myBoard[x][y].getColor() == "White") /*Checking every possibilty for White Knight*/
    {
    
        if(x+1 < 8 && y+2 < 8)
            if(myBoard[x+1][y+2].getColor() != "White")
                myBoard[x+1][y+2].setUnderAttack(true);
        if(x+1 < 8 && y-2 >= 0)
            if(myBoard[x+1][y-2].getColor() != "White")
                myBoard[x+1][y-2].setUnderAttack(true);
        if(x-1 >= 0 && y+2 < 8)
            if(myBoard[x-1][y+2].getColor() != "White")
                myBoard[x-1][y+2].setUnderAttack(true);
        if(x-1 >= 0 && y-2 >= 0)
            if(myBoard[x-1][y-2].getColor() != "White")
                myBoard[x-1][y-2].setUnderAttack(true);
        if(x+2 < 8 && y+1 < 8) 
            if(myBoard[x+2][y+1].getColor() != "White")
                myBoard[x+2][y+1].setUnderAttack(true);
        if(x-2 >= 0 && y+1 < 8)
            if(myBoard[x-2][y+1].getColor() != "White")
                myBoard[x-2][y+1].setUnderAttack(true);
        if(x+2 < 8 && y-1 >= 0)
            if(myBoard[x+2][y-1].getColor() != "White")
                myBoard[x+2][y-1].setUnderAttack(true);
        if(x-2 >= 0 && y-1 >= 0)
            if(myBoard[x-2][y-1].getColor() != "White")
                myBoard[x-2][y-1].setUnderAttack(true);
    }
    else if(myBoard[x][y].getColor() == "Black")    /*Checking every posibility for black*/
    {
        if(x+1 < 8 && y+2 < 8)
            if(myBoard[x+1][y+2].getColor() != "Black")
                myBoard[x+1][y+2].setUnderAttack(true);
        if(x+1 < 8 && y-2 >= 0)
            if(myBoard[x+1][y-2].getColor() != "Black")
                myBoard[x+1][y-2].setUnderAttack(true);
        if(x-1 >= 0 && y+2 < 8)
            if(myBoard[x-1][y+2].getColor() != "Black")
                myBoard[x-1][y+2].setUnderAttack(true);
        if(x-1 >= 0 && y-2 >= 0)
            if(myBoard[x-1][y-2].getColor() != "Black")
                myBoard[x-1][y-2].setUnderAttack(true);
        if(x+2 < 8 && y+1 < 8) 
            if(myBoard[x+2][y+1].getColor() != "Black")
                myBoard[x+2][y+1].setUnderAttack(true);
        if(x-2 >= 0 && y+1 < 8)
            if(myBoard[x-2][y+1].getColor() != "Black")
                myBoard[x-2][y+1].setUnderAttack(true);
        if(x+2 < 8 && y-1 >= 0)
            if(myBoard[x+2][y-1].getColor() != "Black")
                myBoard[x+2][y-1].setUnderAttack(true);
        if(x-2 >= 0 && y-1 >= 0)
            if(myBoard[x-2][y-1].getColor() != "Black")
                myBoard[x-2][y-1].setUnderAttack(true);
    }
}
void Board::threatOfBishop(int x, int y)
{
    if(myBoard[x][y].getColor() == "White")
    {
        if(0 <= x < 7 && 0 <= y < 7)
        {
            for(int i = x+1, j = y+1; i < 8 && j < 8; i++, j++) /*North-East*/
            {
                if(myBoard[i][j].getColor() == "White")
                    break;
                else if(myBoard[i][j].getColor() == "Black")
                {
                    myBoard[i][j].setUnderAttack(true);
                    break;
                }
                else
                    myBoard[i][j].setUnderAttack(true);
            }
        }
        if(0 <= x < 7 && 0 < y <= 7)
        {
            for(int i = x+1, j = y-1; i < 8 && j >= 0; i++, j--) /*South-East*/
            {
                if(myBoard[i][j].getColor() == "White")
                    break;
                else if(myBoard[i][j].getColor() == "Black")
                {
                    myBoard[i][j].setUnderAttack(true);
                    break;
                }
                else
                    myBoard[i][j].setUnderAttack(true);
            }
        }
        if(0 < x <= 7 && 0 <= y < 7)
        {
            for(int i = x-1, j = y+1; i >= 0 && j < 8; i--, j++) /*South-West*/
            {
                if(myBoard[i][j].getColor() == "White")
                    break;
                else if(myBoard[i][j].getColor() == "Black")
                {
                    myBoard[i][j].setUnderAttack(true);
                    break;
                }
                else
                    myBoard[i][j].setUnderAttack(true);
            }
        }
        if(0 < x <= 7 && 0 < y <= 7)
        {
            for(int i = x-1, j = y-1; i >= 0 && j >= 0; i--, j--) /*North-West*/
            {
                if(myBoard[i][j].getColor() == "White")
                    break;
                else if(myBoard[i][j].getColor() == "Black")
                {
                    myBoard[i][j].setUnderAttack(true);
                    break;
                }
                else
                    myBoard[i][j].setUnderAttack(true);
            }
        }
    }
    else if(myBoard[x][y].getColor() == "Black") 
    {
        if(0 <= x < 7 && 0 <= y < 7)
        {
            for(int i = x+1, j = y+1; i < 8 && j < 8; i++, j++) /*NE*/
            {
                if(myBoard[i][j].getColor() == "Black")
                    break;
                else if(myBoard[i][j].getColor() == "")
                {
                    myBoard[i][j].setUnderAttack(true);
                    break;
                }
                else
                    myBoard[i][j].setUnderAttack(true);
            }
        }
        if(0 <= x < 7 && 0 < y <= 7)
        {
            for(int i = x+1, j = y-1; i < 8 && j >= 0; i++, j--) /*SE*/
            {
                if(myBoard[i][j].getColor() == "Black")
                    break;
                else if(myBoard[i][j].getColor() == "White")
                {
                    myBoard[i][j].setUnderAttack(true);
                    break;
                }
                else
                    myBoard[i][j].setUnderAttack(true);
            }
        }
        if(0 < x <= 7 && 0 <= y < 7)
        {
            for(int i = x-1, j = y+1; i >= 0 && j < 8; i--, j++) /*SW*/
            {
                if(myBoard[i][j].getColor() == "Black")
                    break;
                else if(myBoard[i][j].getColor() == "White")
                {
                    myBoard[i][j].setUnderAttack(true);
                    break;
                }
                else
                    myBoard[i][j].setUnderAttack(true);
            }
        }
        if(0 < x <= 7 && 0 < y <= 7)
        {
            for(int i = x-1, j = y-1; i >= 0 && j >= 0; i--, j--) /*NW*/
            {
                if(myBoard[i][j].getColor() == "Black")
                    break;
                else if(myBoard[i][j].getColor() == "White")
                {
                    myBoard[i][j].setUnderAttack(true);
                    break;
                }
                else
                    myBoard[i][j].setUnderAttack(true);
            }
        }
    }
}
void Board::threatOfQueen(int x, int y)
{
    threatOfRook(x,y);  /*Queen only needs threatOfRook & threatOfBishop*/
    threatOfBishop(x,y);
}
void Board::threatOfKing(int x, int y)
{
    if(myBoard[x][y].getColor() == "White")
    {
        if(x+1 < 8 && x-1 >= 0 && y+1 < 8 && y-1 >= 0)  /*Every moveable point*/
        {
            if(myBoard[x+1][y+1].getColor() != "White") /*If it is not teammate piece*/
                myBoard[x+1][y+1].setUnderAttack(true);
            if(myBoard[x-1][y+1].getColor() != "White")
                myBoard[x-1][y+1].setUnderAttack(true);
        }
    }
    else if(myBoard[x][y].getColor() == "Black")
    {
        if(x+1 < 8 && x-1 >= 0 && y+1 < 8 && y-1 >= 0) /*Every moveable point*/
        {
            if(myBoard[x+1][y-1].getColor() != "Black") /*If it is not teammate piece*/
                myBoard[x+1][y-1].setUnderAttack(true);
            if(myBoard[x-1][y-1].getColor() != "Black")
                myBoard[x-1][y-1].setUnderAttack(true);
        }
    }
}
void Board::printThreats() const
{
    for(int j = 7; j >= 0; j--)
    {
        cout << j+1 << " |";
        for(int i = 0; i < 8; i++)
        {
            cout << " " << myBoard[i][j].getUnderAttack() << " ";
        }
        cout << endl;
    }
    cout << "    " << "----------------------" << endl;
    cout << "    " << "a  b  c  d  e  f  g  h" << endl;
}