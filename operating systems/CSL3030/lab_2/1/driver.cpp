#include <bits/stdc++.h>
#include <sys/wait.h>
#include <sys/fcntl.h>
#include <sys/unistd.h>
#include <sys/types.h>
using namespace std;

int main(int argc, char* argv[])
{
	if( argc!=3 )
	{
		fprintf( stderr, "ARGMIS: argument count mismatch; expected 2, found %d ", argc-1);
		exit(1);
	}

	int fd_in= open(argv[1], O_RDONLY );
	if( fd_in < 0)
	{
		fprintf( stderr, "FDOPERR: error in opening file" );
		exit(1);
	}

	int fd_out= creat( argv[2], 0664 );
	if( fd_out < 0)
	{
		fprintf( stderr, "FDCRERR: error creating file" );
		exit(1);
	}

	close(0);
	if( dup(fd_in) < 0)
        {
                fprintf( stderr, "FDOPERR: error in opening file" );
                exit(1);
        }

	close(1);
	if( dup(fd_out) < 0)
        {
                fprintf( stderr, "FDOPERR: error in opening file" );
                exit(1);
        }

	int pipefd[2];
	if( pipe(pipefd) < 0)
        {
                fprintf( stderr, "PIPECRERR: error in creating pipe" );
                exit(1);
        }

	pid_t p1= fork();
	if( p1< 0) 
	{
		fprintf( stderr, "FORKERR: error forking child");
		exit(1);
	}
	else if( p1== 0)
	{
		close(0);
		dup( pipefd[0] );
		close( pipefd[0]);
		close( pipefd[1]);
		execl( "counter", "counter", (char *) 0);

	}
	else 
	{
		pid_t p2= fork();

		if(p2< 0)
		{
			fprintf(stderr, "FORKERR: error while creating child");
			exit(0);
		}
		else if(p2==0)
		{
			close(1);
			dup( pipefd[1]);
			close( pipefd[0]);
			close( pipefd[1]);
			execl("flip", "flip", (char *) 0);
		}
		else
		{
			close( pipefd[0]);
			close( pipefd[1]);
			int process1;
			int process2;
			wait(&process1);
			wait(&process2);
		}
	}
	return 0;
}
