#include <iostream>
#include <string>
#include <vector>
#include "board.hpp"
#include "pieces.hpp"
using namespace std;

/*-------------------------------CHECK & CHECKMATE FUNCTIONS-------------------------------*/
/*Created these functions to check every legal movement of the pieces. In the checkTheCheck 
function, i am checking if the Board is in check position. If it is, then i go into 
checkEveryMovement function to check the every legal moves of the pieces. If one of them saves
the king from the Check, than i return false. If none of them can save the King and King cannot 
move to a non-underAttacked location, then it is checkmated.*/

/*Checking the legal movements of the pieces*/
bool Board::checkPawnMovement(int xp, int yp, int xn, int yn, string side) const
{
    bool canBeMoved = false;
    if(side == "White" && myBoard[xp][yp].getType() == 'P')
    {
        if(yp == 1)
        {
            if((yn == yp + 1 || yn == yp + 2) && (xn == xp) && (!isTherePieceBlack(xn,yn) && !isTherePieceWhite(xn,yn)))
                canBeMoved = true;
            else if(yn == yp + 1 && ((xn == xp+1) || (xn == xp-1)) && isTherePieceBlack(xn,yn))
                canBeMoved = true;
        }
        else
        {
            if((yn == yp + 1 && xn == xp) && (!isTherePieceBlack(xn,yn) && !isTherePieceWhite(xn,yn)))
                canBeMoved = true;
            else if(yn == yp + 1 && ((xn == xp+1) || (xn == xp-1)) && isTherePieceBlack(xn,yn))
                canBeMoved = true;
        }
    }
    else if(side == "Black" && myBoard[xp][yp].getType() == 'p')
    {
        if(yp == 6)
        {
            if((yn == yp - 1 || yn == yp - 2) && xn == xp && (!isTherePieceBlack(xn,yn) && !isTherePieceWhite(xn,yn)))
                canBeMoved = true;
            else if(((yn == yp - 1) && ((xn == xp+1) || (xn == xp-1))) && isTherePieceWhite(xn,yn))
                canBeMoved = true;
        }
        else
        {
            if(yn == yp - 1 && xn == xp && (!isTherePieceBlack(xn,yn) && !isTherePieceWhite(xn,yn)))
                canBeMoved = true;
            else if((yn == yp - 1 && ((xn == xp+1) || (xn == xp-1))) && isTherePieceWhite(xn,yn))
                canBeMoved = true;
        }
    }
    return canBeMoved;
}
bool Board::checkRookMovement(int xp, int yp, int xn, int yn, string side) const
{
    bool canBeMoved = false;
    bool flag = 0;
    if(abs(xn - xp) != abs(yn - yp))
        canBeMoved = false;
    else if(xn > xp && yn > yp) 
    {
        for(int i = xn, j = yn; i > xp, j > yp; i--, j--)
        {
            if(side == "White" && myBoard[xp][yp].getType() == 'Q')
            {
                if(isTherePieceBlack(i,j))
                {
                    flag = 1;
                }
                else if(isTherePieceWhite(i,j) && (i != xn || j != yn))
                {
                    flag = 1;
                }
            }
            else if(side == "Black" && myBoard[xp][yp].getType() == 'q')
            {
                if(isTherePieceBlack(i,j))
                {
                    flag = 1;
                }
                else if(isTherePieceWhite(i,j) && (i != xn || j != yn))
                {
                    flag = 1;
                }
            }
            else
            {
                canBeMoved = false;
                return canBeMoved;
            }
        }
        if(!flag)
            canBeMoved = true;
    }
    else if(xn > xp && yn < yp) 
    {
        for(int i = xn, j = yn; i > xp, j < yp; i--, j++)
        {
            if(side == "White" && myBoard[xp][yp].getType() == 'Q')
            {
                if(isTherePieceBlack(i,j))
                {
                    flag = 1;
                }
                else if(isTherePieceWhite(i,j) && (i != xn || j != yn))
                {
                    flag = 1;
                }
            }
            else if(side == "Black" && myBoard[xp][yp].getType() == 'q')
            {
                if(isTherePieceBlack(i,j))
                {
                    flag = 1;
                }
                else if(isTherePieceWhite(i,j) && (i != xn || j != yn))
                {
                    flag = 1;
                }
            }
            else
            {
                canBeMoved = false;
                return canBeMoved;
            }
        }
        if(!flag)
            canBeMoved = true;
    }
    else if(xn < xp && yn > yp)
    {
        for(int i = xn, j = yn; i < xp, j > yp; i++, j--)
        {
            if(side == "White" && myBoard[xp][yp].getType() == 'Q')
            {
                if(isTherePieceBlack(i,j))
                {
                    flag = 1;
                }
                else if(isTherePieceWhite(i,j) && (i != xn || j != yn))
                {
                    flag = 1;
                }
            }
            else if(side == "Black" && myBoard[xp][yp].getType() == 'q')
            {
                if(isTherePieceBlack(i,j))
                {
                    flag = 1;
                }
                else if(isTherePieceWhite(i,j) && (i != xn || j != yn))
                {
                    flag = 1;
                }
            }
            else
            {
                canBeMoved = false;
                return canBeMoved;
            }
        }
        if(!flag)
            canBeMoved = true;
    }
    else if(xn < xp && yn < yp)
    {
        for(int i = xn, j = yn; i < xp, j < yp; i++, j++)
        {
            if(side == "White" && myBoard[xp][yp].getType() == 'Q')
            {
                if(isTherePieceBlack(i,j))
                {
                    flag = 1;
                }
                else if(isTherePieceWhite(i,j) && (i != xn || j != yn))
                {
                    flag = 1;
                }
            }
            else if(side == "Black" && myBoard[xp][yp].getType() == 'q')
            {
                if(isTherePieceBlack(i,j))
                {
                    flag = 1;
                }
                else if(isTherePieceWhite(i,j) && (i != xn || j != yn))
                {
                    flag = 1;
                }
            }
            else
            {
                canBeMoved = false;
                return canBeMoved;
            }
        }
        if(!flag)
            canBeMoved = true;
    }
    return canBeMoved;
}
bool Board::checkKnightMovement(int xp, int yp, int xn, int yn, string side) const 
{
    bool canBeMoved = false;
    if(side == "White")
    {
        if(myBoard[xp][yp].getType() == 'N')
            if(((xn == xp + 1 && yn == yp + 2) || (xn == xp - 1 && yn == yp + 2) || 
                (xn == xp + 1 && yn == yp - 2) || (xn == xp - 1 && yn == yp - 2) || 
                (xn == xp + 2 && yn == yp + 1) || (xn == xp - 2 && yn == yp + 1) ||
                (xn == xp + 2 && yn == yp - 1) || (xn == xp - 2 && yn == yp - 1)) && !isTherePieceWhite(xn,yn))
                canBeMoved = true;
    }
    else if(side == "Black")
    {
        if(myBoard[xp][yp].getType() == 'n')
                if(((xn == xp + 1 && yn == yp + 2) || (xn == xp - 1 && yn == yp + 2) || 
                (xn == xp + 1 && yn == yp - 2) || (xn == xp - 1 && yn == yp - 2) || 
                (xn == xp + 2 && yn == yp + 1) || (xn == xp - 2 && yn == yp + 1) ||
                (xn == xp + 2 && yn == yp - 1) || (xn == xp - 2 && yn == yp - 1)) && !isTherePieceBlack(xn,yn))
                    canBeMoved = true;
    }
    return canBeMoved;
}
bool Board::checkBishopMovement(int xp, int yp, int xn, int yn, string side) const
{
    bool canBeMoved = false;
    bool flag = 0;
    if(abs(xn - xp) != abs(yn - yp))
        canBeMoved = false;
    else if(xn > xp && yn > yp) 
    {
        for(int i = xn, j = yn; i > xp, j > yp; i--, j--)
        {
            if(side == "White" && myBoard[xp][yp].getType() == 'B')
            {
                if(isTherePieceBlack(i,j))
                {
                    flag = 1;
                }
                else if(isTherePieceWhite(i,j) && (i != xn || j != yn))
                {
                    flag = 1;
                }
            }
            else if(side == "Black" && myBoard[xp][yp].getType() == 'b')
            {
                if(isTherePieceBlack(i,j))
                {
                    flag = 1;
                }
                else if(isTherePieceWhite(i,j) && (i != xn || j != yn))
                {
                    flag = 1;
                }
            }
            else
            {
                canBeMoved = false;
                return canBeMoved;
            }
        }
        if(!flag)
            canBeMoved = true;
    }
    else if(xn > xp && yn < yp) 
    {
        for(int i = xn, j = yn; i > xp, j < yp; i--, j++)
        {
            if(side == "White" && myBoard[xp][yp].getType() == 'B')
            {
                if(isTherePieceBlack(i,j))
                {
                    flag = 1;
                }
                else if(isTherePieceWhite(i,j) && (i != xn || j != yn))
                {
                    flag = 1;
                }
            }
            else if(side == "Black" && myBoard[xp][yp].getType() == 'b')
            {
                if(isTherePieceBlack(i,j))
                {
                    flag = 1;
                }
                else if(isTherePieceWhite(i,j) && (i != xn || j != yn))
                {
                    flag = 1;
                }
            }
            else
            {
                canBeMoved = false;
                return canBeMoved;
            }
        }
        if(!flag)
            canBeMoved = true;
    }
    else if(xn < xp && yn > yp)
    {
        for(int i = xn, j = yn; i < xp, j > yp; i++, j--)
        {
            if(side == "White" && myBoard[xp][yp].getType() == 'B')
            {
                if(isTherePieceBlack(i,j))
                {
                    flag = 1;
                }
                else if(isTherePieceWhite(i,j) && (i != xn || j != yn))
                {
                    flag = 1;
                }
            }
            else if(side == "Black" && myBoard[xp][yp].getType() == 'b')
            {
                if(isTherePieceBlack(i,j))
                {
                    flag = 1;
                }
                else if(isTherePieceWhite(i,j) && (i != xn || j != yn))
                {
                    flag = 1;
                }
            }
            else
            {
                canBeMoved = false;
                return canBeMoved;
            }
        }
        if(!flag)
            canBeMoved = true;
    }
    else if(xn < xp && yn < yp)
    {
        for(int i = xn, j = yn; i < xp, j < yp; i++, j++)
        {
            if(side == "White" && myBoard[xp][yp].getType() == 'B')
            {
                if(isTherePieceBlack(i,j))
                {
                    flag = 1;
                }
                else if(isTherePieceWhite(i,j) && (i != xn || j != yn))
                {
                    flag = 1;
                }
            }
            else if(side == "Black" && myBoard[xp][yp].getType() == 'b')
            {
                if(isTherePieceBlack(i,j))
                {
                    flag = 1;
                }
                else if(isTherePieceWhite(i,j) && (i != xn || j != yn))
                {
                    flag = 1;
                }
            }
            else
            {
                canBeMoved = false;
                return canBeMoved;
            }
        }
        if(!flag)
            canBeMoved = true;
    }
    return canBeMoved;
}
bool Board::checkQueenMovement(int xp, int yp, int xn, int yn, string side) const
{
    bool canBeMoved = false;
    if(side == "White")
    {
        if(myBoard[xp][yp].getType() == 'Q')
        {
            if(xp != xn && yn != yp)
                canBeMoved = checkQueenDiagonal(xp,yp,xn,yn,side);
            else if((xp == xn && yn != yp) || (xp != xn && yn == yp))
                canBeMoved = checkQueenHorizontal(xp,yp,xn,yn,side);
        }
    }
    else if (side == "Black")
    {
        if(myBoard[xp][yp].getType() == 'q')
        {
            if(xp != xn && yn != yp)
                canBeMoved = checkQueenDiagonal(xp,yp,xn,yn,side);
            else if((xp == xn && yn != yp) || (xp != xn && yn == yp))
                canBeMoved = checkQueenHorizontal(xp,yp,xn,yn,side);
        }
    }

    return canBeMoved;
}
bool Board::checkQueenHorizontal(int xp, int yp, int xn, int yn, string side) const
{
    bool canBeMoved = false;
    bool flag = false;
    if(side == "White" && myBoard[xp][yp].getType() == 'Q')
    {
        if(isTherePieceWhite(xn,yn))
        {
            canBeMoved = false;
            return canBeMoved;
        }
    }
    else if(side == "Black" && myBoard[xp][yp].getType() == 'q')
    {
        if(isTherePieceBlack(xn,yn))
        {
            canBeMoved = false;
            return canBeMoved;
        }
    }
    if (xp == xn && yp != yn)
    {
        if (side == "White" && myBoard[xp][yp].getType() == 'Q')
        {
            if (yn > yp && (yn < 8 || yn >= 0))
            {
                for (int i = yp + 1; i < yn; i++)
                {
                    if (isTherePieceWhite(xp, i) || (isTherePieceBlack(xp, i)))
                        flag = true;
                }
                if (!flag)
                    canBeMoved = true;
            }
            else if (yn < yp && (yn < 8 || yn >= 0))
            {
                for (int i = yp - 1; i > yn; i--)
                {
                    if (isTherePieceWhite(xp, i) || (isTherePieceBlack(xp, i)))
                        flag = true;
                }
                if (!flag)
                    canBeMoved = true;
            }
        }
        else if (side == "Black" && myBoard[xp][yp].getType() == 'q')
        {
            if (yn > yp && (yn < 8 || yn >= 0))
            {
                for (int i = yp + 1; i < yn; i++)
                {
                    if (isTherePieceWhite(xp, i) || (isTherePieceBlack(xp, i)))
                        flag = true;
                }
                if (!flag)
                    canBeMoved = true;
            }
            else if (yn < yp && (yn < 8 || yn >= 0))
            {
                for (int i = yp - 1; i > yn; i--)
                {
                    if (isTherePieceWhite(xp, i) || (isTherePieceBlack(xp, i)))
                        flag = true;
                }
                if (!flag)
                    canBeMoved = true;
            }
        }
    }
    else if (yp == yn && xp != xn)
    {
        if (side == "White" && myBoard[xp][yp].getType() == 'Q')
        {
            if (xn > xp && (xn < 8 || xn >= 0))
            {
                for (int i = xp + 1; i < xn; i++)
                {
                    if (isTherePieceWhite(i, yp) || (isTherePieceBlack(i, yp)))
                        flag = true;
                }
                if (!flag)
                    canBeMoved = true;
            }
            else if (xn < xp && (xn < 8 || xn >= 0))
            {
                for (int i = xp - 1; i > xn; i--)
                {
                    if (isTherePieceWhite(i, yp) || (isTherePieceBlack(i, yp)))
                        flag = true;
                }
                if (!flag)
                    canBeMoved = true;
            }
        }
        else if (side == "Black" && myBoard[xp][yp].getType() == 'q')
        {
            if (xn > xp && (xn < 8 || xn >= 0))
            {
                for (int i = xp + 1; i < xn; i++)
                {
                    if (isTherePieceWhite(i, yp) || (isTherePieceBlack(i, yp)))
                        flag = true;
                }
                if (!flag)
                    canBeMoved = true;
            }
            else if (xn < xp && (xn < 8 || xn >= 0))
            {
                for (int i = xp - 1; i > xn; i--)
                {
                    if (isTherePieceWhite(i, yp) || (isTherePieceBlack(i, yp)))
                        flag = true;
                }
                if (!flag)
                    canBeMoved = true;
            }
        }
    }
    return canBeMoved;
}
bool Board::checkQueenDiagonal(int xp, int yp, int xn, int yn, string side) const
{
    bool canBeMoved = false;
    bool flag = 0;
    if(abs(xn - xp) != abs(yn - yp))
        canBeMoved = false;
    else if(xn > xp && yn > yp) 
    {
        for(int i = xn, j = yn; i > xp, j > yp; i--, j--)
        {
            if(side == "White" && myBoard[xp][yp].getType() == 'Q')
            {
                if(isTherePieceBlack(i,j))
                {
                    flag = 1;
                }
                else if(isTherePieceWhite(i,j) && (i != xn || j != yn))
                {
                    flag = 1;
                }
            }
            else if(side == "Black" && myBoard[xp][yp].getType() == 'q')
            {
                if(isTherePieceWhite(i,j) || isTherePieceBlack(i,j))
                    flag = 1;
            }
            else
            {
                canBeMoved = false;
                return canBeMoved;
            }
        }
        if(!flag)
            canBeMoved = true;
    }
    else if(xn > xp && yn < yp) /*D8H4 - 37-73 -- 73 64 55 46 37*/
    {
        for(int i = xn, j = yn; i > xp, j < yp; i--, j++)
        {
            if(side == "White" && myBoard[xp][yp].getType() == 'Q')
            {
                if(isTherePieceBlack(i,j))
                {
                    flag = 1;
                }
                else if(isTherePieceWhite(i,j) && (i != xn || j != yn))
                {
                    flag = 1;
                }
            }
            else if(side == "Black" && myBoard[xp][yp].getType() == 'q')
            {
                if(isTherePieceBlack(i,j))
                {
                    flag = 1;
                }
                else if(isTherePieceWhite(i,j) && (i != xn || j != yn))
                {
                    flag = 1;
                }
            }
            else
            {
                canBeMoved = false;
                return canBeMoved;
            }
        }
        if(!flag)
            canBeMoved = true;
    }
    else if(xn < xp && yn > yp)
    {
        for(int i = xn, j = yn; i < xp, j > yp; i++, j--)
        {
            if(side == "White" && myBoard[xp][yp].getType() == 'Q')
            {
                if(isTherePieceBlack(i,j))
                {
                    flag = 1;
                }
                else if(isTherePieceWhite(i,j) && (i != xn || j != yn))
                {
                    flag = 1;
                }
            }
            else if(side == "Black" && myBoard[xp][yp].getType() == 'q')
            {
                if(isTherePieceBlack(i,j))
                {
                    flag = 1;
                }
                else if(isTherePieceWhite(i,j) && (i != xn || j != yn))
                {
                    flag = 1;
                }
            }
            else
            {
                canBeMoved = false;
                return canBeMoved;
            }
        }
        if(!flag)
            canBeMoved = true;
    }
    else if(xn < xp && yn < yp)
    {
        for(int i = xn, j = yn; i < xp, j < yp; i++, j++)
        {
            if(side == "White" && myBoard[xp][yp].getType() == 'Q')
            {
                if(isTherePieceBlack(i,j))
                {
                    flag = 1;
                }
                else if(isTherePieceWhite(i,j) && (i != xn || j != yn))
                {
                    flag = 1;
                }
            }
            else if(side == "Black" && myBoard[xp][yp].getType() == 'q')
            {
                if(isTherePieceBlack(i,j))
                {
                    flag = 1;
                }
                else if(isTherePieceWhite(i,j) && (i != xn || j != yn))
                {
                    flag = 1;
                }
            }
            else
            {
                canBeMoved = false;
                return canBeMoved;
            }
        }
        if(!flag)
            canBeMoved = true;
    }
    return canBeMoved;
}
bool Board::checkKingMovement(int xp, int yp, int xn, int yn, string side) const
{
    bool canBeMoved = false;
    if(side == "White" && myBoard[xp][yp].getType() == 'K')
    {
        if(((abs(xn - xp) == 1 && abs(yn - yp) == 1) || (xn == xp && abs(yn-yp) == 1) || (abs(yn-yp) == 1 && yn == yp )) && (!isTherePieceWhite(xn,yn) && !isTherePieceBlack(xn,yn)))
            canBeMoved = true;
        else if(((xn == xp + 1 && yn == yp + 1) || (xn == xp - 1 && yn == yp + 1)) && isTherePieceBlack(xn,yn))
            canBeMoved = true;
    }
    else if(side == "Black" && myBoard[xp][yp].getType() == 'k')
    {
        if(((abs(xn - xp) == 1 && abs(yn - yp) == 1) || (xn == xp && abs(yn-yp) == 1) || (abs(yn-yp) == 1 && yn == yp )) && (!isTherePieceWhite(xn,yn) && !isTherePieceBlack(xn,yn)))
            canBeMoved = true;
        else if(((xn == xp + 1 && yn == yp - 1) || (xn == xp - 1 && yn == yp - 1)) && isTherePieceWhite(xn,yn))
            canBeMoved = true;
    }
    return canBeMoved;
}
bool Board::checkEveryMovement(int xk, int yk, string side)
{
    /*If the King is in underAttack, check every move. If one of them saves, return false*/
    if(myBoard[xk][yk].getUnderAttack() == true)
    {
        for(int i = 0; i < 8; i++)
        {
            for(int j = 0; j < 8; j++)
            {
                for(int k = 0; k < 8; k++)
                {
                    for(int m = 0; m < 8; m++)
                    {
                        if(side == "White")
                        {
                            if(checkPawnMovement(i,j,k,m,"Black"))
                                if(canPieceSave(xk,yk,i,j,k,m,side))
                                        return false;
                            if(checkRookMovement(i,j,k,m,"Black"))
                                if(canPieceSave(xk,yk,i,j,k,m,side))
                                        return false;
                            if(checkKnightMovement(i,j,k,m,"Black"))
                                if(canPieceSave(xk,yk,i,j,k,m,side))
                                        return false;
                            if(checkBishopMovement(i,j,k,m,"Black"))
                                if(canPieceSave(xk,yk,i,j,k,m,side))
                                        return false;
                            if(checkQueenMovement(i,j,k,m,"Black"))
                                if(canPieceSave(xk,yk,i,j,k,m,side))
                                        return false;
                            if(checkKingMovement(i,j,k,m,"Black"))
                                if(canPieceSave(xk,yk,i,j,k,m,side))
                                        return false;
                        }
                        else if(side == "Black")
                        {
                            if(checkPawnMovement(i,j,k,m,"White"))
                                if(canPieceSave(xk,yk,i,j,k,m,side))
                                        return false;
                            if(checkRookMovement(i,j,k,m,"White"))
                                if(canPieceSave(xk,yk,i,j,k,m,side))
                                        return false;
                            if(checkKnightMovement(i,j,k,m,"White"))
                                if(canPieceSave(xk,yk,i,j,k,m,side))
                                        return false;
                            if(checkBishopMovement(i,j,k,m,"White"))
                                if(canPieceSave(xk,yk,i,j,k,m,side))
                                        return false;
                            if(checkQueenMovement(i,j,k,m,"White"))
                                if(canPieceSave(xk,yk,i,j,k,m,side))
                                        return false;
                            if(checkKingMovement(i,j,k,m,"White"))
                                if(canPieceSave(xk,yk,i,j,k,m,side))
                                        return false;
                        }
                    }
                }
            }
        }
        return true;
    }
    return false;
} 
bool Board::checkTheCheck(int xk, int yk, string side)
{
    if(myBoard[xk][yk].getUnderAttack() == true)    /*If the King is in the underAttack*/
    {
        cout << "You are in Check! " << endl;
        if(checkEveryMovement(xk,yk,side) == true)  /*If there is no piece to save the King, ChekMate*/
        {
            isOver = true;
            return true;
        }
        else if(side == "White")
        {
            isCheckBlack = true;
            return true;
        }
        else if(side == "Black")
        {
            isCheckWhite = true;
            return true;
        }
        return true;
    }
    else    /*Else, check is false*/
    {
        if(side == "White")
            this->setIsCheckWhite(false);
        else if(side == "Black")
            this->setIsCheckBlack(false);
    }
    return false;

}
bool Board::canPieceSave(int xk, int yk, int xp, int yp, int xn, int yn, string side)
{
    Pieces temp;
    temp = myBoard[xn][yn];
    this->movePiece(xp,yp,xn,yn);   /*Making the simulational move*/
    if(this->myBoard[xk][yk].getUnderAttack() == false) /*If it saves the King from underAttack, return true*/
    {
        movePiece(xn,yn,xp,yp);
        myBoard[xn][yn] = temp;
        return true;    
    }
    else    /*Else, return false*/
    {
        movePiece(xn,yn,xp,yp);
        myBoard[xn][yn] = temp;
    }
    return false;
}
