#include <iostream>
#include <array>
#include <ctime>
#include <vector>
using namespace std;

enum state { Xwin, Owin, notEnd, Tie};


int evaluatMove(array <char,9> &board, char whoMove, int depth);
void printAllBoard(vector <array<char, 9>> allBoard);





bool isNotEnd(array<char,9> board) {
    for(int i = 0; i < 9; i++) {
        if(board.at(i) == ' ') {
                return true;
        }
    }
    return false;
}

state checkState(array<char,9> &board) {
    for(int y = 0; y < 3; y++){
    
        if(board.at(y*3+0) == board.at(y*3+1) && board.at(y*3+1) == board.at(y*3+2) && board.at(y*3) != ' ') {
    	    return(board.at(y*3)) == 'x'?  Xwin: Owin;
        }
        
        else if(board.at(y*1+0) == board.at(y*1+3) && board.at(y*1+3) == board.at(y*1+6) && board.at(y*1) != ' ') {
            return(board.at(y*1)) == 'x'?  Xwin: Owin;
        }
    

    }

    if(board.at(0*3+0) == board.at(1*3+1) && board.at(1*3+1) == board.at(2*3+2) && board.at(0*3+0) != ' ') {
	return(board.at(0*3+0)) == 'x'?  Xwin: Owin;
    }

    else if(board.at(0*3+2) == board.at(1*3+1) && board.at(1*3+1) == board.at(2*3+0) && board.at(0*3+2) != ' ') {
        return(board.at(0*3+2)) == 'x'?  Xwin: Owin;
    }


    else if(isNotEnd(board)){
        return notEnd;
    }

    return Tie;

}



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


