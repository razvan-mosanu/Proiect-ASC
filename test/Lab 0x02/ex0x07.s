

.data
    a: .ascii "Assembly"
    b: .word 0x25
    c: .asciz "x86"
    d: .asciz ";;;"
    e: .long 0x15

.text
.global main
main:
    movl $4, %eax
    movl $1, %ebx
    movl $a, %ecx
    movl $b, %edi
    subl %ecx, %edi
    movl e, %edx
    orl %edi, %edx
    movl %edx, %edx
    int $0x80

    movl $1, %eax
    xorl %ebx, %ebx
    int $0x80

