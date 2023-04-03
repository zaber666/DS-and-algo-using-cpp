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




//==========================================================================================




int main()
{
    int choice, n;
    int *arr;
    while(1)
    {
        printf("1. Generate average case\n");
        printf("2. Generate best case\n");
        printf("3. Generate worst case\n");
        printf("4. Apply Merge sort\n");
        printf("5. Apply Quicksort\n");
        printf("6. Print array\n");
        printf("> ");
        scanf("%d", &choice);

        switch(choice)
        {
        case 1:
            {printf("Number of elements: ");
            scanf("%d", &n);
            // do yourself
            arr=new int[n];
            for(int i=0;i<n;i++)
                arr[i]=rand();}
            break;

        case 2:
            {printf("Number of elements: ");
            scanf("%d", &n);
            // do yourself
            arr=new int[n];
            for(int i=0;i<n;i++)
                arr[i]=rand();
            sort(arr,arr+n);}
            break;

        case 3:
            {printf("Number of elements: ");
            scanf("%d", &n);
            // do yourself
            arr=new int[n];
            for(int i=0;i<n;i++)
                arr[i]=rand();
            sort(arr,arr+n,greater<int>());
            }
            break;

        case 4:
            {printf("Applying merge sort\n");
            // do yourself
            // this should transform the given array into a sorted array
            auto start=high_resolution_clock::now();
            int a=0;
            for(int i=0;i<500000;i++)
                a++;
            merge_sort(arr,n);
            auto stop=high_resolution_clock::now();
            auto duration=duration_cast<microseconds>(stop-start);
            printf("Time taken to finish: %d\n",duration.count());}
            break;

        case 5:
            {printf("Applying quicksort\n");
            // do yourself
            // this should transform the given array into a sorted array
            auto start=high_resolution_clock::now();
            int a=0;
            for(int i=0;i<500000;i++)
                a++;
            quick_sort(arr,0,n-1);
            auto stop=high_resolution_clock::now();
            auto duration=duration_cast<microseconds>(stop-start);
            printf("Time taken to finish: %d\n",duration.count());}
            break;

        case 6:
            {printf("Array\n");
            // do yourself
            for(int i=0;i<n;i++)
                cout<<arr[i]<< "   ";}
            break;
        }
    }
}

