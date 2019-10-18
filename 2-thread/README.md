# 线程
    本页面中包含线程部分PPT中所涉及的相关示例代码，PPT中已经标注好文件名，可根据文件名进行查找。

### 1. pthreads_1.c: 代码中编写了并行和顺序执行的两个函数，可以用两种方式来运行编译好的代码。
> 1. 编译命令：gcc -o pthreads_test pthreads_1.c -lpthread -lm
> 2. 顺序运行：time ./pthreads_test serial 4
> 3. 并行运行：time ./pthreads_test parallel 4
> * 注：参数“serial”表示顺序执行，“parallel”表示并行执行，参数4表示要运行的任务数目。

### 2. pass_arg1.c和pass_arg2.c是两个向线程传递参数的例子，pass_arg1.c中在创建线程的时候向每个线程单独传递一个变量，pass_arg2.c中每个线程创建的时候都传入在main函数中定义的唯一变量t。
> 1. 编译命令：gcc -o pass_arg1 pass_arg1.c -lpthread
> 2. 运行：./pass_arg1
> 3. pass_arg2.c 使用相同命令编译运行
### 3. terminate_pthread.c 中示例了创建线程和终止线程的函数用法:使用pthread_create()创建5个线程，每个线程打印“Hello World!”信息然后调用pthread_exit()函数退出。
> 1. 编译命令：gcc -o terminate_pthread terminate_pthread.c -lpthread
> 2. 运行：./terminate_pthread
### 4. hello.c和join_pthread.c中均示例了pthread_join()函数的用法，其中hello.c是创建（creating）和回收（joining）一个线程的示例，join_pthread.c是创建（creating）和回收（joining）多个线程的示例。
> 1. 编译命令：gcc -o join_pthread join_pthread.c -lm -lpthread
> 2. 运行：./join_pthread
> 3. hello.c编译方法与pass_arg1.c相同