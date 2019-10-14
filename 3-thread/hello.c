#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<errno.h>
#include<stdlib.h>
#include<pthread.h>


void *thread(void *vargp);                    

int main()
{
    pthread_t tid;
    int rc_c,rc_j;

    if ((rc_c = pthread_create(&tid, NULL, thread, NULL)) != 0)
	 fprintf(stderr, "pthread_creat error: %s\n",  strerror(errno));



    if ((rc_j = pthread_join(tid, NULL)) != 0)
	 fprintf(stderr, "pthread_join error: %s\n", strerror(errno));

	    
    exit(0);                                  
}

void *thread(void *vargp) /* thread routine */
{
    printf("Hello, world!\n");
    return NULL;
}

