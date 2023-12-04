#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <string>
#include <vector>
#include "pieces.hpp"
using namespace std;

/*-------------------------------BOARD CLASS-------------------------------*/
/*INCLUDES EVERY MOVEMENT, CHECKING AND THREAT FUNCTIONS ETC.*/
class Board 
{
    public:
        /*BOARD CONSTRUCTOR & DESTRUCTOR*/
        Board();
        ~Board();
        /*OPERATOR OVERLOADS*/
        Board & operator=(const Board & other);
        friend ofstream & operator<<(ofstream &out, const Board &obj);
        friend ifstream & operator>>(ifstream &in, Board &obj);
        /*SETTERS & GETTERS*/
        void setIsOver(bool isIt) { isOver = isIt; }
        void setIsCheckWhite(bool isIt) { isCheckWhite = isIt; }
        void setIsCheckBlack(bool isIt) { isCheckBlack = isIt; }
        bool getIsOver() const { return isOver; }
        bool getIsCheckWhite() const { return isCheckWhite; }
        bool getIsCheckBlack() const { return isCheckBlack; }
        /*BOARD OPERATIONS*/
        void printBoard() const;
        void checkDanger();
        int overallGoodnessScore();
        int nextMove(string side);
        /*PIECE MOVEMENT*/ /*GIVES ERROR*/ /*RETURNS IF PIECE MOVED*/ 
        bool movePawn(int xp, int yp, int xn, int yn, string side);
        bool moveRook(int xp, int yp, int xn, int yn, string side);
        bool moveKnight(int xp, int yp, int xn, int yn, string side);
        bool moveBishop(int xp, int yp, int xn, int yn, string side);
        bool moveQueen(int xp, int yp, int xn, int yn, string side);
        bool moveKing(int xp, int yp, int xn, int yn, string side);
        /*PIECE THREAT*/ /*CHECKS THE UNDER ATTACK PIECES*/
        void threatOfPawn(int x, int y);
        void threatOfRook(int x, int y);
        void threatOfKnight(int x, int y);
        void threatOfBishop(int x, int y);
        void threatOfQueen(int x, int y);
        void threatOfKing(int x, int y);
        void printThreats() const;
        /*VALID MOVEMENT*/
        bool checkKingMovement(int xp, int yp, int xn, int yn, string side) const;
        bool checkPawnMovement(int xp, int yp, int xn, int yn, string side) const;
        bool checkRookMovement(int xp, int yp, int xn, int yn, string side) const;
        bool checkKnightMovement(int xp, int yp, int xn, int yn, string side) const;
        bool checkBishopMovement(int xp, int yp, int xn, int yn, string side) const;
        bool checkQueenMovement(int xp, int yp, int xn, int yn, string side) const;
        bool checkQueenHorizontal(int xp, int yp, int xn, int yn, string side) const;
        bool checkQueenDiagonal(int xp, int yp, int xn, int yn, string side) const;
        /*GENERAL USE FUNCTIONS*/
        bool isTherePieceWhite(int x, int y) const; 
        bool isTherePieceBlack(int x, int y) const;
        bool isValid(int xp, int yp, int xn, int yn, string side);
        bool findPiece(int &x, int &y, char type) const;
        /*MOVE & IMPLEMENT FUNCTIONS*/
        void getMove(string side);
        void checkMove(int xp, int yp, int xn, int yn, string side);
        void movePiece(int xp, int yp, int xn, int yn);
        /*CHECKMATE*/
        bool checkTheCheck(int xk, int yk, string side);
        bool canPieceSave(int xk, int yk,int xp, int yp, int xn, int yn, string side);
        bool checkEveryMovement(int xk, int yk, string side);
        /*SUGGEST*/
        int getScore(int xp, int yp, int xn, int yn, string &move, string side);
        int calculateWhiteScore();
        int calculateBlackScore();
        string suggestMove(string side);
        /*SAVE*/
        int saveBoard() const;
        int loadBoard();
        /*OTHER CHESS RULES*/
        void promotePawn(int xp, int yp);
    private:
        vector<vector<Pieces> > myBoard;
        bool isCheckWhite;
        bool isCheckBlack;
        bool isOver;
};

#endif //board.hpp