array<char,9> moveRand(array<char,9> board, char x) {
    srand(time(NULL));
    int index = rand()%10;
    while(board.at(index) != ' ') {
        index = rand()%10;
    }
    board[index] = x;
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

void printEmptyBoard(array<char,9> board) {
    cout << '-' << '-' << '-'<< '-' << '-' << '-' << '-'<< '\n';
    for(int x = 0; x < 3; x++) {

        cout << '|' << 0+x*3 << board.at(0+x*3) << '|' <<  1+x*3 <<  board.at(1+x*3) << '|' << board.at(2+x*3) << '|'  << 2+x*3<<'\n';
        cout << '-' << '-' << '-'<< '-' << '-' << '-' << '-';
        cout << '\n';
    }

}



array<char,9> clearBoard(array<char,9> &board) {

    for (int i = 0; i < 9; ++i) {
        if(board.at(i) != ' '){
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


int bestScore(vector<int> evaluatMove) {
int bScore = evaluatMove[0];
for(int i = 0; i < evaluatMove.size();i++) {
    if(evaluatMove.at(i) > bScore) {
	    bScore = evaluatMove.at(i);
    }
}
    return bScore;
}

int minScore(vector<int> evaluatMove) {
int mScore = evaluatMove[0];
for(int i = 0; i < evaluatMove.size();i++) {
    if(evaluatMove.at(i) < mScore) {
	    mScore = evaluatMove.at(i);
    }
}
    return mScore;
}

int indexMaxEl(vector<int> allEvaluat) {
    int bScore = allEvaluat[0];
    int index = 0;
    for(int i = 0;i < allEvaluat.size(); i++) {
        if(allEvaluat.at(i) > bScore){
            bScore = allEvaluat.at(i);
            index = i;
        }
    }
    cout << "index max: " << index << endl;
    
    return index;
}


int indexMinEl(vector<int> allEvaluat) {
    int mScore = allEvaluat[0];
    int index = 0;
    for(int i = 0;i < allEvaluat.size(); i++) {
	if(allEvaluat.at(i) < mScore){
	    mScore = allEvaluat.at(i);
	    index = i;
	}
    }
    cout << "index min: " << index << endl;
    return index;
}

array<char,9> bestBoard(array<char,9> board, char whoMove) {
    vector<array<char,9>> aBoards = allBoard(board, whoMove);
    vector<int> allEvaluat;
    for(int i = 0; i < aBoards.size(); i++) {
	    allEvaluat.push_back(evaluatMove(aBoards.at(i), whoMove, 0));
    }
    
    int index = indexMaxEl(allEvaluat);
    return aBoards[index];
}


void printAllBoard(vector <array<char, 9>> allBoard) {
    for(int i = 0; i < allBoard.size();i++) {
	    printBoard(allBoard.at(i));
	    cout << ' ';
    }
}


void printAllBoardGoriz(vector <array<char, 9>> allBoard, vector<int> allEvaluat) {
    for(int z = 0; z < 3; z++) {
	
	for(int i = 0; i < allBoard.size();i++) {
	    for(int y = 0; y < 3; y++) {
		cout << allBoard[i][z*3+y];
	    }
	    cout << "|";
	
	
    }
    cout  << '\n';
    }
    
    
    for(int i = 0; i < allEvaluat.size();i++) {
	    cout << " "  << allEvaluat.at(i) << " ";
    }
    cout << endl;
}

char who_move(char simb) {
    
    if(simb == 'o') {
        return 'x';
    }
    else if(simb == 'x') {
        return 'o';
    }
    return 'E';
}

void printVector(vector<int> vec){
    //cout << "PRINT VECTOR: ";
    for (int i = 0; i < vec.size(); i++)
    {
        cout << vec.at(i) << " ";
    }
    cout << endl;
}

 
// x - user o - ai
int evaluatMove(array <char,9> &board, char whoMove, int Depth) {
    
    if(checkState(board) == Xwin) {
            //
            //cout << "XW ";
	    return -1;
    }
    else if(checkState(board) == Owin) {
            ///
           // cout << "OW ";
	    return 1;
    }
    else if(checkState(board) == Tie) {
        //cout << "Ti ";
            ///напечатать отельную доску с оценкой и depth
	    return 0;
    }
    vector<array<char,9>> allBoards = allBoard(board, who_move(whoMove));
    vector<int> allEvaluat;
    for(int i = 0; i < allBoards.size();i++) {
	    allEvaluat.push_back(evaluatMove(allBoards.at(i), who_move(whoMove), Depth+1));
    }
    //printVector(allEvaluat);
    cout << endl << "Depth: " << Depth << endl;
    printAllBoardGoriz(allBoard(board, who_move(whoMove)), allEvaluat);
    return (whoMove =='o' ? minScore : bestScore)(allEvaluat);
}

bool isInt(int num) {
    int arr[9];
    for (int i = 1; i < 10; i++)
    {
        arr[i] = i;
    }
    for (int i = 0; i < 9; i++)
    {
        if(arr[i] == num) {
            return true;
        }
    }
    return false;
    
}


int inputInt(int m = INT_MIN, int M = INT_MAX)
{
    int N;
    for (;;) {
        cout <<  " enter nuber cell " << m << " to " << M << "): " << flush;
        if ((cin >> N).good() && (m <= N) && (N <= M)) return N;
        if (cin.fail()) {
            cin.clear();
            cout << "incorrect enter, please try agayn.\n";
        } else {
            cout << "number of range, please try agayn.\n";
        }
        cin.ignore(numeric_limits<std::streamsize>::max(),'\n');
    }
}

int main() {

    array<char,9> board = {' ', ' ', ' ',
                           ' ', ' ', ' ',
                           ' ', ' ', ' '};
    array<char,9> emptyBoard = {'1', '2', '3',
                                '4', '5', '6',
                                '7', '8', '9'};
     
    
    

    bool flag = true;
    char simbol = 'x';
    int indexPlayer = 1;
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
        }   */
        printBoard(emptyBoard);
        
        printBoard(board);
        
        //cout << "Choise number empty cell: \n";
        //cin >> indexPlayer;

        indexPlayer = inputInt(1,9);
       
        if (board[indexPlayer - 1] != ' '){
             cout << "Cell not empty, try again choise\n";
            continue;
        }
        
 
       
        board.at(indexPlayer - 1) = simbol;
        if(checkState(board) == Xwin) {
            cout << "X win\n";
                printBoard(board);
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
        board = bestBoard(board, who_move(simbol));
       // printBoard(board);

            if(checkState(board) == Xwin) {
                cout << "X win\n";
                printBoard(board);
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
                printBoard(board);
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
                printBoard(board);
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