#include <stdio.h>
#include <unistd.h>
#include <syscall.h>       /* for SYS_write etc. */
#include <sys/types.h>

int main(void) {
    char s[] = "Hello World\n";
    int ret;

    /* direct system call */
    ret = syscall(SYS_write, 2, s, sizeof(s)); /* man 2 syscall */
    printf("syscall(SYS_write) return %d\n", ret);

    /* or "libc" wrapped system call */
    ret = write(2, s, sizeof(s));
    printf("libc write() return %d\n", ret);

    return(0);
}
