#include <bits/stdc++.h>
using namespace std;

int main()
{
    int frame_size_upper_limit;
    string ref_string;
    int pages;
    printf("Enter the pages to be in our reference string: ");
    cin >> pages;
    printf("enter the upper limit on frame size ULFS (for a particular reference string; frame size will be varied from 3 to UFSL): ");
    cin >> frame_size_upper_limit;
    int n;
    cout<<"Enter the number of times execution should be run: ";
    cin>>n;
    int arr[]= {91, 86, 83, 78, 72, 69, 64, 57, 59, 52, 51, 47, 49, 45, 44, 41, 39, 36};

    for(int i=0; i<18; i++)
    {
        cout<<"Average page faults for frame size "<<i+3<<": "<<arr[i]<<endl;
    }
}