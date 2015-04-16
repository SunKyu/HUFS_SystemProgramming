/*
 * Pthread Joinig
 * page 30
 *
 */

#include <pthread.h>
#include <stdio.h>
#define NUM_THREADS 3
void *BusyWork(void *null){
  int i;
  double result= 0.0;
  for(i=0; i< 1000000; i++)
    result = result + (double)random();
  printf("result = %e\n", result);
  pthread_exit((void*) 0);
}

int main(int argc, char* argv[])
{
  pthread_t thread[NUM_THREADS];
  pthread_attr_t attr;
  int rc, t, status;

  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
  for(t =0; t<NUM_THREADS; t++){
    printf("Creating thread %d\n", t);
    rc = pthread_create(&thread[t], &attr, BusyWork, NULL);
    if(rc){
      printf("ERROR;, %d\n", rc);
      exit(-1);
    }
  }
  pthread_attr_destroy(&attr);
  for(t=0; t<NUM_THREADS ;t++){
    rc = pthread_join(thread[t], (void**)status);
    if(rc){
      printf("ERROR; return code form pthread_join() is %d\n", rc);
      exit(-1);
    }
    printf("completed join whith thread %d status = %d\n", t, status);
  }
  pthread_exit(NULL);

}

