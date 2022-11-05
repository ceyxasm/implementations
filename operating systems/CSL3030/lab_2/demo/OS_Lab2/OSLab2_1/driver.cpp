#include<iostream>
#include<sys/fcntl.h>
#include<sys/unistd.h>
#include<sys/types.h>
#include<bits/stdc++.h>
#include<stdlib.h>
#include<sys/wait.h>

int main(int argc, char *argv[]){

    if(argc!=3){
        fprintf(stderr,"Number of variables mismatch");
        exit(1);
    }

    int fd_in = open(argv[1], O_RDONLY);
    if(fd_in<0){
        fprintf(stderr, "Error in opening the file");
        exit(1);
    }

int fd_out = creat(argv[2],0666);
    if(fd_out<0){
        fprintf(stderr, "Error in opening the file");
        exit(1);
    }

    close(0);
     if( dup(fd_in)<0){
        fprintf(stderr, "Error in opening the file");
        exit(1);
    }
    
    close(1);
     if(dup(fd_out)<0){
        fprintf(stderr, "Error in opening the file");
        exit(1);
    }

    int pipefd[2];
    if(pipe(pipefd)<0){
        fprintf(stderr, "Error while pipe creation");
        exit(1);
    }

    pid_t p1 = fork();
    if(p1<0){
        fprintf(stderr,"Error while creating child process");
        exit(1);
    }
    else if(p1==0){
        // Child Process

        close(0);
        
        dup(pipefd[0]);
        close(pipefd[0]);
        close(pipefd[1]);

        execl("count","count",(char*) 0);


    }

    else{

        pid_t p2 = fork();
        if(p2<0){
            fprintf(stderr,"Error while creating child process");
            exit(1);
        }

        else if(p2==0){

            // Child Process
            close(1);
            dup(pipefd[1]);
            close(pipefd[1]);
            close(pipefd[0]);
            execl("convert","convert",(char*)0);
            


        }
        else{

            // Parent process

            close(pipefd[1]);
            close(pipefd[0]);
            int status1, status2;
            wait(&status1);
            wait(&status2);
        }
    }



    
    








    return 0;

}
