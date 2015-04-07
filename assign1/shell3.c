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
  bool foreground = true;
  char **p_argv = NULL;

  int count = 0;
  int c;
  pid_t pid;
  while(logout){
    printf(PROMPT);
    count =0;
    while(1){
      
         if((c = getchar())==EOF)
         exit(0);
        
      if(count <LINE_LENGTH)
        linebuffer[count++] = c;
      if(c == '\n' && count <LINE_LENGTH)
      {
        linebuffer[count -1] = '\0';
        break;
      }
      if(count >= LINE_LENGTH){
        printf("input too long \n");
        count = 0;
        printf(PROMPT);
        continue;
      }
    }
    if(strlen(linebuffer) == 0 || (strlen(linebuffer) == 1&& linebuffer[strlen(linebuffer)-1] == '&'))
    {
      continue;
    }

    if(linebuffer[strlen(linebuffer)-1] =='&'){
      foreground = false;
      linebuffer[strlen(linebuffer) -1 ] = '\0';
    }

    if((pid= fork()) ==0){
      execv(linebuffer, p_argv);

    }
    if(foreground){
      while(pid!=wait(0));

    }
  }

}
