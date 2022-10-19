#include <iostream>
#include <array>
#include <ctime>
#include <vector>
#define EMPTY ' ' 
using namespace std;

enum state { Xwin, Owin, notEnd, Tie};
void printBoard(array<char,9> board);

char compSimb = 'o';
char userSimb = 'x';

int MIN = false;
int MAX = true;

int bestScore;

//int minimax(array<char,9> board, int depth, bool State);

bool isNotEnd(array<char,9> board) {
    for(int i = 0; i < 9; i++) {
        if(board.at(i) == ' ') {
                return true;
        }
    }
    return false;
}

state checkState(array<char,9> board) {
    for(int y = 0; y < 3; y++){
    
        if(board.at(y*3+0) == board.at(y*3+1) && board.at(y*3+1) == board.at(y*3+2) && board.at(y*3) != ' ') {
    	    return(board.at(y*3)) == 'x'?  Xwin: Owin;
        }
        
        else if(board.at(y*1+0) == board.at(y*1+3) && board.at(y*1+3) == board.at(y*1+6) && board.at(y*1) != ' ') {
            return(board.at(y*1)) == 'x'?  Xwin: Owin;
        }
    

    }

    if(board.at(0*3+0) == board.at(1*3+1) && board.at(1*3+1) == board.at(2*3+2) && board[0*3+0] != ' ') {
	return(board.at(0*3+0)) == 'x'?  Xwin: Owin;
    }

    else if(board.at(0*3+2) == board.at(1*3+1) && board.at(1*3+1) == board.at(2*3+0) && board[0*3+2] != ' ') {
        return(board.at(0*3+2)) == 'x'?  Xwin: Owin;
    }


    else if(isNotEnd(board)){
        return notEnd;
    }

    return Tie;

}

//


void printState(array<char,9> board) {
    cout << "checkBoard : " << checkState(board) << "\n";
    if(checkState(board) == 0){
        cout << "WIN X";
    }
    else if(checkState(board) == 1){
        cout << "WIN 0";
    }
    else if(checkState(board) == 2){
        cout << "NOT END";
    }
    else if(checkState(board) == 3){
        cout << "TIE";
    }
}


/* array<char,9> moveRand(array<char,9> board, char x) {
    srand(time(NULL));
    int index = rand()%10;
    while(board[index] != ' ') {
        index = rand()%10;
    }
    board[index] = x;
    return board;

} */

int max(int x, int y) {
    if (x > y) {
        return x;
    }
    else {
        return y;
    }
}

int min(int x, int y) {
    if (x < y) {
        return x;
    }
    else {
        return y;
    }
}

int minimax(array<char,9> &board, int depth, bool State) {
    if(checkState(board) == Xwin) {
        return -100;
    }
    if(checkState(board) == Owin) {
        return 100;
    }
    if(checkState(board) == Tie) {
        return 0;
    }
    // choise move which best for me
    if(State) {
        bestScore = - 1000;
        for (int i = 0; i < 9; i++)
        {
            if(board.at(i) == EMPTY) {
                board.at(i) = compSimb;
                int score = minimax(board, depth+1, MIN);
                board.at(i) = EMPTY;
                bestScore = max(bestScore, score);
                //cout << "printBoard COMP:";
                //printBoard(board);
                //cout << endl;
            }
        }
        
    // choise move which best for enemy
    }
    else {
        bestScore = 1000;
        for (int i = 0; i < 9; i++)
        {
            if(board.at(i) == EMPTY) {
                board.at(i) = userSimb;
                int score = minimax(board, depth+1, MAX);
                board.at(i) = EMPTY;
                bestScore = min(bestScore, score);
                //cout << "printBoard USER:";
                //printBoard(board);
                //cout << endl;
            }
        }

    }
    //cout << "bestScore: " << bestScore << endl;
    return bestScore;

    
}

array<char,9> copyAray(array<char,9> board1, array<char,9> board2) {

    for (int i = 0; i < 9; i++)
    {
        board1[i] = board2[i];
    }
    return board1;
}

