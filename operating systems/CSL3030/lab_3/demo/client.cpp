#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#define MAX_INPUT_SIZE 256

using namespace std;

int main(int argc, char *argv[])
{
	int sockfd, portnum, n;
	int clientfd;
	struct sockaddr_in server_addr;
	char inputbuf[MAX_INPUT_SIZE];

	if (argc < 3) //./client IP port
	{
		fprintf(stderr,"usage %s <server-ip-addr> <server-port>\n", argv[0]);
		exit(1);
	}
	portnum = atoi(argv[2]);

	/* Create client socket */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
		fprintf(stderr, "ERROR opening socket\n");
		exit(1);
	}

	/* Fill in server address */
	bzero((char *) &server_addr, sizeof(server_addr));// init server_addr to 0000000//
	server_addr.sin_family = AF_INET;
	if(!inet_aton(argv[1], &server_addr.sin_addr)) //converts argv[1] num_dot address to binary data in netbyte order
						       //non zero if address invalid
						       //else 0
	{
		fprintf(stderr, "ERROR invalid server IP address\n");
		exit(1);
	}

	
	server_addr.sin_port = htons(portnum);
	
	/* Connect to server */
	if ( (clientfd= connect(sockfd,(struct sockaddr *)&server_addr,sizeof(server_addr))) <0)
	{
		fprintf(stderr, "ERROR connecting\n");
		exit(1);
	}

	printf("Connected to server\n");
	do
	{
	/* Ask user for message to send to server */
		printf("Please enter the message to the server: ");
		bzero(inputbuf,MAX_INPUT_SIZE);
		fgets(inputbuf,MAX_INPUT_SIZE-1,stdin);
		/* Write to server */
		n = write(sockfd,inputbuf,strlen(inputbuf));
		if (n < 0)
		{
			fprintf(stderr, "ERROR writing to socket\n");
			exit(1);
		}
		/* Read reply */
		bzero(inputbuf,MAX_INPUT_SIZE);
		n = read(sockfd,inputbuf,(MAX_INPUT_SIZE-1));
		if (n < 0)
		{
			fprintf(stderr, "ERROR reading from socket\n");
			exit(1);
		}

		printf("Server replied: %s\n",inputbuf);
	} 
	while(1);

	return 0;
}
