#include <iostream>
using namespace std;

void* operator new(size_t size) {
    cout << "Allocating " << size << " bytes\n";
    return malloc(size);


}

class Object {
     int x, y ,z;
};

int main()
{
    string string = "Cherno";
    Object* obj = new Object;

 return 0;
}