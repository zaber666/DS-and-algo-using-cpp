#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
using namespace std;


struct Node
{
    int rank,parent;
    Node()
    {
        rank=-1;
        parent=-1;
    }
};



class disjoint_set
{
    Node* arr;
    int len;
public:
    disjoint_set(int n)
    {
        arr=new Node[n];
        len=n;
    }
    void make_set(int x)
    {
        if(arr[x].rank!=-1)
        {
            cout<< "The element already exists."<<endl;
            return;
        }
        arr[x].parent=x;
        arr[x].rank=0;
        cout<< "Insertion Successful"<<endl;
    }
    int find_set(int x)
    {
        if(arr[x].parent == -1)
        {
            return -1;
        }
        if(arr[x].parent!=x)
            arr[x].parent=find_set(arr[x].parent);
        return arr[x].parent;
    }
    void union_set(int x,int y)
    {
        int parent1=find_set(x);
        int parent2=find_set(y);

        if(parent1==-1 || parent2 ==-1)
        {
            cout<< "Error!!"<<endl;
            return;
        }

        if(parent1==parent2)
            return;

        if(arr[parent1].rank > arr[parent2].rank)
            arr[parent2].parent = parent1;
        else
        {
            arr[parent1].parent = parent2;
            if(arr[parent1].rank == arr[parent2].rank)
                arr[parent2].rank++;
        }
        cout<< "Union Completed"<<endl;
    }
    void print_set(int x)
    {
        int u=find_set(x);

        if(u==-1)
        {
            cout<< "No set"<<endl;
            return;
        }

        cout<< "The elements in set "<<x<< " is :"<<endl;

        for(int i=0;i<len;i++)
        {
            if(find_set(i) == u)
                cout<< i<< "  ";
        }
        cout<<endl;
    }



};


int main()
{
    int n;
    cout<< "Enter Maximum Size: ";
    cin>>n;
    disjoint_set djs(n);

    int choice;
    while(1)
    {
        cout<< "1.Make Set\n2.Find Set\n3.Union\n4.Print Set\n5.Quit\n";
        cout<< "Choose your action: ";
        cin>>choice;
        if(choice==1)
        {
            cout<< "Enter an element: ";
            int x;
            cin>>x;
            djs.make_set(x);
            cout<< endl;
        }
        if(choice==2)
        {
            cout<< "Enter an element: ";
            int x;
            cin>>x;
            int ans=djs.find_set(x);
            if(ans==-1)
                cout<< "Element doesn't exist"<<endl;
            else
                cout<< "The Parent is: " <<ans<<endl;
            cout<<endl;
        }
        if(choice==3)
        {
            cout<< "Enter Two Elements: ";
            int x,y;
            cin>>x>>y;
            djs.union_set(x,y);
            cout<<endl;
        }
        if(choice==4)
        {
            cout<< "Enter an Element: ";
            int x;
            cin>>x;
            djs.print_set(x);
            cout<<endl;
        }
        if(choice==5)
        {
            break;
        }
    }
}





