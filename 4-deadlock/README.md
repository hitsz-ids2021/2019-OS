# 死锁
    本页面中包含死锁专题PPT中所涉及的相关示例代码，PPT中已经标注好文件名，可根据文件名进行查找。

#### 1. deadlock.c: 代码中创建了两个线程，每个线程都执行count()函数，使用for循环进行cnt++的操作，在cnt++前后分别进程两次PV操作，使用PV操作顺序不当则会产生死锁，示例代码中给出了可能产生死锁的情况。
> 1. 编译命令：gcc -o deadlock deadlock.c -lpthread
> 2. 运行命令：./deadlock
