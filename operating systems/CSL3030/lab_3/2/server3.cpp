#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/select.h>
#include <bits/stdc++.h>

using namespace std;
#define MAXLINE 1024
#define SA struct sockaddr

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

void request_handler(int conn_fd, fd_set *current_sockets, struct sockaddr_in new_addr)
{ 
    char received[MAXLINE+1];
    char send[MAXLINE+1];
    int rsig;

    if( (rsig = read(conn_fd, received, MAXLINE)) < 0)
    {
        perror("read error");
        exit(1);
    }
    if( rsig == 0)
    {
        printf("Client disconnected\n");
        close(conn_fd);
        FD_CLR(conn_fd, current_sockets);
        return;
    }
    received[rsig] = '\0';
    printf("Received: %s", received);
    int result = solver(received, rsig);
    sprintf(send, "%d", result);
    if( write(conn_fd, send, strlen(send)) < 0)
    {
        perror("write error");
        exit(1);
    }
    printf("Sent: %s", send);
    close(conn_fd);
    FD_CLR(conn_fd, current_sockets);
    return;
}

int main( int argc, char** argv)
{
    struct sockaddr_in servaddr, cliaddr;
    if(argc != 2)
    {
        printf("Usage: %s <port>\n", argv[0]);
        exit(1);
    }
    int listen_fd, conn_fd, max_fd, port;
    fd_set current_sockets, ready_sockets;
    socklen_t clilen;
    port = atoi(argv[1]);
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(listen_fd < 0)
    {
        perror("socket error");
        exit(1);
    }
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);
    if(bind(listen_fd, (SA *) &servaddr, sizeof(servaddr)) < 0)
    {
        perror("bind error");
        exit(1);
    }
    if(listen(listen_fd, 5) < 0)
    {
        perror("listen error");
        exit(1);
    }
    FD_ZERO(&current_sockets);
    FD_SET(listen_fd, &current_sockets);
    max_fd = listen_fd;
    printf("Server is running on port %d", port);
    while(1)
    {
        ready_sockets = current_sockets;
        if(select(max_fd + 1, &ready_sockets, NULL, NULL, NULL) < 0)
        {
            perror("select error");
            exit(1);
        }
        for(int i = 0; i <= max_fd; i++)
        {
            if(FD_ISSET(i, &ready_sockets))
            {
                if(i == listen_fd)
                {
                    clilen = sizeof(cliaddr);
                    conn_fd = accept(listen_fd, (SA *) &cliaddr, &clilen);
                    if(conn_fd < 0)
                    {
                        perror("accept error");
                        exit(1);
                    }
                    FD_SET(conn_fd, &current_sockets);
                    if(conn_fd > max_fd)
                    {
                        max_fd = conn_fd;
                    }
                    printf("Client connected\n");
                }
                else{
                    request_handler(i, &current_sockets, cliaddr);
                }
            }
        }

    }
}