#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <bits/stdc++.h>

using namespace std;

/*function to evaluate arithmetic expression*/
int solver(char *buffer, int x)
{
    int num1 = 0, num2 = 0;
    int j = 0;
    char op;
    char *operators = "+-/*";
    for (int i = 0; i < strlen(buffer) - 1; i++)
    {
        if(buffer[i] == '+' || buffer[i] == '-' || buffer[i] == '*' || buffer[i] == '/')
        {
            op = buffer[i];
            j = i;
            break;
        }
        else
        {
            ;
        }
    }

    char *ptr = strtok(buffer, operators);
    num1 = atoi(ptr);
    ptr = strtok(NULL, operators);
    num2 = atoi(ptr);
    int result;
    switch (op)
    {
    case '+':
        result = num1 + num2;
        break;
    case '-':
        result = num1 - num2;
        break;
    case '*':
        result = num1 * num2;
        break;

    case '/':
        result = num1 / num2;
        break;
    default:
        break;
    }
    return result;
}


int main(int argc, char const* argv[])
{
    int server_fd, new_socket, valread;
    const char* port= argv[1];
    int int_port;
    stringstream conv(port);
    conv>>int_port;

    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = { 0 };

    if(argc<2)
    {
        cout<<"Please enter port number"<<endl;
        exit(0);
    }
  
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    {
        perror("error opening socket");
        exit(1);
    }
  
    // Forcefully attaching socket to the port 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
    {
        perror("setsockopt");
        exit(1);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(int_port);
  
    // Forcefully attaching socket to the port
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address))   < 0) 
    {
        perror("bind failed");
        exit(1);
    }
    if (listen(server_fd, 3) < 0) {
        perror("listening error");
        exit(EXIT_FAILURE);
    }
    if ((new_socket   = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen))   < 0) 
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    else{
        cout<<"Connection waiting"<<endl;
    }

    do
    {
    	valread = read(new_socket, buffer, 1024);
    	printf("evaluating: %s", buffer);
    	int sol= solver( buffer, sizeof(buffer)/sizeof(char) );
    	printf("sending solution: %d\n", sol);
    	string tmp= to_string(sol);
    	const char* char_sol= tmp.c_str();

    	send(new_socket, char_sol, strlen(char_sol), 0);
    }while(1);
    
  // closing the connected socket
    close(new_socket);
    printf("terminating server\n");
  // closing the listening socket
    shutdown(server_fd, SHUT_RDWR);
    return 0;
}
