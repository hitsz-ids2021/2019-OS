#include<stdio.h>
#include<unistd.h>

int main()
{
    char *argv[]={"/bin/ls","-al","/usr/lib", NULL};

    char *envp[]={0,NULL}; //传递给执行文件新的环境变量数组

    execve("/bin/ls",argv,envp);

}
