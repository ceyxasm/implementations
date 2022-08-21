#include<iostream>
#include<bits/stdc++.h>
#include<unistd.h>
#include<string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include<cstring>

using namespace std;


int main(int argc, char *argv[], char *envp[])
{
    char c='\0';
    char *buf=(char *)malloc(sizeof(char) * 100);
    string input="";
    size_t size= 200;
    system("echo welcome to ceyshell");
    system("sleep 1");

    system("clear");
    printf("$ ");
    while( c!=EOF)
    {

        /// ref for takun: https://www.javatpoint.com/how-to-split-strings-in-cpp
        //parsing input
        c=getchar();
        int token_count= 0;
        input= input+c;

        if( c== '\n') 
        {
            string tokens[25];
            int i=0;
            tokens[i]=strtok(&input[0], " ");
            //cout<<tokens[i]<<'_'<<endl;

            while(1)
            {
                char* es=strtok(NULL, " ");
                if(es==NULL) break;
                tokens[++i]= es;
            }
            token_count= i;


//            for(int j=0; j<=i; j++) cout<<tokens[j]<<' ';
            //input parse complete


            //IMPLEMENTING COMMANDS
            if( tokens[0].compare("cd") == 0 )
            {
                char path[100];
                int sot1= tokens[1].size();
                int t=0;
                for(t=0; t< sot1; t++)
                {
                    (path[t])= (char)tokens[1][t];
                    //cout<<path[t];
                }
                cout<<tokens[1];
                
                //chdir(path);
                
            }
            else if(tokens[0].compare("pwd\n") == 0)
            {
				getcwd(buf, size);
				cout<<buf<<endl;			
			}

        }
    }


    return 0;
}
