#include <iostream>
#include <string>
#include <vector>
#include "chess.hpp"
using namespace std;

/*NOTES*/
/* Display appropriate error messages and allow the user to correct their input.*/
/*The next move function should return the board that produces best score*/
/*BISHOP MOVE SIK GIBI DUZELT ONU*/
/*CHECKMATE SEG VERIYOR DUZELT ONU*/

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
        chessBoard.getMove("White");  /*Get move for white*/
        chessBoard.checkDanger();
        chessBoard.printBoard();
        chessBoard.getMove("Black");   /*Get move for black*/
        chessBoard.checkDanger();
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
        cout << "Test1" << endl;
        this->checkValidMove(side,input,xp,yp,xn,yn);
        cout << "Test2" << endl;
        this->checkMove(xp,yp,xn,yn);  /*Send the move to the checkMove function*/
    }
}
void Board::checkMove(int xp, int yp, int xn, int yn)
{
    if(yn > 8 || yn < 0 || xn > 8 || xn < 0)
        cout << "Wrong move, out of scope" << endl;
    char type;
    type = myBoard[xp][yp].getType();
    if(type == 'p' || type == 'P')
        movePawn(xp,yp,xn,yn);
    else if(type == 'r' || type == 'R')
        moveRook(xp,yp,xn,yn);
    else if(type == 'n' || type == 'N')
        moveKnight(xp,yp,xn,yn);
    else if(type == 'b' || type == 'B')
        moveBishop(xp,yp,xn,yn);
    else if(type == 'q' || type == 'Q')
        moveQueen(xp,yp,xn,yn);
    else if(type == 'k' || type == 'K')
        moveKing(xp,yp,xn,yn);
}
void Board::movePiece(int xp, int yp, int xn, int yn)
{
    myBoard[xn][yn] = myBoard[xp][yp];  /*Move to the new coordinate*/
    myBoard[xp][yp] = Pieces("Empty",'.',xp,yp);    /*Make the old coordinate empty*/
    overallGoodnessScore();
}
void Board::checkValidMove(string side, string &input,int &xp, int &yp, int &xn, int &yn)
{
    if(side == "White")
        {
            int x, y;
            for(int i = 0; i < 8; i++)
            {
                for(int j = 0; j < 8; j++)
                {
                    if(myBoard[i][j].getType() == 'k')
                    {
                        x = i;
                        y = j;
                        break;
                    }
                }
            }
            cout << x << " " << y << endl;
            cout << myBoard[x][y].getUnderAttack() << endl;
            cout << "Test3" << endl;
            if(myBoard[x][y].getUnderAttack())
            {
                cout << "Test4" << endl;
                cout << "You are in Check!" << endl;
                cout << "Enter your move: ";
                cin >> input;
                xp = input[0] - 97;
                yp = input[1] - 49;
                xn = input[2] - 97;
                yn = input[3] - 49;
                while(!checkKingMovement(xp,yp,xn,yn))
                {
                    cout << "You entered wrong move!" << endl;
                    cout << "Enter your move: ";
                    cin >> input; 
                }
            }
        }
        else if(side == "Black")
        {
            int x, y;
            for(int i = 0; i < 8; i++)
            {
                for(int j = 0; j < 8; j++)
                {
                    if(myBoard[i][j].getType() == 'K')
                    {
                        x = i;
                        y = j;
                        break;
                    }
                }
            }
            if(checkTheCheck(x,y))
            {
                if(checkTheCheckMate(x,y))
                {
                    cout << "GAME OVER!!!"; /*BURAYA BAK*/
                    return ; 
                }
                else
                {   
                    cout << "You are in Check!" << endl;
                    cout << "Enter your move: ";
                        cin >> input;
                    while(input[0] != x || input[1] != y)
                    {
                        cout << "You entered wrong move!" << endl;
                        cout << "Enter your move: ";
                        cin >> input; 
                    }
                    xp = input[0] - 97;
                    yp = input[1] - 49;
                    xn = input[2] - 97;
                    yn = input[3] - 49;
                }
            }
        }
}
/*Individual movement functions for pieces*/ /*These functions checks valid move also*/
void Board::movePawn(int xp, int yp, int xn, int yn)
{
    if(myBoard[xp][yp].getColor() == "White")
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
            }
            else    /*Move if do not eat*/
            {
                this->promotePawn(xp,yp);
                this->movePiece(xp,yp,xn,yn);
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
                this->movePiece(xp,yp,xn,yn);
            else    /*make the move*/
                this->movePiece(xp,yp,xn,yn);
        }
    }
    else if(myBoard[xp][yp].getColor() == "Black")
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
            }
            else
            {
                this->promotePawn(xp,yp);
                this->movePiece(xp,yp,xn,yn);
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
                this->movePiece(xp,yp,xn,yn);
            else    /*make the move*/
                this->movePiece(xp,yp,xn,yn);
        }
    }
}
void Board::moveRook(int xp, int yp, int xn, int yn)
{
    if(myBoard[xp][yp].getColor() == "White")
        if(isTherePieceWhite(xn,yn))
            cout << "Wrong move, white piece exist" << endl;
    else if(myBoard[xp][yp].getColor() == "Black")
        if(isTherePieceBlack(xn,yn))
            cout << "Wrong move, black piece exist" << endl;
    if(yn != yp)
    {
        int flag = 0;
        if(xn != xp)
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
                this->movePiece(xp,yp,xn,yn);
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
                this->movePiece(xp,yp,xn,yn);
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
                this->movePiece(xp,yp,xn,yn);
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
                this->movePiece(xp,yp,xn,yn);
        }
        else 
            cout << "Wrong move 4" << endl;
    }
}
void Board::moveKnight(int xp, int yp, int xn, int yn)
{
    if(myBoard[xp][yp].getColor() == "White")
        if(((xn == xp + 1 && yn == yp + 2) || (xn == xp - 1 && yn == yp + 2) || 
            (xn == xp + 1 && yn == yp - 2) || (xn == xp - 1 && yn == yp - 2) || 
            (xn == xp + 2 && yn == yp + 1) || (xn == xp - 2 && yn == yp + 1) ||
            (xn == xp + 2 && yn == yp - 1) || (xn == xp - 2 && yn == yp - 1)) && !isTherePieceWhite(xn,yn))
        {
            movePiece(xp,yp,xn,yn);
        }
        else
            cout << "Wrong move" << endl;
    if(myBoard[xp][yp].getColor() == "Black")
        if(((xn == xp + 1 && yn == yp + 2) || (xn == xp - 1 && yn == yp + 2) || 
            (xn == xp + 1 && yn == yp - 2) || (xn == xp - 1 && yn == yp - 2) || 
            (xn == xp + 2 && yn == yp + 1) || (xn == xp - 2 && yn == yp + 1) ||
            (xn == xp + 2 && yn == yp - 1) || (xn == xp - 2 && yn == yp - 1)) && !isTherePieceBlack(xn,yn))
        {
            movePiece(xp,yp,xn,yn);
        }
        else
            cout << "Wrong move" << endl;
}
void Board::moveBishop(int xp, int yp, int xn, int yn) /*bidaha bak buna*/
{
    int flag = 0;
    if(abs(xn - xp) != abs(yn - yp))
        cout << "Wrong move 1 - B" << endl;
    if(xn > xp && yn > yp)
    {
        for(int i = xn, j = yn; i > xp, j > yp; i--, j--)
        {
            cout << i << " " << j << endl;
            if(myBoard[xp][yp].getColor() == "White")
                if(isTherePieceWhite(i,j))
                {
                    cout << "Wrong move 2" << endl;
                    flag = 1;
                }
            if(myBoard[xp][yp].getColor() == "Black")
                if(isTherePieceBlack(i,j))
                {
                    cout << "Wrong move 3" << endl;
                    flag = 1;
                }
        }
        if(flag == 0)
            this->movePiece(xp,yp,xn,yn);
    }
    if(xn > xp && yn < yp)
    {
        for(int i = xp, j = yn; i < xn, j < yp; i++, j++)
        {
            cout << i << " " << j << endl;
            if(myBoard[xp][yp].getColor() == "White")
                if(isTherePieceWhite(i,j))
                {
                    cout << "Wrong move 4" << endl;
                    flag = 1;
                }
            if(myBoard[xp][yp].getColor() == "Black")
                if(isTherePieceBlack(i,j))
                {
                    cout << "Wrong move 5" << endl;
                    flag = 1;
                }
        }
        if(flag == 0)
            this->movePiece(xp,yp,xn,yn);
    }
    if(xn < xp && yn > yp)
    {
        for(int i = xn, j = yn; i < xp, j > yp; i++, j--)
        {
            cout << i << " " << j << endl;
            if(myBoard[xp][yp].getColor() == "White")
                if(isTherePieceWhite(i,j))
                {
                    cout << "Wrong move 6" << endl;
                    flag = 1;
                }
            if(myBoard[xp][yp].getColor() == "Black")
                if(isTherePieceBlack(i,j))
                {
                    cout << "Wrong move 7" << endl;
                    flag = 1;
                }
        }
        if(flag == 0)
            this->movePiece(xp,yp,xn,yn);
    }
    if(xn < xp && yn < yp)
    {
        for(int i = xn, j = yn; i < xp, j < yp; i++, j++)
        {
            cout << i << " " << j << endl;
            if(myBoard[xp][yp].getColor() == "White")
                if(isTherePieceWhite(i,j))
                {
                    cout << "Wrong move 8" << endl;
                    flag = 1;
                }
            if(myBoard[xp][yp].getColor() == "Black")
                if(isTherePieceBlack(i,j))
                {
                    cout << "Wrong move 9" << endl;
                    flag = 1;
                }
        }
        if(flag == 0)
            this->movePiece(xp,yp,xn,yn);
    }
}
void Board::moveQueen(int xp, int yp, int xn, int yn)
{
    if(xp != xn && yn != yp)    /*If it is a bishop move*/
        moveBishop(xp,yp,xn,yn);
    else if((xp == xn && yn != yp) || (xp != xn && yn == yp))
        moveRook(xp,yp,xn,yn);
}
void Board::moveKing(int xp, int yp, int xn, int yn)
{
    if(myBoard[xp][yp].getColor() == "White")
    {
        if(abs(xn - xp) > 1 || abs(yn - yp) > 1)
            cout << "Wrong move 1" << endl;
        else if(isTherePieceWhite(xn,yn))
            cout << "Wrong move 2" << endl;
        else if(!((xn == xp + 1 && yn == yp + 1) || (xn == xp - 1 && yn == yp + 1)) && isTherePieceBlack(xn,yn))
            cout << "Wrong move 3" << endl;
        else
        {
            this->movePiece(xp,yp,xn,yn);
        }
            
    }
    else if(myBoard[xp][yp].getColor() == "Black")
    {
        if(abs(xn - xp) > 1 || abs(yn - yp) > 1)
            cout << "Wrong move 1" << endl;
        else if(isTherePieceBlack(xn,yn))
            cout << "Wrong move 2" << endl;
        else if(!((xn == xp + 1 && yn == yp - 1) || (xn == xp - 1 && yn == yp - 1)) && isTherePieceWhite(xn,yn))
            cout << "Wrong move 3" << endl;
        else
        {
            this->movePiece(xp,yp,xn,yn);
        }
    }
}

