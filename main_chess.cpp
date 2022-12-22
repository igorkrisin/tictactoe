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
        matr = new T [hight*width];
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
        cout << this->xArrivle;
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
bool checkForIllegal(int xDep, int yDep, int xArr, int yArr, Matrix<Pieces> &board, color colors);
bool checkOutOfRange(int x, int y, Matrix<Pieces> &board);
pair<int, int> findKing(Matrix<Pieces> &board, color colors);
vector<variant<Move, castling>> &listMovesKing(int x, int y, Matrix<Pieces> &board);
vector<variant<Move, castling>>& filterIlegalMove(vector<variant<Move, castling>> &listMove,  Matrix<Pieces> &board, color colors);
bool isCastling(Matrix<Pieces> &board, castling state, color colors);

void printCastling(castling state);
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

            listMoves->push_back(rightWhite);//переделать присвоение (возможно push_back)
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


Matrix<Pieces> & moveForBoard(Matrix<Pieces> & board, variant<Move, castling> move, color colors) {
    pair<int,int> p = findKing(board, colors);
    //cout << "board.at: ";board.at(move.getXDep(), getYDep(move)).print(); cout << endl;
    //cout << ";P(pawn, white): ";P(pawn, white).print(); cout << endl;
    if( !checkCheck(p.first, p.second, board)) {
       if(isCastling(board, rightBlack,colors) && getXArr(move) == 11){//19.12: теперь убираем ходы кастлинга в moveForBoard
          board.at(4,0) = Empty;
          board.at(7,0) = Empty;
          board.at(5,0) = P(rook, colors);
          board.at(6,0) = P(king, colors);
          return board;
       }
       else if ( isCastling(board, rightWhite,colors) && getXArr(move) == 11){
          board.at(4,7) = Empty;
          board.at(7,7) = Empty;
          board.at(5,7) = P(rook, colors);
          board.at(6,7) = P(king, colors);
          return board;
       }
       else if( isCastling(board, leftBlack,colors) && getXArr(move) == 111){
          board.at(4,0) = Empty;
          board.at(0,0) = Empty;
          board.at(3,0) = P(rook, colors);
          board.at(2,0) = P(king, colors);
          return board;
       }
       else if(isCastling(board, leftWhite,colors) && getXArr(move) == 111){
          board.at(4,7) = Empty;
          board.at(0,7) = Empty;
          board.at(3,7) = P(rook, colors);
          board.at(2,7) = P(king, colors);
          return board;
       }
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
        board.at(getXArr(move), getYArr(move)) =
                    board.at(getXDep(move), getYDep(move));
            board.at(getXDep(move), getYDep(move)) = Empty;
            }
     //cout << "return in move";
    return board;
}


bool checkMate(Matrix<Pieces> &board, color colors) {
    pair<int,int> p = findKing(board, colors);

    //cout << "king x: " <<  p.first << " y: " << p.second << endl;
    //cout << "vector king: " ;printVector(filterIlegalMove(listMovesKing(p.first,p.second, board), board, colors));
    if(checkCheck(p.first, p.second, board) && filterIlegalMove(listMovesKing(p.first,p.second, board), board, colors).empty()) {
        return true;
    }
    return false;
}

