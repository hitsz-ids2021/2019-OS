#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>

void fork5()
{
    if (fork() == 0) {
        /* Child */
        printf("Running Child, PID = %d\n",
               getpid());
        while (1)
            ; /* Infinite loop */
    } else {
        printf("Terminating Parent, PID = %d\n",
               getpid());
        exit(0);
    }
}

int main()
{
    fork5();
    return 0;
}
