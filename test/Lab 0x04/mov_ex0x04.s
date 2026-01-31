 .data
 .balign 4
variabile:
 .long 0,0,0,0,0,0,0,0
flag_carry: .byte 0
flag_zero: .byte 0
flag_below: .byte 0
flag_less: .byte 0
tabel_add:
 .byte 0,1,2,3,4,5,6,7
 .byte 1,2,3,4,5,6,7,0
 .byte 2,3,4,5,6,7,0,1
 .byte 3,4,5,6,7,0,1,2
 .byte 4,5,6,7,0,1,2,3
 .byte 5,6,7,0,1,2,3,4
 .byte 6,7,0,1,2,3,4,5
 .byte 7,0,1,2,3,4,5,6

tabel_carry_add:
 .byte 0,0,0,0,0,0,0,0
 .byte 0,0,0,0,0,0,0,1
 .byte 0,0,0,0,0,0,1,1
 .byte 0,0,0,0,0,1,1,1
 .byte 0,0,0,0,1,1,1,1
 .byte 0,0,0,1,1,1,1,1
 .byte 0,0,1,1,1,1,1,1
 .byte 0,1,1,1,1,1,1,1

add_indice_linie:
 .long tabel_add + 0
 .long tabel_add + 8
 .long tabel_add + 16
 .long tabel_add + 24
 .long tabel_add + 32
 .long tabel_add + 40
 .long tabel_add + 48
 .long tabel_add + 56

Carry_add_indice_linie:
 .long tabel_carry_add + 0
 .long tabel_carry_add + 8
 .long tabel_carry_add + 16
 .long tabel_carry_add + 24
 .long tabel_carry_add + 32
 .long tabel_carry_add + 40
 .long tabel_carry_add + 48
 .long tabel_carry_add + 56

tabel_sub:
 .byte 0,7,6,5,4,3,2,1
 .byte 1,0,7,6,5,4,3,2
 .byte 2,1,0,7,6,5,4,3
 .byte 3,2,1,0,7,6,5,4
 .byte 4,3,2,1,0,7,6,5
 .byte 5,4,3,2,1,0,7,6
 .byte 6,5,4,3,2,1,0,7
 .byte 7,6,5,4,3,2,1,0

tabel_below_sub:
 .byte 0,1,1,1,1,1,1,1
 .byte 0,0,1,1,1,1,1,1
 .byte 0,0,0,1,1,1,1,1
 .byte 0,0,0,0,1,1,1,1
 .byte 0,0,0,0,0,1,1,1
 .byte 0,0,0,0,0,0,1,1
 .byte 0,0,0,0,0,0,0,1
 .byte 0,0,0,0,0,0,0,0

sub_indice_linie:
 .long tabel_sub + 0
 .long tabel_sub + 8
 .long tabel_sub + 16
 .long tabel_sub + 24
 .long tabel_sub + 32
 .long tabel_sub + 40
 .long tabel_sub + 48
 .long tabel_sub + 56

below_sub_indice_linie:
 .long tabel_below_sub + 0
 .long tabel_below_sub + 8
 .long tabel_below_sub + 16
 .long tabel_below_sub + 24
 .long tabel_below_sub + 32
 .long tabel_below_sub + 40
 .long tabel_below_sub + 48
 .long tabel_below_sub + 56

tabel_mask:
 .byte 0,1,2,3,4,5,6,7
 .byte 0,1,2,3,4,5,6,7
 .byte 0,1,2,3,4,5,6,7
 .byte 0,1,2,3,4,5,6,7
 .byte 0,1,2,3,4,5,6,7
 .byte 0,1,2,3,4,5,6,7
 .byte 0,1,2,3,4,5,6,7
 .byte 0,1,2,3,4,5,6,7

tabel_zero:
 .byte 1,0,0,0,0,0,0,0
 .byte 0,1,0,0,0,0,0,0
 .byte 0,0,1,0,0,0,0,0
 .byte 0,0,0,1,0,0,0,0
 .byte 0,0,0,0,1,0,0,0
 .byte 0,0,0,0,0,1,0,0
 .byte 0,0,0,0,0,0,1,0
 .byte 0,0,0,0,0,0,0,1
