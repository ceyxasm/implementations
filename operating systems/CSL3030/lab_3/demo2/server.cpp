#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <bits/stdc++.h>

using namespace std;
#define PORT 8080

int solver(char* equ, int n)
{
	int op=0;
	char opr; 
	string opr1="", opr2="";

	for(int i=0; i<n; i++)
	{
		char c= equ[i];
		if( c=='+' || c=='-' ||c=='/' || c=='*')
		{
			op=1;
			opr=c;
			continue;
		}
		else if(op==0) opr1+=c;
		else opr2+=c;
	}

	int oprnd1= stoi(opr1);
	int oprnd2= stoi(opr2);
	switch( opr)
	{
		case '+':
			return oprnd1+ oprnd2;
		case '-': return oprnd1-oprnd2;
		case '*': return oprnd1*oprnd2;
		case '/': return oprnd1/oprnd2;
		default:
			  {fprintf(stderr, "operation not supported\n");
				  exit(1);
			  }
	}
}

int main(int argc, char const* argv[])
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = { 0 };
    const char* hello = "Hello from server";
  
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0))
        == 0) 
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
  
    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
  
    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr*)&address,
             sizeof(address))
        < 0) 
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket
         = accept(server_fd, (struct sockaddr*)&address,
                  (socklen_t*)&addrlen))
        < 0) 
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    do{
    valread = read(new_socket, buffer, 1024);
    printf("evaluating: %s\n", buffer);
    int sol= solver( buffer, sizeof(valread)/sizeof(char) );
    printf("sending solution: %d\n", sol);
    string tmp= to_string(sol);
    const char* char_sol= tmp.c_str();

    send(new_socket, char_sol, strlen(char_sol), 0);
    }while(1);
    
  // closing the connected socket
    close(new_socket);
  // closing the listening socket
    shutdown(server_fd, SHUT_RDWR);
    return 0;
}
