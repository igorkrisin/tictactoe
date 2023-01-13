#include <iostream>
#include <stdexcept>
#include <cstdio>
#include <string>
#include <initializer_list>
#include <cassert>
#include <vector>
#include <fstream>
#include <array>
#include <utility>
#include <regex>
#include <variant>
#include <ctime>


using namespace std;


enum  pieces {king, queen, bishop, knight, rook, pawn, Empty};
enum color {black,white};

template <typename T>

class Matrix
{

private:
    bool possCastLeftWhite = false;
    bool possCastLeftBlack = false;
    bool possCastRightWhite = false;
    bool possCastRightBlack = false;

    T* matr;
public:
    array<bool, 8> enpasWhite = {false, false, false, false, false, false, false, false};
    array<bool, 8> enpasBlack = {false, false, false, false, false, false, false, false};

    int xKingWhite = 4;
    int yKingWhite = 7;
    int xKingBlack = 4;
    int yKingBlack = 0;
    int matrWidth;
    int matrHight;
    color currentColor = white;


    Matrix(int width, int hight) {
        matrWidth = width;
        matrHight = hight;
        //cout << "calling constructor" << this << endl;
        matr = new T [hight*width];
    }

    Matrix( Matrix &other) {
        this->matrWidth = other.matrWidth;
        this->matrHight = other.matrHight;
        this->possCastLeftBlack = other.getPossLB();
        this->possCastRightWhite = other.getPossRW();
        this->possCastRightBlack = other.getPossRB();
        this->possCastLeftWhite = other.getPossLW();

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

    void resetFlagsWhite(){
        for(int i = 0; i < (int)enpasWhite.size(); ++i){
            enpasWhite[i] = false;
        }
    }
     void resetFlagsBlack(){
        for(int i = 0; i  < (int)enpasBlack.size(); ++i){
            enpasBlack[i] = false;
        }
    }

     void printEnpass(array<bool, 8> arr){
         cout << "enpassBoolList: " <<  "[ ";
         for (int i = 0; i < (int)arr.size(); ++i) {
             cout << arr[i] << ", ";
         }
         cout << "]" << endl;
     }

    bool getPossLW() {
        return possCastLeftWhite;
    }
    bool getPossLB() {
        return possCastLeftBlack;
    }
    bool getPossRW() {
        return possCastRightWhite;
    }
    bool getPossRB() {
        return possCastRightBlack;
    }

    void setPossLW(bool possCastLeftWhite){
        this->possCastLeftWhite = possCastLeftWhite;
    }

    void setPossLB(bool possCastLeftBlack){
        this->possCastLeftBlack = possCastLeftBlack;
    }

    void setPossRW(bool possCastRightWhite){
        this->possCastRightWhite = possCastRightWhite;
    }

    void setPossRB(bool possCastRightBlack){
        this->possCastRightBlack = possCastRightBlack;
    }

    void assignmentForArr(T* arr, int x, int y) {
        for(int i = 0; i < x*y; i++) {
            matr[i] = arr[i];
    }

    }

    void printKingCoord(){
        char simb ='a';
        char printSimbWh = simb+yKingWhite;
        char printSimbBl = simb+yKingBlack;
        cout << "king Wh: " << xKingWhite+1 << ", "<< printSimbWh << " ";
        cout << "king Bl: " << xKingBlack+1 << ", "<< printSimbBl << endl;
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
    X(initializer_list<int> v)//TODO печать списков в шахматной нотации сделать
    //TODO сделать инициализатор для массива доски
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
            cout << "name_piece = " << name_piece << ",  color_piece = " << color_piece << endl;
            cout << "error in printBoard";
        }
    }


    bool operator== (const Pieces &other) const {
        //cout << "!!!overload == : " << (this->name_piece == other.name_piece && this->color_piece == other.color_piece) << endl;
        return this->name_piece == other.name_piece && this->color_piece == other.color_piece;
    }
};

enum castling{rightWhite, leftWhite, rightBlack, leftBlack};

class Move {
private:
    int xDeParture;
    int yDeParture;
    int xArrivle;
    int yArrivle;


public:

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


    vector <variant<Move, castling>> move, state;


    void Print(int xArrivle) {
        cout << xArrivle;
    }

    bool operator ==(const Move &other) const{
        if(
                this->xDeParture == other.xDeParture && this->yDeParture == other.yDeParture &&
                this->xArrivle == other.xArrivle && this->yArrivle == other.yArrivle ){
            return true;

        }
        return false;
    }


    int getXDep(){

        return xDeParture;
    }
    int getYDep(){

        return yDeParture;
    }
    int getXArr(){

        return xArrivle;
    }
    int getYArr(){

        return yArrivle;
    }


    void setXDep(int xDeparture) {
        this->xDeParture = xDeparture;
    }
    void setYDep(int yDeparture) {
        this->yDeParture = yDeparture;
    }
    void setXArr(int xArrivle) {
        this->xArrivle = xArrivle;
    }
    void setYArr(int yArrivle) {
        this->yArrivle = yArrivle;
    }
};

//////////////////////////////////////////////////////////////////////////////////////// class end///////////////////////////////////////////////////////

void push_back_list(vector<variant<Move, castling>> &listMove, vector<variant<Move, castling>> &everyMoveList);//прототип!!!//////////////////////////////////////////////////////////
bool checkCheck(int x, int y, Matrix<Pieces> &board);
bool checkForCheck(int x, int y, Matrix<Pieces> &board, color colors);
void printOneMove(Matrix<Pieces> &board, vector<variant<Move, castling>> &listMove);
void printMove(Matrix<Pieces> &board, vector<variant<Move, castling>> &listMove);
vector<variant<Move, castling>>& everyMoveList(Matrix<Pieces> &board, color colors)  ;
color swapColor(color &colors);
void printVector(vector<variant<Move, castling>> arr);
Pieces P(pieces names, color colors);
bool checkOutOfRange(int x, int y, Matrix<Pieces> &board);
vector<variant<Move, castling>> &listMovesKing(int x, int y, Matrix<Pieces> &board);
vector<variant<Move, castling>>& filterIlegalMove(vector<variant<Move, castling>> &listMove,  Matrix<Pieces> &board, color colors);
bool isCastling(Matrix<Pieces> &board, castling state, color colors);
bool checkMoveInEverList(vector<variant<Move, castling>> &everyMoveList, variant<Move, castling> move);
variant<Move, castling> createMove(int xDep, int yDep, int xArr, int yArr);
void printCastling(castling state);
int converToChessX(int coord);
char converToChessY(int coord);
void printMove(variant<Move, castling> move);


int getYDep(variant<Move, castling> move){

    return get<Move>(move).getYDep();
}

int getXDep(variant<Move, castling> move){

    return get<Move>(move).getXDep();
}

int getYArr(variant<Move, castling> move){

    return get<Move>(move).getYArr();
}

int getXArr(variant<Move, castling> move){

    return get<Move>(move).getXArr();
}

void setXDep(variant<Move, castling> &move, int x) {
    get<Move>(move).setXDep(x);
}
void setYDep(variant<Move, castling> &move, int y) {
    get<Move>(move).setYDep(y);
}

void setXArr(variant<Move, castling> &move, int x) {
    get<Move>(move).setXArr(x);
}

void setYArr(variant<Move, castling> &move, int y) {
    get<Move>(move).setYArr(y);
}

void addMoves(int &x, int &y, int xDir, int yDir, vector<variant<Move, castling>> &listMove) {
    variant<Move, castling> move;
    setXDep(move, x);
    setYDep(move, y);
    setXArr(move, xDir);
    setYArr(move, yDir);
    listMove.push_back(move);
}

bool comparVectorAndMove(vector<variant<Move, castling>> &listMove, variant<Move, castling> move){
    if(listMove.empty()){
        return false;
    }
    if(holds_alternative<castling>(move)){
        return false;
    }
    if( holds_alternative<Move>(listMove[0]) && holds_alternative<Move>(move)){
        if(getXDep(listMove[0]) != getXDep(move)){
            return false;
        }
        if(getYDep(listMove[0]) != getYDep(move)){
            return false;
        }
        if(getXArr(listMove[0]) != getXArr(move)){
            return false;
        }
        if(getYArr(listMove[0]) != getYArr(move)){
            return false;
        }
    }

    return true;
}



