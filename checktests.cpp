bool Board::attackKing(int x, int y)
{
    bool pawn, rook, knight, bishop, queen;
    if(myBoard[x][y].getColor() == "White")
    {
        for(int i = 0; i < 8; i++)
        {
            for(int j = 0; j < 8; j++)
            {
                if(myBoard[i][j].getType() == 'P')
                {
                    pawn = (checkPawn(i,j,x,y+1) || checkPawn(i,j,x,y-1) || checkPawn(i,j,x+1,y) || checkPawn(i,j,x-1,y) 
                            || checkPawn(i,j,x+1,y+1) || checkPawn(i,j,x-1,y-1) || checkPawn(i,j,x-1,y+1) || checkPawn(i,j,x+1,y-1));
                }
                if(myBoard[i][j].getType() == 'R')
                {
                    rook = (checkRook(i,j,x,y+1) || checkRook(i,j,x,y-1) || checkRook(i,j,x+1,y) || checkRook(i,j,x-1,y) 
                            || checkRook(i,j,x+1,y+1) || checkRook(i,j,x-1,y-1) || checkRook(i,j,x-1,y+1) || checkRook(i,j,x+1,y-1));
                }
                if(myBoard[i][j].getType() == 'N')
                {
                    knight = (checkKnight(i,j,x,y+1) || checkKnight(i,j,x,y-1) || checkKnight(i,j,x+1,y) || checkKnight(i,j,x-1,y) 
                            || checkKnight(i,j,x+1,y+1) || checkKnight(i,j,x-1,y-1) || checkKnight(i,j,x-1,y+1) || checkKnight(i,j,x+1,y-1));
                }
                if(myBoard[i][j].getType() == 'B')
                {
                    bishop = (checkBishop(i,j,x,y+1) || checkBishop(i,j,x,y-1) || checkBishop(i,j,x+1,y) || checkBishop(i,j,x-1,y) 
                            || checkBishop(i,j,x+1,y+1) || checkBishop(i,j,x-1,y-1) || checkBishop(i,j,x-1,y+1) || checkBishop(i,j,x+1,y-1));
                }
                if(myBoard[i][j].getType() == 'Q')
                {
                    queen = (checkQueen(i,j,x,y+1) || checkQueen(i,j,x,y-1) || checkQueen(i,j,x+1,y) || checkQueen(i,j,x-1,y) 
                            || checkQueen(i,j,x+1,y+1) || checkQueen(i,j,x-1,y-1) || checkQueen(i,j,x-1,y+1) || checkQueen(i,j,x+1,y-1));
                }
            }
        }
        return (pawn || rook || knight || bishop || queen);
    }
    else if(myBoard[x][y].getColor() == "Black")
    {
        bool pawn, rook, knight, bishop, queen;
        for(int i = 0; i < 8; i++)
        {
            for(int j = 0; j < 8; j++)
            {
                if(myBoard[i][j].getType() == 'p')
                {
                    pawn = (checkPawn(i,j,x,y+1) || checkPawn(i,j,x,y-1) || checkPawn(i,j,x+1,y) || checkPawn(i,j,x-1,y) 
                            || checkPawn(i,j,x+1,y+1) || checkPawn(i,j,x-1,y-1) || checkPawn(i,j,x-1,y+1) || checkPawn(i,j,x+1,y-1));
                }
                if(myBoard[i][j].getType() == 'r')
                {
                    rook = (checkRook(i,j,x,y+1) || checkRook(i,j,x,y-1) || checkRook(i,j,x+1,y) || checkRook(i,j,x-1,y) 
                            || checkRook(i,j,x+1,y+1) || checkRook(i,j,x-1,y-1) || checkRook(i,j,x-1,y+1) || checkRook(i,j,x+1,y-1));
                }
                if(myBoard[i][j].getType() == 'n')
                {
                    knight = (checkKnight(i,j,x,y+1) || checkKnight(i,j,x,y-1) || checkKnight(i,j,x+1,y) || checkKnight(i,j,x-1,y) 
                            || checkKnight(i,j,x+1,y+1) || checkKnight(i,j,x-1,y-1) || checkKnight(i,j,x-1,y+1) || checkKnight(i,j,x+1,y-1));
                }
                if(myBoard[i][j].getType() == 'b')
                {
                    bishop = (checkBishop(i,j,x,y+1) || checkBishop(i,j,x,y-1) || checkBishop(i,j,x+1,y) || checkBishop(i,j,x-1,y) 
                            || checkBishop(i,j,x+1,y+1) || checkBishop(i,j,x-1,y-1) || checkBishop(i,j,x-1,y+1) || checkBishop(i,j,x+1,y-1));
                }
                if(myBoard[i][j].getType() == 'q')
                {
                    queen = (checkQueen(i,j,x,y+1) || checkQueen(i,j,x,y-1) || checkQueen(i,j,x+1,y) || checkQueen(i,j,x-1,y) 
                            || checkQueen(i,j,x+1,y+1) || checkQueen(i,j,x-1,y-1) || checkQueen(i,j,x-1,y+1) || checkQueen(i,j,x+1,y-1));
                }
            }
        }
        return (pawn || rook || knight || bishop || queen);
    }
    
}
bool Board::checkPawn(int xp, int yp, int xn, int yn)
{
    if(myBoard[xp][yp].getColor() == "White")
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
    else if(myBoard[xp][yp].getColor() == "Black")
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
}
bool Board::checkRook(int xp, int yp, int xn, int yn)
{
    if(myBoard[xp][yp].getColor() == "White")
        if(isTherePieceWhite(xn,yn))
            return false;
    else if(myBoard[xp][yp].getColor() == "Black")
        if(isTherePieceBlack(xn,yn))
            return false;
    
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
bool Board::checkKnight(int xp, int yp, int xn, int yn)
{
    if(myBoard[xp][yp].getColor() == "White")
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
    if(myBoard[xp][yp].getColor() == "Black")
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
}
bool Board::checkBishop(int xp, int yp, int xn, int yn)
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
bool Board::checkQueen(int xp, int yp, int xn, int yn)
{
    if(xp != xn && yn != yp)    /*If it is a bishop move*/
        checkBishop(xp,yp,xn,yn);
    else if((xp == xn && yn != yp) || (xp != xn && yn == yp))
        checkRook(xp,yp,xn,yn);
}
