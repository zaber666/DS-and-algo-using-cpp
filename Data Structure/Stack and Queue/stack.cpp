#include<iostream>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;


class myStack
{
    int *arr;
    int mySize;
    int numElm;
public:
    myStack()
    {
        arr=new int[10];
        mySize=10;
        numElm=0;
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
    int top()
    {
        if(numElm==0)
        {
            cout<< "The Stack is empty" <<endl;
            return -INT_MAX;
        }
        else
        {
            return arr[numElm-1];
        }
    }
    void push(int x)
    {
        if(numElm<mySize)
        {
            arr[numElm]=x;
            numElm++;
        }
        else
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
    }
    int pop()
    {
        if (numElm==0)
        {
            cout<< "Stack is Empty. Pop Can not Take Place"<<endl;
            return -INT_MAX;
        }
        else
        {
            numElm--;
            return arr[numElm];
        }
    }

    ~myStack()
    {
        delete[] arr;
    }
};



int main()
{
    myStack s1;
    s1.push(1);
    s1.push(2);
    s1.push(3);
    s1.push(4);
    s1.push(1);
    s1.push(2);
    s1.push(3);
    s1.push(4);
    s1.push(1);
    s1.push(2);
    s1.push(3);
    s1.push(4);

    cout<<s1.Size()<<endl;
    cout<<s1.Empty()<<endl;
    cout<<s1.top()<<endl;
    cout<<s1.pop();

}
