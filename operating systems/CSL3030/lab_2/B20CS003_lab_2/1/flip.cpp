#include <bits/stdc++.h>
using namespace std;

int main()
{
	while(1)
	{
		int c= getchar( );
		if( c==EOF) 
			exit( 0);
		else if ( (c-'A' >=0) && ( c-'A'<=25))
			putchar( c-'A'+'a');
		else if ( (c-'a' >=0) && (c-'a'<=25))
			putchar( c-'a' +'A');
		else putchar( c);

	}
	return 0;
}
