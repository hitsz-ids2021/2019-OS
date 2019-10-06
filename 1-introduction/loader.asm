;loader.asm暂时什么也不做，只显示"hello You"

;-------------------------------------
LOADER_BASE_ADDR equ 0x900
LOADER_START_SECTOR equ 0x2

SECTION LOADER vstart=LOADER_BASE_ADDR
    mov byte [es: 0x00], 'H'
    mov byte [es: 0x01],  0xEE
    
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
    
    mov byte [es: 0x0C], 'H'
    mov byte [es: 0x0D], 0xEE
    
    mov byte [es: 0x0E], 'I'
    mov byte [es: 0x0F], 0xEE
    
    mov byte [es: 0x10], 'T'
    mov byte [es: 0x11], 0xEE

    jmp $

