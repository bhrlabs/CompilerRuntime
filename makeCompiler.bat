echo off
cd Compiler
bison -dv flash.y
flex flash.lex
gcc -c flash.tab.c lex.yy.c 
gcc -o flash flash.tab.o lex.yy.o -lm