/*Score function to calculate overall goodness score*/
void Board::checkDanger()
{
    /*Resetting the board*/
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++)
            myBoard[i][j].setUnderAttack(false);
    
    /*Checking again*/
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(myBoard[i][j].getType() == 'P' || myBoard[i][j].getType() == 'p')
                threatOfPawn(i,j);
            else if(myBoard[i][j].getType() == 'R' || myBoard[i][j].getType() == 'r')
                threatOfRook(i,j);
            else if(myBoard[i][j].getType() == 'N' || myBoard[i][j].getType() == 'n')
                threatOfKnight(i,j);
            else if(myBoard[i][j].getType() == 'B' || myBoard[i][j].getType() == 'b')
                threatOfBishop(i,j);
            else if(myBoard[i][j].getType() == 'Q' || myBoard[i][j].getType() == 'q')
                threatOfQueen(i,j);
            else if(myBoard[i][j].getType() == 'K' || myBoard[i][j].getType() == 'K')
                threatOfKing(i,j);
        }
    }
}
void Board::overallGoodnessScore()
{
    /*Setting scores to 39 at first*/
    double whiteTotalScore = 139.0;
    double blackTotalScore = 139.0;
    checkDanger();
    /*Searching every piece for underAttack*/
    cout << endl;
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(myBoard[i][j].getColor() == "White" && myBoard[i][j].getUnderAttack())
            {
                whiteTotalScore -= 0.5 * myBoard[i][j].getPoint();
            }
            else if(myBoard[i][j].getColor() == "Black" && myBoard[i][j].getUnderAttack())
            {
                blackTotalScore -= 0.5 * myBoard[i][j].getPoint();
            }
            cout << myBoard[j][7-i].getUnderAttack() << "  ";
        }
        cout << endl;
    }
    cout << "White Score: " << whiteTotalScore << endl;
    cout << "Black Score: " << blackTotalScore << endl;
}

