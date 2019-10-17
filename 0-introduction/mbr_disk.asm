;mbr_disk.asm
;读取硬盘，把loader加载到0x900,并跳转过去

;-------------------------------------
LOADER_BASE_ADDR equ 0x900
LOADER_START_SECTOR equ 0x2

SECTION  MBR vstart=0x7c00
;vstart作用是告诉编译器，把我的起始地址编为0x7c00

    mov ax, cs    ;用cs寄存器的值初始化别的寄存器
                  ;由于mbr是由jmp 0:0x7c00跳过来的，cs=0
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov fs, ax
    mov sp, 0x7c00
    mov ax, 0xb800
    mov es, ax


;清屏(向上滚动窗口)
;AH=06H,AL=上滚行数(0表示全部)
;BH=上卷行属性
;(CL,CH)=窗口左上角坐标，(DL,DH)=窗口右下角 
;--------------------------------------
    mov ax, 0x600
    mov bx, 0x700
    mov cx, 0         ;左上角(0,0)
    mov dx, 0x184f    ;右下角(79,24),
                      ;VGA文本模式中一行80个字符，共25行

    int 0x10

;直接从(0,0)开始写入
;---------------------------------------
    mov byte [es: 0x00], 'H'
    mov byte [es: 0x01], 0xEE
    
    mov byte [es: 0x02], 'e'
    mov byte [es: 0x03], 0xEE
    
    mov byte [es: 0x04], 'l'
    mov byte [es: 0x05], 0xEE
    
    mov byte [es: 0x06], 'l'
    mov byte [es: 0x07], 0xEE
    
    mov byte [es: 0x08], 'o'
    mov byte [es: 0x09], 0xEE
    
    mov byte [es: 0x0A], ' '
    mov byte [es: 0x0B], 0xEE
    
    mov byte [es: 0x0C], 'M'
    mov byte [es: 0x0D], 0xEE
    
    mov byte [es: 0x0E], 'B'
    mov byte [es: 0x0F], 0xEE
    
    mov byte [es: 0x10], 'R'
    mov byte [es: 0x11], 0xEE
    
    mov eax, LOADER_START_SECTOR    ;起始扇区lba地址
    mov bx, LOADER_BASE_ADDR        ;写入的地址
    mov cx, 1                       ;待读入的扇区数
    call rd_disk_m_16           

    jmp LOADER_BASE_ADDR

;读取硬盘n个扇区
rd_disk_m_16:
;-------------------------------
                                    ;eax=LBA起始扇区号
                                    ;bx=数据写入的内存地址
                                    ;cx=读入的扇区数
    mov esi, eax                    ;备份eax，cx
    mov di, cx
;step1:设置读取的扇区数
    mov dx, 0x1f2
    mov al, cl                      ;访问8位端口时，使用寄存器AL
    out dx, al                      ;将AL中的数据写入端口号为0x1f2的寄存器中
                                    ;out目的操作数可以是8位立即数或者寄存器DX
                                    ;源操作数必须为AL或AX
    mov eax, esi

;step2:将LBA地址写入0x1f3-0x1f6(在这里我们的地址就是2)
    ;0x1f3放0-7位
    mov dx, 0x1f3
    out dx, al

    ;0x1f4放8-15位
    mov cl, 8
    shr eax, cl                     ;右移8位
    mov dx, 0x1f4
    out dx, al

    ;0x1f5放16-23位
    shr eax, cl
    mov dx, 0x1f5
    out dx, al

    shr eax, cl
    and al, 0x0f
    or al, 0xe0                     ;设置7-4位为1110，LBA模式，主盘
    mov dx, 0x1f6
    out dx, al

;step3:往Command寄存器写入读命令
    mov dx, 0x1f7
    mov al, 0x20
    out dx, al

;step4:检查硬盘状态
  .not_ready:
    nop
    in al, dx
    and al, 0x88
    cmp al, 0x08
    jnz .not_ready

;step5:从0x1f0端口读出数据
    mov ax, di                     ;DI为要读取的扇区数，data寄存器为16位，即每次读2个字节，要读DI*512/2次
    mov dx, 256
    mul dx                         ;mul指令的被乘数隐含在AX中，乘积的低16位在AX中，高16位存在DX中
    mov cx, ax                     ;把AX的值赋给CX，用作计数器
    
    mov dx, 0x1f0
  .go_on_read:
    in ax, dx                      ;把0x1f0端口读出的数据放在AX寄存器中
    mov [bx], ax                   ;再把AX寄存器中的内容放在偏移地址为BX指向的内存空间
    add bx, 2                      ;一次读1个字
    loop .go_on_read
    ret                            ;记得调用函数后要返回


;-------------------------------------
    times 510-( $-$$ ) db 0
    db 0x55, 0xaa

