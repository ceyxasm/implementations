#include <arpa/inet.h>
#include <bits/stdc++.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080
#define MAX_INPUT_SIZE 256
using namespace std;
  
int main(int argc, char const* argv[])
{
    int sock = 0, valread, client_fd;
    const char* cport= argv[2];
    int port;
    stringstream conv(cport);
    conv>> port;

    const char* ip= argv[1];

    char inputbuf[MAX_INPUT_SIZE];
    struct sockaddr_in serv_addr;
    char buffer[1024] = { 0 };
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    {
        printf("\n Socket creation error \n");
        return -1;
    }
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
  
    // Convert IPv4 and IPv6 addresses from text to binary
    // form
    if (inet_pton(AF_INET, ip , &serv_addr.sin_addr)  <= 0) 
    {
        printf( "\nInvalid address/ Address not supported \n");
        return -1;
    }
  
    if ((client_fd = connect(sock, (struct sockaddr*)&serv_addr,  sizeof(serv_addr)))  < 0) 
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    do{
	    printf("enter maths equation to be sent: ");
	    bzero( inputbuf, MAX_INPUT_SIZE);
	    fgets( inputbuf, MAX_INPUT_SIZE-1, stdin);

    send(sock, inputbuf, strlen(inputbuf), 0);
    printf("input message sent\n");
    valread = read(sock, buffer, 1024);
    printf("solution received: %s\n", buffer);
    }while(1);

    // closing the connected socket
    close(client_fd);
    return 0;
}