tabel_below:
 .byte 0,0,0,0,0,0,0,0
 .byte 1,0,0,0,0,0,0,0
 .byte 1,1,0,0,0,0,0,0
 .byte 1,1,1,0,0,0,0,0
 .byte 1,1,1,1,0,0,0,0
 .byte 1,1,1,1,1,0,0,0
 .byte 1,1,1,1,1,1,0,0
 .byte 1,1,1,1,1,1,1,0
zero_indice_linie:
 .long tabel_zero + 0
 .long tabel_zero + 8
 .long tabel_zero + 16
 .long tabel_zero + 24
 .long tabel_zero + 32
 .long tabel_zero + 40
 .long tabel_zero + 48
 .long tabel_zero + 56

below_indice_linie:
 .long tabel_below + 0
 .long tabel_below + 8
 .long tabel_below + 16
 .long tabel_below + 24
 .long tabel_below + 32
 .long tabel_below + 40
 .long tabel_below + 48
 .long tabel_below + 56

tabel_xor:
.byte 0,1,2,3,4,5,6,7
.byte 1,0,3,2,5,4,7,6
.byte 2,3,0,1,6,7,4,5
.byte 3,2,1,0,7,6,5,4
.byte 4,5,6,7,0,1,2,3
.byte 5,4,7,6,1,0,3,2
.byte 6,7,4,5,2,3,0,1
.byte 7,6,5,4,3,2,1,0
xor_indice_linie:
 .long tabel_xor + 0
 .long tabel_xor + 8
 .long tabel_xor + 16
 .long tabel_xor + 24
 .long tabel_xor + 32
 .long tabel_xor + 40
 .long tabel_xor + 48
 .long tabel_xor + 56

tabel_less:
 .byte 0,1,1,1,0,0,0,0
 .byte 0,0,1,1,0,0,0,0
 .byte 0,0,0,1,0,0,0,0
 .byte 0,0,0,0,0,0,0,0
 .byte 1,1,1,1,0,1,1,1
 .byte 1,1,1,1,0,0,1,1
 .byte 1,1,1,1,0,0,0,1
 .byte 1,1,1,1,0,0,0,0
less_indice_linie:
 .long tabel_less + 0
 .long tabel_less + 8
 .long tabel_less + 16
 .long tabel_less + 24
 .long tabel_less + 32
 .long tabel_less + 40
 .long tabel_less + 48
 .long tabel_less + 56

tabel_div:
 .byte 0,0,0,0,0,0,0,0
 .byte 0,1,0,0,0,0,0,0
 .byte 0,2,1,0,0,0,0,0
 .byte 0,3,1,1,0,0,0,0
 .byte 0,4,2,1,1,0,0,0
 .byte 0,5,2,1,1,1,0,0
 .byte 0,6,3,2,1,1,1,0
 .byte 0,7,3,2,1,1,1,1
tabel_mod:
 .byte 0,0,0,0,0,0,0,0
 .byte 0,0,1,1,1,1,1,1
 .byte 0,0,0,2,2,2,2,2
 .byte 0,0,1,0,3,3,3,3
 .byte 0,0,0,1,0,4,4,4
 .byte 0,0,1,2,1,0,5,5
 .byte 0,0,0,0,2,1,0,6
 .byte 0,0,1,1,3,2,1,0
div_indice_linie:
 .long tabel_div + 0
 .long tabel_div + 8
 .long tabel_div + 16
 .long tabel_div + 24
 .long tabel_div + 32
 .long tabel_div + 40
 .long tabel_div + 48
 .long tabel_div + 56

mod_indice_linie:
 .long tabel_mod + 0
 .long tabel_mod + 8
 .long tabel_mod + 16
 .long tabel_mod + 24
 .long tabel_mod + 32
 .long tabel_mod + 40
 .long tabel_mod + 48
 .long tabel_mod + 56