vector<variant<Move, castling>> & Castling(Matrix<Pieces> & board, color colors) {
    //координаты castling для белых
    array <int, 2> kingDepW = {4, 7};
    array <int, 2> rookhDepWL = {0, 7};
    array <int, 2> rookDepWR = {7, 7};
    //координаты castling для черных
    array <int, 2> kingDepBl = {4, 0};
    array <int, 2> rookDepBlL = {0, 0};
    array <int, 2> rookDepBlR = {7, 0};
    vector<variant<Move, castling>> *listMoves = new vector<variant<Move, castling>>;
    //проверяем есть ли слева у белых кастлинг
    //cout << "!!!!!!enter cast!!!" << endl;
    //cout << "listMoves->size() =  "  << listMoves->size();
    if(board.at(kingDepW.at(0),kingDepW.at(1)).name_piece == king && board.at(kingDepW.at(0),kingDepW.at(1)).color_piece == colors){
        if(board.at(rookhDepWL.at(0),rookhDepWL.at(1)).name_piece == rook  && board.at(rookhDepWL.at(0),rookhDepWL.at(1)).color_piece == colors &&
           board.at(1,7).name_piece == Empty && board.at(2,7).name_piece == Empty && board.at(3,7).name_piece == Empty){
            //White Left add in list;

            listMoves->push_back(leftWhite);
        }
        if(board.at(rookDepWR.at(0),rookDepWR.at(1)).name_piece == rook && board.at(rookDepWR.at(0),rookDepWR.at(1)).color_piece == colors &&
           board.at(5,7).name_piece == Empty && board.at(6,7).name_piece == Empty){
            //White Right add in list;

            listMoves->push_back(rightWhite);
        }
    }//newList->push_back(listMove.at(i));
    if(board.at(kingDepBl.at(0),kingDepBl.at(1)).name_piece == king && board.at(kingDepBl.at(0),kingDepBl.at(1)).color_piece == colors){
        if(board.at(rookDepBlL.at(0),rookDepBlL.at(1)).name_piece == rook && board.at(rookDepBlL.at(0),rookDepBlL.at(1)).color_piece == colors &&
                board.at(1,0).name_piece == Empty && board.at(2,0).name_piece == Empty && board.at(3,0).name_piece == Empty){
            //Black Left add in list;

            listMoves->push_back(leftBlack);
        }
        if(board.at(rookDepBlR.at(0),rookDepBlR.at(1)).name_piece == rook && board.at(rookDepBlR.at(0),rookDepBlR.at(1)).color_piece == colors &&
                board.at(5,0).name_piece == Empty && board.at(6,0).name_piece == Empty){
            //Black Right add in list;

            listMoves->push_back(rightBlack);

        }
    }


    return *listMoves;

}

vector<variant<Move, castling>>& enpassant(Matrix<Pieces> & board, color colors){
    //cout << "enter enpassant!!!" << endl;
    //cout << "empasWhiteList: "; board.printEnpass(board.enpasWhite);
    //cout << "empasBlackList: "; board.printEnpass(board.enpasBlack);
    int yEnpasWhite = 3;
    int yEnpasBlack = 4;
    vector<variant<Move, castling>> *listMoves = new vector<variant<Move, castling>>;
    for (int i = 0; i < (int)board.enpasBlack.size(); ++i) {
        if(colors == black && board.enpasBlack[i] == true){
            //cout << "enter to true enpass black" << endl;
            if(!checkOutOfRange(i+1,4, board) && board.at(i+1, yEnpasBlack).name_piece == pawn && board.at(i+1, yEnpasBlack).color_piece == black) {
                board.resetFlagsBlack();
                listMoves->push_back(createMove(i+1, yEnpasBlack, i, 5));
            }
            else if(!checkOutOfRange(i-1,yEnpasBlack, board) && board.at(i-1, yEnpasBlack).name_piece == pawn && board.at(i-1, yEnpasBlack).color_piece == black) {
                board.resetFlagsBlack();
                listMoves->push_back(createMove(i-1, yEnpasBlack, i, 5));
            }
        }
        else if(colors == white && board.enpasWhite[i] == true){
            //cout << "enter to true enpass white" << endl;
            if(!checkOutOfRange(i+1, 3, board) && board.at(i+1, yEnpasWhite).name_piece == pawn && board.at(i+1, yEnpasWhite).color_piece == white) {
                board.resetFlagsWhite();
                listMoves->push_back(createMove(i+1, yEnpasWhite, i, 2));
            }
            else if(!checkOutOfRange(i-1, yEnpasWhite, board) && board.at(i-1, yEnpasWhite).name_piece == pawn && board.at(i-1, yEnpasWhite).color_piece == white) {
                board.resetFlagsWhite();
                listMoves->push_back(createMove(i-1, yEnpasWhite, i, 2));
            }
        }
    }
    //printVector(*listMoves);

    return *listMoves;
}


Matrix<Pieces> & moveCastlingRight(Matrix<Pieces> & board, color colors){
    //cout << "in Move castling" << endl;

    if(colors == black){
       board.at(4,0) = Empty;
       board.at(7,0) = Empty;
       board.at(5,0) = P(rook, colors);
       board.at(6,0) = P(king, colors);
       return board;
    }
    else if (colors == white){
       board.at(4,7) = Empty;
       board.at(7,7) = Empty;
       board.at(5,7) = P(rook, colors);
       board.at(6,7) = P(king, colors);
       return board;
    }
 throw invalid_argument("ERROR in function moveCastling ");
}


Matrix<Pieces> & moveCastlingLeft(Matrix<Pieces> & board, color colors){
    //cout << "in Move castling" << endl;

    if(colors == black){
       board.at(4,0) = Empty;
       board.at(0,0) = Empty;
       board.at(3,0) = P(rook, colors);
       board.at(2,0) = P(king, colors);
       return board;
    }
    else if(colors == white){
       board.at(4,7) = Empty;
       board.at(0,7) = Empty;
       board.at(3,7) = P(rook, colors);
       board.at(2,7) = P(king, colors);
       return board;
    }
 throw invalid_argument("ERROR in function moveCastling ");
}

void possibCastl(Matrix<Pieces> & board, variant<Move, castling> move){
    if(holds_alternative<Move>(move)){
         if(getXDep(move) == 0 && getYDep(move) == 0 && board.getPossLB() == false){
            board.setPossLB(true);
        }
        else if(getXDep(move) == 7 && getYDep(move) == 0 && board.getPossLB() == false){
            board.setPossRB(true);
        }
        else if( getXDep(move) == 0 && getYDep(move) == 7 && board.getPossLB() == false){
            board.setPossLW(true);
        }
        else if(getXDep(move) == 7 && getYDep(move) == 7 && board.getPossLB() == false){
            board.setPossRW(true);
        }
        else if(getXDep(move) == 4 && getYDep(move) == 0 && board.getPossLB() == false){
              board.setPossLB(true);
              board.setPossRB(true);
        }
        else if(getXDep(move) == 4 && getYDep(move) == 7 && board.getPossLB() == false){
              board.setPossLW(true);
              board.setPossRW(true);
        }
        else if(holds_alternative<castling>(move)){
            if(get<castling>(move) == rightBlack || get<castling>(move) == leftBlack ) {
                board.setPossLB(true);
                board.setPossRB(true);
            }
            if(get<castling>(move) == rightWhite || get<castling>(move) == leftWhite ) {
                board.setPossLW(true);
                board.setPossRW(true);
            }


        }
    }
    //cout << "in possible Cast finish" << endl;
}

