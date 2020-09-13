            global      _start
            section     .data
nl:         db          10

            section     .bss
buff        resw        1
finish      resw        1

            section     .text
putch:
            ;pop         buffer
            mov         eax, 1          ; system call for write
            mov         edi, 1          ; file handle 1 is stdout
            mov         esi, buff     ; address of string to output
            mov         edx, 2          ; number of bytes
            syscall                     ; invoke operation
            ret                         ; return control to call func

ln:
            mov         eax, 1          ; system call for write
            mov         edi, 1          ; file handle 1 is stdout
            mov         esi, nl    ; address of string to output
            mov         edx, 1          ; number of bytes
            syscall                     ; invoke operation
            ret                         ; return control to call func

getch:
            mov         eax, 0          ; system call for read
            mov         edi, 0          ; file handle 0 is stdin
            mov         esi, nl     ; address of string to output
            mov         edx, 2          ; number of bytes
            syscall                     ; invoke operation
            ret                         ; return control to call func

exit:
            mov         eax, 60         ; system call for exit
            xor         edi, edi        ; exit code 0
            syscall

_start:
            mov         dword [buff], "А"
            call        putch
            call        ln
            mov         dword [buff], "Б"
            call        putch
            call        ln
            mov         dword [buff], "В"
            call        putch
            call        ln

            call        getch
            mov         rax, [buff]
            mov         [finish], rax
            add         dword [finish], 3
            call        exit