tabel_and:
 .byte 0,0,0,0,0,0,0,0
 .byte 0,1,0,1,0,1,0,1
 .byte 0,0,2,2,0,0,2,2
 .byte 0,1,2,3,0,1,2,3
 .byte 0,0,0,0,4,4,4,4
 .byte 0,1,0,1,4,5,4,5
 .byte 0,0,2,2,4,4,6,6
 .byte 0,1,2,3,4,5,6,7
tabel_or:
 .byte 0,1,2,3,4,5,6,7
 .byte 1,1,3,3,5,5,7,7
 .byte 2,3,2,3,6,7,6,7
 .byte 3,3,3,3,7,7,7,7
 .byte 4,5,6,7,4,5,6,7
 .byte 5,5,7,7,5,5,7,7
 .byte 6,7,6,7,6,7,6,7
 .byte 7,7,7,7,7,7,7,7
tabel_shl:
 .byte 0,0,0,0,0,0,0,0
 .byte 1,2,4,0,0,0,0,0
 .byte 2,4,0,0,0,0,0,0
 .byte 3,6,4,0,0,0,0,0
 .byte 4,0,0,0,0,0,0,0
 .byte 5,2,4,0,0,0,0,0
 .byte 6,4,0,0,0,0,0,0
 .byte 7,6,4,0,0,0,0,0

shl_indice_linie:
 .long tabel_shl + 0
 .long tabel_shl + 8
 .long tabel_shl + 16
 .long tabel_shl + 24
 .long tabel_shl + 32
 .long tabel_shl + 40
 .long tabel_shl + 48
 .long tabel_shl + 56
tabel_shr:
 .byte 0,0,0,0,0,0,0,0
 .byte 1,0,0,0,0,0,0,0
 .byte 2,1,0,0,0,0,0,0
 .byte 3,1,0,0,0,0,0,0
 .byte 4,2,1,0,0,0,0,0
 .byte 5,2,1,0,0,0,0,0
 .byte 6,3,1,0,0,0,0,0
 .byte 7,3,1,0,0,0,0,0

shr_indice_linie:
 .long tabel_shr + 0
 .long tabel_shr + 8
 .long tabel_shr + 16
 .long tabel_shr + 24
 .long tabel_shr + 32
 .long tabel_shr + 40
 .long tabel_shr + 48
 .long tabel_shr + 56
and_indice_linie:
 .long tabel_and + 0
 .long tabel_and + 8
 .long tabel_and + 16
 .long tabel_and + 24
 .long tabel_and + 32
 .long tabel_and + 40
 .long tabel_and + 48
 .long tabel_and + 56

or_indice_linie:
 .long tabel_or + 0
 .long tabel_or + 8
 .long tabel_or + 16
 .long tabel_or + 24
 .long tabel_or + 32
 .long tabel_or + 40
 .long tabel_or + 48
 .long tabel_or + 56

tabel_mul_lo:
 .byte 0,0,0,0,0,0,0,0
 .byte 0,1,2,3,4,5,6,7
 .byte 0,2,4,6,0,2,4,6
 .byte 0,3,6,1,4,7,2,5
 .byte 0,4,0,4,0,4,0,4
 .byte 0,5,2,7,4,1,6,3
 .byte 0,6,4,2,0,6,4,2
 .byte 0,7,6,5,4,3,2,1

tabel_mul_hi:
 .byte 0,0,0,0,0,0,0,0
 .byte 0,0,0,0,0,0,0,0
 .byte 0,0,0,0,1,1,1,1
 .byte 0,0,0,1,1,1,2,2
 .byte 0,0,1,1,2,2,3,3
 .byte 0,0,1,1,2,3,3,4
 .byte 0,0,1,2,3,3,4,5
 .byte 0,0,1,2,3,4,5,6

mul_lo_indice_linie:
 .long tabel_mul_lo + 0
 .long tabel_mul_lo + 8
 .long tabel_mul_lo + 16
 .long tabel_mul_lo + 24
 .long tabel_mul_lo + 32
 .long tabel_mul_lo + 40
 .long tabel_mul_lo + 48
 .long tabel_mul_lo + 56

