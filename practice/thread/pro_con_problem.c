#include <stdio.h>
#include <pthread.h>

int buffer[100];
int count = 0;
int in = -1, out  = -1;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t buffer_has_space = PTHREAD_COND_INITIALIZER;
pthread_cond_t buffer_has_data = PTHREAD_COND_INITIALIZER;

void producer(void){
  int i;
  for(i=0 ; i<1000 ; i++){
    pthread_mutex_lock(&mutex);
    if
      (count==100)
      pthread_cond_wait(&buffer_has_space, &mutex);

    in++;
    in%100;
    buffer[in] = i;
    count++;
    pthread_cond_signal(&buffer_has_data);
    pthread_mutex_unlock(&mutex);
  }
}

int main (void)
{
  int i ;
  pthread_t threads[2];
  pthread_create(%threads[0], NULL, producer, NULL);
