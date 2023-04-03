#include <cstdio>
#include<iostream>
#include<algorithm>
#include<chrono>
using namespace std;
using namespace std::chrono;



int part(int* arr,int start,int endd)
{
    int pivot=endd;
    int pi=start;
    for(int i=start;i<endd;i++)
    {
        if(arr[i]<arr[pivot])
        {
            int temp=arr[pi];
            arr[pi]=arr[i];
            arr[i]=temp;
            pi++;
        }
    }
    int t=arr[pi];
    arr[pi]=arr[pivot];
    arr[pivot]=t;
    return pi;
}

void quick_sort(int* arr,int start,int endd)
{
    if(start>endd)
        return;
    int pivot=part(arr,start,endd);
    quick_sort(arr,start,pivot-1);
    quick_sort(arr,pivot+1,endd);
}




// ==============================================================================================





void merge2(int* left,int* right,int* arr,int leftLen,int rightLen)
{
    int i=0,j=0,k=0;
    while(i<leftLen && j<rightLen)
    {
        if(left[i]<=right[j])
        {
            arr[k]=left[i];
            i++;k++;
        }
        else
        {
            arr[k]=right[j];
            j++;k++;
        }
    }
    while(j<rightLen)
    {
        arr[k]=right[j];
        k++;j++;
    }
    while(i<leftLen)
    {
        arr[k]=left[i];
        i++;k++;
    }
}


void merge_sort(int* arr,int n)
{
    if(n<2)
        return;
    else
    {
        int mid=n/2;
        int left[mid];
        int right[n-mid];
        for(int i=0;i<mid;i++)
            left[i]=arr[i];
        for(int i=mid;i<n;i++)
            right[i-mid]=arr[i];
        merge_sort(left,mid);
        merge_sort(right,n-mid);
        merge2(left,right,arr,mid,n-mid);
    }
}





int main()
{
    int n=10,a;
    while(n<=100000)
    {
        cout<< "For array size "<<n<<endl<<endl;
        int* arr=new int[n];
        int* arr2=new int[n];

        double timeAv=0,timeB=0,timeW=0;
        double timeAv1=0,timeB1=0,timeW1=0;
        for(int c=0;c<5;c++)
        {
            for(int i=0;i<n;i++)
            {
                arr[i]=rand();
                arr2[i]=arr[i];
            }

            auto start1=high_resolution_clock::now();
            a=0;
            for(int i=0;i<500000;i++)
                a++;
            merge_sort(arr,n);
            auto stop1=high_resolution_clock::now();
            auto duration1=duration_cast<microseconds>(stop1-start1);
            timeAv+=duration1.count();


            auto start2=high_resolution_clock::now();
            a=0;
            for(int i=0;i<500000;i++)
                a++;
            quick_sort(arr2,0,n-1);
            auto stop2=high_resolution_clock::now();
            auto duration2=duration_cast<microseconds>(stop2-start2);
            timeAv1+=duration2.count();


            auto start3=high_resolution_clock::now();
            a=0;
            for(int i=0;i<500000;i++)
                a++;
            merge_sort(arr,n);
            auto stop3=high_resolution_clock::now();
            auto duration3=duration_cast<microseconds>(stop3-start3);
            timeB+=duration3.count();


            auto start4=high_resolution_clock::now();
            a=0;
            for(int i=0;i<500000;i++)
                a++;
            quick_sort(arr,0,n-1);
            auto stop4=high_resolution_clock::now();
            auto duration4=duration_cast<microseconds>(stop4-start4);
            timeB1+=duration4.count();



            for(int i=0;i<n;i++)
                arr[i]=arr2[n-i-1];
            for(int i=0;i<n;i++)
                arr2[i]=arr[i];



            auto start5=high_resolution_clock::now();
            a=0;
            for(int i=0;i<500000;i++)
                a++;
            merge_sort(arr,n);
            auto stop5=high_resolution_clock::now();
            auto duration5=duration_cast<microseconds>(stop5-start5);
            timeW+=duration5.count();


            auto start6=high_resolution_clock::now();
            a=0;
            for(int i=0;i<500000;i++)
                a++;
            quick_sort(arr,0,n-1);
            auto stop6=high_resolution_clock::now();
            auto duration6=duration_cast<microseconds>(stop6-start6);
            timeW1+=duration6.count();

        }
        cout<< "For Ascending:"<<endl;
        cout<< "Merge Sort: "<<timeB/5 << "  microseconds"<<endl;
        cout<< "quick Sort: "<<timeB1/5 << "  microseconds"<<endl<<endl;

        cout<< "For Descending:"<<endl;
        cout<< "Merge Sort: "<<timeW/5 << "  microseconds"<<endl;
        cout<< "quick Sort: "<<timeW1/5 << "  microseconds"<<endl<<endl;

        cout<< "For Random:"<<endl;
        cout<< "Merge Sort: "<<timeAv/5 << "  microseconds"<<endl;
        cout<< "quick Sort: "<<timeAv1/5 << "  microseconds"<<endl<<endl<<endl;


        n*=10;
    }
}







