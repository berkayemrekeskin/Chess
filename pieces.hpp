#ifndef PIECES_HPP
#define PIECES_HPP

#include <iostream>
#include <string>
using namespace std;

/*-------------------------------PIECES CLASS-------------------------------*/
/*HOLDS INFORMATION ABOUT THE CHESS PIECES*/
class Pieces 
{ 
    public:
        /*CONSTRUCTOR & DESTRUCTOR*/
        Pieces() {/*INTENTIONALLY EMPTY*/};
        ~Pieces() {/*INTENTIONALLY EMPTY*/};
        Pieces(string color, char type, int x, int y);
        Pieces(char type); 
        /*GETTERS*/
        string getColor() const;
        int getXCoord() const;
        int getYCoord() const;
        char getType() const;
        double getPoint() const;
        bool getUnderAttack() const;
        /*SETTERS*/
        void setColor(string color);
        void setType(char type);
        void setXCoord(int x);
        void setYCoord(int y);
        void setPoint(int point);
        void setUnderAttack(bool underAttack);
    private:
        string color;
        int x_coord;   
        int y_coord;
        char type;
        double point;
        bool isUnderAttack;
};

#endif //pieces.hpp
