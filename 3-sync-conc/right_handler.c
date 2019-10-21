//#include "csapp.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>    
#define N 3
typedef void handler_t(int);

int ccount = 0;

void unix_error(char *msg) /* Unix-style error */
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
}
/* $end unixerror */

 /* Private sio functions */

/* $begin sioprivate */
/* sio_reverse - Reverse a string (from K&R) */
static void sio_reverse(char s[])//逆序
{
    int c, i, j;

    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

/* sio_ltoa - Convert long to base b string (from K&R) */
static void sio_ltoa(long v, char s[], int b) //长整型转b进制字符型
{
    int c, i = 0;
    
    do {  
        s[i++] = ((c = (v % b)) < 10)  ?  c + '0' : c - 10 + 'a';
    } while ((v /= b) > 0);
    s[i] = '\0';
    sio_reverse(s);
}

/* sio_strlen - Return length of string (from K&R) */
static size_t sio_strlen(char s[])//求字符串长度
{
    int i = 0;

    while (s[i] != '\0')
        ++i;
    return i;
}
/* $end sioprivate */

/* Public Sio functions */
/* $begin siopublic */

ssize_t sio_puts(char s[]) //命令行输出字符串
{
    return write(STDOUT_FILENO, s, sio_strlen(s)); //line:csapp:siostrlen
}

ssize_t sio_putl(long v) //输出长整型
{
    char s[128];
    
    sio_ltoa(v, s, 10); /* Based on K&R itoa() */  //line:csapp:sioltoa
    return sio_puts(s);
}

void sio_error(char s[]) //输出错误
{
    sio_puts(s);
    _exit(1);                                      //line:csapp:sioexit
}
/* $end siopublic */

/*******************************
 * Wrappers for the SIO routines
 ******************************/
ssize_t Sio_putl(long v)
{
    ssize_t n;
  
    if ((n = sio_putl(v)) < 0)
    sio_error("Sio_putl error");
    return n;
}

ssize_t Sio_puts(char s[])
{
    ssize_t n;
  
    if ((n = sio_puts(s)) < 0)
    sio_error("Sio_puts error");
    return n;
}

void Sio_error(char s[])
{
    sio_error(s);
}

unsigned int Sleep(unsigned int secs) 
{
    unsigned int rc;

    if ((rc = sleep(secs)) < 0)
    unix_error("Sleep error");
    return rc;
}

void child_handler2(int sig) { //收割子进程
    int olderrno = errno;
    pid_t pid;
    while((pid = wait(NULL)) > 0){//简化的waitpid,waitpid挂起调用进程的执行，知道它的等待集合中的一个子进程终止
            ccount--;
            Sio_puts("Handler reaped child ");
            Sio_putl((long)pid);
            Sio_puts(" \n");
        }
    if (errno != ECHILD)
        Sio_error("waitpid error");

    //sleep(1);
    errno = olderrno;
}

/* $begin forkwrapper */
pid_t Fork(void) //用一次，返回两次，子进程返回0，父进程返回子进程的PID，如果出错，返回-1；
{
    pid_t pid;

    if ((pid = fork()) < 0)
    unix_error("Fork error");
    return pid;
}
/* $end forkwrapper */

/* $begin sigaction */
handler_t *Signal(int signum, handler_t *handler) 
{
    struct sigaction action, old_action;

    action.sa_handler = handler;  
    sigemptyset(&action.sa_mask); /* Block sigs of type being handled */
    action.sa_flags = SA_RESTART; /* Restart syscalls if possible */

    if (sigaction(signum, &action, &old_action) < 0) //
    unix_error("Signal error");
    return (old_action.sa_handler);
}
/* $end sigaction */



void fork12() {
    pid_t pid[N];
    int i;
    ccount = N;
    Signal(SIGCHLD, child_handler2);

    for (i = 0; i < N; i++) {
        if ((pid[i] = Fork()) == 0) {
            printf("Hello from child %d\n",(int)getpid());
            Sleep(1); //挂起一段时间
            exit(0);  /* Child exits */
        }
    }
    while (ccount > 0) /* Parent spins */
        ;
}

int main()
{
    fork12();
}