bool isCastling(Matrix<Pieces> &board, castling state, color colors) {

       vector<variant<Move, castling>> everyList = everyMoveList(board, colors);
        cout << "everyList: " << endl;printVector(everyList);
        for (int i = 0; i < (int)everyList.size(); ++i) {
           cout << "state: ";printCastling(state);cout << endl;
           cout << "holds_alternative<castling>(everyList.at(i)): " << holds_alternative<castling>(everyList.at(i)) <<  endl;
           //cout << "get<castling>(everyList.at(i)): " << get<castling>(everyList.at(i));
            if(holds_alternative<castling>(everyList.at(i))){
                if(state == get<castling>(everyList.at(i))) {
                    cout << "get<castling>(everyList.at(i)): !!!" <<  get<castling>(everyList.at(i)) << endl;
                    return true;
                }
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

Matrix<Pieces> &movePlayer(Matrix<Pieces> &board, color colors){
    string coord;
    int xDep = 0, yDep = 0 , xArr = 0, yArr = 0;
    pair<int,int> p = findKing(board, colors);
    while(true) {

        cout << "enter the coordinats in the format 2b2c" << endl << "now move for "; colors == white? cout << "white :":cout <<"black :";
        cin >> coord;
        cout << "coord: " << coord << endl;


        static const regex r("[1-8][a-h][1-8][a-h]");
        if(regex_match(coord, r)){
            cout << " in regex"<<endl;
            xDep = coord[0]-48-1;
            yDep = coord[1]-97;
            xArr  = coord[2]-48-1;
            yArr = coord[3]-97;
        }
        
        if(board.at(xDep, yDep).color_piece != colors){
            cout << "you entered the wrong coordinate your color it's , " ;  colors == white? cout << "white ":cout << endl <<"black " << endl << "xDep = " << xDep  <<
                     " \tyDep = " << yDep << endl   << "xArr = " << xArr << "\tyArr = " << yArr << "  try agayn" << endl;
             cout << "Enter coordinats again: " << endl;
             continue;
        }
        variant<Move, castling>move = createMove(xDep, yDep, xArr, yArr);//TODO добавить условие, тчо кастлинг невозможен при попадании короля под шах в конечной клетке хода короля
        if(coord == "0-0" && !checkCheck(p.first, p.second, board)) {
            
            setXArr(move, 11);
            cout << "getXArr(move): " << getXArr(move) << endl;
            cout << "getYArr(move): " << getYArr(move) << endl;
            cout << "getXDep(move): " << getXDep(move) << endl;
            cout << "getYDep(move): " << getYDep(move) << endl;
            Castling(board,colors);
            return moveForBoard(board, move,colors);
        }
        else if(coord == "0-0-0"&& !checkCheck(p.first, p.second, board)) {
            
            setXArr(move, 111);
            cout << "getXArr(move): " << getXArr(move) << endl;
            cout << "getYArr(move): " << getYArr(move) << endl;
            cout << "getXDep(move): " << getXDep(move) << endl;
            cout << "getYDep(move): " << getYDep(move) << endl;
          Castling(board,colors);
          return moveForBoard(board, move,colors);

        }

        if(checkOutOfRange(xArr,yArr, board) && checkOutOfRange(xDep, yDep, board)) {
            cout << "you entered the wrong coordinate OUT OF RANGE, "  << endl << "xDep = " << xDep  <<
                     " \tyDep = " << yDep << endl   << "xArr = " << xArr << "\tyArr = " << yArr << "  try agayn" << endl;
             cout << "Enter coordinats again: " << endl;
             continue;
        }
        if(board.at(xDep, yDep).name_piece == Empty) {
            cout << "this coordinats empty, choice other coordinats" << endl;
            continue;
        }


        if(checkForIllegal(xDep, yDep,xArr,yArr, board, colors) &&  !checkCheck(p.first, p.second, board)) {//if по кастлингу вынести отдельно и прописать что ход по кастлингу не возможен - король под шахом

            return moveForBoard(board, move, colors);
        }//TODO надо сделать возможность хода из под шаха, на данный момент ход сделать невозможно, когда ты под шахом игра встает в тупик

        else {
           cout << "you entered the wrong coordinateSUMMARY "  << endl << "xDep = " << xDep  <<
                    " \tyDep = " << yDep << endl   << "xArr = " << xArr << "\tyArr = " << yArr << "  try agayn" << endl;
            cout << "Enter coordinats again: " << endl;
                 //<< endl << "now move for "; colors == white? cout << "white :":cout <<"black :" << endl;
            //cin >> coord;
            continue;
        }
    }

    return board;
}

int counterMove(Matrix<Pieces> &board, color colors, int depth) {

    if(depth == 0){
    return 1;
    }
    vector<variant<Move, castling>> listMove = everyMoveList(board, colors);
    int count = 0;
    for(int i = 0; i < (int)listMove.size(); i++) {
    Matrix<Pieces> newBoard(board);
        newBoard = moveForBoard(newBoard, listMove.at(i), colors);
        //cout << "newBoard : " << endl; newBoard.printBoard();
        //cout << "name_piece: " << newBoard.at(listMove.at(i).getXDep(), listMove.at(i).getXDep()).name_piece << ";" << endl;
        //cout << "list departure Move :" << listMove.at(i).getXDep() << "," << listMove.at(i).getYDep() << ";" << endl;
        //cout << "list arrivle Move :" << listMove.at(i).getXArr() << "," << listMove.at(i).getYArr() << ";" << endl;
        //cout << "count: " << count<< endl;
        count += counterMove(newBoard, swapColor(colors), depth - 1);


    }
    return count;
}

// TODO научится работать с GDB debugger

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


vector<variant<Move, castling>>& filterIlegalMove(vector<variant<Move, castling>> &listMove,  Matrix<Pieces> &board, color colors) {
    vector<variant<Move, castling>> *newList = new vector<variant<Move, castling>>;


    for(int i = 0; i < (int)listMove.size();i++) {

        Matrix<Pieces> newBoard(board);
        moveForBoard(newBoard,listMove.at(i), colors);
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
            cout << getXArr(arr.at(i)) << ", " << getYArr(arr.at(i)) << " ; ";
        }
        else if(holds_alternative<castling>(arr.at(i))){
             cout << " "; printCastling(get<castling>(arr.at(i))); cout << "; ";
        }
    }
    cout << "]" << endl;

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
    //listMoves.insert(listMoves.begin(), listMovesBishop(x,y,board).begin(), listMovesBishop(x,y,board).end());
    //listMoves.insert(listMoves.end(), listMovesRook(x,y,board).begin(), listMovesRook(x,y,board).end());

    return *listMoves;

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
    push_back_list(Castling(board, colors), *everyListMove);
    return *everyListMove;
}


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
            //cout << "!empty" << endl;
            if(board.at(X, Y).name_piece == rook || board.at(X, Y).name_piece == queen) {
                //cout<< "X: " << X << "Y: " << Y << endl;
                if(board.at(xKing, yKing).color_piece != board.at(X, Y).color_piece) {
                    //cout << "true ROOK" << endl;
                    return true;
                }
                else {
                   return false;
                }
            }
            else {
               return false;
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
    for(int i = 0; i < 8; i++) {
        if(checkOutOfRange(arrX.at(i), arrY.at(i), board)){
            continue;
        }

        if(board.at(arrX.at(i), arrY.at(i)).name_piece != Empty) {
            if(board.at(arrX.at(i), arrY.at(i)).name_piece != king){
                continue;
            }
            else {
                return true;
            }
        }

    }
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


bool checkForIllegal(int xDep, int yDep, int xArr, int yArr, Matrix<Pieces> &board, color colors) {
    vector<variant<Move, castling>> everyList = everyMoveList(board, colors);

    for (int i = 0; i < (int)everyList.size(); ++i) {
        if(getXDep(everyList.at(i)) == xDep && getYDep(everyList.at(i)) == yDep
                && getXArr(everyList.at(i)) == xArr && getYArr(everyList.at(i)) == yArr) {
            return true;
        }
    }
    return false;
}


bool checkForCheck(int x, int y, Matrix<Pieces> &board, color colors) {

    vector<variant<Move, castling>> listEnemy = everyMoveList(board, swapColor(colors));// разворачиваю цвет для того что бы было понятно назначение функции - передаем белый и проверяем белый

    for (int i = 0; i < (int)listEnemy.size(); ++i) {
        if(getXArr(listEnemy.at(i)) == x && getYArr(listEnemy.at(i)) == y) {
            return true;
        }
    }
    return false;
}

bool checkCheck(int x, int y, Matrix<Pieces> &board) {


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

    if(colors == 0) {
        cout << "black";
    }
    if(colors == 1) {
        cout << "white";
    }
}

int main (int argc, char* argv[]){

   /* Pieces board[64] = {
    P(rook, black), P(bishop, black), P(knight, black), P(queen, black),P(king, black), P(knight, black), P(bishop, black), P (rook, black),
    P(pawn, black), P(pawn, black), P(pawn, black) , P(pawn, black), P(pawn, black), P(pawn, black), P(pawn, black), P(pawn, black),
    PE(Empty), PE(Empty), PE(Empty),PE(Empty),PE(Empty), PE(Empty),PE(Empty),PE(Empty),
    PE(Empty),PE(Empty), PE(Empty),PE(Empty),PE(Empty), PE(Empty),PE(Empty),PE(Empty),
    PE(Empty), PE(Empty),PE(Empty),PE(Empty),PE(Empty), PE(Empty),PE(Empty),PE(Empty),
    PE(Empty), PE(Empty), PE(Empty),PE(Empty),PE(Empty), PE(Empty),PE(Empty),PE(Empty),
    P(pawn, white), P(pawn, white), P(pawn, white) ,P(pawn, white), P(pawn, white), P(pawn, white) , P(pawn, white), P(pawn, white),
    P(rook, white), P(bishop, white), P(knight, white), P(queen, white), P(king, white), P(knight, white), P(bishop, white), P (rook, white),
};
*/
    Pieces board[64] = {
        P(rook, black), PE(Empty), PE(Empty),PE(Empty),P(king, black), PE(Empty),PE(Empty),P(rook, black),
        PE(Empty),PE(Empty), PE(Empty),PE(Empty),PE(Empty), PE(Empty),PE(Empty),PE(Empty),
        PE(Empty), PE(Empty),PE(Empty),PE(Empty),PE(Empty), PE(Empty),PE(Empty),PE(Empty),
        PE(Empty), PE(Empty), PE(Empty),PE(Empty),PE(Empty), PE(Empty),PE(Empty),PE(Empty),
        PE(Empty), PE(Empty), PE(Empty),PE(Empty),PE(Empty), PE(Empty),PE(Empty),PE(Empty),
        PE(Empty),PE(Empty), PE(Empty),PE(Empty),PE(Empty), PE(Empty),PE(Empty),PE(Empty),
        P(pawn, black), PE(Empty),PE(Empty),PE(Empty),PE(Empty), PE(Empty),PE(Empty),PE(Empty),
        P(rook, white), PE(Empty), PE(Empty),PE(Empty),P(king, white), PE(Empty),PE(Empty),P(rook, white),
    };

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



    color colors = white;
    while(true) {

        //cout << "enter the coordinats in the format 2b2c" << endl << "now move for "; colors == white? cout << "white :":cout <<"black :";

        printBoard(movePlayer(chess, colors));
        colors = swapColor(colors);
        if(checkMate(chess, colors)) {
            cout << "Game over!" << endl << "MATE for " ; printColor(colors); cout << ", WINNER - "; printColor(swapColor(colors)); cout <<  endl;
            break;

        }
    }
    variant<Move, castling> move, state;

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

    vector <variant<Move, castling>> sV ;

   sV.push_back(rightBlack);

   //cout << "castling mV: " << get<castling>(sV.at(0)) << endl;



    //TODO поменять все вектора на variant сделать функцию кастлинг

    //cout << counterMove(chess,white, 3) << endl;



    //cout << "checkToBishopOrQueen: " << checkToRookOrQueen(3,3,chess) << endl;
    //Move m;
    //printVector(everyMoveList(chess,white));
    //cout  <<"check?: " << checkForCheck(4,4,chess,white) << endl;
    //printVector(filterIlegalMove(everyMoveList(chess,white), chess, white));
    //printVector(listMovesQueen(1,0,chess));
    //printOneMove(chess, listMovesQueen(1,0,chess));
    //printOneMove(chess, everyMoveList(chess,white));
    //pair<int,int> p = findKing(chess, white);
    //cout << "xKing: " << p.first << endl;
    //cout << "yKing: " << p.second << endl;
     //cout << checkCheck(p.first,p.second,chess)<< endl;
    //m.Print(m.xArrivle);

     //chess.at(1,2)=42;
//printBoard(chess);
    //cout << king1;
     //cout << chess.at(1,2);

return 0;
}
