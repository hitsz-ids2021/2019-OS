# CPU调度与优化
    本页面中包含CPU调度专题PPT中所涉及的相关示例代码，PPT中已经标注好文件名，可根据文件名进行查找。

#### 1. lower.c: 对比大小写字符转换程序在优化前后的执行时间，优化方式对应PPT内容Optimization Blocker #1。
> 1. 编译命令：gcc -o lower lower.c 
> 2. 运行命令：./lower
#### 2. sum_row.c: 对比矩阵行求和程序执行时间，优化方式对应PPT内容Optimization Blocker #2。
> 1. 编译命令: gcc -o sum_row sum_row.c
> 2. 运行命令: ./sum_row.c
> 3. 将优化前后的函数单独提出来形成文件sum1.c和sum2.c
> 4. 编译命令: gcc -S sum1.c sum2.c
> 5. 生成汇编代码: sum1.s sum2.s
#### 3. benchmark: 优化实验完整代码.
> 1. 运行脚本sh run.sh执行程序示例
> 2. 修改run.sh的-D参数可以更改测试内容
    测试数据类型: 
      整型 -DINT
      长整型 -DLONG
      单精度浮点型 -DFLOAT
      双精度浮点型 -DDOUBLE
      长双精度浮点型 -DEXTEND
      字符型 -DCHAR
    测试操作:
      默认加法
      乘法 -DPROD
      除法 -DDIV
