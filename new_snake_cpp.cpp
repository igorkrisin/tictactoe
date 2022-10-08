#include <stdio.h>
#include <iostream>
using namespace std;

class Vector
{
    private:
    int* arr;
    int baryer;
    int size;

public:

    Vector()
    {
        arr = (int*)malloc(size*sizeof(int));
        baryer = 0;
    }

    void append(int num)
    {
	if(baryer > size)
	{
	    size = size*2;
	    int* arr_new = (int*)malloc(size*sizeof(int));
	    for(int i = 0; i < size; i++)
	    {
		arr_new[i] = arr[i];
		
	    }
	    free(arr);
	    arr = arr_new;
	}
	else
	{
	arr[baryer++] = num;
	}
    }

    int get(int index)
    {
	return arr[index];
    }



};

int main()
{
    Vector  a;
    int x = (int)3.14; // type cast

    for(int i = 0;i <= 100; i++){
		a.append(i);
    
    }

	//a.del_el();
    
    for(int i = 0; i <= 100; i++){
		printf("%d ", a.get(i));
    }
    
    return 0;
}
