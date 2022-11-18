#include <iostream>
#include <stdexcept>
#include <cstdio>
#include <string>
#include <initializer_list>
#include <cassert>
#include <vector>
#include <fstream>
#include <array>


using namespace std;


enum  pieces {king, queen, bishop, knight, rook, pawn, Empty};
enum color {black,white};

template <typename T>

class Matrix
{

private:

    T* matr;
public:

    int matrWidth;
    int matrHight;


    Matrix(int width, int hight) {
        matrWidth = width;
        matrHight = hight;
        //cout << "calling constructor" << this << endl;
        matr = new T [hight*width]; //TODO попробовать разобраться с нью в такой записи и разобраться с Malloc стек с повторным освобождением памяти

        //matr = (T*)malloc(sizeof(T)*hight*width);
    }

    Matrix(const Matrix &other) {
        this->matrWidth = other.matrWidth;
        this->matrHight = other.matrHight;
        this->matr = new T[matrHight*matrWidth];
        for (int i = 0; i < matrHight*matrWidth; i++)
        {
           this->matr[i] = other.matr[i];
           //cout << "calling constructor" << this << endl;
        }

    }
    // WSL
    // Amazon AWS - cloud9


    ~Matrix(){
        //cout << "calling destructor" << this << endl;
        delete [] matr;
        //free(matr);
    }

    T& at(int x, int y) {
        if(x < 0 || x  > matrWidth || y > matrHight || y < 0){
            string mssg = "width= "+to_string(matrWidth)+" hight= "+to_string(matrHight) +" ,but "+" x="+to_string(x)+" y="+to_string(y);
            throw out_of_range(mssg);
        }
        return matr[y * matrWidth + x];
    }

    void assignmentForArr(T* arr, int x, int y) {
        for(int i = 0; i < x*y; i++) {
            matr[i] = arr[i];
    }

    }
    void printBoard() {
        for (int i = 0; i < matrWidth*matrHight; i++)
        {
            matr[i].print();
            if((i+1)%8 == 0) {
                cout << endl;
            }
        }
    }
};
class X {
    vector<int> m_v;

public:
    X(initializer_list<int> v)
        : m_v(v)
    { }
};


class Pieces {

public:

    pieces name_piece;
    color color_piece;
    void SetName(pieces name_piece, color color_piece) {
        this->name_piece = name_piece;
        this->color_piece = color_piece;
    }


    Pieces(){

    }

    Pieces (pieces name_piece, color color_piece) {
        this->name_piece = name_piece;
        this->color_piece = color_piece;
    }

    Pieces (pieces name_piece) {
        this->name_piece = name_piece;
    }

    void print(){
        if(name_piece == king && color_piece == white) {
            printf("[\u2654]");
        }
        else if(name_piece == queen && color_piece == white) {
            printf("[\u2655]");
        }
        else if(name_piece == bishop && color_piece == white) {
            printf("[\u2657]");
        }
        else if(name_piece == knight && color_piece == white) {
            printf("[\u2658]");
        }
        else if(name_piece == rook && color_piece == white) {
            printf("[\u2656]");
        }
        else if(name_piece == pawn && color_piece == white) {
            printf("[\u2659]");
        }
        else if(name_piece == 6) {
            printf("[ ]");
        }
        else if(name_piece == king && color_piece == black) {
           printf("[\u265A]");
        }
        else if(name_piece == queen && color_piece == black) {
            printf("[\u265B]");
        }
        else if(name_piece == bishop && color_piece == black) {
            printf("[\u265D]");
        }
        else if(name_piece == knight && color_piece == black) {
            printf("[\u265E]");
        }
        else if(name_piece == rook && color_piece == black) {
            printf("[\u265C]");
        }
        else if(name_piece == pawn && color_piece == black) {
            printf("[\u265F]");
        }
        else {
            cout << "error in printBoard";
        }
    }

    bool operator== (const Pieces &other) {
        return this->name_piece == other.name_piece && this->color_piece == other.color_piece;
    }
};

//TODO сделать главную функцию, которая собирает списки ходов в один, проходя по доске

class Move {
public:

    int xDeParture;
    int yDeParture;
    int xArrivle;
    int yArrivle;

