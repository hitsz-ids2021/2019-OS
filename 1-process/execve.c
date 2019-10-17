#include<stdio.h>
#include<unistd.h>

void fork1()
{
    printf("H0\n");
    if (fork() == 0) {
        printf("H1\n");
        if (fork() != 0) {
            printf("H2\n");
	}
    }
    printf("Bye\n");
}


int main()
{
    fork1();

}
