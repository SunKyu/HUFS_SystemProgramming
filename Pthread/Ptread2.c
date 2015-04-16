/*
 * Passing Arguments to Threads
 * page 23
 */

#include <pthread.h>
#include <stdio.h>

#define NUM_THREADS 5


struct thread_data {
  int thread_id;
  int sum;
  char * message;
};
struct thread_data thread_data_array[NUM_THREADS];
void *PrintHello(void* threadarg)
{
  struct thread_data * my_data;
  int taskid;
  int sum;
  char * hello_msg;
  my_data = (struct thread_data*) threadarg;
  taskid = my_data->thread_id;
  sum = my_data->sum;
  hello_msg = my_data->message;
  

  printf("task id : %d \n", taskid);
  printf("sum : %d \n", sum);
  printf("message : %s \n", hello_msg);

  pthread_exit(NULL);
}


int main (int argc, char**argv)
{
  pthread_t threads[NUM_THREADS];
  int sum =0;
  int  rc, t ;
  char * messages [5] ={"hello", "hi", "good", "bye", "wofwf"};
  for(t =0; t<NUM_THREADS; t++){
    sum = sum+t;
    thread_data_array[t].thread_id =t;
    thread_data_array[t].sum = sum;
    thread_data_array[t].message=messages[t];
    printf("creating thread %d \n", t);
    rc = pthread_create(&threads[t], NULL, PrintHello,(void*)&thread_data_array[t]);
  }
  pthread_exit(NULL);





}