/*Checking the threat functions*/
void Board::threatOfPawn(int x, int y)
{
    if(myBoard[x][y].getColor() == "White") /*If pawn is white*/
    {
        if(x+1 < 8 && y+1 < 8)
        {
            if(myBoard[x+1][y+1].getColor() != "White") /*If attacking point is not white*/
                myBoard[x+1][y+1].setUnderAttack(true);
        }
        if(x-1 >= 0 && y+1 < 8)
        {
            if(myBoard[x-1][y+1].getColor() != "White")
                myBoard[x-1][y+1].setUnderAttack(true);  
        }

    }
    else if(myBoard[x][y].getColor() == "Black")    /*If pawn is black*/
    {
        if(x+1 < 8 && y-1 >= 0)
        {
            if(myBoard[x+1][y-1].getColor() != "Black") /*If attacking point is not black*/
                myBoard[x+1][y-1].setUnderAttack(true);
        }
        if(x-1 >= 0 && y-1 >= 0) 
        {
            if(myBoard[x-1][y-1].getColor() != "Black")
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
    /*      (xn == xp + 1 && yn == yp + 2) || (xn == xp - 1 && yn == yp + 2) || 
            (xn == xp + 1 && yn == yp - 2) || (xn == xp - 1 && yn == yp - 2) || 
            (xn == xp + 2 && yn == yp + 1) || (xn == xp - 2 && yn == yp + 1) ||
            (xn == xp + 2 && yn == yp - 1) || (xn == xp - 2 && yn == yp - 1))   */

    if(myBoard[x][y].getColor() == "White")
    {
    
        if(x+1 < 8 && y+2 < 8)
        {
            if(myBoard[x+1][y+2].getColor() != "White")
            {
                myBoard[x+1][y+2].setUnderAttack(true);
            }
        }
        if(x+1 < 8 && y-2 >= 0)
        {
            if(myBoard[x+1][y-2].getColor() != "White")
            {
                myBoard[x+1][y-2].setUnderAttack(true);
            }
        }
        if(x-1 >= 0 && y+2 < 8)
        {
            if(myBoard[x-1][y+2].getColor() != "White")
            {
                myBoard[x-1][y+2].setUnderAttack(true);
            }
        }
        if(x-1 >= 0 && y-2 >= 0)
        {
            if(myBoard[x-1][y-2].getColor() != "White")
            {
                myBoard[x-1][y-2].setUnderAttack(true);
            }
        }
        if(x+2 < 8 && y+1 < 8) 
        {
            if(myBoard[x+2][y+1].getColor() != "White")
            {
                myBoard[x+2][y+1].setUnderAttack(true);
            }
        }
        if(x-2 >= 0 && y+1 < 8)
        {
            if(myBoard[x-2][y+1].getColor() != "White")
            {
                myBoard[x-2][y+1].setUnderAttack(true);
            }
        }    
        if(x+2 < 8 && y-1 >= 0)
        {
            if(myBoard[x+2][y-1].getColor() != "White")
            {
                myBoard[x+2][y-1].setUnderAttack(true);
            }
        }
        if(x-2 >= 0 && y-1 >= 0)
        {
            if(myBoard[x-2][y-1].getColor() != "White")
            {
                myBoard[x-2][y-1].setUnderAttack(true);
            }
        }
    }
    else if(myBoard[x][y].getColor() == "Black")
    {
        if(x+1 < 8 && y+2 < 8)
        {
            if(myBoard[x+1][y+2].getColor() != "Black")
            {
                myBoard[x+1][y+2].setUnderAttack(true);
            }
        }
        if(x+1 < 8 && y-2 >= 0)
        {
            if(myBoard[x+1][y-2].getColor() != "Black")
            {
                myBoard[x+1][y-2].setUnderAttack(true);
            }
            
        }
        if(x-1 >= 0 && y+2 < 8)
        {
            if(myBoard[x-1][y+2].getColor() != "Black")
            {
                myBoard[x-1][y+2].setUnderAttack(true);
            }
        }
        if(x-1 >= 0 && y-2 >= 0)
        {
            if(myBoard[x-1][y-2].getColor() != "Black")
            {
                myBoard[x-1][y-2].setUnderAttack(true);
            }
        }
        if(x+2 < 8 && y+1 < 8) 
        {
            if(myBoard[x+2][y+1].getColor() != "Black")
            {
                myBoard[x+2][y+1].setUnderAttack(true);
            }
        }
        if(x-2 >= 0 && y+1 < 8)
        {
            if(myBoard[x-2][y+1].getColor() != "Black")
            {
                myBoard[x-2][y+1].setUnderAttack(true);
            }
        }    
        if(x+2 < 8 && y-1 >= 0)
        {
            if(myBoard[x+2][y-1].getColor() != "Black")
            {
                myBoard[x+2][y-1].setUnderAttack(true);
            }
        }
        if(x-2 >= 0 && y-1 >= 0)
        {
            if(myBoard[x-2][y-1].getColor() != "Black")
            {
                myBoard[x-2][y-1].setUnderAttack(true);
            }
        }
    }
}
void Board::threatOfBishop(int x, int y)
{
    /*White*/
    if(myBoard[x][y].getColor() == "White")
    {
        if(0 <= x < 7 && 0 <= y < 7)
        {
            for(int i = x+1, j = y+1; i < 8 && j < 8; i++, j++) /*NE*/
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
            for(int i = x+1, j = y-1; i < 8 && j >= 0; i++, j--) /*SE*/
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
            for(int i = x-1, j = y+1; i >= 0 && j < 8; i--, j++) /*SW*/
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
            for(int i = x-1, j = y-1; i >= 0 && j >= 0; i--, j--) /*SW*/
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

    /*Black*/
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
            for(int i = x-1, j = y-1; i >= 0 && j >= 0; i--, j--) /*SW*/
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
    threatOfRook(x,y);
    threatOfBishop(x,y);
}
void Board::threatOfKing(int x, int y)
{
    if(myBoard[x][y].getColor() == "White")
    {
        if(x+1 < 8 && x-1 >= 0 && y+1 < 8 && y-1 >= 0)
        {
            if(myBoard[x+1][y+1].getColor() != "White")
                myBoard[x+1][y+1].setUnderAttack(true);
            if(myBoard[x-1][y+1].getColor() != "White")
                myBoard[x-1][y+1].setUnderAttack(true);
        }
    }
    else if(myBoard[x][y].getColor() == "Black")
    {
        if(x+1 < 8 && x-1 >= 0 && y+1 < 8 && y-1 >= 0)
        {
            if(myBoard[x+1][y-1].getColor() != "Black")
                myBoard[x+1][y-1].setUnderAttack(true);
            if(myBoard[x-1][y-1].getColor() != "Black")
                myBoard[x-1][y-1].setUnderAttack(true);
        }
    }
}

/*Check and Check Mate functions*/
bool Board::escapeKing(int x, int y)
{
        if(checkKingMovement(x,y,x+1,y)) return true;
        else if(checkKingMovement(x,y,x,y+1)) return true;
        else if(checkKingMovement(x,y,x-1,y)) return true;
        else if(checkKingMovement(x,y,x,y-1)) return true;
        else if(checkKingMovement(x,y,x+1,y+1)) return true;
        else if(checkKingMovement(x,y,x-1,y-1)) return true;
        else if(checkKingMovement(x,y,x-1,y+1)) return true;
        else if(checkKingMovement(x,y,x+1,y-1)) return true;
    return false;
}
bool Board::checkKingMovement(int xp, int yp, int xn, int yn)
{
    if(myBoard[xp][yp].getColor() == "White" && myBoard[xp][yp].getType() == 'K')
    {
        if(abs(xn - xp) > 1 || abs(yn - yp) > 1)
            return false;
        else if(isTherePieceWhite(xn,yn))
            return false;
        else if(!((xn == xp + 1 && yn == yp + 1) || (xn == xp - 1 && yn == yp + 1)) && isTherePieceBlack(xn,yn))
            return false;
        else
        {
            this->movePiece(xp,yp,xn,yn);
            return true;
        }
    }
    else if(myBoard[xp][yp].getColor() == "Black" && myBoard[xp][yp].getType() == 'k')
    {
        if(abs(xn - xp) > 1 || abs(yn - yp) > 1)
            return false;
        else if(isTherePieceBlack(xn,yn))
            return false;
        else if(!((xn == xp + 1 && yn == yp - 1) || (xn == xp - 1 && yn == yp - 1)) && isTherePieceWhite(xn,yn))
            return false;
        else
        {
            this->movePiece(xp,yp,xn,yn);
            return true;
        }
    }
}
bool Board::checkPawnMovement(int xp, int yp, int xn, int yn)
{
    if(myBoard[xp][yp].getColor() == "White" && myBoard[xp][yp].getType() == 'P')
    {
        if(yn <= yp)    /*check y-axis same or less*/
            return false;
        else if(isTherePieceWhite(xn,yn))   /*check isThere white piece*/
            return false;
        else if(yp != 1) /*if pawn is not in starting point*/
        {
            if(yn > yp + 1 || xn > xp + 1 || xn < xp - 1)   /*yn bigger than 2 or xn bigger than 1*/
                return false;
            else if(xn == xp && isTherePieceBlack(xn,yn))   /*if p moves direct and there is a black piece*/
                return false;
            else if(xn != xp && ((xn > xp + 1 && xn < xp + 2) || (xn < xp - 1 && xn > xp - 2)) && isTherePieceBlack(xn,yn)) /*Eat if there is a black piece*/
            {
                this->promotePawn(xp,yp);
                this->movePiece(xp,yp,xn,yn);
                return true;
            }
            else    /*Move if do not eat*/
            {
                this->promotePawn(xp,yp);
                this->movePiece(xp,yp,xn,yn);
                return true;
            }
        }
        else if (yp == 1)
        {
            if(yn > yp + 2)   /*yn bigger than 2 or xn bigger than 1*/
                return false;
            else if(xn == xp && yn == yn + 2 && (isTherePieceBlack(xn,yn+1) || isTherePieceWhite(xn,yn+1)))   /*if pawn moves direct and there is a black or white piece*/
                return false;
            else if((xn > xp || xn < xp) && !isTherePieceBlack(xn,yn))    /*if pawn moves diagnolly and there is no black piece*/
                return false;
            else if(xn > xp + 1 && xn < xp + 2  && isTherePieceBlack(xn,yn))
            {
                this->movePiece(xp,yp,xn,yn);
                return true;
            }    
            else
            {
                this->movePiece(xp,yp,xn,yn);
                return true;
            }
        }
    }
    else if(myBoard[xp][yp].getColor() == "Black" && myBoard[xp][yp].getType() == 'p')
    {
        if(yn >= yp)    /*check y-axis same or higher*/
            return false;
        else if(isTherePieceBlack(xn,yn))   /*check isThere white piece*/
            return false;
        else if(yp != 6) /*if pawn is not in starting point*/
        {
            if(yn < yp - 1 || xn > xp + 1 || xn < xp - 1)   /*yn lower than 2 or xn bigger than 1*/
                return false;
            else if(xn == xp && isTherePieceWhite(xn,yn))   /*if p moves direct and there is a white piece*/
                return false;
            else if(xn != xp && ((xn > xp + 1 && xn < xp + 2) || (xn < xp - 1 && xn > xp - 2)) && isTherePieceWhite(xn,yn)) /*Eat if there is a black piece*/
            {
                this->promotePawn(xp,yp);
                this->movePiece(xp,yp,xn,yn);
                return true;
            }
            else
            {
                this->promotePawn(xp,yp);
                this->movePiece(xp,yp,xn,yn);
                return true;
            }  
        }
        else if (yp == 6)
        {
            if(yn < yp - 2)   /*yn lower than 2 or xn bigger than 1*/
                return false;
            else if(xn == xp && yn == yn - 2 && (isTherePieceBlack(xn,yn+1) || isTherePieceWhite(xn,yn+1)))   /*if pawn moves direct and there is a black or white piece*/
                return false;
            else if((xn > xp || xn < xp) && !isTherePieceWhite(xn,yn))    /*if pawn moves diagnolly and there is no white piece*/
                return false;
            else if(xn > xp + 1 && xn < xp + 2  && isTherePieceWhite(xn,yn))
            {
                this->movePiece(xp,yp,xn,yn);
                return false;
            }
            else
            {
                this->movePiece(xp,yp,xn,yn);
                return false;
            }
        }
    }
    return false;
}
bool Board::checkRookMovement(int xp, int yp, int xn, int yn)
{
    if(myBoard[xp][yp].getColor() == "White" && myBoard[xp][yp].getType() == 'R')
        if(isTherePieceWhite(xn,yn))
            return false;
    else if(myBoard[xp][yp].getColor() == "Black" && myBoard[xp][yp].getType() == 'R')
        if(isTherePieceBlack(xn,yn))
            return false;
    if(myBoard[xp][yp].getType() == 'R' || myBoard[xp][yp].getType() == 'r')
    {
        if(yn != yp)
        {
            int flag = 0;
            if(xn != xp)
                return false;
            else if(yn > yp && yn < 9 || yn > 0)
            {
                for(int i = yp; i < yn-yp; i++) /*2 - 7 = 3 , 4 , 5 , 5 , 6 , 7*/
                {
                    if(isTherePieceWhite(xp,i+1) || (isTherePieceBlack(xp,i+1) && i+1 != yn)) /*If between new and old coord. there is a white or black*/
                    {
                        flag = 1;
                        return false;
                    }
                }
                if(flag == 0)
                {
                    this->movePiece(xp,yp,xn,yn);
                    return true;
                }
            }
            else if(yn < yp && yn < 9 || yn > 0)
            {
                for(int i = yp; i > yp-yn; i--) /*2 - 7 = 3 , 4 , 5 , 5 , 6 , 7*/
                {
                    if(isTherePieceWhite(xp,i-1) || (isTherePieceBlack(xp,i-1) && i-1 != yn)) /*If between new and old coord. there is a white or black*/
                    {
                        flag = 1;
                        return false;
                    }
                }
                if(flag == 0)
                {
                    this->movePiece(xp,yp,xn,yn);
                    return true;
                }
            }
            else 
                return false;
        }
        else if(xn != xp)
        {
            int flag = 0;
            if(yn != yp)
                return false;
            else if(xn > xp && xn < 9 || xn > 0)
            {
                for(int i = xp; i < xn-xp; i++) /*2 - 7 = 2 , 3 , 4 , 5 , 6 , 7*/
                {
                    if(isTherePieceWhite(i+1,yp) || (isTherePieceBlack(i+1,yp) && i+1 != xn)) /*If between new and old coord. there is a white or black*/
                    {
                        flag = 1;
                        return false;
                    }
                }
                if(flag == 0)
                {
                    this->movePiece(xp,yp,xn,yn);
                    return true;
                }
            }
            else if(xn < xp && xn < 9 || xn > 0)
            {
                for(int i = xp; i > xp-xn; i--) /*2 - 7 = 2 , 3 , 4 , 5 , 6 , 7*/
                {
                    if(isTherePieceWhite(i-1,yp) || (isTherePieceBlack(i-1,yp) && i-1 != xn)) /*If between new and old coord. there is a white or black*/
                    {
                        flag = 1;
                        return false;
                    }
                }
                if(flag == 0)
                {
                    this->movePiece(xp,yp,xn,yn);
                    return true;
                }
            }
            else 
                return false;
        }
    }
    return false;
}
bool Board::checkKnightMovement(int xp, int yp, int xn, int yn)
{
    if(myBoard[xp][yp].getColor() == "White" && myBoard[xp][yp].getType() == 'K')
        if(((xn == xp + 1 && yn == yp + 2) || (xn == xp - 1 && yn == yp + 2) || 
            (xn == xp + 1 && yn == yp - 2) || (xn == xp - 1 && yn == yp - 2) || 
            (xn == xp + 2 && yn == yp + 1) || (xn == xp - 2 && yn == yp + 1) ||
            (xn == xp + 2 && yn == yp - 1) || (xn == xp - 2 && yn == yp - 1)) && !isTherePieceWhite(xn,yn))
        {
            movePiece(xp,yp,xn,yn);
            return true;
        }
        else
            return false;
    if(myBoard[xp][yp].getColor() == "Black" && myBoard[xp][yp].getType() == 'k')
        if(((xn == xp + 1 && yn == yp + 2) || (xn == xp - 1 && yn == yp + 2) || 
            (xn == xp + 1 && yn == yp - 2) || (xn == xp - 1 && yn == yp - 2) || 
            (xn == xp + 2 && yn == yp + 1) || (xn == xp - 2 && yn == yp + 1) ||
            (xn == xp + 2 && yn == yp - 1) || (xn == xp - 2 && yn == yp - 1)) && !isTherePieceBlack(xn,yn))
        {
            movePiece(xp,yp,xn,yn);
            return true;
        }
        else
            return false;
    return false;
}
bool Board::checkBishopMovement(int xp, int yp, int xn, int yn)
{
    if(myBoard[xp][yp].getType() == 'B' || myBoard[xp][yp].getType() == 'b')
    {
        int flag = 0;
        if(abs(xn - xp) != abs(yn - yp))
            return false;
        if(xn > xp && yn > yp)
        {
            for(int i = xn, j = yn; i > xp, j > yp; i--, j--)
            {
                cout << i << " " << j << endl;
                if(myBoard[xp][yp].getColor() == "White")
                    if(isTherePieceWhite(i,j))
                    {
                        return false;
                    }
                if(myBoard[xp][yp].getColor() == "Black")
                    if(isTherePieceBlack(i,j))
                    {
                        return false;
                    }
            }
            if(flag == 0)
            {
                this->movePiece(xp,yp,xn,yn);
                return true;
            }
        }
        if(xn > xp && yn < yp)
        {
            for(int i = xp, j = yn; i < xn, j < yp; i++, j++)
            {
                cout << i << " " << j << endl;
                if(myBoard[xp][yp].getColor() == "White")
                    if(isTherePieceWhite(i,j))
                    {
                        return false;
                    }
                if(myBoard[xp][yp].getColor() == "Black")
                    if(isTherePieceBlack(i,j))
                    {
                        return false;
                    }
            }
            if(flag == 0)
            {
                this->movePiece(xp,yp,xn,yn);
                return true;
            }
        }
        if(xn < xp && yn > yp)
        {
            for(int i = xn, j = yn; i < xp, j > yp; i++, j--)
            {
                cout << i << " " << j << endl;
                if(myBoard[xp][yp].getColor() == "White")
                    if(isTherePieceWhite(i,j))
                    {
                        return false;
                    }
                if(myBoard[xp][yp].getColor() == "Black")
                    if(isTherePieceBlack(i,j))
                    {
                        return false;
                    }
            }
            if(flag == 0)
            {
                this->movePiece(xp,yp,xn,yn);
                return true;
            }
        }
        if(xn < xp && yn < yp)
        {
            for(int i = xn, j = yn; i < xp, j < yp; i++, j++)
            {
                cout << i << " " << j << endl;
                if(myBoard[xp][yp].getColor() == "White")
                    if(isTherePieceWhite(i,j))
                    {
                        return false;
                    }
                if(myBoard[xp][yp].getColor() == "Black")
                    if(isTherePieceBlack(i,j))
                    {
                        return false;
                    }
            }
            if(flag == 0)
            {
                this->movePiece(xp,yp,xn,yn);
                return true;
            }
        }
    }
    return false;
}
bool Board::checkQueenMovement(int xp, int yp, int xn, int yn)
{
    if(xp != xn && yn != yp && (myBoard[xp][yp].getType() == 'Q' || myBoard[xp][yp].getType() == 'q'))    /*If it is a bishop move*/
        checkBishopMovement(xp,yp,xn,yn);
    else if((xp == xn && yn != yp) || (xp != xn && yn == yp) && (myBoard[xp][yp].getType() == 'Q' || myBoard[xp][yp].getType() == 'q'))
        checkRookMovement(xp,yp,xn,yn);
    return false;
}

bool Board::checkEveryMovement(int xp, int yp, int xn, int yn)
{
    return(checkPawnMovement(xp,yp,xn,yn) || checkRookMovement(xp,yp,xn,yn) || checkKnightMovement(xp,yp,xn,yn) ||
           checkBishopMovement(xp,yp,xn,yn) || checkQueenMovement(xp,yp,xn,yn));
}
bool Board::checkTheCheck(int xk, int yk)
{
    if(myBoard[xk][yk].getUnderAttack())
        return true;
}
bool Board::checkTheCheckMate(int xk, int yk)
{
    /*If king is in threat, it will be sent to this function.First we make that player of the
    opponent cannot move any other piece rather than saving the king. Second we check
    if king can move and get out of the Check. If it cant, then finally we will check for every
    friend piece of the king can get the king out of the check.If it doesnt work then game is over*/

    /*x = x of king, y = y of king, type = type of the opponent*/
    bool flag = true;
    if(this->escapeKing(xk,yk))
        return false;
    else
    {
        for(int i = 0; i < 8; i++)
        {
            for(int j = 0; j < 8; j++)
            {
                for(int k = 0; k < 8; k++)
                {
                    for(int m = 0; m < 8; m++)
                    {
                        if(checkEveryMovement(i,j,k,m) && myBoard[xk][yk].getUnderAttack() == false)
                            flag = false;
                    }
                }
            }
        }
        return flag;
    }

}

/*Other rules for chess*/
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