    Move(){
        int xDeParture = 0;
        int yDeParture = 0;
        int xArrivle = 0;
        int yArrivle = 0;
    }

    Move(int xDeParture, int yDeParture, int xArrivle, int yArrivle) {
        this->xDeParture = xDeParture;
        this->yDeParture = yDeParture;
        this->xArrivle = xArrivle;
        this->yArrivle = yArrivle;
    }

    void Print(int xArrivle) {
        cout << this->xArrivle;
    }

};

void push_back_list(vector<Move> listMove, vector<Move> &everyMoveList);//прототип!!!

bool checkOutOfRange(int x, int y, Matrix<Pieces> board) {
    if(x > board.matrWidth-1 || x < 0 || y > board.matrHight-1 || y < 0) {
        return true;
    }
    return false;
}

void printVector(vector<Move> arr) {
    cout << "list moves: [";
    for (int i = 0; i < (int)arr.size(); i++)
    {
       cout << arr[i].xArrivle << ", " << arr[i].yArrivle << " ; ";
    }
    cout << "]" << endl;

}

void addMovesInList(int x, int y, int xDir, int yDir, Move &move, vector<Move> &listMove ,  Matrix<Pieces> &board) {

        if ((!checkOutOfRange(xDir, yDir, board) && board.at(x, y).color_piece != board.at(xDir,yDir).color_piece)||
            (!checkOutOfRange(xDir, yDir, board) && board.at(xDir,yDir).name_piece == Empty)) {
            move.xDeParture = x;
            move.yDeParture = y;
            move.xArrivle = xDir;
            move.yArrivle = yDir;
            listMove.push_back(move);
        }
}

void addMoves(int &x, int &y, int xDir, int yDir, vector<Move> &listMove) {
    Move move;
    move.xDeParture = x;
    move.yDeParture = y;
    move.xArrivle = xDir;
    move.yArrivle = yDir;
    listMove.push_back(move);
}

bool checkAddMove(int x ,int y,int Xorig, int Yorig, Matrix<Pieces> &board) {

    if(!checkOutOfRange(x, y, board) && board.at(x,y).name_piece == Empty) {
        return true;
    }
    else if(!checkOutOfRange(x, y, board) && board.at(x, y).color_piece == board.at(Xorig,Yorig).color_piece) {
          return false;
    }
    else if(!checkOutOfRange(x, y, board) && board.at(x, y).color_piece != board.at(Xorig,Yorig).color_piece) {
        return true;

    }
    return false;
}

vector<Move> listMovesKing(int x, int y, Matrix<Pieces> &board) {
    vector<Move> listMove;
    Move doMove;

    int arrY[] = {y+1, y+1, y+1, y, y-1, y-1, y-1, y};
    int arrX[] = {x+1, x, x-1, x-1, x-1, x, x+1, x+1};

     for (int i = 0; i <(int)(sizeof(arrX)/sizeof(arrX[0])); i++) {
         if(!checkOutOfRange(arrX[i], arrY[i], board)){
            addMovesInList(x, y, arrX[i], arrY[i], doMove, listMove, board);
         }
         else {
             continue;
         }
     }

    return listMove;
}

vector<Move> listMovesKnight(int x, int y, Matrix<Pieces> &board) {
    vector<Move> listMove;
    Move doMove;

    int arrY[] = {y + 2, y + 1, y - 1, y - 2,y - 2, y - 1, y + 1, y + 2};
    int arrX[] = {x + 1, x + 2, x + 2, x + 1, x - 1, x - 2, x - 2, x - 1};

    for (int i = 0; i <(int)(sizeof(arrX)/sizeof(arrX[0])); i++) {
        if(!checkOutOfRange(arrX[i], arrY[i], board)){
           addMovesInList(x, y, arrX[i], arrY[i], doMove, listMove, board);
        }
        else {
            continue;
        }
    }

    return listMove;
}
//
vector<Move> moveSide(int x, int y, Matrix<Pieces> &board, int dirX, int dirY) {
    vector<Move> listMoves;
    for (int X = x+dirX, Y = y+dirY; !checkOutOfRange(X, Y, board); X = X+dirX, Y = Y+dirY) {
       if(checkAddMove(X,Y,x,y, board)) {
            if(board.at(X,Y).color_piece != board.at(x,y).color_piece){
                addMoves(x,y,X, Y, listMoves);
                break;
            }
            addMoves(x,y,X, Y, listMoves);
        }
       else {

           break;
       }
    }
    return listMoves;
}

