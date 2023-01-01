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
(BASE)
    @8192     // initialize i= 8192 , 256 rows of 512 pixels / 16 bits
    D = A
    @i
    M = D


(LOOP)
    @i
    M = M-1
    D = M
    @BASE
    D; JLT

    @KBD   //mem map addr of keyboard RAM[24576]
    D = M 

    @Key_Pressed // if KBD ! 0 ie key is pressed
    D;JNE
    @Key_Not_Pressed // if KBD =0, key is not pressed
    D;JEQ
 

(Key_Pressed)
    @SCREEN
    D = A
    @i
    A = D + M
    M = -1
    @LOOP
    0;JMP


(Key_Not_Pressed)
    @SCREEN
    D = A
    @i
    A = D + M
    M = 0
    @LOOP
    0;JMP

