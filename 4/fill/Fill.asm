// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Fill.asm

// Runs an infinite loop that listens to the keyboard input. 
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel. When no key is pressed, 
// the screen should be cleared.

//// Replace this comment with your code.

//Load in last and first address for screen
//Start at ending address (24575)
// Write M as -1
// Subtract 1 from placer Register
// Check if placer is equal to starting address (16384)
// if yes, jmp to infinite loop
// if no, jmp to writer_loop

//count of pixels on screen
   @8191
   D=A
   @counter
   M=D
   @KBD
   D=M
   @Fill_Screen
   D;JGT
   @Clear_Screen
   0;JMP
(Fill_Screen)
   @8192
   D=A
   @counter
   M=D
(Fill_Loop)
   @16383
   D=A
   @counter
   A=D+M
   M=-1
   @counter
   M=M-1
   @counter
   D=M
   @INFINITE_LOOP
   D;JEQ
   @Fill_Loop
   0;JMP
(Clear_Screen)
   @SCREEN
   D=M
   @INFINITE_LOOP
   D;JEQ
    @8192
   D=A
   @counter2
   M=D
   D=M
(Empty_Loop)
   @counter2
   D=M
   @INFINITE_LOOP
   D;JEQ
   @16383
   D=A
   @counter2
   A=D+M
   M=0
   @counter2
   M=M-1
   @Empty_Loop
   0;JMP
(INFINITE_LOOP)
   @KBD
   D=M
   @Fill_Screen
   D;JGT
   @Clear_Screen
   0;JMP
   @INFINITE_LOOP
   0;JMP