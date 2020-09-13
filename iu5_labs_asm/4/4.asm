            global  _start
            section     .data
newline     db          10
spacing     db          ' – '
table       db          "0123456789ABCDEF"

            section     .bss
buffer      resb        1
remainder   resb        1
temp        resb        1

            section .text

putch_buffer:
            mov         rax, 1          ; system call for write
            mov         rdi, 1          ; file handle 1 is stdout
            mov         rsi, buffer     ; address of string to output
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

putch_tilde:
            mov         rax, 1          ; system call for write
            mov         rdi, 1          ; file handle 1 is stdout
            mov         rsi, spacing     ; address of string to output
            mov         rdx, 5          ; number of bytes
            syscall                     ; invoke operation
            ret


ln:
            mov         rax, 1          ; параметр  ax отвечает за тип операции
            mov         rdi, 1          ; параметр  di говорит куда выводить результат
            mov         rsi, newline    ; параметр  si принимает исходные данные
            mov         rdx, 1          ; параметр  dx говорит сколько байт будет обработано по адресу в si
            syscall                     ; invoke operation
            ret

exit:
            mov         rax, 60         ; system call for exit
            xor         rdi, rdi        ; exit code 0
            syscall

putch_buffer_hex:

      ; translation algorithm from 10 to 16
            mov         al, [buffer]    ; заносим в al делимое
            mov         bl, 16          ; заносим в bl делитель

            div         bl              ; делим al на bl, частное в al, остаток в ah, bl без изменений
            mov         bl, [buffer]    ; сохранияем символ из буффера...
            mov         [temp], bl      ; ... в темп ("временное") чтобы не потерять при печати хекса, так как печать возможна только буффера
            mov         [remainder], ah ; копируем остаток от первого деления в ремайндер для последующего вычисления (это и есть последнее число хекса)
            mov         ebx, table      ; для выполнения поиска соответствия десятичному смволу по отстатку (al выполняет роль индекса) занесём адрес начала таблицы в ebx, ...
            xlat                        ; ... найдённое соответствие кладётся в al
            mov         [buffer], al    ; копируем найденное соответствие в буффер на печать
            call        putch_buffer    ; print :D

            mov         al, [remainder] ; будем дальше искать хекс по остатку (он же ремайндер)
            mov         ebx, table
            xlat
            mov         [buffer], al
            call        putch_buffer

            mov         byte [buffer], 'h'  ; этот символ означает, что число в хексе
            call        putch_buffer

            call        ln              ; конец строки :)

            mov         bl, [temp]
            mov         [buffer], bl

            ret

_start:
            mov         byte [buffer], 'A'
again:
            call        putch_buffer
            call        putch_tilde
            call        putch_buffer_hex
            inc         byte [buffer]
            cmp         byte [buffer], 'Z'
            jle         again

            call exit