array<char,9> MoveComp(array<char,9> &board, char whoMove){
    bestScore = -1000;
    array<char,9> newBoard = board;
    for(int i = 0; i < 9; i++) {
        if(newBoard.at(i) == ' ') {
            newBoard.at(i) = compSimb;
            int score = minimax(newBoard, 0, MIN);
            newBoard.at(i) = ' ';
            if(score > bestScore){
                cout << "best score New Board  ";
                newBoard.at(i) = compSimb;
            }
        }
    }
   
    board = copyAray(board, newBoard);
    return board;
}




void printBoard(array<char,9> board) {
    cout << '-' << '-' << '-'<< '-' << '-' << '-' << '-'<< '\n';
    for(int x = 0; x < 3; x++) {

        cout << '|' << board.at(0+x*3) << '|' <<  board.at(1+x*3) << '|' << board.at(2+x*3) << '|' <<'\n';
        cout << '-' << '-' << '-'<< '-' << '-' << '-' << '-';
        cout << '\n';
    }

}
//1,2 4,5 7,8

array<char,9> clearBoard(array<char,9> &board) {

    for (int i = 0; i < 9; ++i) {
        if(board[i] != ' '){
            board.at(i) = ' ';
        }
    }
    return board;
}




vector<array<char,9>> allBoard(array<char,9> board, char whoMove) {
    vector <array<char, 9>> allBoard;
    
    for(int i = 0; i < 9; i++) {
	if(board.at(i) == ' ') {
	    array<char,9> newBoard = board;
	    newBoard.at(i) = whoMove;
	    allBoard.push_back(newBoard);
	}
    }
    
    return allBoard;
}





void printAllBoard(vector <array<char, 9>> allBoard) {
    cout << allBoard.size() << endl;
    for(int i = 0; i < allBoard.size();i++) {
	printBoard(allBoard.at(i));
	cout << ' ';
    }
}


//TODO  поправить все индексы в .at()
//TODO УЗНАТЬ версию STD
//Minimax 


int main() {

    

    array<char,9> board = {' ', ' ', ' ',
                           ' ', ' ', ' ',
                           ' ', ' ', ' '};
/////////////////////////////////////////////
//printAllBoard(allBoard(board, 'x'));





//////////////////////////////////////////

    bool flag = true;
    //char simbolPlayer = ' ';
    //char simbolComp = ' ';
    while(true) {
        char answer;


        /* if(flag == true) {
            cout << "Choise simbol for playing - o / x: \n";
            cin >> simbolPlayer;
            if(simbolPlayer == 'o') {
                simbolComp = 'x';
                flag = false;
            }
            else if(simbolPlayer == 'x') {
                simbolComp = 'o';
                flag = false;
            }
            else {
                cout << "selected sombol incorrect, please try again\n";
                continue;
            }
        } */
        int indexPlayer = 0;
        cout << "Choise number empty cell: \n";
        cin >> indexPlayer;
        if(board[indexPlayer] != ' '){
            cout << "Cell not empty, try again choise\n";
            continue;
        }

        board[indexPlayer] = userSimb;
        if(!isNotEnd(board)){
            cout << "Tie\n";
            cout << "try again? press y or n\n";
            cin >> answer;
            if(answer == 'y') {

                clearBoard(board);
                flag = true;
                continue;
            }
            else {
                break;
            }
        }
        cout << "Comp move... \n";
        board = MoveComp(board, compSimb);
        printBoard(board);

            if(checkState(board) == Xwin) {
                cout << "X win\n";
                cout << "try again? press y or n\n";
                cin >> answer;
                if(answer == 'y') {
                    clearBoard(board);
                    flag = true;
                    continue;
                }
                else {
                    break;
                }
            }
            else if(checkState(board) == Owin) {
                cout << "0 win\n";
                cout << "try again? press y or n\n";
                cin >> answer;
                if(answer == 'y') {

                    clearBoard(board);
                    flag = true;
                    continue;
                }
                else {
                    break;
                }
            }
            else if(checkState(board) == Tie) {
                cout << "Tie\n";
                cout << "try again? press y or n\n";
                cin >> answer;
                if(answer == 'y') {
                    clearBoard(board);
                    flag = true;
                    continue;
                }
                else {
                    break;
                }
            }

    }





    return 0;
}
