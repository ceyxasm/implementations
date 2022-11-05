#include <bits/stdc++.h>
using namespace std;

int main()
{
	int counter=0;
	while( 1)
	{
		int c= getchar();
		if( c== EOF ) 
		{
			fprintf( stderr, "count of special char is %d\n", counter);
			exit(0);
		}
		if( isalpha(c) || isdigit(c) )
			putchar( c);
		else
		{
			putchar( c);
			counter++;
		}
	}	
	return 0;
}

