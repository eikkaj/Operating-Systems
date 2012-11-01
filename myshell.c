/*
 CS575 Operating Systems
 Implement my own shell
 author name
 date
 */

//Header files needed 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>


//Define constants
#define MAXLINE 1024
#define MAXARGS 20
#define PROMPT "myshell> "
#define HISTSIZE 10 //history size
#define QUIT 0 //loop
#define DELIMITERS " \t\r\n"
#define queue_elem 10
#define queue_size (queue_elem + 1)

//the following two functions are meant to implement a history function for the user,
//unfortunately, due to my inexperience with c, the history function is only printing 
//the first letter of the command a user inputs. This is a FIFO model with 10 max array
//I think the structure is solid but I am having issues with variable types here
//overall it works successfully, but needs tweaking, thank you for your understanding
char queue[queue_size];
int queueIn,queueOut;

void queueInit(void){
	queueIn = queueOut = 0;
}
		
int queuePut(char new) {
	if (queueIn == ((queueOut -1 + queue_size) % queue_size)) {
		queue[0] == NULL;
		queue[queueIn] = new;
		queueIn = (queueIn + 1) % queue_size;
	}
	queue[queueIn] = new;
	queueIn = (queueIn + 1) % queue_size;
	return 0;
}


int main(int argc, char *argv[])
{
	char *command;
	char line[MAXLINE];
	char *arg = NULL;
	char *my_argv[MAXARGS]; 

	while(1) {
		printf(PROMPT);
		if (fgets(line,MAXLINE,stdin) != NULL) {
			//take out \n
			line[strlen(line)-1] = '\0';
		}
		//looks for first delimiter, saves as the command
		command = strtok(line, DELIMITERS);
		//add line to history queue
		char queuearg = *command;

		queuePut(*command);
		
		if (strcmp(command,"cd")==0){
			arg = strtok(0,DELIMITERS);
			my_argv[0] = command;
			my_argv[1] = arg;
			my_argv[2] = NULL;
			if (!arg) {
				//printf("no arg\n");
				//printf("%s",command);
				chdir("/");
			} else { 
				//printf("with args\n");
				//printf("%s",my_argv[1]);
				chdir(my_argv[1]);
			}
		} else if (strcmp(command,"exit")==0) {
			break;
		} else if (strcmp(command,"help")==0) {
			printf("***************************\n");
			printf("myShell 2012 jaldama\n");
			printf("Usage: Type in common shell cmd to execute something\n");
			printf("***************************\n");
		} else if(strcmp(command,"history")==0) {
			printf("%s\n",queue);
		} else {//function allows for multiple parameters
			arg = strtok(0,DELIMITERS);
			my_argv[0] = command;
			my_argv[1] = arg;
			my_argv[2] = NULL;
			char cmd[64] =""; strcat(cmd,"/bin/");strcat(cmd,command);
			
				//fork exec
				int pid = fork();
				if (pid == 0) {
					execve(cmd,my_argv,0);
				} else wait(NULL);
			
		} 
	}
	return 0;
}



