#include <iostream>
#include <string>
#include <vector>
#include "board.hpp"
#include "pieces.hpp"
using namespace std;

/*-------------------------------SUGGEST FUNCTIONS-------------------------------*/ 
int Board::calculateWhiteScore() /*Calculating the White's total score*/
{
    double whiteTotalScore = 0;
    for(int i = 0; i < 8; i++) 
        for(int j = 0; j < 8; j++)
            if(myBoard[i][j].getColor() == "White")
                whiteTotalScore += myBoard[i][j].getPoint();

    /*Setting the danger points*/
    checkDanger();
    /*Searching every piece for under attack*/
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(myBoard[i][j].getColor() == "White" && myBoard[i][j].getUnderAttack())
                whiteTotalScore -= 0.5 * myBoard[i][j].getPoint();
        }
    }
    return whiteTotalScore;
}
int Board::calculateBlackScore() /*Calculating the Black's total score*/
{
    double blackTotalScore = 0;
    for(int i = 0; i < 8; i++) 
        for(int j = 0; j < 8; j++)
            if(myBoard[i][j].getColor() == "Black")
                blackTotalScore += myBoard[i][j].getPoint();
    /*Setting the danger points*/
    checkDanger();
    /*Searching every piece for under attack*/
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(myBoard[i][j].getColor() == "Black" && myBoard[i][j].getUnderAttack())
                blackTotalScore -= 0.5 * myBoard[i][j].getPoint();
        }
    }
    return blackTotalScore;
}
int Board::getScore(int xp, int yp, int xn, int yn, string &move, string side)
{
    Pieces temp;
    temp = myBoard[xn][yn];
    this->movePiece(xp,yp,xn,yn);   /*Make the simulational move*/

    int score;
    char c1,c2,c3,c4;   /*Convert the integers to string*/
    c1 = 'a' + xp;
    c2 = '1' + yp;
    c3 = 'a' + xn;
    c4 = '1' + yn;

    string movement;    /*Creating the string*/
    movement.push_back(c1);
    movement.push_back(c2);
    movement.push_back(c3);
    movement.push_back(c4);
    
    if(side == "White") /*Calculating the scores*/
        score = this-> calculateWhiteScore() - this->calculateBlackScore();
    else if(side == "Black")
        score = this-> calculateBlackScore() - this->calculateWhiteScore();

    move = movement;    /*Changing the move every time the functions called*/

    this->movePiece(xn,yn,xp,yp);   /*Making the movement backwards*/
    myBoard[xn][yn] = temp;
    return score; /*Returning the score*/
}
string Board::suggestMove(string side)
{
    int temp;
    string move, bestMove;
    int maxp = -10000;
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            for(int k = 0; k < 8; k++)
            {
                for(int m = 0; m < 8; m++)
                {
                    if(checkPawnMovement(i,j,k,m,side)) /*Checking every movements of the pieces*/
                    {
                        temp = this->getScore(i,j,k,m,move,side);   /*Getting the score if piece can be moved*/
                        if(maxp <= temp)    /*Checking for the maximum point*/
                        {
                            maxp = temp;    
                            bestMove = move;    /*If it is maximum, then getting the string of the move*/
                        }
                    }
                    if(checkRookMovement(i,j,k,m,side))
                    {
                        temp = this->getScore(i,j,k,m,move,side);
                        if(maxp <= temp)
                        {
                            maxp = temp;
                            bestMove = move;
                        }
                    }
                    if(checkKnightMovement(i,j,k,m,side))
                    {
                        temp = this->getScore(i,j,k,m,move,side);
                        if(maxp <= temp)
                        {
                            maxp = temp;
                            bestMove = move;
                        }
                    }
                    if(checkBishopMovement(i,j,k,m,side))
                    {
                        temp = this->getScore(i,j,k,m,move,side);
                        if(maxp <= temp)
                        {
                            maxp = temp;
                            bestMove = move;
                        }
                    }
                    if(checkQueenMovement(i,j,k,m,side))
                    {
                        temp = this->getScore(i,j,k,m,move,side);
                        if(maxp <= temp)
                        {
                            maxp = temp;
                            bestMove = move;
                        }
                    }
                    if(checkKingMovement(i,j,k,m,side))
                    {
                        temp = this->getScore(i,j,k,m,move,side);
                        if(maxp <= temp)
                        {
                            maxp = temp;
                            bestMove = move;
                        }
                    }
                }
            }
        }
    }
    cout << "Suggested: " << bestMove << endl;
    return bestMove;
}
