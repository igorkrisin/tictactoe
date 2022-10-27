#include <iostream>
#include <stdexcept>
#include <cstdio>
#include <string>
using namespace std;

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
	    // TODO: std::format
	    //TODO can we overload curly bracees and equal
	    // TODO templates
	    // TODO 
	    string mssg = "width= "+to_string(matrWidth)+" hight= "+to_string(matrHight) +" ,but "+" x="+to_string(x)+" y="+to_string(y);
	    throw out_of_range(mssg);
	}
	return matr[y * matrWidth + x];
    }

};






int main (){

    Matrix chess(8,8);
    //cout << chess.at(6,4);
     array<int,3> d = {1,2,3}
     int x[42];
     x[0]=13;
     x[1]=666;
     chess.at(1,2)=42;
     
     cout << chess.at(1,2);
     
return 0;
}