bool isEnpassant(Matrix<Pieces> & board, variant<Move, castling> move) {
    //cout << "in is Enpass" << endl;
    if(board.at(getXDep(move), getYDep(move)).name_piece == pawn){
        if(getXArr(move) - getXDep(move) != 0 && board.at(getXArr(move), getYArr(move)).name_piece == Empty){
            //cout << "enPass true" << endl;
           return true;
        }
      }
     //cout << "enPass false" << endl;
    return false;
}
//           && board.at(getXDep(move) + lookRight, getYDep(move)).name_piece == pawn
//&& board.at(getXDep(move) + lookRight, getYDep(move)).color_piece == swapColor(board.at(getXDep(move), getYDep(move)).color_piece)
//&& ()){

Matrix<Pieces> & moveForBoard(Matrix<Pieces> & board, variant<Move, castling> move) {

    //cout << "board.at: ";board.at(getXDep(move), getYDep(move)).print(); cout << endl;
    //cout << ";P(pawn, white): ";P(pawn, white).print(); cout << endl;
    //cout << "in Move  moveForBoard start" << endl;

    possibCastl(board, move);

        //cout << "in Move  moveForBoard" << endl;
        if(holds_alternative<castling>(move) ){
               //cout << "in cast moveForBoard"  << endl;
               if(get<castling>(move) == leftWhite && !board.getPossLW()){
                   board.setPossLW(true);
                   moveCastlingLeft(board, white);
                   board.xKingWhite = 2;
                   board.yKingWhite = 7;
               }
               if( get<castling>(move) == leftBlack && !board.getPossLB()){
                   board.setPossLB(true);
                   moveCastlingLeft(board, black);
                   board.xKingBlack = 2;
                   board.yKingBlack = 0;
               }
               if(get<castling>(move) == rightWhite && !board.getPossRW()) {
                   board.setPossRW(true);
                   moveCastlingRight(board, white);
                   board.xKingWhite = 6;
                   board.yKingWhite = 7;
               }
               if(get<castling>(move) == rightBlack && !board.getPossRB()){
                   board.setPossRB(true);
                   moveCastlingRight(board, black);
                   board.xKingBlack = 6;
                   board.yKingBlack = 0;
               }
           }
        if(holds_alternative<Move>(move)){
            //cout << "getYDep(move)).name_piece == pawn: " << board.at(getXDep(move), getYDep(move)).name_piece ; cout << " getXArr(move) - getXDep(move): " << getXArr(move) - getXDep(move) << endl;


            if(board.at(getXDep(move), getYDep(move)).name_piece ==  pawn && board.at(getXDep(move), getYDep(move)).color_piece == black &&
               getYArr(move) - getYDep(move) == 2){
                  //cout << "in move board enpassant black" << endl;
                  board.enpasWhite[getXDep(move)] = true;
            }
            if(board.at(getXDep(move), getYDep(move)).name_piece == pawn && board.at(getXDep(move), getYDep(move)).color_piece == white &&
               getYDep(move) - getYArr(move) == 2){
                   //cout << "in move board enpassant white" << endl;
                   board.enpasBlack[getXDep(move)] = true;

            }
            if(board.at(getXDep(move), getYDep(move)).name_piece == pawn && getXArr(move) - getXDep(move) != 0){
               //cout << "before EMPTY" << endl;
               //cout << "board.at(getXArr(move), getYArr(move)): " << board.at(getXArr(move), getYArr(move)).name_piece << endl;
                if(board.at(getXArr(move), getYArr(move)).name_piece == Empty){
                    //cout << "before color" << endl;
                    if(board.at(getXDep(move), getYDep(move)).color_piece == black){
                        //cout << "before Empty black" << endl;
                        board.at(getXArr(move), getYArr(move) -1) = Empty;
                    }
                    if(board.at(getXDep(move), getYDep(move)).color_piece == white){
                        //cout << "befor Empty white" << endl;
                        board.at(getXArr(move), getYArr(move) +1) = Empty;
                    }
                }
            }
            if(board.at(getXDep(move), getYDep(move)).name_piece == king && board.at(getXDep(move), getYDep(move)).color_piece == white){
                //cout << "coord KING WHITE X: " << board.xKingWhite << endl;
                //cout << "coord KING WHITE Y: " << board.yKingWhite << endl;
                board.xKingWhite = getXArr(move);
                board.yKingWhite = getYArr(move);//если то чем мы ходим - это король - то теперь его координаты это кнечные координаты фигуры, сохраняем их в Matrix

            }
            if(board.at(getXDep(move), getYDep(move)).name_piece  == king && board.at(getXDep(move), getYDep(move)).color_piece == black){
                //cout << "coord KING BLACK X: " << board.xKingBlack << endl;
                //cout << "coord KING BLACK Y: " << board.yKingBlack << endl;
                
                board.xKingBlack = getXArr(move);
                board.yKingBlack = getYArr(move);

            }

            if(getYArr(move) == 0 && board.at(getXDep(move), getYDep(move)) == P(pawn, white)){
                    //cout << "in  whitePawn " << "- color: " << board.at(getXArr(move), getYArr(move)).color_piece << " name: " << board.at(getXArr(move), getYArr(move)).name_piece <<   endl;

                    board.at(getXArr(move), getYArr(move)) = P(queen, white);
                    board.at(getXDep(move), getYDep(move)) = Empty;
            }
            else if(getYArr(move) == 7 && board.at(getXDep(move), getYDep(move)) == P(pawn, black)){
                    //cout << "in  blackPawn " << "- color: " << board.at(getXArr(move), getYArr(move)).color_piece << " name: " << board.at(getXArr(move), getYArr(move)).name_piece <<   endl;
                    board.at(getXArr(move), getYArr(move)) = P(queen, black);
                    board.at(getXDep(move), getYDep(move)) = Empty;
                }
            else {
                //cout << "getXArr(move): " << getXArr(move) << "getYDep(move): " << getYArr(move) << endl;
                board.at(getXArr(move), getYArr(move)) =
                            board.at(getXDep(move), getYDep(move));
                    board.at(getXDep(move), getYDep(move)) = Empty;
            }
    }
  
     //cout << "return in move";
    return board;
}


bool checkMate(Matrix<Pieces> &board, color colors) {


    //cout << "king x: " <<  p.first << " y: " << p.second << endl;
    //cout << "vector king: " ;printVector(filterIlegalMove(listMovesKing(p.first,p.second, board), board, colors));
    if(colors == white) {
        if(checkCheck(board.xKingWhite,board.yKingWhite, board) && filterIlegalMove(listMovesKing(board.xKingWhite,board.yKingWhite, board), board, colors).empty()) {
            return true;
        }
    }
    if(colors == black) {
        if(checkCheck(board.xKingBlack,board.yKingBlack, board) && filterIlegalMove(listMovesKing(board.xKingBlack,board.yKingBlack, board), board, colors).empty()) {
            return true;
        }
    }
    return false;
}


variant<Move, castling> createMove(int xDep, int yDep, int xArr, int yArr){
    variant<Move, castling> move ;
    setXDep(move, xDep);
    setYDep(move, yDep);
    setXArr(move, xArr);
    setYArr(move, yArr);
    return move;
}

//0-0 - rightBlack
//0-0-0 - leftBlack
//O-O - rightWhite
//O-O-O - leftWhite

void printColors(color colors) {
    colors == white?cout << "white": cout << "black";
}

/*1&1  -> 1*1 -> 1
0&1 -> 0*1 -> 0
1&0  -> 1*0 -> 0
0&0  -> 0*0  -> 0


1|0   -> 1+0 -> 1
0|1   -> 0+1 -> 1
1|1    -> 1+1 -> 2 -> 1
0+0 -> 0


-1-1-1
-1*3^2 + -1*3^1 + -1*3^0*/

variant<Move, castling> convertZeroToVariant(string str, color colors){
    variant<Move, castling> state;
    castling state1 = rightBlack;
    castling state2 = rightWhite;
    castling state3 = leftBlack;
    castling state4 = leftWhite;
    //cout << "convToVar"<<endl;
    if(str == "0-0" && colors == black){
        state = state1;
        return state;
    }
    else if(str == "0-0" && colors == white){
        state = state2;

        return state;
    }
    else if(str == "0-0-0" && colors == black){
        state = state3;
        return state;
    }
    else if(str == "0-0-0" && colors == white){
        //cout << "in 0-0-0" << endl;
        state = state4;
        //cout << "state= "  << endl;
        return state;
    }
    throw invalid_argument("ERROR in function convertZeroToVariant");

}


