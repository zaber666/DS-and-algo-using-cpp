#include<iostream>
#include<cstdlib>
#include<algorithm>
using namespace std;

class priority_Queue
{
    int *arr;
    int size;
    //int tail;
public:
    priority_Queue()
    {
        arr=new int[10];
        size=10;
        arr[0]=0;
    }
    void up_heapify(int pos)
    {
        if(pos==1)
            return;
        int parent=pos/2;
        if(arr[parent]>=arr[pos])
            return;
        int temp=arr[parent];
        arr[parent]=arr[pos];
        arr[pos]=temp;
        up_heapify(parent);
    }
    void down_heapify(int pos)
    {
        int left=2*pos;
        int right=left+1;
        int largest=pos;
        if(left<=arr[0]  &&  arr[pos]<arr[left])
            largest=left;
        else if(right<=arr[0]  &&  arr[pos]<arr[right])
            largest=right;
        if(largest==pos)
            return;
        else
        {
            int temp=arr[pos];
            arr[pos]=arr[largest];
            arr[largest]=temp;
            down_heapify(largest);
        }
    }
    void insert(int n)
    {
        arr[0]++;
        if(arr[0]==size)
        {
            int* newarr=new int[size+10];
            for(int i=1;i<size;i++)
                newarr[i]=arr[i];
            newarr[arr[0]]=n;
            newarr[0]=arr[0];
            delete[] arr;
            arr=newarr;
        }
        else
        {
            arr[arr[0]]=n;
        }
        up_heapify(arr[0]);
    }
    int findMax()
    {
        return arr[1];
    }
    int extraxt_max()
    {
        int ret=arr[1];
        arr[1]=arr[arr[0]];
        arr[0]--;
        down_heapify(1);
        return ret;
    }
    void increaseKey(int i, int newVal)
    {
        arr[i]=newVal;
        up_heapify(i);
    }
    void decreaseKey(int i, int newVal)
    {
        arr[i]=newVal;
        down_heapify(i);
    }
    void print()
    {
        for(int i=1;i<=arr[0];i++)
        {
            cout<< arr[i]<< "   ";
        }
        cout<<endl;
    }
};





int main()
{
    priority_Queue q;
    int choice=100;
    while(choice!=7)
    {
        cout<< "Choose An Action\n1. Insert\n2. Find Max\n3. Extract Max\n4. Increase Key\n5. Decrease Key\n6. Print\n7.Quit\n";
        cin>>choice;
        if(choice==1)
        {
            cout<< "Insert Number :  ";
            int n;
            cin>>n;
            q.insert(n);
        }
        else if(choice==2)
        {
            cout<<q.findMax()<<endl;
        }
        else if(choice==3)
        {
            cout<<q.extraxt_max()<<endl;
        }
        else if(choice==4)
        {
            cout<< "Enter Position:  ";
            int pos,val;
            cin>>pos;
            cout<< "Enter New Value:  ";
            cin>>val;
            q.increaseKey(pos,val);
        }
        else if(choice==5)
        {
            cout<< "Enter Position:  ";
            int pos,val;
            cin>>pos;
            cout<< "Enter New Value:  ";
            cin>>val;
            q.decreaseKey(pos,val);
        }
        else if(choice==6)
            q.print();
        cout<<endl<<endl;
    }
}
