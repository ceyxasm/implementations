#include <bits/stdc++.h>
using namespace std;

int main( int argc, char *argv[])
{
	FILE  *fp, *fp2; //file pointer 
	char *name= argv[1]; //name of the file to be access is assummed
			      //to be passed as first argument

	fp= open( name, "r" ); // "r" for read
				// "w" for write
				// "a" for append
	fp2= creat( argv[2], 0644 );
	int c;
	int counter=0;

	while(1)
	{
		c=fgetc(fp);
		if( feof(fp)) break;
		if( c>='A' && c<='Z')
			printf( "%c", c-'A'+'a' );
		if( c>='a' && c<='z')
			printf( "%c", c-'a'+'A');
		else {
			printf("%c", c);
			counter++;
		}
	}
	fclose(fp);
	printf( "%d", counter);

	///////incomplete
	return 0;
}