Matrix<Pieces> &movePlayer(Matrix<Pieces> &board, color colors){
    
    string coord;
    int xDep = 0, yDep = 0, xArr = 0, yArr = 0;
    
    while(true) {

        cout << "enter the coordinats in the format 2b2c" << endl << "now move for "; colors == white? cout << "white :":cout <<"black :";
        cin >> coord;
        cout << "coord: " << coord << endl;
        colors = board.currentColor;
        vector<variant<Move, castling>> &everyMove = everyMoveList(board, colors);
    
        vector<variant<Move, castling>> &everyFilterMove = filterIlegalMove(everyMove, board,  colors);
        
        if(coord == "0-0" && checkMoveInEverList(everyMove, convertZeroToVariant(coord, colors))){

            return moveForBoard(board, colors==white?rightWhite:rightBlack);
        }

        else if(coord == "0-0-0" && checkMoveInEverList(everyMove, convertZeroToVariant(coord, colors))) {

           return moveForBoard(board, colors==white?leftWhite:leftBlack);

        }

        else if((coord == "0-0" || coord == "0-0-0") && checkMoveInEverList(everyMove, convertZeroToVariant(coord, colors)) && !checkMoveInEverList(everyFilterMove, convertZeroToVariant(coord, colors))){
            cout << "you don't can castling, because your king on chek or move for king will do check" << endl;
            continue;
        }

        static const regex r("[1-8][a-h][1-8][a-h]");
        if(regex_match(coord, r)){
            //cout << " in regex"<<endl;
            xDep = coord[0]-48-1;
            yDep = coord[1]-97;
            xArr  = coord[2]-48-1;
            yArr = coord[3]-97;
        }
        cout << "everyMove \t";printVector(everyMove); cout << endl;
        cout << "everyFilterMove";printVector(everyFilterMove);
        printMove(createMove(xDep, yDep, xArr, yArr));
        //cout << "befor regex" << endl;
        //cout<< "move(xArr, yArr) : " <<  converToChessX(xArr) << " ," << converToChessY(yArr) << endl;
        variant<Move, castling>move = createMove(xDep, yDep, xArr, yArr);
        if(board.at(xDep, yDep).name_piece != Empty && board.at(xDep, yDep).color_piece != colors){
            cout << "you entered the wrong coordinate your color it's , " ;  colors == white? cout << "white " << endl:cout <<"black " << endl << "xDep = " << xDep  <<
                     " \tyDep = " << yDep << endl   << "xArr = " << xArr << "\tyArr = " << yArr << "  try agayn" << endl;
             cout << "Enter coordinats again: " << endl;
             continue;
        }
        
        else if(!checkMoveInEverList(everyMove, createMove(xDep, yDep, xArr, yArr))) {
            cout << "your move is invalid, select other move" << endl;
        }
        else if (!checkMoveInEverList(everyFilterMove, createMove(xDep, yDep, xArr, yArr))) {
            cout << "this move make chess for king" << endl;
            continue;
        }
        //cout << "1" << endl;
        
        else if(checkOutOfRange(xArr,yArr, board) && checkOutOfRange(xDep, yDep, board)) {
            cout << "you entered the wrong coordinate OUT OF RANGE, "  << endl << "xDep = " << xDep  <<
                     " \tyDep = " << yDep << endl   << "xArr = " << xArr << "\tyArr = " << yArr << "  try agayn" << endl;
             cout << "Enter coordinats again: " << endl;
             continue;
        }
        else if(board.at(xDep, yDep).name_piece == Empty) {
            cout << "this coordinats empty, choice other coordinats" << endl;
            continue;
        }
        else if(colors == white && board.at(xDep, yDep).name_piece != king && checkCheck(board.xKingWhite, board.yKingWhite, board) ){
            cout << "your king has check,  move for other pieces unavailable. Eliminate check" << endl;
            continue;
        }
        else if(colors == black && board.at(xDep, yDep).name_piece != king && checkCheck(board.xKingBlack, board.yKingBlack, board) ){
            cout << "your king has check,  move for other pieces unavailable. Eliminate check" << endl;
            continue;
        }
        
        else if(checkMoveInEverList(everyMove, move)) {
            if(board.at(xDep, yDep).name_piece == king){
                moveForBoard(board, move);
                //board.printBoard();
                if(checkCheck(xArr, yArr, board)){
                    //cout << "everiList: " ;printVector(everyMoveList(board,swapColor(colors)));
                    //cout << "xDep = " << xDep  << " \tyDep = " << yDep << endl   << "xArr = " << xArr << "\tyArr = " << yArr << endl;
                    //cout << "checkCheck(xArr, yArr, board) : " << checkCheck(xArr, yArr, board)<< endl;
                    cout << "your king has check, select other move. Eliminate check" << endl;
                    board.at(xArr, yArr) = Empty;
                    board.at(xDep, yDep) = P(king, (colors));
                    //board.printBoard();
                    continue;
                }
                else if(!checkCheck(xArr, yArr, board)){
                    board.at(xArr, yArr) = Empty;
                    board.at(xDep, yDep) = P(king, (colors));
                    //board.printBoard();
                    return moveForBoard(board, move);
                }

            }

            //cout << "from movePlaeyr to moveForBoard"<< endl;
            variant<Move, castling>move = createMove(xDep, yDep, xArr, yArr);
            return moveForBoard(board, move);
        }


        else {
           cout << "you entered the wrong coordinate SUMMARY "  << endl << "xDep = " << xDep  <<
                    " \tyDep = " << yDep << endl   << "xArr = " << xArr << "\tyArr = " << yArr << "  try agayn" << endl;
            cout << "Enter coordinats again: " << endl;
                 //<< endl << "now move for "; colors == white? cout << "white :":cout <<"black :" << endl;
            //cin >> coord;
            continue;
        }
    }
    
    cout << "return board";
    return board;
}

int converToChessX(int coord){
    return coord+1;
}
char converToChessY(int coord){
    char simb = 'a';
    return simb + coord;
}


pair<int, int> findKing(Matrix<Pieces> &board, color colors) {

    for(int y = 0; y < board.matrHight; y++) {
        for(int x = 0; x < board.matrWidth; x++) {
            if(board.at(x,y).name_piece == king && board.at(x,y).color_piece == colors) {
                //cout << "make_pair" << endl;
                return make_pair(x,y);
            }

        }
    }

    throw runtime_error("error in function findKing");


}

int counterMove(Matrix<Pieces> &board, color colors, int depth) {

    if(depth == 0){
    return 1;
    }
    vector<variant<Move, castling>> listMove = filterIlegalMove(everyMoveList(board, colors), board, colors);
    int count = 0;
    for(int i = 0; i < (int)listMove.size(); i++) {
    Matrix<Pieces> newBoard(board);
        newBoard = moveForBoard(newBoard, listMove.at(i));
        //cout << "newBoard : " << endl; newBoard.printBoard();
        //cout << "name_piece: " << newBoard.at(listMove.at(i).getXDep(), listMove.at(i).getXDep()).name_piece << ";" << endl;
        //cout << "list departure Move :" << listMove.at(i).getXDep() << "," << listMove.at(i).getYDep() << ";" << endl;
        //cout << "list arrivle Move :" << listMove.at(i).getXArr() << "," << listMove.at(i).getYArr() << ";" << endl;
        //cout << "count: " << count<< endl;
        count += counterMove(newBoard, swapColor(colors), depth - 1);


    }
    return count;
}


