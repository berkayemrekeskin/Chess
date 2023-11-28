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
        int getXCoord() const;
        int getYCoord() const;
        char getType() const;
        int getPoint() const;
        double getSafety() const;
        bool getUnderAttack() const;
        string getColor() const;
        static int getTotalPoint();
        /*setters*/
        void setType(char type);
        void setXCoord(int x);
        void setYCoord(int y);
        void setPoint(int point);
        void setSafety(double safety);
        void setUnderAttack(bool underAttack);
        void setColor(string color);
        static void setTotalPoint(int point);
        /*other member functions*/
        int movePiece(int x, int y);    /*move piece accordingly*/
        int removePiece(); /*if eaten then remove*/
    private:
        string color;
        int x_coord;   
        int y_coord;
        char type;
        int point;  /*point of piece*/
        double safety;  /*point of safety of piece*/
        bool isUnderAttack;
        static int totalPoint;
};
class Board 
{
    public:
        /*constructor*/
        Board();
        /*member functions*/
        void playChess() const;
        void printBoard() const;
        /*functions for piece movements*/
        void movePawn(int xp, int yp, int xn, int yn, string side);
        void moveRook(int xp, int yp, int xn, int yn, string side);
        void moveKnight(int xp, int yp, int xn, int yn, string side);
        void moveBishop(int xp, int yp, int xn, int yn, string side);
        void moveQueen(int xp, int yp, int xn, int yn, string side);
        void moveKing(int xp, int yp, int xn, int yn, string side);
        /*attack functions*/
        bool attackPawn(int x, int y);
        bool attackRook(int x, int y);
        bool attackKnight(int x, int y);
        bool attakBishop(int x, int y);
        bool attackQueen(int x, int y);
        bool attackKing(int x, int y);
        /*calculating points of sides*/
        int calculatePoints();
        /*while playing*/
        void getMove(string side);
            void checkMove(int xp, int yp, int xn, int yn, string side);    /*if move*/
                bool checkCheck(int xp, int yp) const;   /*Check if opponent is in Check*/
                bool checkCheckMate(int xp, int yp) const;   /*Check if opponent is in Check Mate*/
                    void checkDanger(string side);
                void promotePawn(int xp, int yp); /*Promote pawn if pawn's coordinate according to 0 or 7*/
                void movePiece(int xp, int yp, int xn, int yn);
                int overallScore();      
            void suggestMove() const;   /*if suggest*/
                //int checkDanger(); /*check danger and return the min danger to yourself and max danger to opp.*/
            void saveBoard(string filename) const;  /*if save*/
        
        /*other member functions*/
        bool isTherePieceWhite(int x, int y) const; 
        bool isTherePieceBlack(int x, int y) const;
        Board & loadBoard();
    private:
        vector<vector<Pieces>> myBoard;
        bool isOver; /*returns true if game is over*/
};
