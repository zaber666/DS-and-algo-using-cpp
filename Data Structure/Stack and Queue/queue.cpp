#include<iostream>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;


class myQueue
{
    int *arr;
    int mySize;
    int numElm;
    int start;

public:

    myQueue()
    {
        arr=new int[10];
        mySize=10;
        numElm=0;
        start=0;
    }
    int Empty()
    {
        if(numElm==0)
            return 1;
        else
            return 0;
    }
    int Size()
    {
        return mySize;
    }
    int Front()
    {
        if(numElm==0)
        {
            cout<< "No elements found"<<endl;
            return -INT_MAX;
        }
        else
            return arr[start];
    }
    int rear()
    {
        if(numElm==0)
        {
            cout<< "No elements found"<<endl;
            return -INT_MAX;
        }
        else
            return arr[numElm-1];
    }
    void push(int x)
    {
        if(numElm==mySize)
        {
            int *newArr=new int[mySize+10];
            for(int i=0;i<numElm;i++)
                newArr[i]=arr[i];
            newArr[numElm]=x;
            numElm++;
            mySize+=10;
            delete[] arr;
            arr=newArr;
        }
        else
        {
            arr[numElm]=x;
            numElm++;
        }
    }

};


int main()
{

}
