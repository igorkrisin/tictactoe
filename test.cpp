#include <iostream>

template<typename T>
T min_num(T a, T b){
   return a>b?a:b;
}

template<typename T>
int foo(T x){
	return sizeof(x);
}


int main(){
   std::cout<<min_num<double>(42.9, 13.4)<<"\n";
   std::cout<<foo<char>(42)<<std::endl;
   return 0;
}
