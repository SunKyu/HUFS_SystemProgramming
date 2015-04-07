#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define PROMPT "$> "
#define LINE_LENGTH 80
#define bool int
#define true 1
#define false 0

int main (int argc, char *argv[]){
  char linebuffer[LINE_LENGTH];
  bool logout = true;
  bool forground = true;
  int count = 0;
  int c;
  pid_t pid;
  while(logout){
    printf(PROMPT);
    count =0;
    while(1){
      /*
      if((c = getchar())==EOF)
        exit(0);
        */
      if(count <LINE_LENGTH)
        buffer[count++] = c;
      if(c == '\n' && count <LINE_LENGTH)
      {
        buffer[count -1] = '\0';

      }
  }

}
