#include <iostream>
#include <stdexcept>
#include <cstdio>
#include <string>
#include <initializer_list>
#include <cassert> 
#include <vector>

using namespace std;


enum  pieces {king, queen, bishop, knight, rook, pawn, Empty};
enum color {white, black};


class Matrix 
{

public:
    int* matr;
    int matrWidth;
    int matrHight;
    
    
    Matrix(int width, int hight) {
	matrWidth = width;
	matrHight = hight;
	matr = new int [hight*width];
    }
    
    int& at(int x, int y) {
	if(x > matrWidth || y > matrHight){
	    // TODO: std::format - выдает ошибку при подключении библиотеки формат
	    
	    // TODO templates
        /* tempalte <typename T> 
        T foo(T a){ }*/

	    // TODO 
	    string mssg = "width= "+to_string(matrWidth)+" hight= "+to_string(matrHight) +" ,but "+" x="+to_string(x)+" y="+to_string(y);
	    throw out_of_range(mssg);
	}
	return matr[y * matrWidth + x];
    }
    
    void assignmentForArr(int* arr, int x, int y) {
	for(int i = 0; i < x*y; i++) {
	    matr[i] = arr[i];
	}
	
    }
};
//TODO can we overload curly bracees and equal
class X {
    vector<int> m_v; 

public:
    X(initializer_list<int> v)
        : m_v(v) 
    { } 
};


class Pieces {
    
    vector<Pieces> m; 
    pieces name_piece;
    color color_piece;
    
    
 
    

    public:
        Pieces (initializer_list<Pieces> t)
            : m(t) 
        { } 
    
    
    Pieces () {
	
    }

    Pieces (pieces name_piece, color color_piece) {
	    this->name_piece = name_piece;
	    this->color_piece = color_piece;
    }
    
    Pieces (pieces name_piece) {
	this->name_piece = name_piece;
    }

    Pieces operator[](int index) {
        
        return  m[index];
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

    void printBoard() {
        for (int i = 0; i < m.size(); i++)
        {
            
            m[i].print();
            if((i+1)%8 == 0) {
                cout << endl;
            }
        }
        
    }

};

Pieces returnPieces(pieces names, color colors) {
    Pieces pieces(names, colors);
    return pieces;

}

Pieces returnPiecesEmpty(pieces names) {
    Pieces pieces(names);
    return pieces;

}
//TODO функция которая печатает доску

int main (){

    Pieces board  {
    returnPieces(rook, black), returnPieces(bishop, black), returnPieces(knight, black), returnPieces(king, black), returnPieces(queen, black), returnPieces(knight, black), returnPieces(bishop, black), returnPieces (rook, black),
    returnPieces(pawn, black), returnPieces(pawn, black), returnPieces(pawn, black) , returnPieces(pawn, black), returnPieces(pawn, black), returnPieces(pawn, black) , returnPieces (pawn, black), returnPieces(pawn, black),
    returnPiecesEmpty(Empty), returnPiecesEmpty(Empty), returnPiecesEmpty(Empty),returnPiecesEmpty(Empty),returnPiecesEmpty(Empty), returnPiecesEmpty(Empty),returnPiecesEmpty(Empty),returnPiecesEmpty(Empty),
    returnPiecesEmpty(Empty), returnPiecesEmpty(Empty), returnPiecesEmpty(Empty),returnPiecesEmpty(Empty),returnPiecesEmpty(Empty), returnPiecesEmpty(Empty),returnPiecesEmpty(Empty),returnPiecesEmpty(Empty),
    returnPiecesEmpty(Empty), returnPiecesEmpty(Empty), returnPiecesEmpty(Empty),returnPiecesEmpty(Empty),returnPiecesEmpty(Empty), returnPiecesEmpty(Empty),returnPiecesEmpty(Empty),returnPiecesEmpty(Empty),
    returnPiecesEmpty(Empty), returnPiecesEmpty(Empty), returnPiecesEmpty(Empty),returnPiecesEmpty(Empty),returnPiecesEmpty(Empty), returnPiecesEmpty(Empty),returnPiecesEmpty(Empty),returnPiecesEmpty(Empty),
    returnPieces(pawn, white), returnPieces(pawn, white), returnPieces(pawn, white) , returnPieces(pawn, white), returnPieces(pawn, white), returnPieces(pawn, white) , returnPieces (pawn, white), returnPieces(pawn, white),
    returnPieces(rook, white), returnPieces(bishop, white), returnPieces(knight, white), returnPieces(king, white), returnPieces(queen, white), returnPieces(knight, white), returnPieces(bishop, white), returnPieces (rook, white),	
};
    Matrix chess(8,8);
    //cout << chess.at(6,4);
     X x {1, 2, 3, 4, 5};
     
     //Pieces e {1, 2, 3, 4, 5};
    //board[0].print();
    Pieces king1(king, white);
    //king1.print();
    board.printBoard();
     
     chess.at(1,2)=42;
     
     //cout << chess.at(1,2);
     
return 0;
}