vector<variant<Move, castling>>& filterIlegalMove(vector<variant<Move, castling>> &listMove,  Matrix<Pieces> &board, color colors) {
    vector<variant<Move, castling>> *newList = new vector<variant<Move, castling>>;

    for(int i = 0; i < (int)listMove.size();i++) {
    
            Matrix<Pieces> newBoard(board);
            moveForBoard(newBoard,listMove.at(i));
            pair<int,int> coordKing = findKing(newBoard, colors);
            if(!checkCheck(coordKing.first, coordKing.second, newBoard)) {
                //cout<< "checkForChek : " << checkCheck(coordKing.first, coordKing.second, newBoard) << endl;
                //newBoard.printBoard();
                //cout << endl;
                newList->push_back(listMove.at(i));
    
            }
    
        }
        push_back_list(Castling(board, colors), *newList);
        return *newList;
    
    }
    /*for(int i = 0; i < (int)listMove.size();i++) {

        int coordXKingWhite = board.xKingWhite;
        int coordYKingWhite = board.yKingWhite;
        int coordXKingBlack = board.xKingBlack;
        int coordYKingBlack = board.yKingBlack;
        //colors = swapColor(colors);
        Matrix<Pieces> newBoard(board);
        moveForBoard(newBoard,listMove.at(i));
        cout << "numb move: " << i+1 << endl;
        
        if(colors == black ){
            if(!checkCheck(coordXKingBlack, coordYKingBlack, newBoard)) {

                cout<< "!!!checkForChek!!! for black: " << checkCheck( coordXKingBlack, coordYKingBlack, newBoard ) << endl;
                //newBoard.printBoard();
                //cout << endl;
                newList->push_back(listMove.at(i));

            }
        }
        if(colors == white){
            if(!checkCheck(coordXKingWhite, coordYKingWhite, newBoard)) {
                cout<< "!!!checkForChek!!! for white: " << checkCheck(coordXKingWhite, coordYKingWhite, newBoard)  << endl;
                //newBoard.printBoard();
                //cout << endl;
                newList->push_back(listMove.at(i));
            }
        }

    }


    return *newList;

}*/


bool checkOutOfRange(int x, int y, Matrix<Pieces> &board) {
    if(x > board.matrWidth-1 || x < 0 || y > board.matrHight-1 || y < 0) {
        return true;
    }
    return false;
}

void printCastling(castling state) {
    switch (state) {
    case rightWhite:
        cout << "rightWhite";
        break;
    case leftWhite:
        cout << "leftWhite";
        break;
    case  rightBlack:
        cout << "rightBlack";
        break;
    case leftBlack:
        cout << "leftBlack";
        break;
    default:
        throw invalid_argument("error type in printCastling()");
    }
}
//rightWhite, leftWhite, rightBlack, leftBlack}
void printVector(vector<variant<Move, castling>> arr) {

    cout << "list moves: [";

    for (int i = 0; i < (int)arr.size(); i++)
    {

        if(holds_alternative<Move>(arr.at(i))){

            cout << converToChessX(getXDep(arr.at(i))) << "," << converToChessY(getYDep(arr.at(i))) << " -> " << converToChessX(getXArr(arr.at(i))) << "," << converToChessY(getYArr(arr.at(i))) << " ; ";
        }
        else if(holds_alternative<castling>(arr.at(i))){
             cout << " "; printCastling(get<castling>(arr.at(i))); cout << "; ";
        }
    }
    cout << "]" << endl;

}

void printMove(variant<Move, castling> move) {
    cout << "move: ";
    cout << converToChessX(getXDep(move)) << "," << converToChessY(getYDep(move)) << "->" 
         << converToChessX(getXArr(move))  << "," << converToChessY(getYArr(move)) << endl;
}

