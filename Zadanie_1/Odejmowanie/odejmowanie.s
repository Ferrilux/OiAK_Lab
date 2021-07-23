# sekcja danych, które będą wykorzystane w programie
.data
first_num:
    .long 0x10304008, 0x701100ff, 0x45100020, 0x08570030
first_num_len = (. - first_num)/4

second_num:
    .long 0xf040500c, 0x00220026, 0x321000cb, 0x04520031
second_num_len = (. - second_num)/4

# zarezerwowanie miejsca w pamięci na wynik
.section .bss
result:
    .space (first_num_len *4) + 1

.text 
.globl _start

_start:
# wyczyszczenie rejestrów oraz flagi przeniesienia
    xor %eax, %eax
    xor %ebx, %ebx
    xor %ecx, %ecx
    xor %edx, %edx
    clc
    pushf

    # ilość razy wykonywania pętli
    mov $first_num_len, %edi
    clc
    jmp subtraction
    
with_pop:
    popf

# %edi - licznik pętli
# %eax - wartość z pierwszej liczby
# %ebx - wartość z drugiej liczby
subtraction:    
    # zminiejszamy licznik pętli
    dec %edi

    # wczytujemy do rejestrów po jednym słowie maszynowym z każdej z liczb
    mov first_num(,%ecx,4), %eax
    mov second_num(,%ecx,4), %ebx

    sub %ebx, %eax
    pushf

    movl %eax, result(,%ecx,4)

    # sprawdzenie czy doszlismy do konca petli
    cmp $0, %edi
    jz end
    jmp with_pop

carry:
    push $1
    jmp exit

end:
    popf
    jc carry

# koniec programu
exit:
    mov $1, %eax
    mov $0, %ebx
    int $0x80