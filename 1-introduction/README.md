# 实验1 系统调用
  - test1.c 使用syscall()或write()编写程序
  - test2.c 使用和分析系统调用write()  
    
# 实验2 一个典型操作系统的启动
## 2.1 实验步骤
  - boot.asm 软盘启动汇编程序
  1. VMware虚拟机、Ubuntu 18.04操作系统
  2. nasm编译软件。Nasm是一个汇编器，可以从Linux发行版的软件仓库安装。
     sudo apt-get install nasm
  3. 磁盘格式转换工具qemu-img。用于将二进制转化为虚拟磁盘文件。
     sudo apt-get update
     sudo apt-get install qemu-utils
  4. 使用nasm对上述汇编代码编译，生成二进制：
     nasm boot.asm -o boot.bin
  5. 使用软盘镜像来模拟软盘。执行以下命令，写入软盘的第一个扇区。
     dd if=/dev/zero of=emptydisk.img bs=512 count=2880 #生成空白软盘镜像文件
     dd if=boot.bin of=boot.img bs=512 count=1 #用 bin file 生成对应的镜像文件
     dd if=emptydisk.img of=boot.img skip=1 seek=1 bs=512 count=2879 #在 bin 生成的镜像文件后补上空白，成为合适大小的软盘镜像

  - boot.s at&t格式的软盘启动汇编程序 
  1. VMware虚拟机、Ubuntu 18.04操作系统
  2. 编译代码，生成二进制：
     as -o boot.o boot.s
     ld -o boot.bin --oformat binary -e init -Ttext 0x7c00 -o boot.bin boot.o
  3. 使用软盘镜像来模拟软盘。执行以下命令，写入软盘的第一个扇区。
     dd if=/dev/zero of=emptydisk.img bs=512 count=2880 #生成空白软盘镜像文件
     dd if=boot.bin of=boot.img bs=512 count=1 #用 bin file 生成对应的镜像文件
     dd if=emptydisk.img of=boot.img skip=1 seek=1 bs=512 count=2879 #在 bin 生成的镜像文件后补上空白，成为
合适大小的软盘镜像

  - mbr_disk.asm 硬盘启动汇编mbr程序
  - loader.asm   硬盘启动汇编loader程序
  6.使用nasm对上述汇编代码编译，生成二进制：
    nasm -o mbr_disk.bin mbr_disk.asm
    nasm -o loader.bin loader.asm
  7.执行以下命令，生成虚拟磁盘文件
    dd if=mbr_disk.bin of=hello.img bs=512 count=1 conv=notrunc
    dd if=loader.bin of=hello.img bs=512 count=1 seek=2 conv=notrunc
    dd if=/dev/zero of=emptydisk1.img bs=512 count=2880
    dd if=emptydisk1.img of=hello.img seek=3 bs=512 count=3000
    qemu-img convert -f raw hello.img -O vmdk hello.vmdk
  
  ## 2.2 实验结果
  把以上生成boot.img和hello.vmdk都拷贝到虚拟机外。
  1、软盘启动。
     实验vmware虚拟机将生成的boot.img挂载成软盘。
     在虚拟机上添加设备。
     ![启动软盘](https://github.com/HITSZ-SYSTEMS/2019-OS/blob/master/img/1.png?raw=true){:height="50%" width="50%"}

