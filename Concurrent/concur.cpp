/*
 *Fork System call
 */

#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
using namespace std;


int a = 3;
int main (void){
  pid_t pid;
  if((pid = fork())==0){
    a =5 ;
    cout<< "chald a = " << a << endl;
    exit(0);
  }
  else{
    a = 6;
    cout<< "parent a = "<<a<<endl;
    wait(NULL);
  }
  
}
    
