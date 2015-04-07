#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

#define bool int
#define true 1
#define false 0
#define BUF_SIZE 100
int main (int argc, char * argv[]){
  bool logout = false;
  char stdinput[BUF_SIZE];
  bool foreground = false;
  char argv2 [BUF_SIZE];
  while(!logout){
    printf("$> ");
    getline(stdinput, BUF_SIZE, stdin);
    pid_t pid;
  //need to pasing the line

    if (strlen(stdinput-1) == '&')
      foreground = false;
    else
      foreground = true;

    if((pid =fork()) ==0) {//child
      //IO redirection if desingnated
      printf("execev\n ");
      execv("a.out", NULL);
    }
    if (foreground){
      while(wait(&pid) !=pid); //wait for the death of the foreground process
      //if a bacground did exit() , it is removed here as a side effect.
      //
    }//if background, does not wait()
  }

}
