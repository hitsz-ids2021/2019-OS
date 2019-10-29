/* 
 * goodcnt.c - A correctly synchronized counter program 
 */
/* $begin goodcnt */
//#include "csapp.h"
#include <semaphore.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
volatile long cnt = 0; /* Counter */
sem_t mutex;           /* Semaphore that protects counter */

void *thread(void *vargp) ;
void unix_error(char *msg); /* Unix-style error */
void posix_error(int code, char *msg); /* Posix-style error */
void Pthread_create(pthread_t *tidp, pthread_attr_t *attrp, 
            void * (*routine)(void *), void *argp);
void Pthread_join(pthread_t tid, void **thread_return);
void P(sem_t *sem);
void V(sem_t *sem); 
void Sem_init(sem_t *sem, int pshared, unsigned int value);

int main(int argc, char **argv) 
{
    int niters;
    pthread_t tid1, tid2;

    /* Check input argument */
    if (argc != 2) {
	printf("usage: %s <niters>\n", argv[0]);
	exit(0);
    }
    niters = atoi(argv[1]);

    /* Create threads and wait for them to finish */
/* $begin goodcntseminit */
    Sem_init(&mutex, 0, 1);  /* mutex = 1 */
/* $end goodcntseminit */
    Pthread_create(&tid1, NULL, thread, &niters);
    Pthread_create(&tid2, NULL, thread, &niters);
    Pthread_join(tid1, NULL);
    Pthread_join(tid2, NULL);

    /* Check result */
    if (cnt != (2 * niters))
	printf("BOOM! cnt=%ld\n", cnt);
    else
	printf("OK cnt=%ld\n", cnt);
    exit(0);
}


/* Thread routine */
void *thread(void *vargp) 
{
    int i, niters = *((int *)vargp);

/* $begin goodcntthread */
    for (i = 0; i < niters; i++) {
    P(&mutex);
    cnt++;
    V(&mutex);
    }
/* $end goodcntthread */
    return NULL;
}

void unix_error(char *msg) /* Unix-style error */
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
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
void P(sem_t *sem) 
{
    if (sem_wait(sem) < 0)
    unix_error("P error");
}

void V(sem_t *sem) 
{
    if (sem_post(sem) < 0)
    unix_error("V error");
}

void Sem_init(sem_t *sem, int pshared, unsigned int value) 
{
    if (sem_init(sem, pshared, value) < 0)
    unix_error("Sem_init error");
}

/* $end goodcnt */


