            global _start

            section .text


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

exit:
            mov         rax, 60         ; system call for exit
            xor         rdi, rdi        ; exit code 0
            syscall

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

printline:
            mov         byte [counter], 0

printline_l:mov         rbx, [pointer]
            xor         rcx, rcx
            mov         cl, [counter]
            add         rbx, rcx
            cmp         byte [rbx], 0
            je          printline_e

            mov         cl, [rbx]
            mov         [buffer], cl
            call        putch
            inc         byte [counter]
            jmp         printline_l

printline_e:ret

strcmp:
            mov         byte [counter], 0

strcmp_l:   mov         rbx, [pointer]
            mov         rdx, [pointer2]
            xor         rcx, rcx
            mov         cl, [counter]
            add         rbx, rcx
            add         rdx, rcx

            mov         bh, [rbx]
            mov         bl, [rdx]

            cmp         bh, bl
            jne         strcmp_nok

            cmp         bh, 0
            je          strcmp_ok

            inc         byte [counter]
            jmp         strcmp_l

strcmp_ok:  mov         byte [buffer], 1
            ret

strcmp_nok: mov         byte [buffer], 0
            ret


_start:
            mov	        rbp,rsp

            mov         qword [pointer], mess1
            call        printline

            mov         qword [pointer], lastname
            mov         rsi, [rbp + 16]
            mov         qword [pointer2], rsi
            call        strcmp
            mov         al, [buffer]
            cmp         al, 1
            jne         nok1
ok1:
            mov         qword [pointer], mess21
            call        printline
            mov         rsi, [rbp + 16]
            mov         [pointer], rsi
            call        printline
            call        ln
            jmp         s2
nok1:
            mov         qword [pointer], mess22
            call        printline
            call        ln
s2:
            mov         qword [pointer], mess3
            call        printline
            mov         al, [rbp]
            cmp         al, 3
            jl          nok2
ok2:
            mov         qword [pointer], mess41
            jmp         finish
nok2:
            mov         qword [pointer], mess42
finish:
            call        printline
            call        ln
            call        exit

            section     .data
newline     db          10
spacing     db          ' - '
table       db          "0123456789ABCDEF"
testmsg     db          'A', 'B', 10, 0
testmsg1    db          'A', 0, 'B', 10
lastname    db          'Stolyarov', 0
mess1       db          'The first argument is ', 0
mess21      db          'correct: ', 0
mess22      db          'wrong', 0
mess3       db          'The second param is ', 0
mess41      db          'present', 0
mess42      db          'missing', 0


            section     .bss
buffer      resb        1
remainder   resb        1
temp        resb        1
pointer     resq        1
counter     resb        1
pointer2    resq        1

