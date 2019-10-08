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
  
  1.软盘启动。  
    实验vmware虚拟机将生成的boot.img挂载成软盘。  
    在虚拟机上添加设备。  
      <div align=center><img width="350" height="250" src="https://github.com/HITSZ-SYSTEMS/2019-OS/blob/master/img/1.png?raw=true"></div>
      <div align=center>图1-1 添加设备</div>
      <div align=center><img width="350" height="250" src="https://github.com/HITSZ-SYSTEMS/2019-OS/blob/master/img/%E8%BD%AF%E9%A9%B1.png?raw=true"></div>
      <div align=center>图1-2 选择软驱</div>
    添加完成后重启虚拟机。  
    实验结果如图所示：
      <div align=center><img width="350" height="250" src="https://github.com/HITSZ-SYSTEMS/2019-OS/blob/master/img/%E8%BD%AF%E7%9B%98%E5%90%AF%E5%8A%A8%E7%BB%93%E6%9E%9C.png?raw=true"></div>
      <div align=center>图1-3 软盘启动结果</div>
      
   2.硬盘启动  
     实验vmware虚拟机将生成的hello.vmdk挂载成虚拟磁盘。
      <div align=center><img width="350" height="250" src="https://github.com/HITSZ-SYSTEMS/2019-OS/blob/master/img/%E7%8E%B0%E6%9C%89%E7%A1%AC%E7%9B%98.png?raw=true"></div>
      <div align=center>图2-1 选择"现有硬盘"</div>
      <div align=center><img width="350" height="250" src="https://github.com/HITSZ-SYSTEMS/2019-OS/blob/master/img/IDE.png?raw=true"></div>
      <div align=center>图2-2 总线类型为IDE</div>
     添加完后，选择“启动到固件”。
      <div align=center><img width="350" height="250" src="https://github.com/HITSZ-SYSTEMS/2019-OS/blob/master/img/%E5%9B%BA%E4%BB%B6.png?raw=true"></div>
      <div align=center>图2-3 启动到固件</div>
     在Boot项把VMware Virtual IDE Hard-(PM)移到第一个。
       <div align=center><img width="350" height="250" src="https://github.com/HITSZ-SYSTEMS/2019-OS/blob/master/img/%E4%BF%AE%E6%94%B9%E9%A1%BA%E5%BA%8F.png?raw=true"></div>
      <div align=center>图2-4 修改启动顺序</div>
     按F10保存并退出。  
     实验结果如图所示：
      <div align=center><img width="350" height="250" src="https://github.com/HITSZ-SYSTEMS/2019-OS/blob/master/img/%E7%A1%AC%E7%9B%98%E7%BB%93%E6%9E%9C.png?raw=true"></div>
      <div align=center>图2-5 硬盘启动结果</div>

      
      


