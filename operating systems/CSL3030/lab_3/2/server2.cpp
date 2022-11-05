#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <netdb.h>
#include <signal.h>
#include<bits/stdc++.h>
using namespace std;

#define MAX_INPUT_SIZE 256

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

int main(int argc, char *argv[])
{
    int fd, sockfd, newsockfd, clilen, portno, n, flag;
    struct sockaddr_in serv_addr, newaddr;
    pid_t childpd;
    char buffer[MAX_INPUT_SIZE];
    if (argc < 2)
    {
        fprintf(stderr, " no port \n");
        exit(1);
    }

    portno = atoi(argv[1]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("error opening socket");
        exit(1);
    }


    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("error binding");
        exit(0);
    }

    if (listen(sockfd, 4) < 0)
    {
        perror("error in listening");
        exit(1);
    }
    else
    {
        printf("waiting connection\n");
    }
    while (1)
    {
        clilen = sizeof(serv_addr);
        newsockfd = accept(sockfd, (struct sockaddr *)&newaddr, (socklen_t *)&clilen);
        if (newsockfd < 0)
        {
            perror("error on accept");
            exit(1);
        }

        else
        {
            printf("connected to %s: %d\n", inet_ntoa(newaddr.sin_addr), ntohs(newaddr.sin_port));
        }
        if ((childpd = fork()) == 0)
        {

            close(sockfd);
            while (1)
            {
                recv(newsockfd, buffer, sizeof(buffer), 0);

                if (buffer[0] == '\0')
                {

                    printf("client disconnected...\n");
                    exit(0);
                }
                else
                {
                    printf("evaluating: %s\n", buffer);
                    int result = solver(buffer, sizeof(buffer)/sizeof(char));
                    printf("Client %d message received\n", ntohs(newaddr.sin_port));
                    printf("Sending reply to client %d:%i\n", ntohs(newaddr.sin_port), result);
                    bzero(buffer, MAX_INPUT_SIZE);
                    sprintf(buffer, "%d", result);
                    send(newsockfd, buffer, strlen(buffer), 0);
                    bzero(buffer, sizeof(buffer));
                }
            }
        }
    }
    if (read(newsockfd, buffer, sizeof(buffer)) <= 0)
        printf("closing server..\n");

    close(newsockfd);
    return 0;
}