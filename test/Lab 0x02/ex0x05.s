.data
.text
.global main
main:
    mov $0x2, %eax
    mov $0x1, %edx
    mov $2, %ebx
    div %ebx
et_exit:
    mov $1, %eax
    mov $0, %ebx
    int $0x80


