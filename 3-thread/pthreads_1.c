//usage: gcc -o pthreads_test pthreads_1.c -lpthread -lm

#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


/* A task that takes some time to complete. The ID identifies distinct
   tasks for printed messages. */
void *task(void *ID) {
  long id = (long)ID;
  printf("Task %ld started\n",id);
  int i;
  double result = 0.0;
  for (i = 0; i < 10000000; i++) {
    result = result + sin(i) * tan(i);
  }
  printf("Task %ld completed with result %e\n",id, result);
}

/* Run 'task' num_tasks times serially. */
void *serial(int num_tasks) {
  long i;
  for (i = 0; i < num_tasks; i++) {
    task((void *)i);
  }
}

/* Run 'task' num_tasks times, creating a separate thread for each
   call to 'task'. */
void *parallel(int num_tasks)
{
  int num_threads = num_tasks;
  pthread_t thread[num_threads];
  int rc;
  long t;
  for (t = 0; t < num_threads; t++) {
    printf("Creating thread %ld\n", t);
    rc = pthread_create(&thread[t], NULL, task, (void *)t);
    if (rc) {
      printf("ERROR: return code from pthread_create() is %d\n", rc);
      exit(-1);
    }
  }
}

void *print_usage(int argc, char *argv[]) {
  printf("Usage: %s serial|parallel num_tasks\n", argv[0]);
  exit(1);
}

int main(int argc, char *argv[]) {

  
  if (argc != 3) {print_usage(argc, argv);}

  int num_tasks = atoi(argv[2]);


  if (!strcmp(argv[1], "serial")) {
    serial(num_tasks);
  } else if (!strcmp(argv[1], "parallel")) {
    parallel(num_tasks);
  }
  else {
    print_usage(argc, argv);
  }

  printf("Main completed\n");
  pthread_exit(NULL);
}
