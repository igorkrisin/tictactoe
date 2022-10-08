#include <stdio.h>
#include <iostream>
using namespace std;
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
    
    int app_x;
    int app_y;
    int size_wh;
    int size_wv;
    int x = 0;
    int y = 0;
    int napr_x;
    int napr_y;
    int speed;

void gen_app(int size_wh,  int size_wv){
    app_x = rand()%size_wv;
    app_y = rand()%size_wh;
}
template<typename T> class Vector
{
    private:
    T* arr;
    int baryer;
    
public:
    int size;

    
    
    Vector()
    {
        arr = (T*)malloc(size*sizeof(T));
        baryer = 0;
    }
    void append(T num)
    {
        if(baryer >= size)
        {
            size = size*2;
            T* arr_new = (int*)malloc(size*sizeof(T));
            for(int i = 0; i < size; i++)
            {
                arr_new[i] = arr[i];
            } 
            free(arr);
            arr_new[baryer++] = num;
            arr = arr_new;
        }
        else
        {
            arr[baryer++] = num;
        }
    }


    T get(int index)
    {
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
 
    /* void print_sn()
    {
        for (int i = 0; i < baryer; i++)
        {
            mvaddstr(arr[i],arr[i], "s");
        }
        
    }
 */

};



int main()
{
    Vector <int> a;

    srand(time(NULL));
    initscr();
    noecho();    
    getmaxyx(stdscr, size_wh, size_wv);
    speed = 5;
    halfdelay(speed);
    gen_app(size_wh, size_wv);
    a.size = 1; //size_wv*size_wh;
    napr_x = 1;
    napr_y = 0;
    a.append(a.size);
    while(1){
    

        int key = getch();
        erase();
        
        

        if(key == 'w'){
            napr_y = -1;
            napr_x = 0;
        }
        else if(key == 's'){
            napr_y = 1;
            napr_x = 0;
        }
        else if(key == 'd'){
            napr_y = 0;
            napr_x = 1;
        }
        else if(key == 'a'){
            napr_y = 0;
            napr_x = -1;
        }
        else if(key == 'q'){
            return 0;
        }

        x = napr_x+x;
        y = napr_y+y;
        
        if(y < 0){
            y = size_wh-1;
        }
        else if(y >= size_wh){
            y = 0;
        }
        if(x < 0){
            x = size_wv-1;
        }
        else if(x >= size_wv){
            x = 0;
        }
        a.append(a.size);
        //a.print_sn();
        
        mvaddstr(app_y, app_x, "a");
    
}



endwin();
    /* Vector<int>  a;
    int x = (int)3.14; // type cast

    for(int i = 0;i <= 100; i++){
		a.append(i);
    
    }

    a.del_el();
    
    for(int i = 0; i < 100; i++){
		printf("%d ", a.get(i));
    } */
    
    return 0;
}
