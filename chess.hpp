#ifndef CHESS_HPP
#define CHESS_HPP

#include <iostream>
#include <string>
#include <vector>
#include "board.hpp"
#include "pieces.hpp"
using namespace std;


class Chess
{
    public:
        Chess();
    private:
        Board gameBoard;
};

void Chess::playChess() const
{

}

#endif //chess_hpp
