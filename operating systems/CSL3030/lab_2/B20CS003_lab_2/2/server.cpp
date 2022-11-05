#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <bits/stdc++.h>

using namespace std;

typedef struct message{
	long type;
	char text[512];
} message;

int main( int argc, char* argv[])
{
	int client_count=3;
	cout<<"enter number of clients :";
	cin>>client_count;
	cout<<endl;

	if( client_count <2)
	{
		fprintf( stderr, "CLIERR: Client count insuffient/invalid");
		exit(1);
	}

	system("touch log.txt"); // attempt this to do without system
	key_t key= ftok( "log.txt", 639);

	if( key < 0)
	{
		fprintf( stderr, "FTOKERR: Error in ftok()");
		exit(1);
	}

	int msg_id= msgget( key, 0644 | IPC_CREAT );
	if( msg_id < 0)
	{
		fprintf(stderr, "MSGGETERR: msgget failure");
		exit(1);
	}

	int client_score[client_count]= {0};
	int mx_score= 0;
	int c=0;
	//int c=1;
	while( mx_score< 50)
	{
		message msg;
	/*	if(c==0)
		{
			fgets(log.txt, 512, stdin);
			c++;
			continue;
		}
	*/
		int mn, mx;
		cout<<"question "<<c+1<<" from the server: enter minimum and maximum value: ";
		cin>>mn>>mx;

		if( mx< mn)
		{
			fprintf(stderr, "MXMNERR: max is less than min\n");
			exit(1);
		}

		system( "sleep 1");

		msg.type=1;
		cout<<endl; c++;

		int guess[client_count]={0};
		for( int j=0; j< client_count; j++)
		{
			string com="./client "+to_string(mn)+ ' '+to_string(mx)+' '+to_string(j);
			const char* com2= com.c_str();
			system( com2);
			message msg;
			msgrcv( msg_id, &msg, 512, 2, 0);
			char* info=  msg.text;
			stringstream convert(info);
			convert >> guess[j];
		//	printf("%d\n", guess[j]);

		}
		int winner=0;
		int server_guess=int(rand()%(mx-mn+1) +mn);

		for( int i=1; i< client_count; i++)
			if( abs(server_guess- guess[i]) <abs( server_guess- guess[winner])) winner=i;
		client_score[winner]+= 5;
		mx_score= ( client_score[winner]> mx_score)? client_score[winner]: mx_score;

		printf("____________\nROUND %d RESULTS\n\nServer Guess: %d\n", c, server_guess);
		for( int i=0; i< client_count; i++)
			printf("Client: %d, Client_guess: %d, Current_score: %d\n", i+1, guess[i], client_score[i]);
		printf("\nAnd the round winner is..... %d\n____________\n\n", winner+1);
	}

	int winner=0;
	for( int i=1; i< client_count; i++)
		winner= ( client_score[i]> client_score[winner])? i: winner;

	printf("\n~~~~~~~~~~\n AND THE WINNER IS CLIENT: %d\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n", winner+1);	
	
	return 0;
}
