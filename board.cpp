#include <iostream>
#include <string>
#include <vector>
#include "chess.hpp"
using namespace std;

/*NOTES*/
/*Constructor*/
Board::Board() : myBoard(8, vector<Pieces>(8))
{
    /*white pieces on the board*/
    for(int i = 0; i < 8; i++)
        myBoard[i][1] = Pieces("White",'P',i,1);
    myBoard[0][0] = Pieces("White",'R',0,0);
    myBoard[1][0] = Pieces("White",'N',1,0);
    myBoard[2][0] = Pieces("White",'B',2,0);
    myBoard[3][0] = Pieces("White",'Q',3,0);
    myBoard[4][0] = Pieces("White",'K',4,0);
    myBoard[5][0] = Pieces("White",'B',5,0);
    myBoard[6][0] = Pieces("White",'N',6,0);
    myBoard[7][0] = Pieces("White",'R',7,0);
    /*black pieces on the board*/
    for(int i = 0; i < 8; i++)
        myBoard[i][6] = Pieces("Black",'p',i,6);
    myBoard[0][7] = Pieces("Black",'r',0,7);
    myBoard[1][7] = Pieces("Black",'n',1,7);
    myBoard[2][7] = Pieces("Black",'b',2,7);
    myBoard[3][7] = Pieces("Black",'q',3,7);
    myBoard[4][7] = Pieces("Black",'k',4,7);
    myBoard[5][7] = Pieces("Black",'b',5,7);
    myBoard[6][7] = Pieces("Black",'n',6,7);
    myBoard[7][7] = Pieces("Black",'r',7,7);

    for(int i = 0; i < 8; i++)
        for(int j = 2; j < 6; j++)
            myBoard[i][j] = Pieces("Empty",'.',i,j);
}
/*General game functions*/
void Board::playChess() const
{
    Board chessBoard;
    cout << "Welcome to the Chess Game!" << endl;
    chessBoard.printBoard();
    int i = 0;
    while(/*!isOver*/ i < 6)
    {
        chessBoard.getMove("White");   /*Get move for white*/
        chessBoard.printBoard();
        chessBoard.getMove("Black");   /*Get move for black*/
        chessBoard.printBoard();
        i++;
    }
}
void Board::printBoard() const
{
    for(int j = 7; j >= 0; j--)
    {
        cout << j+1 << " |";
        for(int i = 0; i < 8; i++)
        {
            cout << " " << myBoard[i][j].getType() << " ";
        }
        cout << endl;
    }
    cout << "    " << "----------------------" << endl;
    cout << "    " << "a  b  c  d  e  f  g  h" << endl;
}
/*Bool functions to check pieces*/
bool Board::isTherePieceWhite(int x, int y) const
{
    if(myBoard[x][y].getColor() == "White")
        return 1;
    return 0;
}
bool Board::isTherePieceBlack(int x, int y) const
{
    if(myBoard[x][y].getColor() == "Black")
        return 1;
    return 0;
}
/*General movement functions*/
void Board::getMove(string side) /*Converts the string to coordinates and suggests or saves.*/
{
    /*Check the player*/
    if(side == "White")
        cout << "[White's Turn]" << endl;
    else if(side == "Black")
        cout << "[Black's Turn]" << endl;

    string input;
    cout << "Enter your move: ";
    cin >> input;

    if(input == "suggest")  /*Suggest*/
        cout << "suggested" << endl;
        //this->suggestMove();
    else if(input == "save")  /*Save to the file*/
    {
        string filename;
        cout << "Enter filename you want to save the board: ";
        getline(cin,filename);
        cout << "saved " << endl;
        //this->saveBoard(filename);
    }
    else
    {
        /*Get the move in chess code and convert*/
        int xp, yp, xn, yn;
        xp = input[0] - 97;
        yp = input[1] - 49;
        xn = input[2] - 97;
        yn = input[3] - 49;
        this->checkMove(xp,yp,xn,yn,side);  /*Send the move to the checkMove function*/
    }
}
void Board::checkMove(int xp, int yp, int xn, int yn, string side)
{
    if(yn > 8 || yn < 0 || xn > 8 || xn < 0)
        cout << "Wrong move, out of scope" << endl;
    char type;
    type = myBoard[xp][yp].getType();
    if(type == 'p' || type == 'P')
        movePawn(xp,yp,xn,yn,side);
    else if(type == 'r' || type == 'R')
        moveRook(xp,yp,xn,yn,side);
    else if(type == 'n' || type == 'N')
        moveKnight(xp,yp,xn,yn,side);
    else if(type == 'b' || type == 'B')
        moveBishop(xp,yp,xn,yn,side);
    else if(type == 'q' || type == 'Q')
        moveQueen(xp,yp,xn,yn,side);
    else if(type == 'k' || type == 'K')
        moveKing(xp,yp,xn,yn,side);
}
void Board::movePiece(int xp, int yp, int xn, int yn)
{
    myBoard[xn][yn].setTotalPoint(myBoard[xn][yn].getPoint()); /*Get the opp. piece point and decrease from total point of opp. side (if empty than dec. 0 pts)*/
    myBoard[xn][yn] = myBoard[xp][yp];  /*Move to the new coordinate*/
    myBoard[xp][yp] = Pieces("Empty",'.',xp,yp);    /*Make the old coordinate empty*/
}
/*Individual movement functions for pieces*/ /*These functions checks valid move also*/
void Board::movePawn(int xp, int yp, int xn, int yn, string side)
{
    if(side == "White")
    {
        if(yn <= yp)    /*check y-axis same or less*/
            cout << "Wrong move! 1" << endl;
        else if(isTherePieceWhite(xn,yn))   /*check isThere white piece*/
            cout << "Wrong move! 2" << endl;
        else if(yp != 1) /*if pawn is not in starting point*/
        {
            if(yn > yp + 1 || xn > xp + 1 || xn < xp - 1)   /*yn bigger than 2 or xn bigger than 1*/
                cout << "Wrong move! 3" << endl;
            else if(xn == xp && isTherePieceBlack(xn,yn))   /*if p moves direct and there is a black piece*/
                cout << "Wrong move! 4" << endl;
            else if(xn != xp && ((xn > xp + 1 && xn < xp + 2) || (xn < xp - 1 && xn > xp - 2)) && isTherePieceBlack(xn,yn)) /*Eat if there is a black piece*/
            {
                this->promotePawn(xp,yp);
                this->movePiece(xp,yp,xn,yn);
                /*this->checkCheck*/
                /*this->checkCheckMate*/
            }
            else    /*Move if do not eat*/
            {
                this->promotePawn(xp,yp);
                this->movePiece(xp,yp,xn,yn);
                /*this->checkCheck*/
                /*this->checkCheckMate*/    
            }
        }
        else if (yp == 1)
        {
            if(yn > yp + 2)   /*yn bigger than 2 or xn bigger than 1*/
                cout << "Wrong move! 5" << endl;
            else if(xn == xp && yn == yn + 2 && (isTherePieceBlack(xn,yn+1) || isTherePieceWhite(xn,yn+1)))   /*if pawn moves direct and there is a black or white piece*/
                cout << "Wrong move! 6" << endl;
            else if((xn > xp || xn < xp) && !isTherePieceBlack(xn,yn))    /*if pawn moves diagnolly and there is no black piece*/
                cout << "Wrong move! 7" << endl;
            else if(xn > xp + 1 && xn < xp + 2  && isTherePieceBlack(xn,yn))    /*make the move, eat the piece*/
            {
                this->movePiece(xp,yp,xn,yn);
                /*this->checkCheck*/
                /*this->checkCheckMate*/
            }
            else    /*make the move*/
            {
                this->movePiece(xp,yp,xn,yn);
                /*this->checkCheck*/
                /*this->checkCheckMate*/
            }
        }
    }
    else if(side == "Black")
    {
        if(yn >= yp)    /*check y-axis same or higher*/
            cout << "Wrong move! 1" << endl;
        else if(isTherePieceBlack(xn,yn))   /*check isThere white piece*/
            cout << "Wrong move! 2" << endl;
        else if(yp != 6) /*if pawn is not in starting point*/
        {
            if(yn < yp - 1 || xn > xp + 1 || xn < xp - 1)   /*yn lower than 2 or xn bigger than 1*/
                cout << "Wrong move! 3" << endl;
            else if(xn == xp && isTherePieceWhite(xn,yn))   /*if p moves direct and there is a white piece*/
                cout << "Wrong move! 4" << endl;
            else if(xn != xp && ((xn > xp + 1 && xn < xp + 2) || (xn < xp - 1 && xn > xp - 2)) && isTherePieceWhite(xn,yn)) /*Eat if there is a black piece*/
            {
                this->promotePawn(xp,yp);
                this->movePiece(xp,yp,xn,yn);
                /*this->checkCheck*/
                /*this->checkCheckMate*/
            }
            else    /*Move if do not eat*/
            {
                this->promotePawn(xp,yp);
                this->movePiece(xp,yp,xn,yn);
                /*this->checkCheck*/
                /*this->checkCheckMate*/
            }
        }
        else if (yp == 6)
        {
            if(yn < yp - 2)   /*yn lower than 2 or xn bigger than 1*/
                cout << "Wrong move! 5" << endl;
            else if(xn == xp && yn == yn - 2 && (isTherePieceBlack(xn,yn+1) || isTherePieceWhite(xn,yn+1)))   /*if pawn moves direct and there is a black or white piece*/
                cout << "Wrong move! 6" << endl;
            else if((xn > xp || xn < xp) && !isTherePieceWhite(xn,yn))    /*if pawn moves diagnolly and there is no white piece*/
                cout << "Wrong move! 7" << endl;
            else if(xn > xp + 1 && xn < xp + 2  && isTherePieceWhite(xn,yn))    /*make the move, eat the piece*/
            {
                this->movePiece(xp,yp,xn,yn);
                /*this->checkCheck*/
                /*this->checkCheckMate*/
            }
            else    /*make the move*/
            {
                this->movePiece(xp,yp,xn,yn);
                /*this->checkCheck*/
                /*this->checkCheckMate*/
            }
        }
    }
}
void Board::moveRook(int xp, int yp, int xn, int yn, string side)
{
    if(yn != yp)
    {
        int flag = 0;
        if(side == "White")
            if(isTherePieceWhite(xn,yn))
                cout << "Wrong move, white piece exist" << endl;
        else if(side == "Black")
            if(isTherePieceBlack(xn,yn))
                cout << "Wrong move, black piece exist" << endl;
        else if(xn != xp)
            cout << "Wrong move 1" << endl;
        else if(yn > yp && yn < 9 || yn > 0)
        {
            for(int i = yp; i < yn-yp; i++) /*2 - 7 = 3 , 4 , 5 , 5 , 6 , 7*/
            {
                if(isTherePieceWhite(xp,i+1) || (isTherePieceBlack(xp,i+1) && i+1 != yn)) /*If between new and old coord. there is a white or black*/
                {
                    cout << "Wrong move 2" << endl;
                    flag = 1;
                }
            }
            if(flag == 0)
            {
                this->movePiece(xp,yp,xn,yn);
                /*this->checkCheck*/
                /*this->checkCheckMate*/
            }
        }
        else if(yn < yp && yn < 9 || yn > 0)
        {
            for(int i = yp; i > yp-yn; i--) /*2 - 7 = 3 , 4 , 5 , 5 , 6 , 7*/
            {
                if(isTherePieceWhite(xp,i-1) || (isTherePieceBlack(xp,i-1) && i-1 != yn)) /*If between new and old coord. there is a white or black*/
                {
                    cout << "Wrong move 3" << endl;
                    flag = 1;
                }
            }
            if(flag == 0)
            {
                this->movePiece(xp,yp,xn,yn);
                /*this->checkCheck*/
                /*this->checkCheckMate*/
            }
        }
        else 
            cout << "Wrong move 4" << endl;
    }
    else if(xn != xp)
    {
        int flag = 0;
        if(yn != yp)
            cout << "Wrong move 1" << endl;
        else if(xn > xp && xn < 9 || xn > 0)
        {
            for(int i = xp; i < xn-xp; i++) /*2 - 7 = 2 , 3 , 4 , 5 , 6 , 7*/
            {
                if(isTherePieceWhite(i+1,yp) || (isTherePieceBlack(i+1,yp) && i+1 != xn)) /*If between new and old coord. there is a white or black*/
                {
                    cout << "Wrong move 2" << endl; 
                    flag = 1;
                }
            }
            if(flag == 0)
            {
                this->movePiece(xp,yp,xn,yn);
                /*this->checkCheck*/
                /*this->checkCheckMate*/
            }
        }
        else if(xn < xp && xn < 9 || xn > 0)
        {
            for(int i = xp; i > xp-xn; i--) /*2 - 7 = 2 , 3 , 4 , 5 , 6 , 7*/
            {
                if(isTherePieceWhite(i-1,yp) || (isTherePieceBlack(i-1,yp) && i-1 != xn)) /*If between new and old coord. there is a white or black*/
                {
                    cout << "Wrong move 3" << endl; 
                    flag = 1;
                }
            }
            if(flag == 0)
            {
                this->movePiece(xp,yp,xn,yn);
                /*this->checkCheck*/
                /*this->checkCheckMate*/
            }
        }
        else 
            cout << "Wrong move 4" << endl;
    }
}
void Board::moveKnight(int xp, int yp, int xn, int yn, string side)
{
    if(side == "White")
        if(((xn == xp + 1 && yn == yp + 2) || (xn == xp - 1 && yn == yp + 2) || 
            (xn == xp + 1 && yn == yp + 2) || (xn == xp - 1 && yn == yp - 2) || 
            (xn == xp + 2 && yn == yp + 1) || (xn == xp - 2 && yn == yp + 1) ||
            (xn == xp + 2 && yn == yp - 1) || (xn == xp - 2 && yn == yp - 1)) && !isTherePieceWhite(xn,yn))
        {
            movePiece(xp,yp,xn,yn);
            /*this->checkCheck*/
            /*this->checkCheckMate*/
        }
        else
            cout << "Wrong move" << endl;
    if(side == "Black")
        if(((xn == xp + 1 && yn == yp + 2) || (xn == xp - 1 && yn == yp + 2) || 
            (xn == xp + 1 && yn == yp - 2) || (xn == xp - 1 && yn == yp - 2) || 
            (xn == xp + 2 && yn == yp + 1) || (xn == xp - 2 && yn == yp + 1) ||
            (xn == xp + 2 && yn == yp - 1) || (xn == xp - 2 && yn == yp - 1)) && !isTherePieceBlack(xn,yn))
        {
            movePiece(xp,yp,xn,yn);
            /*this->checkCheck*/
            /*this->checkCheckMate*/
        }
        else
            cout << "Wrong move" << endl;
}
void Board::moveBishop(int xp, int yp, int xn, int yn, string side)
{
    int flag = 0;
    if(abs(xn - xp) != abs(yn - yp))
        cout << "Wrong move 1" << endl;
    else if(xn > xp && yn > yp)
    {
        for(int i = xn, j = yn; i > xp, j > yp; i--, j--)
        {
            cout << i << " " << j << endl;
            if(side == "White")
                if(isTherePieceWhite(i,j))
                {
                    cout << "Wrong move 2" << endl;
                    flag = 1;
                }
            if(side == "Black")
                if(isTherePieceBlack(i,j))
                {
                    cout << "Wrong move 2" << endl;
                    flag = 1;
                }
        }
        if(flag == 0)
            this->movePiece(xp,yp,xn,yn);
    }
    else if(xn > xp && yn < yp)
    {
        for(int i = xp, j = yn; i < xn, j < yp; i++, j++)
        {
            cout << i << " " << j << endl;
            if(side == "White")
                if(isTherePieceWhite(i,j))
                {
                    cout << "Wrong move 2" << endl;
                    flag = 1;
                }
            if(side == "Black")
                if(isTherePieceBlack(i,j))
                {
                    cout << "Wrong move 2" << endl;
                    flag = 1;
                }
        }
        if(flag == 0)
            this->movePiece(xp,yp,xn,yn);
    }
    else if(xn < xp && yn > yp)
    {
        for(int i = xp, j = yn; i > xn, j > yp; i--, j--)
        {
            cout << i << " " << j << endl;
            if(side == "White")
                if(isTherePieceWhite(i,j))
                {
                    cout << "Wrong move 2" << endl;
                    flag = 1;
                }
            if(side == "Black")
                if(isTherePieceBlack(i,j))
                {
                    cout << "Wrong move 2" << endl;
                    flag = 1;
                }
        }
        if(flag == 0)
            this->movePiece(xp,yp,xn,yn);
    }
    else if(xn < xp && yn < yp)
    {
        for(int i = xn, j = yn; i < xp, j < yp; i++, j++)
        {
            cout << i << " " << j << endl;
            if(side == "White")
                if(isTherePieceWhite(i,j))
                {
                    cout << "Wrong move 2" << endl;
                    flag = 1;
                }
            if(side == "Black")
                if(isTherePieceBlack(i,j))
                {
                    cout << "Wrong move 2" << endl;
                    flag = 1;
                }
        }
        if(flag == 0)
            this->movePiece(xp,yp,xn,yn);
    }
}
void Board::moveQueen(int xp, int yp, int xn, int yn, string side)
{
    
}
void Board::moveKing(int xp, int yp, int xn, int yn, string side)
{

}
void Board::promotePawn(int xp, int yp)
{
        if(myBoard[xp][yp].getColor() == "White" && myBoard[xp][yp].getType() == 'P')
        {
            if(yp == 7)
            {
                int i;
                char newType;
                cout << "Enter what piece you want to get (only one letter in uppercase and except K): ";  /*Ask for new type of piece*/
                cin >> newType;
                if(newType == 'K')
                    return;
                Pieces promotedPiece("White",newType,xp,yp);
                myBoard[xp][yp+1] = promotedPiece;
            }
        }
        else if(myBoard[xp][yp].getColor() == "Black" && myBoard[xp][yp].getType() == 'p')
        {
            if(yp == 0)
            {
                int i;
                char newType;
                cout << "Enter what piece you want to get (only one letter in uppercase and except k): ";  /*Ask for new type of piece*/
                cin >> newType;
                if(newType == 'k')
                    return;
                Pieces promotedPiece("Black",newType,xp,yp);
                myBoard[xp][yp-1] = promotedPiece;
            }
        }
}
/*Checking the under attack conditions*/
bool Board::attackPawn(int x, int y)
{
    if(myBoard[x][y].getColor() == "White")
    {
        if(myBoard[x+1][y+1].getColor() != "White")
            myBoard[x+1][y+1].setUnderAttack(true);
        if(myBoard[x-1][y+1].getColor() != "White")
            myBoard[x-1][y+1].setUnderAttack(true);
    }
    else if(myBoard[x][y].getColor() == "Black")
    {
        if(myBoard[x+1][y+1].getColor() != "Black")
            myBoard[x+1][y+1].setUnderAttack(true);
        if(myBoard[x-1][y+1].getColor() != "Black")
            myBoard[x-1][y+1].setUnderAttack(true);
    }
}
bool Board::attackRook(int x, int y)
{
    if(myBoard[x][y].getColor() == "White")
    {
        for(int i = 0; i < 8; i++)
        {
            if(myBoard[i][y].getColor() == "Black") /*If there is a opponent piece*/
            {
                myBoard[i][y].setUnderAttack(true);
                break;
            }
            else if(myBoard[i][y].getColor() == "White")    /*If there is a teammate piece*/
                break;
            else                                        
                myBoard[i][y].setUnderAttack(true); /*If it is an empty piece*/
        }
        for(int j = 0; j < 8; j++)
        {
            if(myBoard[x][j].getColor() == "Black") /*If there is a opponent piece*/
            {
                myBoard[x][j].setUnderAttack(true);
                break;
            }
            else if(myBoard[x][j].getColor() == "White")    /*If there is a teammate piece*/
                break;
            else                                        
                myBoard[x][j].setUnderAttack(true); /*If it is an empty piece*/
        }
    }
    else if(myBoard[x][y].getColor() == "Black")
    {
        for(int i = 0; i < 8; i++)
        {
            if(myBoard[i][y].getColor() == "White") /*If there is a opponent piece*/
            {
                myBoard[i][y].setUnderAttack(true);
                break;
            }
            else if(myBoard[i][y].getColor() == "Black")    /*If there is a teammate piece*/
                break;
            else                                        
                myBoard[i][y].setUnderAttack(true); /*If it is an empty piece*/
        }
        for(int j = 0; j < 8; j++)
        {
            if(myBoard[x][j].getColor() == "White") /*If there is a opponent piece*/
            {
                myBoard[x][j].setUnderAttack(true);
                break;
            }
            else if(myBoard[x][j].getColor() == "Black")    /*If there is a teammate piece*/
                break;
            else                                        
                myBoard[x][j].setUnderAttack(true); /*If it is an empty piece*/
        }
    }
}

bool Board::attackKnight(int x, int y)
{
}

bool Board::attakBishop(int x, int y)
{
}

bool Board::attackQueen(int x, int y)
{
}

bool Board::attackKing(int x, int y)
{
}
