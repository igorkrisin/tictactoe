#include <stdio.h>
#include <iostream>
#include <cstdio>
using namespace std;
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
    
int app_x;
int app_y;
int size_wv;
int size_wh;


void gen_app()
	{
		app_x = rand()%size_wv;
    	app_y = rand()%size_wh;
	}

class Coord
{
	public:
	int x;
	int y;

	
	Coord()
	{
		x = 0;
		y = 0;
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
	for(int i = 1; i < baryer; i++)
	{
	    if(arr[i] == elem)
	    {
		return true;
	    }
	    
	}
	return false;
    }
    
    
    ~ Vector()
    {
	free(arr);
	//cout << "Деструктор вызван" << endl;
    }
};






int main()
{
	
	//Coord j;
    
    
    //cout << "x " <<  b.x << endl;
    //cout << "y " << b.y << endl;
    
    Vector <Coord> a;

	Coord b(b.x, b.y);

	srand(time(NULL));
    initscr();
    noecho();    
	halfdelay(5);
    getmaxyx(stdscr, size_wv, size_wh);
	//int elem1_x = a[0].x;
	//int elem1_y = a[0].y;

	gen_app();
	int napr_x = 1;
	int napr_y = 0;

	a.append(Coord(b.x, b.y));

	while(1){
    int key = getch();
    erase();
    if(key == 'w'){
		napr_y = 0;
		napr_x = -1;
	}
    if(key == 's'){
		napr_y = 0;
        napr_x = 1;
	}
    if(key == 'd'){
        napr_y = 1;
        napr_x = 0;
	}
    if(key == 'a'){
        napr_y = -1;
        napr_x = 0;
	}
    if(key == 'q'){
        return 0;
    }
    
    if(b.y < 0){
        b.y = size_wh-1;
    }
    if(b.y >= size_wh){
        b.y = 0;
    }
    if(b.x < 0){
        b.x = size_wv-1;
    }
    if(b.x >= size_wv){
        b.x = 0;
    }
    
	b.x += napr_x;
    b.y += napr_y;

	

	
	
    Coord c(a[0].x, a[0].y);

	 if(a.member(c))
	{
		return 0;	
	}  

	a.append(Coord(b));

	Coord e(app_x, app_y);

	if(!a.member(e))
	{
		a.del_el();
		
	}
	else
	{
		
		gen_app();
	}
	
	for(int i = 0; i < a.baryer; i++){
		mvaddstr(a[i].x, a[i].y, "s");
    }

    mvaddstr(app_x, app_y, "a");
	
    
}


    /* for(int i = 0;i <= 100; i++){
		Coord b(i, i+1);
		a.append(b);
    
    }  
	 */
	// уничтожение *b &b
	
	//a.insert(67, 66);

	//a.del_el();
    
    for(int i = 0; i < a.baryer; i++){
		printf("(x = %d , y = %d)", a[i].x, a[i].y);
    }
    Coord c(34,35);
    //cout << "member " << a.member(c) << endl;
	endwin();		
    return 0;
}
