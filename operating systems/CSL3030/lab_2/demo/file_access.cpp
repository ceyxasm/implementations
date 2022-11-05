#include <bits/stdc++.h>
#include <sys/wait.h>
#include <sys/fcntl.h>
#include <sys/unistd.h>
#include <sys/types.h>

using namespace std;

int main( int argc, char *argv[])
{
	FILE  *fp, *fp2; //file pointer 
	char *name= argv[1]; //name of the file to be access is assummed
			      //to be passed as first argument

	fp= fopen( name, "r" ); // "r" for read
				// "w" for write
				// "a" for append
	fp2= fopen( argv[2], "w" );
	int c;
	int counter=0;

	while(1)
	{
		c=getc(fp);
		if( feof(fp)) break;
		if( c>='A' && c<='Z')
			putw(  c-'A'+'a' , fp2);
		if( c>='a' && c<='z')
			putw( c-'a'+'A', fp2);
		else {
			putw( c, fp2);
			counter++;
		}
	}
	fclose(fp);
	printf( "%d", counter);

	///////incomplete
	return 0;
}
