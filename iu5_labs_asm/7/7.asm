global  _start
section .text

flush:
            cmp         byte [buffer], 10
            je          flush_e

flush_l:    call        getch
            cmp         byte[buffer], 10
            jne         flush_l

flush_e:    ret

putch:
            mov         rax, 1          ; system call for write
            mov         rdi, 1          ; file handle 1 is stdout
            mov         rsi, buffer     ; address of string to output
            mov         [register], rsi
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

            mov         bl, [temp]
            mov         [buffer], bl

            ret

readline:
            mov         [strlen], byte 0
readline_l: call        getch
            cmp         byte [strlen], 4
            je          readline_e

            xor         eax, eax
            mov         al, byte [strlen]
            mov         dl, [buffer]
            mov         [strbuf + eax], dl

            inc         byte [strlen]

            cmp         byte [buffer], '*'
            je          readline_e

            cmp         byte [strlen], 20
            je          readline_e

            jmp         readline_l

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
            cmp         al, 4
            jl          printline_hex_l

            call        ln
            ret


convert:
            mov         byte [counter], 0
convert_l:  cmp         byte [counter], 4
            je          convert_e

            xor         eax, eax
            mov         al, [counter]
            mov         dl, [strbuf + eax]

            cmp         dl, 'A'
            jge          convert_AF

            sub         dl, '0'

            cmp         byte [counter], 0
            je          convert13
            cmp         byte [counter], 2
            je          convert13


            jmp         convert_le
            ; mov         [machined + eax], dl

convert_AF: sub         dl, 'A'
            add         dl, 10

            cmp         byte [counter], 0
            je          convert13
            cmp         byte [counter], 2
            je          convert13

            jmp         convert_le

convert13:  shl         dl, 4

convert_le: mov         [strbuf + eax], dl
            inc         byte [counter]
            jmp         convert_l

convert_e:  ret


to_machine:
            mov         byte [counter], 0
            mov         byte [machined], 0
            mov         byte [machined + 1], 0
to_machine_l:
            cmp         byte [counter], 4
            je          to_machine_e

            xor         eax, eax
            mov         al, [counter]
            mov         dl, [strbuf + eax]




            cmp         byte [counter], 2
            jge         to_machine_sec

            add         [machined], dl
            inc         byte [counter]
            jmp         to_machine_l
to_machine_sec:
            add         [machined + 1], dl
            inc         byte [counter]
            jmp         to_machine_l
to_machine_e:
            ret


to_decimal:
            mov         byte [decimal_cnt], 0
to_decimal_l:
            cmp         byte [decimal_cnt], 5
            je          to_decimal_e

            mov         bx, 10
            xor         dx, dx
            mov         ah, [machined]
            mov         al, [machined + 1]
            div         bx

            xor         ebx, ebx
            xor         ecx, ecx
            mov         bl, [decimal_cnt]
            mov         cl, 4
            sub         cl, bl
            mov         [decimal + ecx], dl
            mov         [machined], ah
            mov         [machined + 1], al


            inc         byte [decimal_cnt]
            jmp         to_decimal_l
to_decimal_e:
            ret

print_dec:
            mov         byte [counter], 0
print_dec_l:
            cmp         byte [counter], 5
            je          print_dec_e

            xor         eax, eax
            mov         al, [counter]
            mov         bl, [decimal + eax]
            mov         al, bl
            mov         ebx, table
            xlat
            mov         [buffer], al
            call        putch

            inc         byte [counter]
            jmp         print_dec_l
print_dec_e:
            ret


printline_reg:
            mov         byte [counter], 0
printline_reg_l:
            xor         eax, eax
            mov         al, [counter]
            mov         dl, byte [register + eax]
            mov         [buffer], dl
            call        print_hex_inline

            inc         byte [counter]
            mov         al, [counter]
            cmp         al, 8
            jl          printline_reg_l

            call        ln
            ret


_start:
            mov         rcx, 10

lop:
            push        rcx

            call        readline

            cmp         byte [strbuf], '*'
            je          enough


            call        convert
            call        to_machine

            call        printline_reg

            mov         al, [machined]
            mov         [buffer], al
            call        print_hex_inline

            mov         al, [machined + 1]
            mov         [buffer], al
            call        print_hex_inline

            mov         byte [buffer], 'h'
            call        putch

            mov         byte [buffer], ' '
            call        putch

            call        to_decimal
            call        print_dec

            call        ln
            pop         rcx
            loop        lop

enough:     call        exit

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
machined    resb        2
decimal     resb        5
decimal_cnt resb        1
register    resq        1
