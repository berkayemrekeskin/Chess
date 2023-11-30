#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Pieces
{ 
    public:
        /*constructor*/
        Pieces() {};
        Pieces(string color, char type, int x, int y);
        /*getters*/
        string getColor() const;
        int getXCoord() const;
        int getYCoord() const;
        char getType() const;
        double getPoint() const;
        double getSafety() const;
        bool getUnderAttack() const;
        /*setters*/
        void setColor(string color);
        void setType(char type);
        void setXCoord(int x);
        void setYCoord(int y);
        void setPoint(int point);
        void setSafety(double safety);
        void setUnderAttack(bool underAttack);
    private:
        string color;
        int x_coord;   
        int y_coord;
        char type;
        double point;
        bool isUnderAttack;
};
class Board 
{
    public:
        /*BOARD CONSTRUCTOR*/
        Board();
        /*PLAY & PRINT*/
        void playChess() const;
        void printBoard() const;
        /*PIECE MOVEMENT*/ /*GIVES ERROR*/ /*DOESN'T RETURN*/ 
        void movePawn(int xp, int yp, int xn, int yn);
        void moveRook(int xp, int yp, int xn, int yn);
        void moveKnight(int xp, int yp, int xn, int yn);
        void moveBishop(int xp, int yp, int xn, int yn);
        void moveQueen(int xp, int yp, int xn, int yn);
        void moveKing(int xp, int yp, int xn, int yn);
        /*PIECE THREAT*/
        void threatOfPawn(int x, int y);
        void threatOfRook(int x, int y);
        void threatOfKnight(int x, int y);
        void threatOfBishop(int x, int y);
        void threatOfQueen(int x, int y);
        void threatOfKing(int x, int y);
        /*VALID MOVEMENT*/ /*DOESN'T GIVE ERROR*/ /*RETURNS VALID OR NOT*/
        bool checkKingMovement(int xp, int yp, int xn, int yn);
        bool checkPawnMovement(int xp, int yp, int xn, int yn);
        bool checkRookMovement(int xp, int yp, int xn, int yn);
        bool checkKnightMovement(int xp, int yp, int xn, int yn);
        bool checkBishopMovement(int xp, int yp, int xn, int yn);
        bool checkQueenMovement(int xp, int yp, int xn, int yn);
        bool checkEveryMovement(int xp, int yp, int xn, int yn);
        bool isTherePieceWhite(int x, int y) const; 
        bool isTherePieceBlack(int x, int y) const;
        /*MOVE & CHECK*/
        void getMove(string side);
        void checkValidMove(string side, string &input, int &xp, int &yp, int &xn, int &yn);
        void checkMove(int xp, int yp, int xn, int yn);
        void movePiece(int xp, int yp, int xn, int yn);
        void findPiece(int &x, int &y, char type);
        void checkDanger();
        void overallGoodnessScore();
        /*CHECKMATE*/
        bool checkTheCheck(int xk, int yk);
        bool checkTheCheckMate(int xk, int yk); 
        bool escapeKing(int x, int y);
        /*OTHER CHESS RULES*/
        void promotePawn(int xp, int yp);
        /*SUGGEST & SAVE*/
        void suggestMove() const;
        void saveBoard(string filename) const;
        Board & loadBoard();
    private:
        vector<vector<Pieces>> myBoard;
        bool isOver; 
};
