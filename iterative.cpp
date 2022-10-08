#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;
#include <ncurses.h>





class Point
{
private:
    int x;
    int y;
public:


    Point ()
    {
        x = 0;
        y = 0;
    }
     Point(int valueX, int valueY)
    {
        x = valueX;
        y = valueY;
    } 

    int GetX()
    {
        return x;
    }
    
    void SetX(int valueX)
    {
        x = valueX;
    }

    int GetY()
    {
        return y;
    }
    
    void SetY(int valueY)
    {
        y = valueY;
    }

     void Print()
    {
        cout << "x = " << x << "\t y =  " << y << endl; 
    }
    
    bool operator ==(const Point & other)
    {
       return this->x == other.x && this->y == other.y;
        
    }

    Point operator +(const Point & other)
    {
        Point temp;
        temp.x = this->x+other.x;
        temp.y = this->y+other.y;
        return temp;
    }

    Point & operator ++()
    {
        this->x++;

        this->y += 1;

        return *this;
    }


};

class Human
{
public:

    int age;
    int Weight;
    string name;

    void Print()
    {
        cout << "Имя " << name << "\t Вес " << Weight << "\t Возраст " << age << endl; 
    }

};

class CofeeGrinder

{
private:
    bool CheckVoltage()
    {
        return false;
    }
public:
    
   void Start()
   {
       
       if(CheckVoltage())
       {
            cout << "Vjjjooouh" << endl;
       }
       else
       {
        cout << "Peep pp" << endl;
       }
   }
};

/* class MyClass
{
private:
    int Size;    
public:
    int* data;

    MyClass(int size)
    {
        this->Size = size;
        this->data = new int[size];
        for (int i = 0; i < size; i++)
        {
            data[i] = i;
        }
        
        cout << "Вызвался конструктор " << this << endl;
    }

    MyClass(const MyClass &other)
    {


        cout << "Вызвался конструктор копирования" << this << endl;

        this->data = new int [other.Size];
        for (int i = 0; i < other.Size; i++)
        {
            this->data[i] = other.data[i];
        }
        
        this->data = new int [other.Size];
        for (int i = 0; i < other.Size; i++)
        {
            this->data[i] = other.data[i];
        }
      
    }

    ~MyClass()
    {
        cout << "Вызывался деструктор " << this << endl;
        delete[] data;
    }
    MyClass &operator = (const MyClass &other)
    {
        cout << "Вызывался оператор присваивания " << this << endl;

        this->Size = other.Size;
        if(this->data != nullptr)
        {
            delete[] this-> data;
        }
        
    }

    //return this;
};

void Foo(MyClass value)
{
    cout << "Вызвалаcь функция Foo" << endl;
}


MyClass Foo2()
{
    cout << "Вызвалаcь функция Foo2" << endl;
    MyClass temp(2);

    return temp;

}


 */
int main()
{   
    initscr();
    if (has_colors()) 
    {
        use_default_colors();
        start_color();
        init_pair(2, COLOR_RED, -1);
    }
    printw("line 1\n");
    attrset(COLOR_PAIR(2));
    printw("line 2\n");
    attrset(COLOR_PAIR(2));
    printw("line 3");
    getch();
    endwin();

}