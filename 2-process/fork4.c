#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>

void fork4() {
    if (fork() == 0) {
        /* Child */
        printf("Terminating Child, PID = %d\n", getpid());
        exit(0);
    } else {
        printf("Running Parent, PID = %d\n", getpid());
        while (1)
            ; /* Infinite loop */
    }
}

int main()
{
    fork4();
    return 0;
}
