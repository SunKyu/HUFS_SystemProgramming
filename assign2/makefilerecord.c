
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define NUM_RECORDS 100

struct record{
  int id;
  char name[20];
  int balance;
};


int main (int argc, char *argv[]){
  struct record current;
  int record_no;
  int fd, pos, i, n;
  int amount;
  fd = open("Account_File", O_RDWR);
  for ( i = 0; i<101; i++){
    current.id = i;
    *current.name = "a";
    current.balance = i*100;
    write(fd, &current, sizeof(struct record));
  }

}
