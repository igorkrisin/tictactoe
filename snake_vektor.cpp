#include <stdio.h>
#include <iostream>
#include <cstdio>
using namespace std;



class Coord
{
	public:
	int x;
	int y;
	
	Coord(const Coord &argum2)
	{
	    x = argum2.x;
	    y = argum2.y;
	    
	    cout << "вызван констр копирования" << endl; 
	}

	Coord(int arg_x, int arg_y)
	{
	    x = arg_x;
	    y = arg_y;
	}
	bool operator==(const Coord &argum2)
	    {
		return x == argum2.x && y == argum2.y;

		
	    }
	    

};

template<typename T> class  Vector
{

private:
    T* arr;
    int size;
    
public:

    
    int baryer;
    
    Vector()
    {
    size = 20;
    arr = (T*)malloc(size*sizeof(T));
    baryer = 0;
    }

    void insert(int index, T num)
    {
    
	if(index >= baryer || index < 0)
	{
	    throw out_of_range("out of range");
	
	}
	if(baryer >= size)
	{
		//cout << " цикл в if" << endl;
		int new_size = size*2;
		T* arr_new = (T*)malloc(new_size*sizeof(T));	

		for(int i = 0; i <= baryer; ++i)
		{
			arr_new[i] = arr[i];
			//cout << " цикл копирования в if" << endl;
		}
		
		for(int i = baryer; i >= index; i--)
		{
			arr_new[i] = arr_new[i-1];
		}
		free(arr);
		arr_new[index] = num;
		arr = arr_new;
		baryer++;

	}
	else
	{
		//cout << " цикл в else\t" << endl;
		int new_size;
		for(int i = baryer; i >= index; i--)
		{
			//cout << "цикл в else arr[i]\t" <<  arr[i] << endl;
			arr[i] = arr[i-1];
			//cout << "цикл в else arr[i] после добавления\t" <<  arr[i] << endl;
			//cout << "цикл в else arr[i+1]\t"<< arr[i+1] << endl;
		}
		
		arr[index] = num;
		baryer++;
		//cout << "барьер"<< baryer << endl;
		//cout << "добавляем число в else" << endl;
	}
	
    }


    void append(T num)
    {
	if(baryer >= size)
	{
	    
	    int new_size = size*2;
	    T* arr_new = (T*)malloc(new_size*sizeof(T));
	    for(int i = 0; i < size; i++)
	    {
		arr_new[i] = arr[i];
		
	    }
	    size = new_size;
	    free(arr);
	    arr_new[baryer++] = num;
	    arr = arr_new;
	}
	else
	{
	arr[baryer++] = num;
	}
	    
	    
    }
    T &operator[](int index)
    {
	if(index >= baryer || index < 0)
	{
	    throw out_of_range("index out of range");
	    
	}
	return arr[index];
    }

    void del_el()
    {
    	for(int i = 0; i < baryer; i++)
    		{
    			arr[i] = arr[i+1];
    		}
    	baryer--;
    }
    
    bool member(T elem)
    {
	for(int i = 0; i < baryer; i++)
	{
	    if(arr[i] == elem)
	    {
		return true;
	    }
	    else
	    {
		continue;
	    }
	}
	return false;
    }
    
    
    ~ Vector()
    {
	free(arr);
	cout << "Деструктор вызван" << endl;
    }
};




template<typename T> 
T  min_num(T a, T b) 
{
	return a > b? b: a;
		
}

int main()
{
	//cout << min_num(2.3, 3) << endl;
	
    Coord b(11,1);
    
    cout << "x " <<  b.x << endl;
    cout << "y " << b.y << endl;
    
    Vector <Coord> a;
    int x = (int)3.14; // type cast преобразование типа объекта

    for(int i = 0;i <= 100; i++){
	Coord b(i, i+1);
	a.append(b);
    
    }  // уничтожение *b &b
	
	//a.insert(67, 66);

	//a.del_el();
    
    for(int i = 0; i < a.baryer; i++){
		printf("(x = %d , y = %d)", a[i].x, a[i].y);
    }
    Coord c(34,35);
    cout << "member " << a.member(c) << endl;

    return 0;
}