vector<Move> listMovesRook(int x, int y, Matrix<Pieces> &board) {
    vector<Move> listMoves;

    push_back_list(moveSide(x,y,board,1,0), listMoves);
    push_back_list(moveSide(x,y,board,-1,0), listMoves);
    push_back_list(moveSide(x,y,board,0,-1), listMoves);
    push_back_list(moveSide(x,y,board,0,1), listMoves);

    return listMoves;
}

vector<Move> listMovesBishop(int x, int y, Matrix<Pieces> &board) {
    vector<Move> listMoves;
    push_back_list(moveSide(x,y,board,1,1), listMoves);
    push_back_list(moveSide(x,y,board,-1,1), listMoves);
    push_back_list(moveSide(x,y,board,1,-1), listMoves);
    push_back_list(moveSide(x,y,board,-1,-1), listMoves);

    return listMoves;
}

vector<Move> listMovesPawn(int x, int y, Matrix<Pieces> &board) {
    vector<Move> listMove;
    Move doMove;
    bool flag = true;

     if(!checkOutOfRange(x,y-1, board) && board.at(x, y).color_piece == white && y != 6
             && board.at(x, y-1).name_piece == Empty) {

         addMovesInList(x, y, x, y-1, doMove, listMove, board);
     }
     else if(!checkOutOfRange(x,y+1, board) && board.at(x, y).color_piece == black && y != 1
             && board.at(x, y+1).name_piece == Empty) {

         addMovesInList(x, y, x, y+1, doMove, listMove, board);
     }
     else if(!checkOutOfRange(x,y-1, board) && board.at(x, y).color_piece == white && y == 6
             && board.at(x, y-1).name_piece == Empty) {
         addMovesInList(x, y, x, y-1, doMove, listMove, board);
     }
     else if(!checkOutOfRange(x,y-1, board) && board.at(x, y).color_piece == white && y == 6
             && board.at(x, y-1).name_piece != Empty) {
          flag = false;
     }
     if(!checkOutOfRange(x,y-2, board) && board.at(x, y).color_piece == white && y == 6
                   && board.at(x, y-2).name_piece == Empty && flag) {
               addMovesInList(x, y, x, y-2, doMove, listMove, board);
           }

     else if(!checkOutOfRange(x,y+1, board) && board.at(x, y).color_piece == black && y == 1
            && board.at(x, y+1).name_piece == Empty) {
         addMovesInList(x, y, x, y+1, doMove, listMove, board);

     }
     else if(!checkOutOfRange(x,y-1, board) && board.at(x, y).color_piece == white && y == 6
             && board.at(x, y-1).name_piece != Empty) {
          flag = false;
     }
     if(!checkOutOfRange(x,y+2, board) && board.at(x, y).color_piece == black && y == 1
                   && board.at(x, y+2).name_piece == Empty && flag) {
               addMovesInList(x, y, x, y+2, doMove, listMove, board);
           }
     if(board.at(x,y).color_piece == white) {

         if (!checkOutOfRange(x-1,y-1, board) && board.at(x-1,y-1).color_piece == black
                 && board.at(x-1, y-1).name_piece != Empty) {
            addMovesInList(x, y, x-1, y-1, doMove, listMove, board);
         }
         if(!checkOutOfRange(x+1,y-1, board) && board.at(x+1,y-1).color_piece == black
                 && board.at(x+1, y-1).name_piece != Empty){
            addMovesInList(x, y, x+1, y-1, doMove, listMove, board);
        }
     }
     if(board.at(x,y).color_piece == black) {

         if (!checkOutOfRange(x+1,y+1, board) && board.at(x+1,y+1).color_piece == white
                 && board.at(x+1, y+1).name_piece != Empty) {
            addMovesInList(x, y, x+1, y+1, doMove, listMove, board);
         }
         if(!checkOutOfRange(x-1,y+1, board) && board.at(x-1,y+1).color_piece == white
                 && board.at(x-1, y+1).name_piece != Empty){
            addMovesInList(x, y, x-1, y+1, doMove, listMove, board);
        }
     }
    return listMove;
}


