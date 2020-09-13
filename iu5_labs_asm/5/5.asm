global  _start
section     .data
newline     db          10
spacing     db          ' - '
table       db          "0123456789ABCDEF"

section     .bss
buffer      resb        1
remainder   resb        1
temp        resb        1
strbuf      resb        20
strlen      resb        1
counter     resq        1

section .text

; flush -- посимвольное чтение со входа
flush_e:    ret

flush:
            cmp         byte [buffer], 10
            je          flush_e

flush_l:    call        getch
            cmp         byte[buffer], 10
            jne         flush_l


putch:
            mov         rax, 1          ; system call for write
            mov         rdi, 1          ; file handle 1 is stdout
            mov         rsi, buffer     ; address of string to output
            mov         rdx, 1          ; number of bytes
            syscall                     ; invoke operation
            ret

ln:
            mov         rax, 1          ; system call for write
            mov         rdi, 1          ; file handle 1 is stdout
            mov         rsi, newline     ; address of string to output
            mov         rdx, 1          ; number of bytes
            syscall                     ; invoke operation
            ret

getch:
            mov         rax, 0          ; system call for read
            mov         rdi, 0          ; file handle 0 is stdin
            mov         rsi, buffer     ; address of string to output
            mov         rdx, 1          ; number of bytes
            syscall                     ; invoke operation
            ret

exit:
            mov         rax, 60         ; system call for exit
            xor         rdi, rdi        ; exit code 0
            syscall

print_hex_inline:
            mov         al, [buffer]
            mov         bl, 16
            div         bl

            mov         bl, [buffer]
            mov         [temp], bl
            mov         [remainder], ah

            mov         ebx, table
            xlat
            mov         [buffer], al
            call        putch




            mov         al, [remainder]
            mov         ebx, table
            xlat
            mov         [buffer], al
            call        putch

            mov         byte [buffer], 'h'
            call        putch

            mov         byte [buffer], ' '
            call        putch

            mov         bl, [temp]
            mov         [buffer], bl

            ret

print_hex:
            call        putch

            mov         rax, 1          ; system call for write
            mov         rdi, 1          ; file handle 1 is stdout
            mov         rsi, spacing     ; address of string to output
            mov         rdx, 3          ; number of bytes
            syscall                     ; invoke operation

            mov         al, [buffer]
            mov         bl, 16
            div         bl

            mov         bl, [buffer]
            mov         [temp], bl
            mov         [remainder], ah

            mov         ebx, table
            xlat
            mov         [buffer], al
            call        putch

            mov         al, [remainder]
            mov         ebx, table
            xlat
            mov         [buffer], al
            call        putch

            mov         byte [buffer], 'h'
            call        putch

            call        ln

            mov         bl, [temp]
            mov         [buffer], bl

            ret

readline:
            mov         [strlen], byte 0

readline_l: call        getch               ; заносим символ в буфер
            cmp         byte [buffer], '$'  ; если бакс, то...
            je          readline_e          ; ... скипаем его

            xor         eax, eax
            mov         al, byte [strlen]
            mov         dl, [buffer]
            mov         [strbuf + eax], dl  ; заносим символ в ,буффер. адрес (основного буфефа + смещение strlen)

            inc         byte [strlen]

            cmp         byte [buffer], '*'
            je          readline_e

            cmp         byte [strlen], 20
            je          readline_e
            jmp         readline_l          ; повторяем цикл, если меньше 20 символов считано

readline_e: call        flush
            ret

printline_hex:
            mov         byte [counter], 0

printline_hex_l:
            xor         eax, eax
            mov         al, [counter]
            mov         dl, byte [strbuf + eax]
            mov         [buffer], dl
            call        print_hex_inline

            inc         byte [counter]
            mov         al, [counter]
            cmp         al, byte [strlen]
            jl          printline_hex_l

            call        ln
            ret


_start:
            mov         rcx, 10 ; 10 раз будет принимать строки на перевод

lop:
            push        rcx     ; сохраняем значение на стеке

            call        readline

            cmp         byte [strlen], 1
            jne         endlop

            cmp         byte [strbuf], '*'
            je          enough

endlop:
            call        printline_hex

            pop         rcx   ; возвращаем, чтобы прочитать и сохранить после перехода
            loop        lop

enough:     call        exit