//void setXDep(variant<Move, castling> move, int x)
void addMovesInList(int x, int y, int xDir, int yDir, variant<Move, castling> &move, vector<variant<Move, castling>> &listMove ,  Matrix<Pieces> &board) {

        if ((!checkOutOfRange(xDir, yDir, board) && board.at(x, y).color_piece != board.at(xDir,yDir).color_piece)||
            (!checkOutOfRange(xDir, yDir, board) && board.at(xDir,yDir).name_piece == Empty)) {
            setXDep(move, x);
            setYDep(move, y);
            setXArr(move, xDir);
            setYArr(move, yDir);
            listMove.push_back(move);
        }
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

vector<variant<Move, castling>> &listMovesKing(int x, int y, Matrix<Pieces> &board) {
    vector<variant<Move, castling>> *listMove = new vector<variant<Move, castling>>;
    variant<Move, castling> doMove;

    array <int, 8> arrY = {y+1, y+1, y+1, y, y-1, y-1, y-1, y};
    array <int, 8> arrX = {x+1, x, x-1, x-1, x-1, x, x+1, x+1};

     for (int i = 0; i <(int)(sizeof(arrX)/sizeof(arrX.at(0))); i++) {
         if(!checkOutOfRange(arrX.at(i), arrY.at(i), board)){
             addMovesInList(x, y, arrX.at(i), arrY.at(i), doMove, *listMove, board);
         }
         else {
             continue;
         }
     }

    return *listMove;
}


vector<variant<Move, castling>> &listMovesKnight(int x, int y, Matrix<Pieces> &board) {
    vector<variant<Move, castling>> *listMove = new vector<variant<Move, castling>>;
    variant<Move, castling> doMove;

    array<int, 8> arrY = {y + 2, y + 1, y - 1, y - 2,y - 2, y - 1, y + 1, y + 2};
    array<int, 8> arrX = {x + 1, x + 2, x + 2, x + 1, x - 1, x - 2, x - 2, x - 1};

    for (int i = 0; i <(int)(sizeof(arrX)/sizeof(arrX.at(0))); i++) {
        if(!checkOutOfRange(arrX.at(i), arrY.at(i), board)){
            addMovesInList(x, y, arrX.at(i), arrY.at(i), doMove, *listMove, board);
        }
        else {
            continue;
        }
    }

    return *listMove;
}
//
vector<variant<Move, castling>>& moveSide(int x, int y, Matrix<Pieces> &board, int dirX, int dirY) {
    vector<variant<Move, castling>> *listMoves = new vector<variant<Move, castling>>;
    for (int X = x+dirX, Y = y+dirY; !checkOutOfRange(X, Y, board); X = X+dirX, Y = Y+dirY) {
       if(checkAddMove(X,Y,x,y, board)) {
            if(board.at(X,Y).name_piece != Empty && board.at(X,Y).color_piece != board.at(x,y).color_piece){
                addMoves(x,y,X, Y, *listMoves);
                break;
            }
            else if(board.at(X,Y).name_piece == Empty) {
                addMoves(x,y,X, Y, *listMoves);
            }
        }
       else {

           break;
       }
    }
    return *listMoves;
}

vector<variant<Move, castling>> &listMovesRook(int x, int y, Matrix<Pieces> &board) {
    vector<variant<Move, castling>> *listMoves = new vector<variant<Move, castling>>;

    push_back_list(moveSide(x,y,board,1,0), *listMoves);
    push_back_list(moveSide(x,y,board,-1,0), *listMoves);
    push_back_list(moveSide(x,y,board,0,-1), *listMoves);
    push_back_list(moveSide(x,y,board,0,1), *listMoves);

    return *listMoves;
}

vector<variant<Move, castling>> &listMovesBishop(int x, int y, Matrix<Pieces> &board) {
    vector<variant<Move, castling>> *listMoves = new vector<variant<Move, castling>>;
    push_back_list(moveSide(x,y,board,1,1), *listMoves);
    push_back_list(moveSide(x,y,board,-1,1), *listMoves);
    push_back_list(moveSide(x,y,board,1,-1), *listMoves);
    push_back_list(moveSide(x,y,board,-1,-1), *listMoves);

    return *listMoves;
}

vector<variant<Move, castling>>& listMovesPawn(int x, int y, Matrix<Pieces> &board) {
    vector<variant<Move, castling>> *listMove = new vector<variant<Move, castling>>;
    variant<Move, castling> doMove;
    bool flag = true;

     if(!checkOutOfRange(x,y-1, board) && board.at(x, y).color_piece == white && y != 6
             && board.at(x, y-1).name_piece == Empty) {

         addMovesInList(x, y, x, y-1, doMove, *listMove, board);
     }
     else if(!checkOutOfRange(x,y+1, board) && board.at(x, y).color_piece == black && y != 1
             && board.at(x, y+1).name_piece == Empty) {

         addMovesInList(x, y, x, y+1, doMove, *listMove, board);
     }
     else if(!checkOutOfRange(x,y-1, board) && board.at(x, y).color_piece == white && y == 6
             && board.at(x, y-1).name_piece == Empty) {
         addMovesInList(x, y, x, y-1, doMove, *listMove, board);
     }
     else if(!checkOutOfRange(x,y-1, board) && board.at(x, y).color_piece == white && y == 6
             && board.at(x, y-1).name_piece != Empty) {
          flag = false;
     }
     if(!checkOutOfRange(x,y-2, board) && board.at(x, y).color_piece == white && y == 6
                   && board.at(x, y-2).name_piece == Empty && flag) {
         addMovesInList(x, y, x, y-2, doMove, *listMove, board);
           }

     else if(!checkOutOfRange(x,y+1, board) && board.at(x, y).color_piece == black && y == 1
            && board.at(x, y+1).name_piece == Empty) {
         addMovesInList(x, y, x, y+1, doMove, *listMove, board);

     }
     else if(!checkOutOfRange(x,y-1, board) && board.at(x, y).color_piece == white && y == 6
             && board.at(x, y-1).name_piece != Empty) {
          flag = false;
     }
     if(!checkOutOfRange(x,y+2, board) && board.at(x, y).color_piece == black && y == 1
                   && board.at(x, y+2).name_piece == Empty && flag) {
         addMovesInList(x, y, x, y+2, doMove, *listMove, board);
           }
     if(board.at(x,y).color_piece == white) {

         if (!checkOutOfRange(x-1,y-1, board) && board.at(x-1,y-1).color_piece == black
                 && board.at(x-1, y-1).name_piece != Empty) {
             addMovesInList(x, y, x-1, y-1, doMove, *listMove, board);
         }
         if(!checkOutOfRange(x+1,y-1, board) && board.at(x+1,y-1).color_piece == black
                 && board.at(x+1, y-1).name_piece != Empty){
             addMovesInList(x, y, x+1, y-1, doMove, *listMove, board);
        }
     }
     if(board.at(x,y).color_piece == black) {

         if (!checkOutOfRange(x+1,y+1, board) && board.at(x+1,y+1).color_piece == white
                 && board.at(x+1, y+1).name_piece != Empty) {
             addMovesInList(x, y, x+1, y+1, doMove, *listMove, board);
         }
         if(!checkOutOfRange(x-1,y+1, board) && board.at(x-1,y+1).color_piece == white
                 && board.at(x-1, y+1).name_piece != Empty){
             addMovesInList(x, y, x-1, y+1, doMove, *listMove, board);
        }
     }
    return *listMove;
}


void push_back_list(vector<variant<Move, castling>> &listMove, vector<variant<Move, castling>> &everyMoveList) {

    for (int i = 0; i < (int)listMove.size(); ++i) {
        everyMoveList.push_back(listMove.at(i));
    }

}

/*
In C++, a Copy Constructor may be called for the following cases:

1) When an object of the class is returned by value.
2) When an object of the class is passed (to a function) by value as an argument.
3) When an object is constructed based on another object of the same class.
4) When the compiler generates a temporary object.

*/

void printMove(Matrix<Pieces> &board, vector<variant<Move, castling>> &listMove) {
    Matrix<Pieces> newBoard(board);
    for(int i = 0; i < (int)listMove.size(); i++) {

        variant<Move, castling> temp = listMove.at(i);
        newBoard.at(getXArr(temp), getYArr(temp)) = newBoard.at(getXDep(temp), getYDep(temp));
        //newBoard.at(temp.getXDep(), temp.getYDep()) = Empty;
        cout << endl;

        cout << endl;
    }
    newBoard.printBoard();
}


void printOneMove(Matrix<Pieces> &board, vector<variant<Move, castling>> &listMove) {

    for(int i = 0; i < (int)listMove.size(); i++) {
        Matrix<Pieces> newBoard(board);
        variant<Move, castling> temp = listMove.at(i);
        newBoard.at(getXArr(temp), getYArr(temp)) = newBoard.at(getXDep(temp), getYDep(temp));
        newBoard.at(getXDep(temp), getYDep(temp)) = Empty;
        cout << endl;
        newBoard.printBoard();
        cout << endl;
    }

}


vector<variant<Move, castling>> &listMovesQueen(int x, int y, Matrix<Pieces> &board) {
    vector<variant<Move, castling>> *listMoves = new vector<variant<Move, castling>>;
    push_back_list(listMovesBishop(x,y,board), *listMoves);
    push_back_list(listMovesRook(x,y,board), *listMoves);

    return *listMoves;

}
bool checkMoveInEverList(vector<variant<Move, castling>> &everyMoveList, variant<Move, castling> move) {
    //cout << "!!!!in checkMoveInEverList " << endl;
    for(int i = 0; i < (int)everyMoveList.size(); i ++) {
            //cout << "!!!!befor Move == Move" << endl;
            if(holds_alternative<Move>(move) && holds_alternative<Move>(everyMoveList.at(i))){
                
                if(get<Move>(move) == get<Move>(everyMoveList.at(i))){
                    //cout << "move: \t"; printMove(move);
                    //cout << "everyMoveList.at(i): "; printMove(everyMoveList.at(i));cout << endl;
                    //cout << "TRUE!!!!! in checkMoveEveryList" << endl;
                    return true;
                }
            }
            if(holds_alternative<castling>(move) && holds_alternative<castling>(everyMoveList.at(i))){
            //cout << "befor cast == cast" << endl;
                if(move == everyMoveList.at(i)){
                    return true;
                }
            }


    }
    //cout << "return false checkMoveEveryList" << endl;
    return false;

}

vector<variant<Move, castling>>& everyMoveList(Matrix<Pieces> &board, color colors)  {
    vector<variant<Move, castling>> *everyListMove = new vector<variant<Move, castling>>;
    for (int y = 0; y < board.matrHight; y++) {
        for (int x = 0; x < board.matrWidth; x++) {
            //cout << board.at(x,y).color_piece;
            if(board.at(x,y).color_piece == colors && !checkOutOfRange(x,y,board)) {
                //cout << "in if" << endl;
                switch (board.at(x,y).name_piece) {
                case king:
                    push_back_list(listMovesKing(x,y,board), *everyListMove);
                    break;
                case queen:
                    push_back_list(listMovesQueen(x,y,board), *everyListMove);
                    break;
                case rook:
                    push_back_list(listMovesRook(x,y,board), *everyListMove);
                    break;
                case bishop:
                    push_back_list(listMovesBishop(x,y,board), *everyListMove);
                    break;
                case pawn:
                    push_back_list(listMovesPawn(x,y,board), *everyListMove);
                    break;
                case knight:
                    push_back_list(listMovesKnight(x,y,board), *everyListMove);
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

    push_back_list(enpassant(board, colors), *everyListMove);
    push_back_list(Castling(board, colors), *everyListMove);
    return *everyListMove;
}//TODO доделать эн пассант функцию и добавить такой ход в общий список, тестить, дебажить




void printBoard(Matrix<Pieces> &board) {
    char simb = 'a';
    for (int i = 1; i < 9; ++i) {
        cout << "  " << i;
    }
    cout << endl;


        for (int y = 0; y < board.matrHight ;y++) {

            cout  <<  simb ;
            simb++;

            for(int x = 0; x < board.matrWidth; x++) {

                board.at(x, y).print();

            }
            cout << endl;
        }
    }


Pieces P(pieces names, color colors) {
    Pieces pieces(names, colors);
    return pieces;

}

Pieces PE(pieces names) {
    Pieces pieces(names);
    return pieces;

}

 ostream& operator<<(ostream& os, const Pieces& piece){
    os << piece.color_piece << " " << piece.name_piece;
    return os;
}


bool checkToRookOrQueenUnif(int xKing, int yKing, Matrix<Pieces> &board, int dirX, int dirY) {
    for (int X = xKing+dirX, Y = yKing+dirY; !checkOutOfRange(X, Y, board); X = X+dirX, Y = Y+dirY) {
        //cout << "xKing = " << xKing << "yKing = " << yKing << endl;
       //cout << " !checkOutOfRange(X, Y, board) = " << checkOutOfRange(X, Y, board) << endl;
        if(board.at(X, Y).name_piece != Empty){
            //cout << "!empty : X " << X << "Y: " << Y << endl;
            if(board.at(X, Y).name_piece == rook || board.at(X, Y).name_piece == queen) {
                //cout << " board.at(xKing, yKing).name_piece: " <<  board.at(xKing, yKing).name_piece << endl;
                //cout << " board.at(xKing, yKing).color_piece: " <<  board.at(xKing, yKing).color_piece << endl;
                
                if(board.at(xKing, yKing).color_piece != board.at(X, Y).color_piece) {
                   // cout << "board.at(X, Y).name_piece: " <<  board.at(X, Y).name_piece << endl;
                    //cout << "board.at(X, Y).color_piece: " <<  board.at(X, Y).color_piece << endl;
                    //cout << "true ROOK" << endl;
                    return true;
                }
                else {
                   return false;
                }
            }
            else {
               return false;    //этот false возвращается, когда наткнулись на фигуру другого цвета не на rook  и не на queen
            }
        }
    }
    //cout << "false ROOK" << endl;
    return false;
    //throw runtime_error("error in function checkToRookOrQueenUnif");
}

bool checkToRookOrQueen(int x, int y, Matrix<Pieces> &board){
    return
    checkToRookOrQueenUnif(x, y, board, 1, 0) ||
    checkToRookOrQueenUnif(x, y, board, -1, 0) ||
    checkToRookOrQueenUnif(x, y, board, 0, 1) ||
    checkToRookOrQueenUnif(x, y, board, 0, -1);
}

bool checkToBishopOrQueenUnif(int xKing, int yKing, Matrix<Pieces> &board, int dirX, int dirY ) {// one line
    for(int X = xKing+dirX, Y = yKing+dirY; !checkOutOfRange(X,Y, board) ; X = X+dirX, Y = Y+dirY) {
        if(board.at(X, Y).name_piece != Empty){
            if(board.at(X, Y).name_piece == bishop || board.at(X, Y).name_piece == queen ) {
                if(board.at(xKing, yKing).color_piece != board.at(X, Y).color_piece) {
                    return true;
                }

            }
            else {
               return false;
            }


        }
        else {
           return false;
        }
    }


    return false;

    //throw runtime_error("error in function checkToBishopOrQueenUnif");
}

bool checkToBishopOrQueen(int x, int y, Matrix<Pieces> &board) {
    return
    checkToBishopOrQueenUnif(x, y, board, 1, 1) ||
    checkToBishopOrQueenUnif(x, y, board, -1, 1) ||
    checkToBishopOrQueenUnif(x, y, board, -1, -1)||
    checkToBishopOrQueenUnif(x, y, board, 1, -1);
}



bool checkToKing(int x, int y, Matrix<Pieces> &board) {

    array<int,8> arrY = {y+1, y+1, y+1, y, y-1, y-1, y-1, y};
    array<int,8> arrX = {x+1, x, x-1, x-1, x-1, x, x+1, x+1};
    //cout << "checkToKing X : " << converToChessX(x) << " y: " << converToChessY(y) << endl;

    for(int i = 0; i < 8; i++) {
        if(checkOutOfRange(arrX.at(i), arrY.at(i), board)){
            continue;
        }

        //cout << "arrX.at(i): " << arrX.at(i) << " arrY.at(i): " << arrY.at(i) << endl;

        if(board.at(arrX.at(i), arrY.at(i)).name_piece == king){
            //cout << "board.at(arrX.at5a4b(i), arrY.at(i)).name_piece TRUE!!!!!: " << board.at(arrX.at(i), arrY.at(i)).name_piece<< endl;
            //cout << "board.at(arrX.at(i), arrY.at(i)).color_piece: " << board.at(arrX.at(i), arrY.at(i)).color_piece << endl;
            //board.printBoard();
            //cout << "CHECKTOKING TRUE!!!!board.at(x, y).name_piece: " << board.at(x, y).name_piece<< endl;
            //cout << "board.at(x, y).color_piece: " << board.at(x, y).color_piece << endl;
            return true;
        }
        

    }
    //cout << "board.at(arrX.at(i), arrY.at(i)).name_piece CHECK TO KING TRUE!!!!!: " << board.at(arrX.at(i), arrY.at(i)).name_piece<< endl;
   // cout << "board.at(x, y).name_piece: " << board.at(x, y).name_piece<< endl;
   // cout << "board.at(x, y).color_piece: " << board.at(x, y).color_piece << endl;
    //cout << "checkToKing  FALSE!!!!!: ";
    return false;
}

bool checkToPawn(int x, int y, Matrix<Pieces> &board) {
    array<int, 4> arrY = {y + 1, y + 1, y - 1, y - 1};
    array<int, 4> arrX = {x + 1, x - 1, x + 1, x - 1};

    for (int i = 0; i < 4; i++) {
        if(checkOutOfRange(arrX.at(i), arrY.at(i), board)){
            continue;
        }
        if(board.at(arrX.at(i), arrY.at(i)).name_piece != Empty) {
            if(board.at(arrX.at(i), arrY.at(i)).name_piece != pawn) {
                continue;
            }
            if(board.at(arrX.at(i), arrY.at(i)).name_piece == pawn && board.at(x, y).color_piece == board.at(arrX.at(i), arrY.at(i)).color_piece) {
                continue;
            }
            else if(board.at(arrX.at(i), arrY.at(i)).name_piece == pawn && board.at(x, y).color_piece != board.at(arrX.at(i), arrY.at(i)).color_piece) {
                //cout << "checkToPawn TRUE!!!" << endl;
                return true;
            }
        }
    }

    return false;
}



bool checkToKnight(int x, int y, Matrix<Pieces> &board) {

    array<int,8> arrY = {y + 2, y + 1, y - 1, y - 2,y - 2, y - 1, y + 1, y + 2};
    array<int,8> arrX = {x + 1, x + 2, x + 2, x + 1, x - 1, x - 2, x - 2, x - 1};

    for (int i = 0; i < 8; i++)
    {
        if(checkOutOfRange(arrX.at(i), arrY.at(i), board)){
            continue;
        }
        if(board.at(arrX.at(i), arrY.at(i)).name_piece != Empty) {
            if(board.at(arrX.at(i), arrY.at(i)).name_piece != knight) {
                continue;
            }
            if(board.at(arrX.at(i), arrY.at(i)).name_piece == knight && board.at(x, y).color_piece == board.at(arrX.at(i), arrY.at(i)).color_piece) {//проверить есть ли конь в пятне короля?
                continue;
            }
            else if(board.at(arrX.at(i), arrY.at(i)).name_piece == knight && board.at(x, y).color_piece != board.at(arrX.at(i), arrY.at(i)).color_piece) {
                return true;
            }
        }
    }

    return false;//нет угрозы от фигуры - поэтому я false
}

color swapColor(color &colors){
    if(colors == white) {
        return black;
    }
    return white;

}


bool checkForCheck(int x, int y, Matrix<Pieces> &board, color colors) {//данная функция неоптимальна, много ресурсов задействует, так как смотрит все хода противника, а не то лько те что угрожают королю, поэтомц ее не задейстуем
//TODO посмотреть разницу по количеству ходов между checkCheck и checkForCheck

    vector<variant<Move, castling>> listEnemy = everyMoveList(board, swapColor(colors));// разворачиваю цвет для того что бы было понятно назначение функции - передаем белый и проверяем белый

    for (int i = 0; i < (int)listEnemy.size(); ++i) {
        if(getXArr(listEnemy.at(i)) == x && getYArr(listEnemy.at(i)) == y) {
            return true;
        }
    }
    return false;
}

bool checkCheck(int x, int y, Matrix<Pieces> &board) {
//cout << "checkCheck: " <<  "x :" << converToChessX(x) << " y: " << converToChessY(y)  << endl;
//cout<< "checkToRookOrQueen(x, y, board): " << checkToRookOrQueen(x, y, board) << endl;
//cout<< "checkToBishopOrQueen: " << checkToBishopOrQueen(x, y, board) << endl;
//cout<< "checkToKing: " << checkToKing(x, y, board) << endl;
//cout<< "checkToPawn: " << checkToPawn(x, y, board) << endl;
//cout<< "checkToKnight: " << checkToKnight(x, y, board) << endl;
//cout << "in checkCheck x : " << x << " y: " << y << endl;
    return (checkToRookOrQueen(x, y, board) ||
            checkToBishopOrQueen(x, y, board) ||
            checkToKing(x, y, board) ||
            checkToPawn(x, y, board) ||
            checkToKnight(x, y, board));

}

bool checkBoardForBoard(Matrix<Pieces> &board, Matrix<Pieces> &board2){
    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            if(board.at(x,y).name_piece != board2.at(x, y).name_piece) {
                return false;
            }
        }
    }
    return true;
}

void printColor(color colors) {
    switch(colors){
    case black:
        cout << "black";

    case white:
        cout << "white";


    //default: throw invalid_argument("error type in func printColor");
    }
}

void mainWhile(Matrix<Pieces> &board, color &colors){
    while(true) {
        cout << "COLORS IN MAIN WHILE: " << colors;
        cout << endl;
        cout << "where king: ";board.printKingCoord();
        
        printBoard(movePlayer(board, colors));

        if(checkMate(board, colors)) {
            cout << "Game over!" << endl << "MATE for " ; printColor(colors); cout << ", WINNER - "; printColor(swapColor(colors)); cout <<  endl;
            break;

        }
        board.currentColor = swapColor(board.currentColor);
        
    }
}

int main (int argc, char* argv[]){

    Pieces board[64] = {
    P(rook, black), P(bishop, black), P(knight, black), P(queen, black),P(king, black), P(knight, black), P(bishop, black), P (rook, black),
    P(pawn, black), P(pawn, black), P(pawn, black) , P(pawn, black), P(pawn, black), P(pawn, black), P(pawn, black), P(pawn, black),
    PE(Empty), PE(Empty), PE(Empty),PE(Empty),PE(Empty), PE(Empty),PE(Empty),PE(Empty),
    PE(Empty),PE(Empty), PE(Empty),PE(Empty),PE(Empty), PE(Empty),PE(Empty),PE(Empty),
    PE(Empty), PE(Empty),PE(Empty),PE(Empty),PE(Empty), PE(Empty),PE(Empty),PE(Empty),
    PE(Empty), PE(Empty), PE(Empty),PE(Empty),PE(Empty), PE(Empty),PE(Empty),PE(Empty),
    P(pawn, white), P(pawn, white), P(pawn, white) ,P(pawn, white), P(pawn, white), P(pawn, white) , P(pawn, white), P(pawn, white),
    P(rook, white), P(bishop, white), P(knight, white), P(queen, white), P(king, white), P(knight, white), P(bishop, white), P (rook, white),
};

    /*Pieces board[64] = {
        PE(Empty), PE(Empty), PE(Empty),PE(Empty),P(king, black), PE(Empty),PE(Empty),PE(Empty),
        PE(Empty),PE(Empty), PE(Empty),PE(Empty),PE(Empty), PE(Empty),PE(Empty),PE(Empty),
        PE(Empty), PE(Empty),PE(Empty),PE(Empty),PE(Empty), PE(Empty),PE(Empty),PE(Empty),
        PE(Empty), PE(Empty), PE(Empty),PE(Empty),PE(Empty), P(king, white),PE(Empty),PE(Empty),
        PE(Empty), PE(Empty), PE(Empty),PE(Empty),PE(Empty), PE(Empty),PE(Empty),PE(Empty),
        PE(Empty),PE(Empty), PE(Empty),PE(Empty),PE(Empty), PE(Empty),PE(Empty),PE(Empty),
        PE(Empty), PE(Empty),PE(Empty),PE(Empty),PE(Empty), PE(Empty),PE(Empty),PE(Empty),
        PE(Empty), PE(Empty), PE(Empty),PE(Empty),PE(Empty), PE(Empty),PE(Empty),PE(Empty),
    };*/

    Matrix<Pieces>  chess(8,8);

    //Pieces P1;
    //Pieces P2;
    //cout <<"P1 == P2 " << (P1==P2) << endl; // разобраться с данным предупреждением ISO C++20 considers use of overloaded operator '
    //==' (with operand types 'Pieces' and 'Pieces') to be ambiguous despite there being a unique best viable function
    //Добавил после формальных аргументов const и замечание пропало  в описании ошибки на SOF говорится о том, что const есть только слева,
    //а по стандарту 2020г операторы сравнения добавляют новое понятие из переписанных и обращенных кандидатов и
    //поэтомк равенство будет рассматриватся компилятором с двух сторон, а если с одной не const -  то оно заведомо неверное.


    //Matrix<int> chess(3,3);

    //Pieces* x=new Pieces[42];

    chess.assignmentForArr(board, 8, 8);
    //cout << "6,0";
    //chess.at(6,0).print() ;
    //cout << endl;
    //X x {1, 2, 3, 4, 5};

     //Pieces e {1, 2, 3, 4, 5};
    //board[0].print();
    //Pieces king1(king, white);
    //king1.print();
    printBoard(chess);

    //mainWhile(chess, chess.currentColor);

    /*cout << "color in FilELMove: " << chess.currentColor << endl;
    cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
    board.currentColor = swapColor(board.currentColor);
    cout << "color in FilELMove: " << board.currentColor << endl ;*/
    variant<Move, castling> move, state;
    //int x,y;

    //cout << "isCastling : " << isCastling(chess, rightBlack, black) << endl;

   // printVector(filterIlegalMove(everyMoveList(chess,white), chess, white));


    Move m;
    m.setXDep(0);
    m.setYDep(1);
    m.setXArr(1);
    m.setYArr(2);

    move = m;

    castling state1 = rightWhite;

    state = state1;

    //cout << "castling state: " << get<castling>(state);

    //int getDEp(variant<....> x){

     //   return get<Move>(x).getYDep
    //}

    //cout <<  get<Move>(move).getYDep() << endl;

    //vector <variant<Move, castling>> sV ;

   //sV.push_back(rightBlack);

   //cout << "castling mV: " << get<castling>(sV.at(0)) << endl;



   for (int var = 1; var < 6; ++var) {
       unsigned int start_time =  clock();
       cout << "depth " << var << ": " << counterMove(chess,white, var) << '\t';
       unsigned int end_time = clock();
       unsigned int search_time = end_time - start_time;
       cout << "search_time sec: " << search_time/1000000  << '\t' <<  "search_time milsec: " << search_time/1000 << endl;
   }




    //cout << "checkToBishopOrQueen: " << checkToRookOrQueen(3,3,chess) << endl;
    //Move m;
    //printVector(everyMoveList(chess,white));
    //cout  <<"check?: " << checkForCheck(4,0,chess,black) << endl;
    //printVector(filterIlegalMove(everyMoveList(chess,white), chess, white));
    //printVector(listMovesRook(7,1,chess));
    //printOneMove(chess,filterIlegalMove(listMovesKing(4,0,chess), chess, white));
    //printVector(filterIlegalMove(listMovesKing(chess.xKingBlack,chess.yKingBlack,chess), chess, black));
    //printOneMove(chess, everyMoveList(chess,white));
    //pair<int,int> p = findKing(chess, white);
    //cout << "xKing: " << p.first << endl;
    //cout << "yKing: " << p.second << endl;
     //cout  << checkCheck(4, 6 ,chess) << " checkCheck: "<< endl;
     //cout << "chess.xKingBlack: " << chess.xKingBlack << " " << " chess.yKingBlack: " <<  chess.yKingBlack << endl;
    //m.Print(m.xArrivle);
//TODO добавить в Matrix метод пеяати координат короля в шахматной нотации
     //chess.at(1,2)=42;
//printBoard(chess);
    //cout << king1;
     //cout << chess.at(1,2);

return 0;
}