mul_hi_indice_linie:
 .long tabel_mul_hi + 0
 .long tabel_mul_hi + 8
 .long tabel_mul_hi + 16
 .long tabel_mul_hi + 24
 .long tabel_mul_hi + 32
 .long tabel_mul_hi + 40
 .long tabel_mul_hi + 48
 .long tabel_mul_hi + 56

tabel_imul_hi:
 .byte 0,0,0,0,0,0,0,0
 .byte 0,0,0,0,15,15,15,15
 .byte 0,0,0,0,15,15,15,15
 .byte 0,0,0,0,15,15,15,15
 .byte 0,15,15,15,1,0,0,0
 .byte 0,15,15,15,0,0,0,0
 .byte 0,15,15,15,0,0,0,0
 .byte 0,15,15,15,0,0,0,0

imul_hi_indice_linie:
 .long tabel_imul_hi + 0
 .long tabel_imul_hi + 8
 .long tabel_imul_hi + 16
 .long tabel_imul_hi + 24
 .long tabel_imul_hi + 32
 .long tabel_imul_hi + 40
 .long tabel_imul_hi + 48
 .long tabel_imul_hi + 56

 v: .long 26, 12, 3, 56, 3, 18, 27, 35, 15
 n: .long 9
 frecv: .space 404
 formatAfisare: .asciz "Numarul care apare cele mai multe ori: %d\n"
 .text
 .global main
 .extern printf
 main:
 movl n, %eax
 movl %eax, variabile+8
 movl $v, %eax
 movl %eax, variabile+20
 movzbl variabile+0, %eax
 movzbl tabel_mask(%eax), %eax
 movzbl variabile+0, %ebx
 movzbl tabel_mask(%ebx), %ebx
 movl xor_indice_linie(,%eax,4), %ecx
 movzbl (%ecx,%ebx,1), %edx
 movl %edx, variabile+0
 movl %edx, %eax
 movl $0, %ebx
 movl zero_indice_linie(,%eax,4), %ecx
 movzbl (%ecx,%ebx,1), %edx
 movb %dl, flag_zero
 et_tablou_frecv:
 movl $0, %eax
 movzbl tabel_mask(%eax), %eax
 movzbl variabile+8, %ebx
 movzbl tabel_mask(%ebx), %ebx
 movl zero_indice_linie(,%eax,4), %ecx
 movzbl (%ecx,%ebx,1), %edx
 movb %dl, flag_zero
 movl below_indice_linie(,%eax,4), %ecx
 movzbl (%ecx,%ebx,1), %edx
 movb %dl, flag_below
 movl less_indice_linie(,%eax,4), %ecx
 movzbl (%ecx,%ebx,1), %edx
 movb %dl, flag_less
 cmpb $1, flag_zero
 je et_parcurgere
 movl variabile+20, %ebx
 movl variabile+0, %esi
 movl (%ebx, %esi, 4), %eax
 movl %eax, variabile+4
 movl $frecv, %eax
 movl %eax, variabile+16
 movl variabile+16, %ebx
 movl variabile+4, %esi
 movl (%ebx, %esi, 4), %eax
 movl %eax, variabile+12
 movzbl variabile+12, %eax
 movzbl tabel_mask(%eax), %eax
 movl $1, %ebx
 movzbl tabel_mask(%ebx), %ebx
 movl add_indice_linie(,%eax,4), %ecx
 movzbl (%ecx,%ebx,1), %edx
 movl %edx, variabile+12
 movl Carry_add_indice_linie(,%eax,4), %ecx
 movzbl (%ecx,%ebx,1), %edx
 movb %dl, flag_carry
 movl variabile+16, %ebx
 movl variabile+4, %esi
 movl variabile+12, %eax
 movl %eax, (%ebx, %esi, 4)
 movzbl variabile+0, %eax
 movzbl tabel_mask(%eax), %eax
 movl $1, %ebx
 movzbl tabel_mask(%ebx), %ebx
 movl add_indice_linie(,%eax,4), %ecx
 movzbl (%ecx,%ebx,1), %edx
 movl %edx, variabile+0
 movl Carry_add_indice_linie(,%eax,4), %ecx
 movzbl (%ecx,%ebx,1), %edx
 movb %dl, flag_carry
 movzbl variabile+8, %eax
 movzbl tabel_mask(%eax), %eax
 movl $1, %ebx
 movzbl tabel_mask(%ebx), %ebx
 movl sub_indice_linie(,%eax,4), %ecx
 movzbl (%ecx,%ebx,1), %edx
 movl %edx, variabile+8
 movl below_sub_indice_linie(,%eax,4), %ecx
 movzbl (%ecx,%ebx,1), %edx
 movb %dl, flag_below
 jmp et_tablou_frecv
 et_parcurgere:
 movl $0, variabile+0
 movl $0, variabile+4
 movl $0, variabile+12
 movl $frecv, %eax
 movl %eax, variabile+16
 et_cautare:
 movl $100, %eax
 movzbl tabel_mask(%eax), %eax
 movzbl variabile+0, %ebx
 movzbl tabel_mask(%ebx), %ebx
 movl zero_indice_linie(,%eax,4), %ecx
 movzbl (%ecx,%ebx,1), %edx
 movb %dl, flag_zero
 movl below_indice_linie(,%eax,4), %ecx
 movzbl (%ecx,%ebx,1), %edx
 movb %dl, flag_below
 movl less_indice_linie(,%eax,4), %ecx
 movzbl (%ecx,%ebx,1), %edx
 movb %dl, flag_less
 cmpb $1, flag_less
 je not_jg_0
 cmpb $1, flag_zero
 je not_jg_0
 jmp afisare
 not_jg_0:
 movl variabile+16, %ebx
 movl variabile+0, %esi
 movl (%ebx, %esi, 4), %eax
 movl %eax, variabile+8
 movzbl variabile+12, %eax
 movzbl tabel_mask(%eax), %eax
 movzbl variabile+8, %ebx
 movzbl tabel_mask(%ebx), %ebx
 movl zero_indice_linie(,%eax,4), %ecx
 movzbl (%ecx,%ebx,1), %edx
 movb %dl, flag_zero
 movl below_indice_linie(,%eax,4), %ecx
 movzbl (%ecx,%ebx,1), %edx
 movb %dl, flag_below
 movl less_indice_linie(,%eax,4), %ecx
 movzbl (%ecx,%ebx,1), %edx
 movb %dl, flag_less
 cmpb $1, flag_less
 je et_cont_parcurgere
 cmpb $1, flag_zero
 je et_cont_parcurgere
 movl variabile+8, %eax
 movl %eax, variabile+12
 movl variabile+0, %eax
 movl %eax, variabile+4
 et_cont_parcurgere:
 movzbl variabile+0, %eax
 movzbl tabel_mask(%eax), %eax
 movl $1, %ebx
 movzbl tabel_mask(%ebx), %ebx
 movl add_indice_linie(,%eax,4), %ecx
 movzbl (%ecx,%ebx,1), %edx
 movl %edx, variabile+0
 movl Carry_add_indice_linie(,%eax,4), %ecx
 movzbl (%ecx,%ebx,1), %edx
 movb %dl, flag_carry
 jmp et_cautare
 afisare:
 movl variabile+4, %eax
 push %eax
     pushl $formatAfisare
     call printf
 add $8, %esp
 et_exit:
 movl $1, variabile+0
 movzbl variabile+4, %eax
 movzbl tabel_mask(%eax), %eax
 movzbl variabile+4, %ebx
 movzbl tabel_mask(%ebx), %ebx
 movl xor_indice_linie(,%eax,4), %ecx
 movzbl (%ecx,%ebx,1), %edx
 movl %edx, variabile+4
 movl %edx, %eax
 movl $0, %ebx
 movl zero_indice_linie(,%eax,4), %ecx
 movzbl (%ecx,%ebx,1), %edx
 movb %dl, flag_zero
 movl variabile+0, %eax
 movl variabile+4, %ebx
 movl variabile+8, %ecx
 movl variabile+12, %edx
 int $0x80
