// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
//
// This program only needs to handle arguments that satisfy
// R0 >= 0, R1 >= 0, and R0*R1 < 32768.

// Put your code here.

//Harikrishnan Kokkanthara Jeevan



@R1                   // load r1 into memory
D=M

@i
M=D                   // load r1 as i into mem16

@p
M=0                  // load mem17 = 0 for partial sum

(LOOP)
    @i
    D=M
    @LDREG          // if i!=0 // loop
    D; JEQ 

    @R0
    D = M           // D = R0
    @p
    M = M + D       // Add R0 R1 times 
    @i
    M= M - 1       // decrement i
    @LOOP
    0;JMP

(LDREG)
    @p             //load p into D 
    D = M
    @R2            // load addr of destination register R2
    M = D          // load product into R2
    @END           // Jump to END loop
    0;JMP

(END)
    @END
    0;JMP









 