void push_back_list(vector<Move> listMove, vector<Move> &everyMoveList) {

    for (int i = 0; i < (int)listMove.size(); ++i) {
        everyMoveList.push_back(listMove[i]);
    }

}

/*
In C++, a Copy Constructor may be called for the following cases:

1) When an object of the class is returned by value.
2) When an object of the class is passed (to a function) by value as an argument.
3) When an object is constructed based on another object of the same class.
4) When the compiler generates a temporary object.

*/

void printMove(Matrix<Pieces> &board, vector<Move> listMove) {
    Matrix<Pieces> newBoard(board);
    for(int i = 0; i < (int)listMove.size(); i++) {

        Move temp = listMove.at(i);
        newBoard.at(temp.xArrivle, temp.yArrivle) = newBoard.at(temp.xDeParture, temp.yDeParture);
        //newBoard.at(temp.xDeParture, temp.yDeParture) = Empty;
        cout << endl;

        cout << endl;
    }
    newBoard.printBoard();
}


void printOneMove(Matrix<Pieces> &board, vector<Move> listMove) {

    for(int i = 0; i < (int)listMove.size(); i++) {
        Matrix<Pieces> newBoard(board);
        Move temp = listMove.at(i);
        newBoard.at(temp.xArrivle, temp.yArrivle) = newBoard.at(temp.xDeParture, temp.yDeParture);
        newBoard.at(temp.xDeParture, temp.yDeParture) = Empty;
        cout << endl;
        newBoard.printBoard();
        cout << endl;
    }

}


vector<Move> listMovesQueen(int x, int y, Matrix<Pieces> &board) {
    vector<Move> listMoves;
    push_back_list(listMovesBishop(x,y,board), listMoves);
    push_back_list(listMovesRook(x,y,board), listMoves);
    //listMoves.insert(listMoves.begin(), listMovesBishop(x,y,board).begin(), listMovesBishop(x,y,board).end());
    //listMoves.insert(listMoves.end(), listMovesRook(x,y,board).begin(), listMovesRook(x,y,board).end());

    return listMoves;

}

vector<Move> everyMoveList(Matrix<Pieces> &board, color colors)  {
    vector<Move> everyListMove;
    for (int y = 0; y < board.matrHight; y++) {
        for (int x = 0; x < board.matrWidth; x++) {
            //cout << board.at(x,y).color_piece;
            if(board.at(x,y).color_piece == colors && !checkOutOfRange(x,y,board)) {
                //cout << "in if" << endl;
                switch (board.at(x,y).name_piece) {
                case king:
                    push_back_list(listMovesKing(x,y,board), everyListMove);
                    break;
                case queen:
                    push_back_list(listMovesQueen(x,y,board), everyListMove);
                    break;
                case rook:
                    push_back_list(listMovesRook(x,y,board), everyListMove);
                    break;
                case bishop:
                    push_back_list(listMovesBishop(x,y,board), everyListMove);
                    break;
                case pawn:
                    push_back_list(listMovesPawn(x,y,board), everyListMove);
                    break;
                case knight:
                    push_back_list(listMovesKnight(x,y,board), everyListMove);
                    break;
                default:
                    break;
                }
            }

            else {
                continue;
            }
        }

    }

    return everyListMove;
}



void printBoard(Matrix<Pieces> board) {
        for (int y = 0; y < board.matrHight ;y++) {
            for(int x = 0; x < board.matrWidth; x++) {
                board.at(x, y).print();

            }
            cout << endl;
        }
    }



Pieces returnPieces(pieces names, color colors) {
    Pieces pieces(names, colors);
    return pieces;

}

Pieces returnPiecesEmpty(pieces names) {
    Pieces pieces(names);
    return pieces;

}

 ostream& operator<<(ostream& os, const Pieces& piece){
    os << piece.color_piece << " " << piece.name_piece;
    return os;
}



