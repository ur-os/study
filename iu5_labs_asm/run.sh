#!/bin/bash
nasm -f elf64 "$1.asm" -o "$1.o"
ld -m elf_x86_64 "$1.o" -o "$1.tmp"

./"$1.tmp"
rm "$1.o" 2> /dev/null
rm "$1.tmp" 2> /dev/null
