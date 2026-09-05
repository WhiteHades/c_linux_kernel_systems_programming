BITS 32

section .multiboot
align 4
dd 0x1BADB002
dd 0
dd -(0x1BADB002)

section .text
global _start
_start:
    mov eax, 0x10
    mov dx, 0xF4
    out dx, eax
.halt:
    cli
    hlt
    jmp .halt
