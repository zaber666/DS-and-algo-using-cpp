#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<ctime>
#include<fstream>
#include<chrono>
#include<algorithm>
using namespace std;
using namespace std::chrono;

int linear_search(int *arr,int len,int key)
{
    for(int a=0;a<len;a++)
    {
        if(arr[a]==key)
            return a;
    }
    return -1;
}


int binary_search2(int *arr,int start,int stop,int key)
{
    int mid=((start-stop)/2)+stop;
    if(start>stop)
        return -1;
    if(arr[mid]==key)
        return mid;

    else if(arr[mid]<key)
        binary_search2(arr,mid+1,stop,key);

    else if(arr[mid]>key)
        binary_search2(arr,start,mid-1,key);


}


int main()
{

    int n,a;
    cout<< "Input Size: ";
    cin>>n;

    //Populating Array
    int arr[n];
    for(a=0;a<n;a++)
    {
        arr[a]=rand()%1000;

    }
    sort(arr,arr+n);

    int key= rand()%(1000);

    auto start=high_resolution_clock::now();
    int b=linear_search(arr,n,key);
    auto stop= high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(stop - start);
    cout<<"Duration for Linear Search: "<<duration.count()<<"nanoseconds."<<endl<< "Key Found at position: "<<b<<endl;

    auto start2=high_resolution_clock::now();
    int c=binary_search2(arr,0,n-1,key);
    auto stop2=high_resolution_clock::now();
    auto duration2 = duration_cast<nanoseconds>(stop2 - start2);
    cout<<"Duration for Binary Search: "<<duration2.count()<<"nanoseconds."<<endl<< "Key Found at position: "<<c<<endl;




}





