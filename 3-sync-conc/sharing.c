/* $begin sharing */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define N 2
void *thread(void *vargp);

char **ptr;  /* Global variable */ //line:conc:sharing:ptrdec

int main() 
{
    long i;  
    pthread_t tid;
    char *msgs[N] = {
	"Hello from foo",  
	"Hello from bar"   
    };

    ptr = msgs; 
    for (i = 0; i < N; i++)  
        pthread_create(&tid, NULL, thread, (void *)i); 
    pthread_exit(NULL); 
}

void *thread(void *vargp) 
{
    long myid = (long)vargp;
    static int cnt = 0; //line:conc:sharing:cntdec
    printf("[%ld]: %s (cnt=%d)\n", myid, ptr[myid], ++cnt); //line:conc:sharing:stack
    return NULL;
}
/* $end sharing */
