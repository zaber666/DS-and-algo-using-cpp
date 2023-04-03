#include<iostream>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<chrono>
using namespace std;
using namespace std::chrono;


void print_set(vector<char>&sub)
{

    int len=sub.size();
    for(int i=0;i<len;i++)
    {
        //cout<< sub.at(i) << "  ";
    }
    /*if(len==0)
        cout<< "Null Set";
    cout<<endl;*/
}

void find_all_subset(char *arr,vector<char>&sub,int i)
{
    if(i<0)
    {
        print_set(sub);
        return;
    }
    sub.push_back(arr[i]);
    find_all_subset(arr,sub,i-1);
    sub.pop_back();
    while(arr[i]==arr[i-1])
        i-=1;
    find_all_subset(arr,sub,i-1);
}

int main()
{
    int n,a=0,b,i,j,k,l;
    char str;


    cout<< "Enter size of your parent set: ";
    cin>>n;




    char container_arr[62];
    char arr[n];



    for(i=0;i<62;i++)
    {
        if(i<10)
            container_arr[i]='0'+i;
        else if(i<36)
            container_arr[i]='a'+i-10;
        else
            container_arr[i]='A'+i-36;
    }

    //for(k=5;k<31;k++){
        //n=k;
    for(i=0;i<n;i++)
    {
        int temp=rand()%62;
        arr[i]=container_arr[temp];
    }


    sort(arr,arr+n);


    cout<< "Parent set :   {  ";
    for(i=0;i<n-1;i++)
        cout<< arr[i]<< " , ";
    cout<<arr[n-1]<< " }"<<endl;



    vector<char>sub;

    auto start=high_resolution_clock::now();

    find_all_subset(arr,sub,n-1);
    for(j=0;j<100000;j++)
        a++;

    auto stop=high_resolution_clock::now();
    auto duration=duration_cast<nanoseconds>(stop-start);


    cout<< "Time passed for generating subsets for  : "<<duration.count()<< " nanoseconds"<<endl;
    //}
}
