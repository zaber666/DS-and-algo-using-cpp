#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;

struct interval
{
    int start,finish,id;
};

bool compare(interval i1, interval i2)
{

    if(i1.finish>i2.finish)
        return false;
    return true;

}

void print(interval iv)
{
    cout<< "Event Number: "<< iv.id<< "    Starting Time: "<<iv.start<< "   Ending Time: "<<iv.finish<<endl;
}


void maximum_activities(interval* arr, int n)
{
    print(arr[0]);
    int done=0;
    for(int i=1;i<n;i++)
    {
        if(arr[i].start >=arr[done].finish)
        {
            print(arr[i]);
            done=i;
        }
    }
}



int main()
{
    cout<< "Enter Number of intervals: ";
    int n;
    cin>>n;
    interval arr[n];
    for(int i=0;i<n;i++)
    {
        interval temp;
        temp.start=rand();
        temp.finish=rand();
        while(temp.finish<temp.start)
            temp.finish=rand();
        temp.id=i+1;
        arr[i]=temp;
    }


    sort(arr,arr+n,compare);


    cout<<endl<< "Intervals After sorting on earliest finish time: "<<endl;

    for(int i=0;i<n;i++)
        cout<< arr[i].start<< " "<<arr[i].finish<<endl;

    cout<<endl<<endl<< "Solution:"<<endl;
    maximum_activities(arr,n);
}
