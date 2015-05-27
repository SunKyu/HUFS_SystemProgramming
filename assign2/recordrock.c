#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define NUM_RECORDS 100

struct record{
  int id;
  int balance;
};

int reclock (int fd, int recno, int len, short type){
  struct flock fl;
  switch(type){
    case F_RDLCK:
    case F_WRLCK:
    case F_UNLCK:
      fl.l_type = type;
      fl.l_whence = SEEK_SET;
      fl.l_start = recno*len;
      fcntl(fd, F_SETLKW, &fl);
      return 1;
    default:
      return -1;
  };
}
void display(struct record * current){
  printf("id : %d\n", current->id);
  printf("balance : %d \n", current->balance);
}

int main (int argc, char * argv[]){
  struct record current;
  int record_no;
  int fd, pos, i,n;
  char yes;
  char operation;
  int amount;
  fd = open("Account_File", O_RDWR);
  while(1){
    printf("enter account number \n");
    scanf("%d%*c", &record_no);
    if(!(record_no>= 0 && record_no<NUM_RECORDS))
      break;
    printf("enter operation name \n");
    scanf("%c%*c", &operation);
    
    switch(operation){
      case 'r':
        reclock(fd, record_no, sizeof(struct record), F_RDLCK);
        pos = record_no* sizeof(struct record);
        lseek(fd, pos, SEEK_SET);
        n = read(fd, &current, sizeof(struct record));
        display(&current);
        reclock(fd, record_no, sizeof(struct record), F_UNLCK);
        break;
      case 'd':
        reclock(fd, record_no, sizeof(struct record), F_WRLCK);
        pos = record_no*sizeof (struct record);
        lseek(fd, pos, SEEK_SET);
        n = read(fd, &current, sizeof(struct record));
        display(&current);
        printf("enter amount \n");
        scanf("%d%*c", &amount);
        current.balance += amount;
        lseek(fd,pos,SEEK_SET);
        write(fd, &current, sizeof(struct record));
        reclock(fd, record_no, sizeof(struct record), F_UNLCK);
        break;
      case 'w':
        reclock(fd, record_no, sizeof(struct record), F_WRLCK);
        pos = record_no*sizeof(struct record);
        lseek(fd, pos, SEEK_SET);
        n = read(fd, &current, sizeof(struct record));
        display(&current);
        printf("enter amount to withdraw\n");
        scanf ("%d%*c", &amount);
        current.balance -=amount;
        lseek(fd, pos, SEEK_SET);
        write(fd, &current, sizeof(struct record));
        reclock(fd, record_no, sizeof(struct record), F_UNLCK);
        break;
      case 't':
        reclock(fd, record_no, sizeof(struct record), F_WRLCK);
        pos = record_no* sizeof(struct record);
        lseek(fd, pos, SEEK_SET);
        n = read(fd, &current, sizeof(struct record));
        display(&current);
        printf("enter the target record_no \n");
        scanf("%d%*c", &record_no);
        printf("enter the amount for transfer\n");
        scanf("%d%*c", &amount);
        current.balance -=amount;
        lseek(fd, pos, SEEK_SET);
        write(fd, &current, sizeof(struct record));
        reclock(fd, record_no, sizeof(struct record), F_UNLCK);

        reclock(fd, record_no, sizeof(struct record), F_WRLCK);
        pos = record_no* sizeof(struct record);
        lseek(fd, pos, SEEK_SET);
        n = read(fd, &current, sizeof(struct record));
        current.balance += amount;
        lseek(fd, pos, SEEK_SET);
        write(fd, &current, sizeof(struct record));
        reclock(fd, record_no, sizeof(struct record), F_UNLCK);
        break;
      default:
        printf("ilegal input \n");
        continue;
    };
  }
  close(fd);
}