bool checkToRookOrQueenUnif(int x, int y, Matrix<Pieces> board, int dirX, int dirY) {
    for (int X = x, Y = y; !checkOutOfRange(X, Y, board); X = X+dirX, Y = Y+dirY) {
       if(board.at(X, Y).name_piece != Empty){
            if(board.at(X, Y).name_piece == rook || board.at(X, Y).name_piece == queen) {
                if(board.at(x, y).color_piece != board.at(X, Y).color_piece) {
                    return true;
                }
            }
            else {
                return false;
            }

        }
    }
    throw runtime_error("error in function checkToRookOrQueenUnif");
}

bool checkToRookOrQueen(int x, int y, Matrix<Pieces> board){
    return
    checkToRookOrQueenUnif(x, y, board, 1, 0) ||
    checkToRookOrQueenUnif(x, y, board, -1, 0) ||
    checkToRookOrQueenUnif(x, y, board, 0, 1) ||
    checkToRookOrQueenUnif(x, y, board, 0, -1);
}

bool checkToBishopOrQueenUnif(int x, int y, Matrix<Pieces> board, int dirX, int dirY ) {
    for(int X = x, Y = y; !checkOutOfRange(X,Y, board) ; X = X+dirX, Y = Y+dirY) {
        if(board.at(X, Y).name_piece != Empty){
            if(board.at(X, Y).name_piece == bishop || board.at(X, Y).name_piece == queen ) {
                if(board.at(x, y).color_piece != board.at(X, Y).color_piece) {
                    return true;
                }
            }
            else {
                return false;
            }
        }
    }
    throw runtime_error("error in function checkToBishopOrQueenUnif");
}

bool checkToBishopOrQueen(int x, int y, Matrix<Pieces> board) {
    return
    checkToBishopOrQueenUnif(x, y, board, 1, 1) ||
    checkToBishopOrQueenUnif(x, y, board, -1, 1) ||
    checkToBishopOrQueenUnif(x, y, board, -1, -1)||
    checkToBishopOrQueenUnif(x, y, board, 1, -1);
}



bool checkToKing(int x, int y, Matrix<Pieces> board) {

    int arrY[] = {y+1, y+1, y+1, y, y-1, y-1, y-1, y};
    int arrX[] = {x+1, x, x-1, x-1, x-1, x, x+1, x+1};
    for(int i = 0; i < 8; i++) {
        if(checkOutOfRange(arrX[i], arrY[i], board)){
            continue;
        }

        if(board.at(arrX[i], arrY[i]).name_piece != Empty) {
            if(board.at(arrX[i], arrY[i]).name_piece != king){
                continue;
            }
            else {
                return true;
            }
        }

    }
    return false;
}

bool checkToPawn(int x, int y, Matrix<Pieces> board) {
    int arrY[] = {y + 1, y + 1, y - 1, y - 1};
    int arrX[] = {x + 1, x - 1, x + 1, x - 1};
    for (int i = 0; i < 4; i++) {
        if(checkOutOfRange(arrX[i], arrY[i], board)){
            continue;
        }
        if(board.at(arrX[i], arrY[i]).name_piece != Empty) {
            if(board.at(arrX[i], arrY[i]).name_piece != pawn) {
                continue;
            }
            if(board.at(arrX[i], arrY[i]).name_piece == pawn && board.at(x, y).color_piece == board.at(arrX[i], arrY[i]).color_piece) {
                continue;
            }
            else if(board.at(arrX[i], arrY[i]).name_piece == pawn && board.at(x, y).color_piece != board.at(arrX[i], arrY[i]).color_piece) {
                return true;
            }
        }
    }

    return false;
}

bool checkToKnight(int x, int y, Matrix<Pieces> board) {
    int arrY[] = {y + 2, y + 1, y - 1, y - 2,y - 2, y - 1, y + 1, y + 2};
    int arrX[] = {x + 1, x + 2, x + 2, x + 1, x - 1, x - 2, x - 2, x - 1};
    for (int i = 0; i < 8; i++)
    {
        if(checkOutOfRange(arrX[i], arrY[i], board)){
            continue;
        }
        if(board.at(arrX[i], arrY[i]).name_piece != Empty) {
            if(board.at(arrX[i], arrY[i]).name_piece != knight) {
                continue;
            }
            if(board.at(arrX[i], arrY[i]).name_piece == knight && board.at(x, y).color_piece == board.at(arrX[i], arrY[i]).color_piece) {
                continue;
            }
            else if(board.at(arrX[i], arrY[i]).name_piece == knight && board.at(x, y).color_piece != board.at(arrX[i], arrY[i]).color_piece) {
                return true;
            }
        }
    }

    return false;
}


