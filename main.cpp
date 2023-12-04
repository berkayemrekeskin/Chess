#include <iostream>
#include "board.hpp"
#include "pieces.hpp"
using namespace std;

int main()
{
    Board chessBoard;
    cout << "Welcome to the Chess Game!" << endl;
    cout << endl;
    cout << "Game Codes:" << endl;
    cout << "suggest : Computer returns a generated move" << endl;
    cout << "save : Save the current board to a file" << endl;
    cout << "load : Load a board from a file" << endl;
    cout << "nextmove : Makes computer a generated move for you" << endl;
    cout << "quit : Quit from the game" << endl; 
    cout << endl;
    while(!chessBoard.getIsOver())
    {
        chessBoard.getMove("White");
        chessBoard.getMove("Black");
    }
}