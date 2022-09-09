#include <bits/stdc++.h>
using namespace std;

int main( int argc, char *argv[])
{
	cout<<"number of arguments are :"<<argc-1<<endl;
	cout<<"name of executable is :"<<argv[0]<<endl;

	for(int i=1; i< argc; i++)
		cout<<argv[i]<<' ';
	cout<<endl;

	return 0;
}
