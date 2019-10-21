/* $begin sigint */
//#include "csapp.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
void unix_error(char *msg) /* Unix-style error */
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
}
void sigint_handler(int sig) /* SIGINT handler */   //line:ecf:sigint:beginhandler
{
    //printf("Caught SIGINT!\n");    //line:ecf:sigint:printhandler
    //exit(0);                      //line:ecf:sigint:exithandler

    printf("So you think you can stop the bomb with ctrl-c, do you?\n");
    sleep(2);
    printf("Well...");
    fflush(stdout);
    sleep(1);
    printf("OK. :-)\n");
    exit(0);

}                                              //line:ecf:sigint:endhandler

int main() 
{
    /* Install the SIGINT handler */         
    if (signal(SIGINT, sigint_handler) == SIG_ERR)  //line:ecf:sigint:begininstall
	unix_error("signal error");                 //line:ecf:sigint:endinstall
    
    pause(); /* Wait for the receipt of a signal */  //line:ecf:sigint:pause
    
    return 0;
}
/* $end sigint */
