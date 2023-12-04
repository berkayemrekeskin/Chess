#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "board.hpp"
#include "pieces.hpp"
using namespace std;

/*BOARD CONSTRUCTOR, OPERATOR OVERLOADS & DESTRUCTOR*/
Board::Board() : myBoard(8, vector<Pieces> (8)), isOver(false), isCheckWhite(false), isCheckBlack(false)
{
    for(int i = 0; i < 8; i++)
        for(int j = 2; j < 6; j++)
            myBoard[i][j] = Pieces("Empty",'.',i,j);
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
}
Board & Board::operator=(const Board &other)
{
    /*Clear the first board*/
    for(int i = 0; i < 8; i++)
        this->myBoard[i].clear();
    this->myBoard.clear();
    /*Copy the second board to first board*/
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++)
            this->myBoard[i][j] = other.myBoard[i][j];
    isOver = other.isOver;
    isCheckWhite = other.isCheckWhite;
    isCheckBlack = other.isCheckBlack;
    return *this;
}
ofstream & operator<<(ofstream &out, const Board &obj)
{
    for(int j = 7; j >= 0; j--)
        {
            for(int i = 0; i < 8; i++)
            {
                out << obj.myBoard[i][j].getType();
            }
            out << endl;
        }
    return out;
}
ifstream & operator>>(ifstream &in, Board &obj)
{
    char type;
    string color;
    vector<Pieces> temp_board;
    for(int j = 0; j < 8; j++)
    {
        for(int i = 7; i >= 0; i--)
        {
            in >> type;
            if(type < 'Z' && type > 'A')
                color = "White";
            else if(type < 'z' && type > 'a')
                color = "Black";
            if(type == 'P' || type == 'p')
                temp_board.push_back(Pieces(color,type,j,i));
            else if(type == 'R' || type == 'r')
                temp_board.push_back(Pieces(color,type,j,i));
            else if(type == 'N' || type == 'n')
                temp_board.push_back(Pieces(color,type,j,i));
            else if(type == 'B' || type == 'b')
                temp_board.push_back(Pieces(color,type,j,i));
            else if(type == 'Q' || type == 'q')
                temp_board.push_back(Pieces(color,type,j,i));
            else if(type == 'K' || type == 'k')
                temp_board.push_back(Pieces(color,type,j,i));
            else if(type == '.')
                temp_board.push_back(Pieces("Empty",type,j,i));
            else
                exit(-1);
        }
        obj.myBoard[j] = temp_board;
        temp_board.clear();
    }
    
    return in;
    

}
Board::~Board() {/*DESTRUCTOR*/}
/*BOARD OPERATIONS*/ 
void Board::printBoard() const
{
    /*Print the board*/
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
void Board::checkDanger()
{
    /*Resetting the board's underAttack variables to false*/
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++)
            myBoard[i][j].setUnderAttack(false);
    
    /*Checking again to change the underAttack variables*/
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            /*Using the threat functions to check the "underAttacked" pieces*/
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
int Board::overallGoodnessScore()
{
    /*Summing the points for each round*/
    double whiteTotalScore = this->calculateWhiteScore();
    double blackTotalScore = this->calculateBlackScore();

    /*Setting the underAttacked points*/
    checkDanger();
    /*Searching every piece for under attack*/
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(myBoard[i][j].getColor() == "White" && myBoard[i][j].getUnderAttack())
                whiteTotalScore -= 0.5 * myBoard[i][j].getPoint();
            else if(myBoard[i][j].getColor() == "Black" && myBoard[i][j].getUnderAttack())
                blackTotalScore -= 0.5 * myBoard[i][j].getPoint();
        }
    }
        
    return 0;
}
int Board::nextMove(string side)
{
    /*Getting the suggested move from suggestMove function*/
    string input = this->suggestMove(side);
    /*Changing it to integers*/
    int xp, yp, xn, yn;
    xp = input[0] - 97;
    yp = input[1] - 49;
    xn = input[2] - 97;
    yn = input[3] - 49;
    /*Checking the move is correct or not & making the move*/
    this->checkMove(xp,yp,xn,yn,side);
    int x, y;
    /*Checking is Board is in check*/
    if(side == "White")
    {
        findPiece(x,y,'k');
        checkTheCheck(x,y,side);
    }
    else if(side == "Black")
    {
        findPiece(x,y,'K');
        checkTheCheck(x,y,side);
    }
    /*Checking is Board is in check mate*/
    if(isOver)
    {
        printBoard();
        cout << "Checkmate!" << endl;
        exit(0);
    }
    return 0;
}
/*GENERAL USE FUNCTIONS*/
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
bool Board::isValid(int xp, int yp, int xn, int yn, string side)
{
    /*First, finding the king of the side*/
    int x,y;
    if(side == "White")
        findPiece(x,y,'K');
    else if(side == "Black")
        findPiece(x,y,'k');
    /*Checking if the king is in underAttack*/
    if(myBoard[x][y].getUnderAttack() == true)  /*If it is in underAttack, then it is in check*/
    {
        /*Temporary Piece to hold the next moved Piece*/
        Pieces temp;
        temp = myBoard[xn][yn];
        movePiece(xp,yp,xn,yn);
        /*Checking after the move, is king still underAttack*/
        if(myBoard[x][y].getUnderAttack() == false) /*If is not, then setting the check variables to false*/
        {
            movePiece(xn,yn,xp,yp);
            myBoard[xn][yn] = temp;
            if(side == "White")
                this->setIsCheckBlack(false);
            else if(side == "Black")
                this->setIsCheckWhite(false);
            return false;
        }
        else    /*Returning true if the movement is not valid (Can't save the king)*/
        {
            movePiece(xn,yn,xp,yp);
            myBoard[xn][yn] = temp;
            return true;
        }
    }
    else if(myBoard[x][y].getUnderAttack() == false) /*If it is not, then it is not in check*/
    {
        Pieces temp;
        temp = myBoard[xn][yn];
        movePiece(xp,yp,xn,yn);

        if(myBoard[x][y].getUnderAttack() == true)  /*If the movement makes the king in check*/
        {
            movePiece(xn,yn,xp,yp);
            myBoard[xn][yn] = temp;
            return true;    /*Returning true that the move is not valid*/
        }
        else if(myBoard[xn][yn].getUnderAttack() == true && (myBoard[xn][yn].getType() == 'K' || myBoard[xn][yn].getType() == 'k')) /*Returning false*/
        {
            movePiece(xn,yn,xp,yp);
            myBoard[xn][yn] = temp;
            return false;
        }
        else 
        {
            movePiece(xn,yn,xp,yp);
            myBoard[xn][yn] = temp;
            return false;
        }
    }
    return false;
}
bool Board::findPiece(int &x, int &y, char type) const
{
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++)
            if(myBoard[i][j].getType() == type)
            {
                x = i;
                y = j;
                return true;
            }
    return false;
}
/*INPUT & IMPLEMENT FUNCTIONS*/
void Board::getMove(string side)
{
    /*Checking the danger points & printing the board*/
    this->checkDanger(); 
    this->printBoard();
    /*Checking the sides & isInCheck*/
    int x, y;
    if(side == "White")
    {
        cout << "[White's Turn]" << endl;
        this->findPiece(x,y,'k');
        checkTheCheck(x,y,side);
    }
    else if(side == "Black")
    {
        cout << "[Black's Turn]" << endl;
        this->findPiece(x,y,'K');
        checkTheCheck(x,y,side);
    }
    /*Getting the input*/
    string input;
    cout << "Enter your move: " << endl;;
    cout << "> ";
    getline(std::cin, input);

    if(input == "suggest")  /*Suggest move*/
    {
        this->suggestMove(side);
        this->getMove(side);
    }
    else if(input == "save") /*Save to file*/
    {
        this->saveBoard();  
        this->getMove(side);
    }  
    else if(input == "load") /*Load from file*/
    {
        this->loadBoard();
        this->getMove(side);
    }
    else if(input == "nextmove") /*Make the comp. move*/
    {
        this->nextMove(side);
    }
    else if(input == "quit") /*Quit*/
        exit(0);
    else 
    {
        int xp, yp, xn, yn; /*Change the input to integers*/

        xp = input[0] - 97;
        yp = input[1] - 49;
        xn = input[2] - 97;
        yn = input[3] - 49;

        if(yn > 7 || yn < 0 || xn > 7 || xn < 0) /*If the input is not in the board*/
        {
            cout << "Wrong move, out of scope" << endl;
            this->getMove(side);
        }
        else if(isValid(xp,yp,xn,yn,side)) /*Checking the isValid*/
        {
            cout << "Wrong move!" << endl;
            this->getMove(side);
            checkTheCheck(x,y,side);
        }
        else    /*Checking the move & if it is true moving it*/
        {
            this->checkMove(xp,yp,xn,yn,side);
            checkTheCheck(x,y,side);
        }
        if(isOver)  /*Checking is the game over*/
        {
            cout << "Checkmate!" << endl;
            exit(0);
        }
    }
}
void Board::checkMove(int xp, int yp, int xn, int yn, string side)
{
    /*Checking the type of the piece and sending it to the according move function*/
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
    else
    {
        cout << "Wrong move! You can't move an empty piece!" << endl;;
        this->getMove(side);
    }
}
/*OTHER CHESS RULES*/
void Board::promotePawn(int xp, int yp)
{
        /*Cheking the "Çoban Matı", If the pawn is in the opponents first line, then it can become a changeable Piece*/
        if(myBoard[xp][yp].getType() == 'P')
        {
            if(yp == 7)
            {
                int i;
                char newType;
                cout << "Enter what piece you want to get (only one letter in uppercase and except K): ";  /*Ask for new type of piece*/
                std::cin >> newType;
                if(newType == 'K')
                    return;
                Pieces promotedPiece("White",newType,xp,yp);
                myBoard[xp][yp+1] = promotedPiece;
            }
        }
        else if(myBoard[xp][yp].getType() == 'p')
        {
            if(yp == 0)
            {
                int i;
                char newType;
                cout << "Enter what piece you want to get (only one letter in uppercase and except k): ";  /*Ask for new type of piece*/
                std::cin >> newType;
                if(newType == 'k')
                    return;
                Pieces promotedPiece("Black",newType,xp,yp);
                myBoard[xp][yp-1] = promotedPiece;
            }
        }
}
/*FILE SAVING & LOADING FUNCTIONS*/
int Board::saveBoard() const
{
    string filename;
    cout << "Enter filename you want to save the board: ";
    getline(std::cin,filename);
    ofstream out;
    out.open(filename);
    if(out.is_open())
        out << *this;
    else
        return 0;
    out.close();
    return 0;
}
int Board::loadBoard() 
{
    string filename;

    cout << "Enter filename you want to load the board: ";
    getline(std::cin,filename);
    ifstream in;
    in.open(filename);
    if(in.is_open())
    {
        in >> *this;
    }
    else
        return 0;

    in.close();
    return 1;
}
