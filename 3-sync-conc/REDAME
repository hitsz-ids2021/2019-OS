# 并发与同步
      本页面包含信号及并发与同步部分PPT中相关的代码示例，PPT已经对应文件名，可以根据文件名查找。
### 1.shellex.c 代码中实现了模拟简单shell的功能,注意这个文件是有bug的
> 1.编译文件：gcc shellex.c -o shellex
> 2.编译hello程序： gcc hello.c -o hello
> 3.运行shell: ./shellex
> 4.待出现命令提示符“>”后，可以测试前台进程和后台进程
       测试前台进程如: hello
       测试后台进程如：hello &
       还可以测试shell内置的唯一命令：quit
> 5. 可以使用ps来测试后台进程是否被回收：ps -ef|grep hello
> * 注：可以自己扩展shell的功能，添加更多内置命令，也可以自己写其他的文件以丰富shell

### 2. shell2.c 代码修复了shellex.c不能回收后台进程的bug
方法，如上

### 3. sigint.c 一个简单的设置信号处理程序的实例
> 1. 编译：gcc sigint.c -o sigint
> 2. 运行：./sigint

### 4. wrong_handler.c 和 right_handler.c n 正确的信号处理的正反例
> 1. 编译： 同上
> 2. 运行
