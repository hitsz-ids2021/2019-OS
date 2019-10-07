.code16
.text

init:
    mov %cs, %ax
    mov %ax, %ds
    mov %ax, %es
    call DispStr
    jmp .

DispStr:
    mov $BootMessage, %ax
    mov %ax, %bp
    mov $22, %cx
    mov $0x1301, %ax
    mov $0x000c, %bx
    mov $0, %dl
    int $0x10
    ret

BootMessage:    .asciz "Hello, HITSZ OS World!"
.fill 510-(.-init), 1, 0
.word 0xaa55
