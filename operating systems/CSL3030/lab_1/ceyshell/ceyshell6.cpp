/*
AUTHOR: CEYXASM
*/
#include <bits/stdc++.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
using namespace std;


/*
Built-in functions
Can be further expanded
*/
//Function Declarations:
int csh_cd(char **args);
int csh_help(char **args);
int csh_exit(char **args);
int csh_history(char **args);
int pipeCommand(char** cmd1, char** cmd2, char** inp);
string get_working_path();



//List of builtin commands, followed by their corresponding functions.
const char *builtin_str[] = { //const to convert string to char* >>const
  "cd",
  "help",
  "exit",
  "history"
};

int (*builtin_func[]) (char **) = {
  &csh_cd,
  &csh_help,
  &csh_exit,
  &csh_history
};

int csh_num_builtins() {
  return sizeof(builtin_str) / sizeof(char *);
}

//Builtin function implementations.

int csh_cd(char **args) //to change directory
{
  if (args[1] == NULL) {
    fprintf(stderr, "csh: expected argument to \"cd\"\n");
  } else {
    if (chdir(args[1]) != 0) {
      perror("csh");
    }
  }
  return 1;
}



static void appendLineToFile(string filepath, string line) //to implement history functionality
{
    std::ofstream file;
    //can't enable exception now because of gcc bug that raises ios_base::failure with useless message
    //file.exceptions(file.exceptions() | std::ios::failbit);
    file.open(filepath, std::ios::out | std::ios::app);
    if (file.fail())
        throw std::ios_base::failure(std::strerror(errno));

    //make sure write fails with exception if something is wrong
    file.exceptions(file.exceptions() | std::ios::failbit | std::ifstream::badbit);

    file << line << std::endl;
}

int csh_history( char **args)
{
	const char* fileName= "history.txt";
	int n=100;
	if( args[1]!=NULL) n=atoi(args[1]);
	n++;
    const int k = n;
    ifstream file(fileName);
    string l[k];
    int size = 0 ;

    while(file.good()){
        getline(file, l[size%k]); //this is just circular array
     //   cout << l[size%k] << '\n';
        size++;
    }

    //start of circular array & size of it 
    int start = size > k ? (size%k) : 0 ; //this get the start of last k lines 
    int count = min(k, size); // no of lines to print
	cout<<'\n';
    for(int i = 0; i< count ; i++){
        cout << l[(start+i)%k] << '\n' ; // start from in between and print from start due to remainder till all counts are covered
    }
    return 1;
}

int csh_help(char **args)
{
  int i;
  printf("Ceyxasm's ceyshell\n");
  //printf("<More instructions to be added here>\n"); //--->>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>additions here;
  printf("Type program names and arguments, and hit enter.\n");
  printf("Originally built on Ubuntu 20.04\nFor more details, please refer to the Readme file\n");
  printf("https://github.com/ceyxasm/ceyxasm/blob/main/blogs_temp/ceyshell_files/README.md");
  printf("\nThe following are built in:\n");

  for (i = 0; i < csh_num_builtins(); i++) {
    printf("  %s\n", builtin_str[i]);
  }

  printf("Use the man command for information on other programs.\n");
  return 1;
}
int csh_exit(char **args)
{
  return 0;
}


