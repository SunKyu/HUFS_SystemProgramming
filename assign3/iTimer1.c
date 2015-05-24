#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>

int ticks = 0;
pthread_t thread[1];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t wakeupsig = PTHREAD_COND_INITIALIZER;


void* time_triggered_thread(){
 // time_t mytime;
  char buff[100];
  time_t now = time (0);
 // mytime = time(NULL);
  pthread_mutex_lock(&mutex);
  while(1){
    pthread_cond_wait(&wakeupsig, &mutex);
    now = time(0);
    strftime (buff, 100, "%Y-%m-%d %H:%M:%S.000", localtime (&now));
    printf ("%s\n", buff);
    
    //printf(ctime(&mytime));
  }
  pthread_mutex_unlock(&mutex);
  pthread_exit(NULL);
}


void alarm_handler(int sino)
{
  pthread_mutex_lock(&mutex);
  ticks ++;
  if(ticks%100 == 0){
    ticks = 0;
    pthread_cond_signal(&wakeupsig);
  }
  pthread_mutex_unlock(&mutex);
  signal(SIGALRM, alarm_handler);
}

int main (int argc, char * argv[]){
  printf("%d\n", __LINE__);
  signal(SIGALRM, alarm_handler);
  printf("%d\n", __LINE__);
  struct itimerval delay;
  int rc;
  int ret;
  delay.it_value.tv_sec = 0;
  delay.it_value.tv_usec = 10000;
  delay.it_interval.tv_sec= 0;
  delay.it_interval.tv_usec = 10000;
  rc = pthread_create(&thread[0], NULL, time_triggered_thread, NULL);
  ret = setitimer(ITIMER_REAL, &delay, NULL);
  while(1)
  {
    pause();
  }
}


