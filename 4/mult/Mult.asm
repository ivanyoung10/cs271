// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
// The algorithm is based on repetitive addition.

//// Replace this comment with your code.


// Add R0 to R2 R1 amount of times 
// 1 - Load in R1 to memory
@2
M=0
@1
D=M
@Infinite_loop
D;JEQ
(Add_loop)
@R0
D=M
@2
M=D+M
@1
M=M-1
@1
D=M
@Add_loop
D;JGT
(Infinite_loop)
@Infinite_loop
0;JMP


