#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <time.h>
#include <bits/stdc++.h>

using namespace std;
typedef struct message{
	long type;
	char text[512];
} message;

int main( int argc, char* argv[])
{
	srand( time(0)*atoi(argv[3] )*atoi(argv[2] )+atoi(argv[1] ));
	int mn= atoi( argv[1]); int mx= atoi( argv[2]);
	//printf("\n %d %d \n", mn, mx);
	key_t key= ftok("log.txt", 639);

	if( key< 0)
	{
		fprintf( stderr, "error in generating key" );
		exit(1);
	}
	int msgq_id= msgget( key, 0644 |IPC_CREAT );
	if( msgq_id <0)
	{
		fprintf( stderr, "error in generating message queue/ msgget");
		exit( 1);
	}

	message msg;
	int guess= int(rand()%(mx-mn+1)+mn);
	//printf("\n%d", guess);
	char* guess2;
	asprintf( &guess2, "%d" ,guess);
	//printf("%s\n", guess2);
	strcpy( msg.text, guess2);
//	printf("%s\n", msg.text);
	msg.type=2;

	int status= msgsnd( msgq_id, &msg, 512, 0);
	if( status < 0)
	{
		fprintf( stderr, "error in sending message/ client ");
		exit(1);
	}
	

	return 0;
}
