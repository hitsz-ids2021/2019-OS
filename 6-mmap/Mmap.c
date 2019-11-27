#include "csapp.h"

void mmapcopy(int fd, int size)
{
    // pointer to memory mapped area.
    char *bufp;

    // map fd to bufp.
    bufp = mmap(NULL,size,PROT_READ,MAP_PRIVATE,fd,0);
    // write bufp to stdout.
    write(1,bufp,size);
    printf("\n");
    return ;
}

int main(int argc, char **argv)
{
    struct stat stat;
    int fd;

    // check for required argv (file path).
    if(argc != 2)
    {
        printf("usage:%s<filename>\n",argv[0]);
        exit(0);
    }

    // copy input file to stdout.
    fd = open(argv[1],O_RDONLY,0);
    fstat(fd,&stat);
    mmapcopy(fd,stat.st_size);
    exit(0);
}