#include <iostream>
using namespace std;

class MyString
{
private:
    char *str;
public:

    MyString(){
        str = nullptr;
    }
    MyString(char* str){
        
        int lenght = strlen(str);
        this->str = new char[lenght+1];
        for (int i = 0; i < lenght; i++)
        {
            this->str[i] = str[i];
        }
        this->str[lenght] = '\0';
    }
    ~MyString(){
        delete [] this->str;
    }

    MyString &operator = (const MyString &other){
        if(this->str != nullptr){
            delete [] str;
        }
       int lenght = strlen(other.str);
        this->str = new char[lenght+1];
        for (int i = 0; i < lenght; i++)
        {
            this->str[i] = other.str[i];
        }
        this->str[lenght] = '\0';
        
        return *this;
    }

    MyString operator+ (const MyString &other){
        MyString newStr;
        int thisLength = strlen(this->str);
        int otherLenght = strlen(other.str);

        newStr.str = new char[thisLength+otherLenght+1];
        int i = 0;
        for (; i < thisLength; i++)
        {
            newStr.str[i] = this->str[i];
        }
        for (int j = 0; j < otherLenght; j++, i++)
        {
            newStr.str[i] = other.str[j];
        }
        
        newStr.str[thisLength+otherLenght] = '\0';

        return newStr;
    }

    MyString(const MyString &other){
        if(this->str != nullptr){
            delete [] str;
        }
       int lenght = strlen(other.str);
        this->str = new char[lenght+1];
        for (int i = 0; i < lenght; i++)
        {
            this->str[i] = other.str[i];
        }
        this->str[lenght] = '\0';
        
       
    }

    void Print(){
        cout << str;
    }
};

int main(){

    MyString str("test");
    MyString str2("World");
    //str = str2;

    MyString result;

    result =  str + str2;

    result.Print();
    //str.Print();


    return 0;
}
