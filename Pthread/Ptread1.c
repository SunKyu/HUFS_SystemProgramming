/* ppt 20 page
 * Pthread Creation and Termination
 *
 */

#include <pthread.h>
#include <stdio.h>

#define NUM_THREADS 5
void *PrintHello(void* threadid)
{
  printf("\n%d : Hello world!\n", threadid);
  pthread_exit(NULL);
}


int main (int argc, char**argv)
{
  pthread_t threads[NUM_THREADS];
  int rc, t;
  for(t=0; t<NUM_THREADS; t++){
    printf("Creating thread %d\n", t);
    rc = pthread_create(&threads[t], NULL, PrintHello, (void*)t);
    if(rc){
      printf("ERROR; .... %d\n ", rc);
      exit(-1);
    }
  }
  pthread_exit(NULL);
}