bool checkCheck(int x, int y, Matrix<Pieces> board) {

    return (checkToRookOrQueen(x, y, board) || checkToBishopOrQueen(x, y, board) || checkToKing(x, y, board) || checkToPawn(x, y, board) || checkToKnight(x, y, board));

}


int main (int argc, char* argv[]){

    Pieces board[64] = {
    returnPieces(rook, black), returnPieces(bishop, black), returnPieces(knight, black), returnPieces(queen, black), returnPieces(king, black), returnPieces(knight, black), returnPieces(bishop, black), returnPieces (rook, black),
    returnPieces(pawn, black), returnPieces(pawn, black), returnPieces(pawn, black) , returnPieces(pawn, black), returnPieces(pawn, black), returnPieces(pawn, black), returnPieces (pawn, black), returnPieces(pawn, black),
    returnPiecesEmpty(Empty), returnPiecesEmpty(Empty), returnPiecesEmpty(Empty),returnPiecesEmpty(Empty),returnPiecesEmpty(Empty), returnPiecesEmpty(Empty),returnPiecesEmpty(Empty),returnPiecesEmpty(Empty),
    returnPiecesEmpty(Empty), returnPiecesEmpty(Empty), returnPiecesEmpty(Empty),returnPiecesEmpty(Empty),returnPiecesEmpty(Empty), returnPiecesEmpty(Empty),returnPiecesEmpty(Empty),returnPiecesEmpty(Empty),
    returnPiecesEmpty(Empty), returnPiecesEmpty(Empty), returnPiecesEmpty(Empty),returnPiecesEmpty(Empty),returnPiecesEmpty(Empty), returnPiecesEmpty(Empty),returnPiecesEmpty(Empty),returnPiecesEmpty(Empty),
    returnPiecesEmpty(Empty), returnPiecesEmpty(Empty), returnPiecesEmpty(Empty),returnPieces(queen, black),returnPiecesEmpty(Empty), returnPiecesEmpty(Empty),returnPiecesEmpty(Empty),returnPiecesEmpty(Empty),
    returnPieces(pawn, white), returnPieces(pawn, white), returnPieces(pawn, white) ,returnPieces(pawn, white), returnPieces(pawn, white), returnPieces(pawn, white) , returnPieces(pawn, white), returnPieces(pawn, white),
    returnPieces(rook, white), returnPieces(bishop, white), returnPieces(knight, white), returnPieces(queen, white), returnPieces(king, white), returnPieces(knight, white), returnPieces(bishop, white), returnPieces (rook, white),
};


    Matrix<Pieces>  chess(8,8);

    Pieces P1;
    Pieces P2;
    //cout <<"P1 == P2 " << (P1==P2) << endl; //TODO разобраться с данным предупреждением ISO C++20 considers use of overloaded operator '==' (with operand types 'Pieces' and 'Pieces') to be ambiguous despite there being a unique best viable function

    //Matrix<int> chess(3,3);

    //Pieces* x=new Pieces[42];

    chess.assignmentForArr(board, 8, 8);
    cout << "6,0";
    chess.at(6,0).print() ;
    cout << endl;
    //X x {1, 2, 3, 4, 5};

     //Pieces e {1, 2, 3, 4, 5};
    //board[0].print();
    //Pieces king1(king, white);
    //king1.print();
    printBoard(chess);

    //cout << checkCheck(4,0,chess)<< endl;
    Move m;
    //printVector(everyMoveList(chess, white));
    //printVector(listMovesQueen(3,5,chess));
    printOneMove(chess, everyMoveList(chess, white));

    //m.Print(m.xArrivle);

     //chess.at(1,2)=42;

    //cout << king1;
     //cout << chess.at(1,2);

return 0;
}
