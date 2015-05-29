#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>

struct TCB{
  int period;
  int thread_id;
  int time_left_to_invoke;
};
/*
 *for passing arguments, make struct
 */
struct arg{
  int period;
  int thread_id;
};


pthread_t thread[10];
pthread_cond_t cond_array[10] = {PTHREAD_COND_INITIALIZER, PTHREAD_COND_INITIALIZER, PTHREAD_COND_INITIALIZER, PTHREAD_COND_INITIALIZER, PTHREAD_COND_INITIALIZER, PTHREAD_COND_INITIALIZER, PTHREAD_COND_INITIALIZER, PTHREAD_COND_INITIALIZER, PTHREAD_COND_INITIALIZER, PTHREAD_COND_INITIALIZER};


pthread_mutex_t API_mutex = PTHREAD_MUTEX_INITIALIZER;
struct TCB TCB_array[10];
int num_threads =5 ;
struct arg parameter[10];


void tt_thread_register(int period, int thread_id){
  pthread_mutex_lock(&API_mutex);
  TCB_array[thread_id].period = period;
  TCB_array[thread_id].thread_id= thread_id;
  TCB_array[thread_id].time_left_to_invoke = period;
  pthread_mutex_unlock(&API_mutex);
}

void tt_thread_wait_invocation(int thread_id){
  pthread_mutex_lock(&API_mutex);
  pthread_cond_wait(&cond_array[thread_id], &API_mutex);
  pthread_mutex_unlock(&API_mutex);
}

void * Time_triggered_thread(void * parameter){
  struct arg * targv = (struct arg *) parameter;
  int myperiod, thread_id;
  myperiod = targv->period;
  thread_id = targv->thread_id;
  tt_thread_register(myperiod, thread_id);
  char buff[100];
  time_t now = time (0);
  while(1){
    tt_thread_wait_invocation(thread_id);
    now = time(0);
    strftime (buff, 100, "%Y-%m-%d %H:%M:%S", localtime (&now));
    printf ("%s , thread id %d, period %d\n", buff, thread_id, myperiod);
  }
}

void SIGALRM_handler(int signo){
  int i = 0;
  pthread_mutex_lock(&API_mutex);
  for (i= 0 ; i<num_threads ; i++){
    if((TCB_array[i].time_left_to_invoke -= 10)<=0){
      TCB_array[i].time_left_to_invoke = TCB_array[i].period;
      pthread_cond_signal(&cond_array[i]);
    }
  }
  pthread_mutex_unlock(&API_mutex);
  signal(SIGALRM, SIGALRM_handler);
}



int main (int argc, char **argv){
  num_threads = atoi(argv[1]);
  int rc[10], ret, i;
  struct itimerval delay;
  signal(SIGALRM, SIGALRM_handler);
  delay.it_value.tv_sec = 0;
  delay.it_value.tv_usec = 10000;
  delay.it_interval.tv_sec = 0;
  delay.it_interval.tv_usec= 10000;
  for (i = 0 ; i<num_threads; i++){
    parameter[i].thread_id = i;
    parameter[i].period = (i+1) * 1000;
    rc[i] = pthread_create(&(thread[i]), NULL, Time_triggered_thread, (void*) &parameter[i]);
  }
  ret = setitimer(ITIMER_REAL, &delay, NULL);
  while(1){
    pause();
  }
}
