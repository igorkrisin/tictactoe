#include <iostream>
#include <array>
using namespace std;

enum state { Xwin, Owin, notEnd, Tie};

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
    if(board.at(y*3+0) == board.at(y*3+1) && board.at(y*3+1) == board.at(y*3+2) && board.at(y*3) != ' ' && board.at(y*3) == 'x') {
	    return Xwin;
	}
    else if(board.at(y*3+0) == board.at(y*3+1) && board.at(y*3+1) == board.at(y*3+2) && board.at(y*3) != ' ' && board.at(y*3) == 'o') {
	    return Owin;
	}
	
    }
    
    if(board.at(0*3+0) == board.at(1*3+1) && board.at(1*3+1) == board.at(2*3+2) && board[0*3+0] != ' ' && board.at(0*3+0) == 'x') {
        return Xwin;
    }
    
    else if(board.at(0*3+2) == board.at(1*3+1) && board.at(1*3+1) == board.at(2*3+0) && board[0*3+2] != ' ' && board.at(0*3+2) == 'x') {
        return Xwin;
    }
    
    else if(board.at(0*3+0) == board.at(1*3+1) && board.at(1*3+1) == board.at(2*3+2) && board[0*3+0] != ' ' && board.at(0*3+0) == 'o') {
        return Owin;
    }
    
    else if(board.at(0*3+2) == board.at(1*3+1) && board.at(1*3+1) == board.at(2*3+0) && board[0*3+2] != ' ' && board.at(0*3+2) == '0') {
        return Owin;
    }

    else if(isNotEnd(board)){
        return notEnd;
    }
    else {
        return Tie;
    }
    

}





//0, 4, 8  2, 4, 6



int main() {

array<char,9> board = {' ', ' ', ' ',
                       ' ', ' ', ' ',
                       ' ', ' ', ' '};
		     

for(int i = 0; i < board.size()+1; i++) {
    cout << board.at(i) << ", ";

}


    return 0;
}
