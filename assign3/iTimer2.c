#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>

pthread_cond_t cond_array[10]= {PTHREAD_COND_INITIALIZER, };
pthread_mutex_t API_mutex;
struct TCB{
  int period;
  int thread_id;
  int time_left_to_invoke;
};


int main (int argc, char **argv){


}
