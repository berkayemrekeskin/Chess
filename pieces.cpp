#include <iostream>
#include "board.hpp"
#include "pieces.hpp"
using namespace std;

/*-------------------------------PIECES FUNCTIONS-------------------------------*/
/*CONSTRUCTOR*/
Pieces::Pieces(string _color, char _type, int _x, int _y)
: color(_color), type(_type), x_coord(_x), y_coord(_y), isUnderAttack(false) 
{
    if(color == "White")
    {
        switch(type)
        {
            case 'K': point = 100.0; break;
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
            case 'k': point = 100.0; break;
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
string Pieces::getColor() const {return color; }
int Pieces::getXCoord() const { return x_coord; }
int Pieces::getYCoord() const { return y_coord; }
char Pieces::getType() const { return type; }
double Pieces::getPoint() const { return point; }
bool Pieces::getUnderAttack() const { return isUnderAttack; }
/*SETTERS*/
void Pieces::setType(char _type) { this->type = _type; }
void Pieces::setXCoord(int _x) { this->x_coord = _x; }
void Pieces::setYCoord(int _y) { this->y_coord = _y; }
void Pieces::setPoint(int _point) { this->point = _point; }
void Pieces::setUnderAttack(bool underAttack) { this->isUnderAttack = underAttack; }
void Pieces::setColor(string _color) { this->color = _color; }