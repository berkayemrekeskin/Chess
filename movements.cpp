#include <iostream>
#include <string>
#include <vector>
#include "board.hpp"
#include "pieces.hpp"

/*-------------------------------MOVEMENT FUNCTIONS-------------------------------*/
/*Created these functions to move the pieces, every function includes it's valid moves*/

void Board::movePiece(int xp, int yp, int xn, int yn)
{
    myBoard[xn][yn] = myBoard[xp][yp];  /*Move to the new coordinate*/
    myBoard[xp][yp] = Pieces("Empty",'.',xp,yp);  /*Make the old coordinate to an empty piece*/
    overallGoodnessScore(); /*Checking and setting the scores*/
} 
bool Board::movePawn(int xp, int yp, int xn, int yn, string side)
{
    bool canBeMoved = false;
    if(side == "White" && myBoard[xp][yp].getType() == 'P')
    {
        if(yn <= yp)  /*If piece is white, it's only increasing in y-axis*/
        {
            cout << "Wrong move!" << endl;
            this->getMove(side);
        }
        else if(isTherePieceWhite(xn,yn))   /*If is there a white piece*/
        {
            cout << "Wrong move!" << endl;
            this->getMove(side);
        }
        else if(yp != 1) /*If pawn is not in starting point*/
        {
            if(yn != yp + 1 || xn > xp + 1 || xn < xp - 1)   /*If yn bigger than yp+2 or xn bigger than xp+1 || xp-1*/
            {
                cout << "Wrong move!" << endl;
                this->getMove(side);
            }
            else if(xn == xp && isTherePieceBlack(xn,yn))   /*If p moves direct and there is a black piece*/
            {
                cout << "Wrong move!" << endl;
                this->getMove(side);
            }
            else if((yn == yp+1 && (xn == xp+1 || xn == xp - 1)) && !isTherePieceBlack(xn,yn))
            {
                cout << "Wrong move!" << endl;
                this->getMove(side);
            }
            else if((xn == xp + 1 || xn == xp - 1) && isTherePieceBlack(xn,yn)) /*Eat if there is a black piece*/
            {
                this->promotePawn(xp,yp);
                this->movePiece(xp,yp,xn,yn);
                canBeMoved = true;
            }
            else
            {
                this->promotePawn(xp,yp);
                this->movePiece(xp,yp,xn,yn);
                canBeMoved = true;
            }
        }
        else if (yp == 1)
        {
            if(yn > yp + 2)   /*yn bigger than 2 or xn bigger than 1*/
            {
                cout << "Wrong move!" << endl;
                this->getMove(side);
            }
            else if(xn == xp && yn == yn + 2 && (isTherePieceBlack(xn,yn+1) || isTherePieceWhite(xn,yn+1)))   /*if pawn moves direct and there is a black or white piece*/
            {
                cout << "Wrong move!" << endl;
                this->getMove(side);
            }
            else if((xn == xp + 1 || xn == xp - 1) && !isTherePieceBlack(xn,yn))    /*if pawn moves diagnolly and there is no black piece*/
            {
                cout << "Wrong move!" << endl;
                this->getMove(side);
            }
            else if((xn == xp + 1 || xn == xp - 1) && isTherePieceBlack(xn,yn)) /*Eat if there is a black piece*/
            {
                this->movePiece(xp,yp,xn,yn);
                canBeMoved = true;
            }
            else
            {
                this->movePiece(xp,yp,xn,yn);
                canBeMoved = true;
            }
        }
    }
    else if(side == "Black" && myBoard[xp][yp].getType() == 'p')
    {
        if(yn >= yp)    /*check y-axis same or higher*/
        {
            cout << "Wrong move!" << endl;
            this->getMove(side);
        }
        else if(isTherePieceBlack(xn,yn))   /*check isThere white piece*/
        {
            cout << "Wrong move!" << endl;
            this->getMove(side);
        }
        else if(yp != 6) /*if pawn is not in starting point*/
        {
            if(yn < yp - 1 || xn > xp + 1 || xn < xp - 1)   /*yn lower than yp-2 or xn bigger than 1*/
            {
                cout << "Wrong move!" << endl;
                this->getMove(side);
            }
            else if(xn == xp && isTherePieceWhite(xn,yn))   /*if p moves direct and there is a white piece*/
            {
                cout << "Wrong move!" << endl;
                this->getMove(side);
            }
            else if((yn == yp-1 && (xn == xp+1 || xn == xp - 1)) && !isTherePieceWhite(xn,yn))
            {
                cout << "Wrong move!" << endl;
                this->getMove(side);
            }
            else if((xn == xp + 1 || xn == xp - 1) && isTherePieceWhite(xn,yn)) /*Eat if there is a black piece*/
            {
                this->promotePawn(xp,yp);
                this->movePiece(xp,yp,xn,yn);
                canBeMoved = true;
            }
            else
            {
                this->promotePawn(xp,yp);
                this->movePiece(xp,yp,xn,yn);
                canBeMoved = true;
            }  
        }
        else if (yp == 6) /*Starting conditions*/
        {
            if(yn < yp - 2 || xn > xp + 1 || xn < xp - 1)   /*yn lower than 2 or xn bigger than 1*/
            {
                cout << "Wrong move!" << endl;
                this->getMove(side);
            }
            else if(xn == xp && yn == yp - 2 && (isTherePieceBlack(xn,yn+1) || isTherePieceWhite(xn,yn+1)))   /*if pawn moves direct and there is a black or white piece*/
            {
                cout << "Wrong move!" << endl;
                this->getMove(side);
            }
            else if((xn > xp || xn < xp) && !isTherePieceWhite(xn,yn))    /*if pawn moves diagnolly and there is no white piece*/
            {
                cout << "Wrong move!" << endl;
                this->getMove(side);
            }
            else if(xn != xp && ((xn > xp + 1 && xn < xp + 2) || (xn < xp - 1 && xn > xp - 2)) && isTherePieceWhite(xn,yn)) /*Eat if there is a black piece*/
            {
                this->movePiece(xp,yp,xn,yn);
                canBeMoved = true;
            }
            else
            {
                this->movePiece(xp,yp,xn,yn);
                canBeMoved = true;
            }
        }
    }
    else
    {
        cout << "Wrong move!" << endl;
        this->getMove(side);
    }

    return canBeMoved;
}
bool Board::moveRook(int xp, int yp, int xn, int yn, string side)
{
   bool canBeMoved = false;
    /*If xn,yn holds a friend piece*/
    if(side == "White" && myBoard[xp][yp].getType() == 'R' || myBoard[xp][yp].getType() == 'Q')
    {
        if(isTherePieceWhite(xn,yn))
        {
            cout << "Wrong move!" << endl;
            this->getMove(side);
        }
    }
    else if(side == "Black" && myBoard[xp][yp].getType() == 'r' || myBoard[xp][yp].getType() == 'q')
    {
        if(isTherePieceBlack(xn,yn))
        {
            cout << "Wrong move!" << endl;
            this->getMove(side);
        }
    }
    
    /*Two conditions for Rook = xn != xp and yn != yp*/
    if(yn != yp)
    {
        bool flag = false;
        if(xn != xp) /*Must equal*/
        {
            cout << "Wrong move!" << endl;
            this->getMove(side);
        }

        if(side == "White" && myBoard[xp][yp].getType() == 'R' || myBoard[xp][yp].getType() == 'Q')
        {
            if(yn > yp && (yn < 8 || yn >= 0))
            {
                for(int i = yp+1; i < yn; i++)
                {
                    if(isTherePieceWhite(xp,i) || isTherePieceBlack(xp,i))
                    {
                        cout << "Wrong move!" << endl;
                        flag = 1;
                    }
                }
                if(flag)
                    this->getMove(side);
                else
                {
                    canBeMoved = true;
                    this->movePiece(xp,yp,xn,yn);
                }
            }
            else if(yn < yp && (yn < 8 || yn >= 0))
            {
                for(int i = yp-1; i > yn; i--) /*2 - 7 = 3 , 4 , 5 , 5 , 6 , 7*/
                {
                    if(isTherePieceWhite(xp,i) || isTherePieceBlack(xp,i))
                    {
                        cout << "Wrong move!" << endl;
                        flag = 1;
                    }
                }
                if(flag)
                    this->getMove(side);
                else
                {
                    canBeMoved = true;
                    this->movePiece(xp,yp,xn,yn);
                }
            }
            else
            {
                cout << "Wrong move!" << endl;
                this->getMove(side);
            }

        }
        else if(side == "Black" && myBoard[xp][yp].getType() == 'r' || myBoard[xp][yp].getType() == 'q')
        {
            if(yn > yp && (yn < 8 || yn >= 0))
            {
                for(int i = yp+1; i < yn; i++)
                {
                    if(isTherePieceWhite(xp,i) || isTherePieceBlack(xp,i))
                    {
                        cout << "Wrong move!" << endl;
                        flag = 1;
                    }
                }
                if(flag)
                    this->getMove(side);
                else
                {
                    canBeMoved = true;
                    this->movePiece(xp,yp,xn,yn);
                }
            }
            else if(yn < yp && (yn < 8 || yn >= 0))
            {
                for(int i = yp-1; i > yn; i--) /*2 - 7 = 3 , 4 , 5 , 5 , 6 , 7*/
                {
                    if(isTherePieceWhite(xp,i) || isTherePieceBlack(xp,i))
                    {
                        cout << "Wrong move!" << endl;
                        flag = 1;
                    }
                }
                if(flag)
                    this->getMove(side);
                else
                {
                    canBeMoved = true;
                    this->movePiece(xp,yp,xn,yn);
                }
            }
            else
            {
                cout << "Wrong move!" << endl;
                this->getMove(side);
            }
        }
        else
        {
            cout << "Wrong move!" << endl;
            this->getMove(side);
        }
    }
    else if(xn != xp)
    {
        bool flag = false;
        if(yn != yp)
        {    
            cout << "Wrong move!" << endl;
            this->getMove(side);
        }
        if(side == "White" && myBoard[xp][yp].getType() == 'R' || myBoard[xp][yp].getType() == 'Q')
        {
            if(xn > xp && (xn < 8 || xn >= 0))
            {
                for(int i = xp+1; i < xn; i++)
                {
                    if(isTherePieceWhite(i,yp) || isTherePieceBlack(i,yp))
                    {
                        cout << "Wrong move!" << endl;
                        flag = 1;
                    }
                }
                if(flag)
                    this->getMove(side);
                else
                {
                    canBeMoved = true;
                    this->movePiece(xp,yp,xn,yn);
                }
            }
            else if(xn < xp && (xn < 8 || xn >= 0))
            {
                for(int i = xp-1; i > xn; i--)
                {
                    if(isTherePieceWhite(i,yp) || isTherePieceBlack(i,yp))
                    {
                        cout << "Wrong move!" << endl;
                        flag = 1;
                    }
                }
                if(flag)
                    this->getMove(side);
                else
                {
                    canBeMoved = true;
                    this->movePiece(xp,yp,xn,yn);
                }
            }
            else
            {
                cout << "Wrong move!" << endl;
                this->getMove(side);
            }
        }
        else if(side == "Black" && myBoard[xp][yp].getType() == 'r' || myBoard[xp][yp].getType() == 'q')
        {
            if(xn > xp && (xn < 8 || xn >= 0))
            {
                for(int i = xp+1; i < xn; i++)
                {
                    if(isTherePieceWhite(i,yp) || isTherePieceBlack(i,yp))
                    {
                        cout << "Wrong move!" << endl;
                        flag = 1;
                    }
                }
                if(flag)
                    this->getMove(side);
                else
                {
                    canBeMoved = true;
                    this->movePiece(xp,yp,xn,yn);
                }
            }
            else if(xn < xp && (xn < 8 || xn >= 0))
            {
                for(int i = xp-1; i > xn; i--)
                {
                    if(isTherePieceWhite(i,yp) || isTherePieceBlack(i,yp))
                    {
                        cout << "Wrong move!" << endl;
                        flag = 1;
                    }
                }
                if(flag)
                    this->getMove(side);
                else
                {
                    canBeMoved = true;
                    this->movePiece(xp,yp,xn,yn);
                }
            }
            else
            {
                cout << "Wrong move!" << endl;
                this->getMove(side);
            }
        }
        else
        {
            cout << "Wrong move!" << endl;
            this->getMove(side);
        }
    }
    return canBeMoved;
}
bool Board::moveKnight(int xp, int yp, int xn, int yn, string side)
{
    bool canBeMoved = false;
    if(side == "White" && myBoard[xp][yp].getType() == 'N')
    {
        if(((xn == xp + 1 && yn == yp + 2) || (xn == xp - 1 && yn == yp + 2) || 
            (xn == xp + 1 && yn == yp - 2) || (xn == xp - 1 && yn == yp - 2) || 
            (xn == xp + 2 && yn == yp + 1) || (xn == xp - 2 && yn == yp + 1) ||
            (xn == xp + 2 && yn == yp - 1) || (xn == xp - 2 && yn == yp - 1)) && !isTherePieceWhite(xn,yn))
        {
            movePiece(xp,yp,xn,yn);
            canBeMoved = true;
        }
        else
        {
            cout << "Wrong move!" << endl;
            this->getMove(side);
        }
    }
    else if(side == "Black" && myBoard[xp][yp].getType() == 'n')
    {
        if(((xn == xp + 1 && yn == yp + 2) || (xn == xp - 1 && yn == yp + 2) || 
            (xn == xp + 1 && yn == yp - 2) || (xn == xp - 1 && yn == yp - 2) || 
            (xn == xp + 2 && yn == yp + 1) || (xn == xp - 2 && yn == yp + 1) ||
            (xn == xp + 2 && yn == yp - 1) || (xn == xp - 2 && yn == yp - 1)) && !isTherePieceBlack(xn,yn))
        {
            movePiece(xp,yp,xn,yn);
            canBeMoved = true;
        }
        else
        {
            cout << "Wrong move!" << endl;
            this->getMove(side);
        }
    }
    else    /*If piece is not Knight*/
    {
        cout << "Wrong move!" << endl;
        this->getMove(side);
    }
    return canBeMoved;
}
bool Board::moveBishop(int xp, int yp, int xn, int yn, string side)
{
    bool canBeMoved = false;
    bool flag = 0;
    if(abs(xn - xp) != abs(yn - yp))
    {
        cout << "Wrong move !" << endl;
        this->getMove(side);
    }
    else if(xn > xp && yn > yp)  /*c1g5 - 2-0 - 6-4*/
    {
        for(int i = xn, j = yn; i > xp, j > yp; i--, j--)
        {
            if(side == "White" && myBoard[xp][yp].getType() == 'B' || myBoard[xp][yp].getType() == 'Q')
            {
                if(isTherePieceWhite(i,j))
                {
                    cout << "Wrong move!" << endl;
                    flag = 1;
                }
                else if(isTherePieceBlack(i,j) && (i != xn || j != yn))
                {
                    cout << "Wrong move!" << endl;
                    flag = 1;
                }
            }
            else if(side == "Black" && myBoard[xp][yp].getType() == 'b' || myBoard[xp][yp].getType() == 'q')
            {
                if(isTherePieceBlack(i,j))
                {
                    cout << "Wrong move!" << endl;
                    flag = 1;
                }
                else if(isTherePieceWhite(i,j) && (i != xn || j != yn))
                {
                    cout << "Wrong move!" << endl;
                    flag = 1;
                }
            }
            else
            {
                cout << "Wrong move!" << endl;
                this->getMove(side);
            }
        }
        if(flag)
            this->getMove(side);
        else
        {
            canBeMoved = true;
            this->movePiece(xp,yp,xn,yn);
        }
    }
    else if(xn > xp && yn < yp) /*D8H4 - 37-73 -- 73 64 55 46 37*/
    {
        for(int i = xn, j = yn; i > xp, j < yp; i--, j++)
        {
            if(side == "White" && myBoard[xp][yp].getType() == 'B' || myBoard[xp][yp].getType() == 'Q')
            {
                if(isTherePieceWhite(i,j))
                {
                    cout << "Wrong move!" << endl;
                    flag = 1;
                }
                else if(isTherePieceBlack(i,j) && (i != xn || j != yn))
                {
                    cout << "Wrong move!" << endl;
                    flag = 1;
                }
            }
            else if(side == "Black" && myBoard[xp][yp].getType() == 'b' || myBoard[xp][yp].getType() == 'q')
            {
                if(isTherePieceBlack(i,j))
                {
                    cout << "Wrong move!" << endl;
                    flag = 1;
                }
                else if(isTherePieceWhite(i,j) && (i != xn || j != yn))
                {
                    cout << "Wrong move!" << endl;
                    flag = 1;
                }
            }
            else
            {
                cout << "Wrong move!" << endl;
                this->getMove(side);
            }
        }
        if(flag)
            this->getMove(side);
        else
        {
            canBeMoved = true;
            this->movePiece(xp,yp,xn,yn);
        }
    }
    else if(xn < xp && yn > yp)
    {
        for(int i = xn, j = yn; i < xp, j > yp; i++, j--)
        {
            if(side == "White" && myBoard[xp][yp].getType() == 'B' || myBoard[xp][yp].getType() == 'Q')
            {
                if(isTherePieceWhite(i,j))
                {
                    cout << "Wrong move!" << endl;
                    flag = 1;
                }
                else if(isTherePieceBlack(i,j) && (i != xn || j != yn))
                {
                    cout << "Wrong move!" << endl;
                    flag = 1;
                }
            }
            else if(side == "Black" && myBoard[xp][yp].getType() == 'b' || myBoard[xp][yp].getType() == 'q')
            {
                if(isTherePieceBlack(i,j))
                {
                    cout << "Wrong move!" << endl;
                    flag = 1;
                }
                else if(isTherePieceWhite(i,j) && (i != xn || j != yn))
                {
                    cout << "Wrong move!" << endl;
                    flag = 1;
                }
            }
            else
            {
                cout << "Wrong move!" << endl;
                this->getMove(side);
            }
        }
        if(flag)
            this->getMove(side);
        else
        {
            canBeMoved = true;
            this->movePiece(xp,yp,xn,yn);
        }
    }
    else if(xn < xp && yn < yp)
    {
        for(int i = xn, j = yn; i < xp, j < yp; i++, j++)
        {
            if(side == "White" && myBoard[xp][yp].getType() == 'B' || myBoard[xp][yp].getType() == 'Q')
            {
                if(isTherePieceWhite(i,j))
                {
                    cout << "Wrong move!" << endl;
                    flag = 1;
                }
                else if(isTherePieceBlack(i,j) && (i != xn || j != yn))
                {
                    cout << "Wrong move!" << endl;
                    flag = 1;
                }
            }
            else if(side == "Black" && myBoard[xp][yp].getType() == 'b' || myBoard[xp][yp].getType() == 'q')
            {
                if(isTherePieceBlack(i,j))
                {
                    cout << "Wrong move!" << endl;
                    flag = 1;
                }
            }
            else
            {
                cout << "Wrong move!" << endl;
                this->getMove(side);
            }
        }
        if(flag)
            this->getMove(side);
        else
        {
            canBeMoved = true;
            this->movePiece(xp,yp,xn,yn);
        }
    }
    else
    {
        cout << "Wrong move!" << endl;
        this->getMove(side);
    }
    return canBeMoved;
}
bool Board::moveQueen(int xp, int yp, int xn, int yn, string side)
{
    bool canBeMoved = false;
    if(side == "White" )
    {
        if(myBoard[xp][yp].getType() == 'Q')
        {
            if(xp != xn && yn != yp)    /*If the movement is diagonal*/
            {
                canBeMoved = true;
                moveBishop(xp,yp,xn,yn,side);
            }
            else if((xp == xn && yn != yp) || (xp != xn && yn == yp)) /*If the movements is vertical or horizontal*/
            {
                canBeMoved = true;
                moveRook(xp,yp,xn,yn,side);
            }
        }
        else /*If the selected piece is not Q*/
        {
            cout << "Wrong move!" << endl;
            this->getMove(side);
        }
    }
    else if(side == "Black")
    {
        if(myBoard[xp][yp].getType() == 'q')
        {
            if(xp != xn && yn != yp) /*If the movement is diagonal*/
            {
                canBeMoved = true;
                moveBishop(xp,yp,xn,yn,side);
            }
            else if((xp == xn && yn != yp) || (xp != xn && yn == yp)) /*If the movement is vertical or horizontal*/
            {
                canBeMoved = true;
                moveRook(xp,yp,xn,yn,side);
            }
        }
        else /*If the selected piece is not q*/
        {
            cout << "Wrong move!" << endl;
            this->getMove(side);
        }
    }
    return canBeMoved;
}
bool Board::moveKing(int xp, int yp, int xn, int yn, string side)
{
    bool canBeMoved = false;

    if(side == "White" && myBoard[xp][yp].getType() == 'K')
    {
        if(abs(xn - xp) > 1 || abs(yn - yp) > 1)    /*If movement is above the 1 piece*/
        {
            cout << "Wrong move!" << endl;
            this->getMove(side);
        }
        else if(isTherePieceWhite(xn,yn))   /*If is there a teammate*/
        {
             cout << "Wrong move!" << endl;
            this->getMove(side);
        }
        else if(!((xn == xp + 1 && yn == yp + 1) || (xn == xp - 1 && yn == yp + 1)) && isTherePieceBlack(xn,yn))    /*If there is a opponent piece which is not in the eating point*/
        {
             cout << "Wrong move!" << endl;
            this->getMove(side);
        }
        else
        {
            canBeMoved = true;
            this->movePiece(xp,yp,xn,yn);
        }
            
    }
    else if(side == "Black" && myBoard[xp][yp].getType() == 'k')
    {
        if(abs(xn - xp) > 1 || abs(yn - yp) > 1)  /*If movement is above the 1 piece*/
        {
             cout << "Wrong move!" << endl;
            this->getMove(side);
        }
        else if(isTherePieceBlack(xn,yn)) /*If is there a teammate*/
        {
             cout << "Wrong move!" << endl;
            this->getMove(side);
        }
        else if(!((xn == xp + 1 && yn == yp - 1) || (xn == xp - 1 && yn == yp - 1)) && isTherePieceWhite(xn,yn)) /*If there is a opponent piece which is not in the eating point*/
        {
             cout << "Wrong move!" << endl;
            this->getMove(side);
        }
        else
        {
            canBeMoved = true;
            this->movePiece(xp,yp,xn,yn);
        }
    }
    return canBeMoved;
}
