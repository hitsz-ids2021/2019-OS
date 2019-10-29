#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

volatile long cnt = 0; /* Counter */

void *thread(void* vargp);
void posix_error(int code, char *msg); /* Posix-style error */
void Pthread_create(pthread_t *tidp, pthread_attr_t *attrp, 
            void * (*routine)(void *), void *argp); 
void Pthread_join(pthread_t tid, void **thread_return);


int main(int argc, char **argv)
{
    long niters;
    pthread_t tid1, tid2;

    niters = atoi(argv[1]);
    Pthread_create(&tid1, NULL,
        thread, &niters);
    Pthread_create(&tid2, NULL,
        thread, &niters);
    Pthread_join(tid1, NULL);
    Pthread_join(tid2, NULL);

    /* Check result */
    if (cnt != (2 * niters))
        printf("BOOM! cnt=%ld\n", cnt);
    else
        printf("OK cnt=%ld\n", cnt);
    exit(0);
}

void * thread(void* vargp)                                                                                                                                                                         
{                                                                                                                
    long i, niters = *((long*)vargp);                                                                       
                                                                                                                 
    for (i = 0; i < niters; i++)
        cnt++;                   
                                                                                                                 
    return NULL;                                                                                                 
} 

void posix_error(int code, char *msg) /* Posix-style error */
{
    fprintf(stderr, "%s: %s\n", msg, strerror(code));
    exit(0);
}

void Pthread_create(pthread_t *tidp, pthread_attr_t *attrp, 
            void * (*routine)(void *), void *argp) 
{
    int rc;

    if ((rc = pthread_create(tidp, attrp, routine, argp)) != 0)
    posix_error(rc, "Pthread_create error");
}
void Pthread_join(pthread_t tid, void **thread_return) {
    int rc;

    if ((rc = pthread_join(tid, thread_return)) != 0)
    posix_error(rc, "Pthread_join error");
}