int csh_launch(char **args)
{
  pid_t pid;
  int status;

  int no_tokens= 0;
  while(args[no_tokens++]!=NULL);
  no_tokens--;
    if(strcmp(args[no_tokens-1],"&")==0)
    {
	    args[no_tokens-1]=NULL;
    }
  pid = fork();
  if (pid == 0) {
    // Child process
    if (execvp(args[0], args) == -1) {
      perror("csh");
    }
    exit(EXIT_FAILURE);
  } else if (pid < 0) {
    // Error forking
    perror("csh");
  } else {
    // Parent process
    if( args[no_tokens-1]!=NULL)
    {
	  do {
      waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
  }

  return 1;
}


int csh_execute(char **args)
{
  int i;

  if (args[0] == NULL) {
    // An empty command was entered.
    return 1;
  }

  for (i = 0; i < csh_num_builtins(); i++) {
    if (strcmp(args[0], builtin_str[i]) == 0) {
      return (*builtin_func[i])(args);
    }
  }

  return csh_launch(args);
}


char *csh_read_line(void)
{
#ifdef CSH_USE_STD_GETLINE

  char *line = NULL;
  ssize_t bufsize = 0; // have getline allocate a buffer for us
  if (getline(&line, &bufsize, stdin) == -1) {
    if (feof(stdin)) {
      exit(EXIT_SUCCESS);  // We received an EOF
    } else  {
      perror("csh: getline\n");
      exit(EXIT_FAILURE);
    }
  }
  return line;
#else
#define CSH_RL_BUFSIZE 1024
  int bufsize = CSH_RL_BUFSIZE;
  int position = 0;
  char *buffer = (char*)malloc(sizeof(char) * bufsize);
  int c;

  if (!buffer) {
    fprintf(stderr, "csh: allocation error\n");
    exit(EXIT_FAILURE);
  }

  while (1) {
    // Read a character
    c = getchar();

    if (c == EOF) {
      exit(EXIT_SUCCESS);
    } else if (c == '\n') {
      buffer[position] = '\0';
      return buffer;
    } else {
      buffer[position] = c;
    }
    position++;

    // If we have exceeded the buffer, reallocate.
    if (position >= bufsize) {
      bufsize += CSH_RL_BUFSIZE;
      buffer = (char*)realloc(buffer, bufsize);
      if (!buffer) {
        fprintf(stderr, "csh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }
  }
#endif
}

#define CSH_TOK_BUF 64
#define CSH_TOK_DELIM " \t\r\n\a"

char **csh_split_line(char *line)
{
  int bufsize = CSH_TOK_BUF, position = 0;
  char **tokens = (char**)malloc(bufsize * sizeof(char*));
  char *token, **tokens_backup;

  if (!tokens) {
    fprintf(stderr, "csh: allocation error\n");
    exit(EXIT_FAILURE);
  }

  token = strtok(line, CSH_TOK_DELIM);
  while (token != NULL) {
    tokens[position] = token;
    position++;

    if (position >= bufsize) {
      bufsize += CSH_TOK_BUF;
      tokens_backup = tokens;
      tokens = (char**)realloc(tokens, bufsize * sizeof(char*));
      if (!tokens) {
		free(tokens_backup);
        fprintf(stderr, "csh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }

    token = strtok(NULL, CSH_TOK_DELIM);
  
  }
  tokens[position] = NULL;

  return tokens;
}


void csh_loop(void)
{
  char *line;
  char **args;
  int status;

  do {
    cout << "\033[1;36m";
    cout<<get_working_path();
    printf("$ ");
    cout << "\033[0m";

    line = csh_read_line();
    appendLineToFile("history.txt", line);
    args = csh_split_line(line);
    //splitting for pipe and foreground/background
    int no_tokens= 0;
    bool flag_and=false; bool flag_pipe=false;
    while(args[no_tokens]!= NULL)
    {
	    if( strcmp( args[no_tokens], "&&" )==0) flag_and=true;
	    if( strcmp( args[no_tokens], "|"  )==0) flag_pipe=true;
	    no_tokens++;
    }

    char **args1= (char**)malloc( sizeof(char*)* 1024); args1[0]=NULL;
    char **args2= (char**)malloc( sizeof(char*)* 1024); args2[0]=NULL;


    if( flag_pipe || flag_and)
    {

	    bool cmd1_end= false;
	    int pos=0;
	    int pos1=0;
	    int pos2=0;

	    while( args[pos]!= NULL)
	    {
		    if( strcmp(args[pos],"&&")==0 || strcmp( args[pos], "|")==0 )
		    {
			    cmd1_end= true;
			    args1[pos1]= NULL;
			    pos++;
			    continue;
		    }
		    if(!cmd1_end)
		    {
			    args1[pos1++]=args[pos++];
		    }
		    if( cmd1_end)
		    {
			    args2[pos2++]=args[pos++];
		    }
	    }
    }

    if( !flag_pipe && !flag_and)
    status = csh_execute(args);
    if( flag_and) 
    {
	    status= csh_execute( args1);
      if( status==1)
	    status= csh_execute( args2);
    }
    if( flag_pipe)
    {
	status= pipeCommand( args1, args2,args);
    }

    free(line);
    free(args);
    free(args1);
    free(args2);
  } while (status);
}


int main(int argc, char **argv)
{
  // Load config files, if any.
  system("echo Welcome to ceyshell...");
  system("echo Initializing......");
  system("sleep 2");
  system("clear");

  // Run command loop.
  csh_loop();

  // Perform any shutdown/cleanup.

  return EXIT_SUCCESS;
}


//PWD
string get_working_path()
{
    char temp [ PATH_MAX ];

    if ( getcwd(temp, PATH_MAX) != 0)
            return std::string ( temp);

    int error = errno;
//
    switch ( error ) {
        // EINVAL can't happen - size argument > 0

        // PATH_MAX includes the terminating nul, 
        // so ERANGE should not be returned

        case EACCES:
            throw std::runtime_error("Access denied");

        case ENOMEM:
            throw std::runtime_error("Insufficient storage");

        default: {
            std::ostringstream str;
            str << "Unrecognised error" << error;
            throw std::runtime_error(str.str());
        }
    }
}

//PWD
//
//
//PIPES
/*
int pipeCommand(char** cmd1, char** cmd2) {
  int fds[2]; // file descriptors
  pipe(fds);
  // child process #1
  if (fork() == 0) {
    // Reassign stdin to fds[0] end of pipe.
    dup2(fds[0], STDIN_FILENO);
    close(fds[1]);
    close(fds[0]);
    // Execute the second command.
    // child process #2
    if (fork() == 0) {
        // Reassign stdout to fds[1] end of pipe.
        dup2(fds[1], STDOUT_FILENO);
        close(fds[0]);
        close(fds[1]);
        // Execute the first command.
        execvp(cmd1[0], cmd1);
	cout<<"ran first\n";
    }
    wait(NULL);
    execvp(cmd2[0], cmd2);
    cout<<"ran second\n";
    }
    close(fds[1]);
    close(fds[0]);
    wait(NULL);
    return 1;
}*/

#define INPUT_END 1
#define WRITE_END 1
#define READ_END 0
#define OUTPUT_END 0
int pipeCommand(char** cmd1, char** cmd2, char **inp)
{
/*	pid_t pid;
int fd[2];

pipe(fd);
pid = fork();

if(pid==0)
{
    dup2(fd[WRITE_END], 1);
    close(fd[READ_END]);
    close(fd[WRITE_END]);
    execvp( cmd1[0], cmd1);
    fprintf(stderr, "Failed to execute '%s'\n", cmd1);
    exit(1);
}
else
{
    pid=fork();

    if(pid==0)
    {
        dup2(fd[READ_END], 0);
        //close(fd[WRITE_END]);
        //close(fd[READ_END]);
        execvp( cmd2[0], cmd2);
        fprintf(stderr, "Failed to execute '%s'\n", cmd2);
        //exit(1);
    }
    else
    {
        int status;
        close(fd[READ_END]);
        close(fd[WRITE_END]);
    //    waitpid(pid, &status, 0);
    wait(0);
    }
} return 1;*/
	/*
    pid_t pid1;                                  // [STDIN -> terminal_input, STDOUT -> terminal_output]                       (of the parent process)
    pid_t pid2;                                  //
    int fd[2];                                   //
                                                 //
    pipe(fd);                                    // [STDIN -> terminal_input, STDOUT -> terminal_output, fd[0] -> pipe_input, fd[1] -> pipe_output]
    pid1 = fork();                               //
                                                 //
    if(pid1==0)                                  //
    {                                            // I am going to be the wc process (i.e. taking input from the pipe)
        close(fd[INPUT_END]);                    // [STDIN -> terminal_input, STDOUT -> terminal_output, fd[1] -> pipe_output] (of the WC process)
        dup2(fd[OUTPUT_END], STDIN_FILENO);      // [STDIN -> pipe_output, STDOUT -> terminal_output, fd[1] -> pipe_output]    (of the WC process)
        close(fd[OUTPUT_END]);                   // [STDIN -> pipe_output, STDOUT -> terminal_output]                          (of the WC process)
        execlp(cmd2[0], cmd2);   //
    }                                            //
    else                                         //
    {                                            //
        pid2=fork();                             //
                                                 //
        if(pid2==0)                              //
        {                                        // I am going to be the ls process (i.e. producing output to the pipe)
            close(fd[OUTPUT_END]);               // [STDIN -> terminal_input, STDOUT -> terminal_output, fd[0] -> pipe_input] (of the ls process)
            dup2(fd[INPUT_END], STDOUT_FILENO);  // [STDIN -> terminal_input, STDOUT -> pipe_input, fd[0] -> pipe_input]      (of the ls process)
            close(fd[INPUT_END]);                // [STDIN -> terminal_input, STDOUT -> pipe_input]                           (of the ls process)
            execlp(cmd1[0], cmd1); //
        }                                        //
                                                 //
        close(fd[OUTPUT_END]);                   // [STDIN -> terminal_input, STDOUT -> terminal_output, fd[0] -> pipe_input] (of the parent process)
        close(fd[INPUT_END]);                    // [STDIN -> terminal_input, STDOUT -> terminal_output]                      (of the parent process)
        waitpid(-1, NULL, 0);                    // As the parent process - we wait for a process to die (-1) means I don't care which one - it could be either ls or wc
        waitpid(-1, NULL, 0);                    // As the parent process - we wait for the another process to die.
                                                 // At this point we can safely assume both process are completed
    }
    return 1;*/
	/*
	int pos1=0; int pos2=0;
	while( cmd2[pos1++]) cout<<cmd2[pos1-1]<<' ';
	cout<<'\n';*/
	/*
           int fds[2];
           pipe(fds);
	   pid_t pid1, pid2;

           // child process #1
           if ((pid1 = fork()) == 0) 
	   {// inside child
                dup2(fds[1], 1); //write has been assigned fd 1
		close(fds[0]);
		close(fds[1]);
                execvp(cmd1[0], cmd1);
                perror("execvp failed");

                // child process #2
           } 
	   else if ((pid2 = fork()) == 0) 
	   {
                  dup2(fds[0], 0);

                  close(fds[1]);
                  execvp(cmd2[0], cmd2);
                  perror("execvp failed");


           }
	   else
	   {
    		close(fds[1]);
    		waitpid(pid1, NULL, 0);
		waitpid(pid2, NULL, 0);
	  }*/
	//return 1;
char cmd[256]= "";
int pos=0;
while( inp[pos]) 
{
	strcat( cmd, inp[pos]);
	strcat( cmd, " ");
	pos++;
}
system(cmd);
return 1;
}

//PIPES
