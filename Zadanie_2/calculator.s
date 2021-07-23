SYSEXIT = 1
SYSCALL = 0x80
EXIT_SUCCES = 0
SYSWRITE = 4
STDOUT = 1
SYSREAD = 3
STDIN = 0

.text
message:
    .ascii "Wybierz operacje do wykonania: + - * / \n" 
message_len = . - message
message2:
    .ascii "Wybierz precyzje (f - float, d - double) \n"
message2_len = . - message2

.data
float_num1: .float 1.34
float_num2: .float 1.25
double_num1: .double 2.871
double_num2: .double 1.771
buff:
  .ascii " "
buff_len = . - buff
buff2:
  .ascii " "
buff2_len = . - buff2

.global _start
_start:
display_precision:
    mov $SYSWRITE, %eax
    mov $STDOUT, %ebx
    mov $message2, %ecx
    mov $message2_len, %edx
    int $SYSCALL

    mov $SYSREAD, %eax
    mov $STDIN, %ebx
    mov $buff, %ecx
    mov $buff_len, %edx
    int $SYSCALL

    mov $0, %edi
    mov buff(,%edi,1),%al
    cmp $0x66, %al
    je push_float
    cmp $0x64, %al
    je push_double
    jmp display_precision

push_double:
    fld double_num2
    fld double_num1
    jmp display_options

push_float:
    fld float_num2
    fld float_num1
    jmp display_options

display_options:
    mov $SYSWRITE, %eax
    mov $STDOUT, %ebx
    mov $message, %ecx
    mov $message_len, %edx
    int $SYSCALL

    mov $SYSREAD,%eax
    mov $STDIN,%ebx
    mov $buff,%ecx
    mov $buff_len, %edx
    int $SYSCALL

    mov $0, %edi
    mov buff(,%edi,1),%al

    cmp $0x2B,%al
    je add
    cmp $0x2D,%al
    je sub
    cmp $0x2A,%al
    je mul
    cmp $0x2F,%al
    je div
    cmp $0x64,%al
    je exit
    jmp display_options

add:
    faddp
    jmp exit

sub:
    fsubp
    jmp exit

mul:
    fmulp
    jmp exit

div:
    fdivp
    jmp exit

exit:
    mov $SYSEXIT, %eax
    mov $EXIT_SUCCES, %ebx
    int $SYSCALL