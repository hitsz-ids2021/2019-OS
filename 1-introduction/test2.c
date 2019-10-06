#include <unistd.h>
int main(int argc, char **argv)
{
    write(2, "Hello World!\n", 13);
    return 0;
}
