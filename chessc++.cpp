#include <iostream>
#include <stdexcept>
#include <cstdio>
#include <string>
#include <initializer_list>
#include <cassert> 
#include <vector>
#include <fstream>

using namespace std;


enum  pieces {king, queen, bishop, knight, rook, pawn, Empty};
enum color {white, black};

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
        cout << "calling constructor" << endl;
        //matr = new T [hight*width]; TODO попробовать разобраться с нью в такой записи и разобраться с Malloc стек с повторным освобождением памяти
        
        matr = (T*)malloc(sizeof(T)*hight*width);
    }
    // WSL
    // Amazon AWS - cloud9
    

    ~Matrix(){
        cout << "calling destructor" << endl;
        //delete matr;
        //free(matr);
    } 
    
    T& at(int x, int y) {
        if(x > matrWidth || y > matrHight){
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
        for (int i = 0; i < matrWidth+matrHight; i++)
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
    //vector<Pieces> m; 
    pieces name_piece;
    color color_piece;
    void SetName(pieces name_piece, color color_piece) {
        this->name_piece = name_piece;
        this->color_piece = color_piece;
    }

    

    Pieces (pieces name_piece, color color_piece) {
	    this->name_piece = name_piece;
	    this->color_piece = color_piece;
    }
    
    Pieces (pieces name_piece) {
	this->name_piece = name_piece;
    }

    

    void print(){
        if(name_piece == 0 && color_piece == 1) {
            printf("[\u2654]");
        }
        else if(name_piece == 1 && color_piece == 1) {
            printf("[\u2655]");
        }
        else if(name_piece == 2 && color_piece == 1) {
            printf("[\u2657]");
        }
        else if(name_piece == 3 && color_piece == 1) {
            printf("[\u2658]");
        }
        else if(name_piece == 4 && color_piece == 1) {
            printf("[\u2656]");
        }
        else if(name_piece == 5 && color_piece == 1) {
            printf("[\u2659]");
        }
        else if(name_piece == 6) {
            printf("[ ]");
        }
        else if(name_piece == 0 && color_piece == 0) {
           printf("[\u265A]");
        }
        else if(name_piece == 1 && color_piece == 0) {
            printf("[\u265B]");
        }
        else if(name_piece == 2 && color_piece == 0) {
            printf("[\u265D]");
        }
        else if(name_piece == 3 && color_piece == 0) {
            printf("[\u265E]");
        }
        else if(name_piece == 4 && color_piece == 0) {
            printf("[\u265C]");
        }
        else if(name_piece == 5 && color_piece == 0) {
            printf("[\u265F]");
        }
    }

    
};

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

bool checkToRookOrQueen(int x, int y, Matrix<Pieces> board){
    for(int X = 0; X < 8; X++) {
        if(board.at(X, y).name_piece != Empty){
            if(board.at(X, y).name_piece != rook || board.at(X, y).name_piece != queen) {
                return false;
            }
            else if(board.at(X, y).name_piece == rook || board.at(X, y).name_piece == queen && board.at(x, y).color_piece != board.at(X, y).color_piece) {
                return true;	
                } 
            } 
    }
    for(int X = 7; X >= 0; X--) {
        if(board.at(X, y).name_piece != Empty){
            if(board.at(X, y).name_piece != rook || board.at(X, y).name_piece != queen) {
                return false;
            }
            else if(board.at(X, y).name_piece == rook || board.at(X, y).name_piece == queen && board.at(x, y).color_piece != board.at(X, y).color_piece) {
                return true;	
                } 
            } 
    }
    for(int Y = 0; Y < 8; Y++) {
        if(board.at(x, Y).name_piece != Empty){
            if(board.at(x, Y).name_piece != rook || board.at(x, Y).name_piece != queen) {
                return false;
            }
            else if(board.at(x, Y).name_piece == rook || board.at(x, Y).name_piece == queen && board.at(x, y).color_piece != board.at(x, Y).color_piece) {
                return true;	
                } 
            } 
    }
    for(int Y = 7; Y >=0 ; Y--) {
        if(board.at(x, Y).name_piece != Empty){
            if(board.at(x, Y).name_piece != rook || board.at(x, Y).name_piece != queen) {
                return false;
            }
            else if(board.at(x, Y).name_piece == rook || board.at(x, Y).name_piece == queen && board.at(x, y).color_piece != board.at(x, Y).color_piece) {
                return true;	
                } 
            } 
    }  
    return false; 
}

bool checkToBishopOrQueen(int x, int y, Matrix<Pieces> board) {
    for(int X, Y = 0; X < 8 && Y < 8; X++, Y++) {
	    if(board.at(X, Y).name_piece != Empty){
            if(board.at(X, Y).name_piece != bishop || board.at(X, Y).name_piece != queen) {
                return false;
            }
            else if(board.at(X, Y).name_piece == bishop || board.at(X, Y).name_piece == queen && board.at(x, y).color_piece != board.at(X, Y).color_piece) {
                return true;	
            } 
        }  
    } 
    for(int X = 7, Y = 0; X >= 0 && Y < 8; X--, Y++) {
	    if(board.at(X, Y).name_piece != Empty){
            if(board.at(X, Y).name_piece != bishop || board.at(X, Y).name_piece != queen) {
                return false;
            }
            else if(board.at(X, Y).name_piece == bishop || board.at(X, Y).name_piece == queen && board.at(x, y).color_piece != board.at(X, Y).color_piece) {
                return true;	
            } 
        }  
    } 
    for(int X = 0, Y = 7; X < 8 && Y >= 0; X++, Y--) {
	    if(board.at(X, Y).name_piece != Empty){
            if(board.at(X, Y).name_piece != bishop || board.at(X, Y).name_piece != queen) {
                return false;
            }
            else if(board.at(X, Y).name_piece == bishop || board.at(X, Y).name_piece == queen && board.at(x, y).color_piece != board.at(X, Y).color_piece) {
                return true;	
            } 
        }  
    } 
    for(int X = 7, Y = 7; X >= 0 && Y >= 0; X--, Y--) {
	    if(board.at(X, Y).name_piece != Empty){
            if(board.at(X, Y).name_piece != bishop || board.at(X, Y).name_piece != queen) {
                return false;
            }
            else if(board.at(X, Y).name_piece == bishop || board.at(X, Y).name_piece == queen && board.at(x, y).color_piece != board.at(X, Y).color_piece) {
                return true;	
            } 
        }  
    } 
    return false;
}


bool checkToKing(int x, int y, Matrix<Pieces> board) {
    
    int arrY[] = {y+1, y+1, y+1, y, y-1, y-1, y-1, y};
    int arrX[] = {x+1, x, x-1, x-1, x-1, x, x+1, x+1};
    for(int i = 0; i < 8; i++) {
        if(board.at(arrY[i], arrX[i]).name_piece != Empty) {
            if(board.at(arrY[i], arrX[i]).name_piece != king){
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
        if(board.at(arrY[i], arrX[i]).name_piece != Empty) {
            if(board.at(arrY[i], arrX[i]).name_piece != pawn) {
                continue;
            }
            if(board.at(arrY[i], arrX[i]).name_piece == pawn && board.at(x, y).color_piece == board.at(arrY[i], arrX[i]).color_piece) {
                continue;
            }
            else if(board.at(arrY[i], arrX[i]).name_piece == pawn && board.at(x, y).color_piece != board.at(arrY[i], arrX[i]).color_piece) {
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
        if(board.at(arrY[i], arrX[i]).name_piece != Empty) {
            if(board.at(arrY[i], arrX[i]).name_piece != knight) {
                continue;
            }
            if(board.at(arrY[i], arrX[i]).name_piece == knight && board.at(x, y).color_piece == board.at(arrY[i], arrX[i]).color_piece) {
                continue;
            }
            else if(board.at(arrY[i], arrX[i]).name_piece == knight && board.at(x, y).color_piece != board.at(arrY[i], arrX[i]).color_piece) {
                return true;
            }
        }
    }
    
    return false;
}


bool check(int x, int y, Matrix<Pieces> board) {

    return (checkToRookOrQueen(x, y, board) || checkToBishopOrQueen(x, y, board) || checkToKing(x, y, board) || checkToPawn(x, y, board) || checkToKing(x, y, board));
    
}


int main (int argc, char* argv[]){

    Pieces board[64] = {
    returnPieces(rook, black), returnPieces(bishop, black), returnPieces(knight, black), returnPieces(king, black), returnPieces(queen, black), returnPieces(knight, black), returnPieces(bishop, black), returnPieces (rook, black),
    returnPieces(pawn, black), returnPieces(pawn, black), returnPieces(pawn, black) , returnPieces(pawn, black), returnPieces(pawn, black), returnPieces(pawn, black) , returnPieces (pawn, black), returnPieces(pawn, black),
    returnPiecesEmpty(Empty), returnPiecesEmpty(Empty), returnPiecesEmpty(Empty),returnPiecesEmpty(Empty),returnPiecesEmpty(Empty), returnPiecesEmpty(Empty),returnPiecesEmpty(Empty),returnPiecesEmpty(Empty),
    returnPiecesEmpty(Empty), returnPiecesEmpty(Empty), returnPiecesEmpty(Empty),returnPiecesEmpty(Empty),returnPiecesEmpty(Empty), returnPiecesEmpty(Empty),returnPiecesEmpty(Empty),returnPiecesEmpty(Empty),
    returnPiecesEmpty(Empty), returnPiecesEmpty(Empty), returnPiecesEmpty(Empty),returnPiecesEmpty(Empty),returnPiecesEmpty(Empty), returnPiecesEmpty(Empty),returnPiecesEmpty(Empty),returnPiecesEmpty(Empty),
    returnPiecesEmpty(Empty), returnPiecesEmpty(Empty), returnPiecesEmpty(Empty),returnPiecesEmpty(Empty),returnPiecesEmpty(Empty), returnPiecesEmpty(Empty),returnPiecesEmpty(Empty),returnPiecesEmpty(Empty),
    returnPieces(pawn, white), returnPieces(pawn, white), returnPieces(pawn, white) , returnPieces(pawn, white), returnPieces(pawn, white), returnPieces(pawn, white) , returnPieces (pawn, white), returnPieces(pawn, white),
    returnPieces(rook, white), returnPieces(bishop, white), returnPieces(knight, white), returnPieces(king, white), returnPieces(queen, white), returnPieces(knight, white), returnPieces(bishop, white), returnPieces (rook, white),	
};

    
    Matrix<Pieces>  chess(8,8);
    
    //Matrix<int> chess(3,3);
    
    //Pieces* x=new Pieces[42];
    
    chess.assignmentForArr(board, 8, 8); 
    //cout << chess.at(6,4);
    //X x {1, 2, 3, 4, 5};
    
     //Pieces e {1, 2, 3, 4, 5};
    //board[0].print();
    //Pieces king1(king, white);
    //king1.print();
    printBoard(chess);
     
     //chess.at(1,2)=42;
    
    //cout << king1;
     //cout << chess.at(1,2);
     
return 0;
}