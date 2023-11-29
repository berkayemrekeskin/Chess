#include <iostream>
#include "chess.hpp"
using namespace std;
/*CONSTRUCTOR*/
Pieces::Pieces(string _color, char _type, int _x, int _y)
: color(_color), type(_type), x_coord(_x), y_coord(_y), safety(0.0), isUnderAttack(false) 
{
    if(color == "White")
    {
        switch(type)
        {
            case 'K': point = 0.0; break;
            case 'Q': point = 9.0; break;
            case 'R': point = 5.0; break;
            case 'B': point = 3.0; break;
            case 'N': point = 3.0; break;
            case 'P': point = 1.0; break;
        }
    }
    else if(color == "Black")
    {
        switch(type)
        {
            case 'k': point = 0.0; break;
            case 'q': point = 9.0; break;
            case 'r': point = 5.0; break;
            case 'b': point = 3.0; break;
            case 'n': point = 3.0; break;
            case 'p': point = 1.0; break;
        }
    }
    else if(color == "Empty")
        point = 0;
}

/*GETTERS*/
int Pieces::getXCoord() const { return x_coord; }
int Pieces::getYCoord() const { return y_coord; }
char Pieces::getType() const { return type; }
double Pieces::getPoint() const { return point; }
double Pieces::getSafety() const { return safety; }
bool Pieces::getUnderAttack() const { return isUnderAttack; }
string Pieces::getColor() const {return color; }

/*SETTERS*/
void Pieces::setType(char _type) { this->type = _type; }
void Pieces::setXCoord(int _x) { this->x_coord = _x; }
void Pieces::setYCoord(int _y) { this->y_coord = _y; }
void Pieces::setPoint(int _point) { this->point = _point; }
void Pieces::setSafety(double _safety) { this->safety = _safety; }
void Pieces::setUnderAttack(bool underAttack) { this->isUnderAttack = underAttack; }
void Pieces::setColor(string _color) { this->color = _color; }