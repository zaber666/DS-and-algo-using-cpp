#include<iostream>
#include<cstring>
#include<ctime>
#include<chrono>
using namespace std;
using namespace std::chrono;

void copy_arr(int *given,int *copied,int n)
{
    for(int i=0;i<n;i++)
        copied[i]=given[i];
}

void rev_arr(int *given,int *reversed,int n)
{
    for(int i=0;i<n;i++)
        reversed[i]=given[n-i-1];
}


void selection_sort(int* arr,int n)
{
    for(int i=0;i<n-1;i++)
    {
        int minInt=arr[i];
        int minPos=i;
        for(int j=i;j<n;j++)
        {
            if(arr[j]<minInt)
            {
                minInt=arr[j];
                minPos=j;
            }
        }
        int temp=arr[i];
        arr[i]=minInt;
        arr[minPos]=temp;
    }
}



void insertion_sort(int *arr, int n)
{

    for(int i=1;i<n;i++)
    {
        int val=arr[i];
        int valPos=i;
        for(int j=i-1;j>=0;j--)
        {
            if(arr[j]>val)
            {
                arr[j+1]=arr[j];
                valPos--;
            }
            else
                break;

        }
        arr[valPos]=val;

    }
}






int main()
{
    int n;
    cout<< "Input size: ";
    cin>>n;
    int arr1[n];
    for(int i=0;i<n;i++)
        arr1[i]=rand()%3000;
    int arr2[n];
    copy_arr(arr1,arr2,n);

    for(int i=0;i<n;i++)
        cout<<arr1[i]<< "  ";
    cout<<endl;

    auto start1=high_resolution_clock::now();
    insertion_sort(arr1,n);
    auto stop1=high_resolution_clock::now();
    auto duration1=duration_cast<nanoseconds>(stop1-start1);

    auto start2=high_resolution_clock::now();
    selection_sort(arr2,n);
    auto stop2=high_resolution_clock::now();
    auto duration2=duration_cast<nanoseconds>(stop2-start2);

    cout<< "Time for Insertion Sort in Average Case: "<<duration1.count()<< " nanoseconds"<<endl;
    cout<< "Time for Selection Sort in Average Case: "<<duration2.count()<< " nanoseconds"<<endl;

    auto start3=high_resolution_clock::now();
    insertion_sort(arr1,n);
    auto stop3=high_resolution_clock::now();
    auto duration3=duration_cast<nanoseconds>(stop3-start3);

    auto start4=high_resolution_clock::now();
    selection_sort(arr2,n);
    auto stop4=high_resolution_clock::now();
    auto duration4=duration_cast<nanoseconds>(stop4-start4);

    cout<< "Time for Insertion Sort in Best Case: "<<duration3.count()<< " nanoseconds"<<endl;
    cout<< "Time for Selection Sort in Best Case: "<<duration4.count()<< " nanoseconds"<<endl;

    int arr3[n],arr4[n];
    rev_arr(arr1,arr3,n);
    rev_arr(arr1,arr4,n);
    for(int i=0;i<n;i++)
        cout<<arr4[i]<< "  ";
    cout<<endl;

    auto start5=high_resolution_clock::now();
    insertion_sort(arr3,n);
    auto stop5=high_resolution_clock::now();
    auto duration5=duration_cast<nanoseconds>(stop5-start5);

    auto start6=high_resolution_clock::now();
    selection_sort(arr4,n);
    auto stop6=high_resolution_clock::now();
    auto duration6=duration_cast<nanoseconds>(stop6-start6);

    cout<< "Time for Insertion Sort in Worst Case: "<<duration5.count()<< " nanoseconds"<<endl;
    cout<< "Time for Selection Sort in Worst Case: "<<duration6.count()<< " nanoseconds"<<endl;



}
