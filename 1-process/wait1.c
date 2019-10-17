#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>


void fork7() {
    int child_status;

    if (fork() == 0) {
        printf("HC: hello from child\n");
	exit(0);
    } else {
        printf("HP: hello from parent\n");
        wait(&child_status);
        printf("CT: child has terminated\n");
    }
    printf("Bye\n");
}


int main()
{
    fork7();
    return 0;
}
