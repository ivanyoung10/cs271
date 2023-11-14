// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

// Put your code here.

(START)
@SCREEN // Stores screen memory in DATA
D=A
@STORAGE // Calls Storage screen bit 
M=D // Changes the Storage bit to Screen memory 

(LOOP)
@KBD
D=M // Acceses Keyboard memory to see if a key has been pressed
@BLANK
D;JEQ // Leaves the Screen Blank if no key has been pressed (i.e 0)
@BLACK
0;JMP // Accesses black if there is there was no jump (i.e >0)

(BLANK)
@STORAGE
A=M
M=0 // Leaves Storage bit blank or changes it to blank
@FILL
0;JMP // Jumps to Fill to change whole screen blank

(BLACK)
@STORAGE
A=M
M=-1 // Leaves Storage bit black or changes it to black
@FILL
0;JMP // Jumps to Fill to change whole screen black

(FILL)
@STORAGE
D=M+1
M=D // Increments Storage bit
@KBD
D=A-D // Used to see if there has been a key change
@START
D;JEQ // Jumps back to Start if nothing has changed
@LOOP
0;JMP // Jumps to Loop if something has changed