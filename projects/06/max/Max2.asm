   1@R0
   2D=M              // D = first number
   3@R1
   4D=D-M            // D = first number - second number
  5 @OUTPUT_FIRST
   6D;JGT            // if D>0 (first is greater) goto output_first
  7 @R1
   8D=M              // D = second number
  9 @OUTPUT_D
   100;JMP            // goto output_d
(OUTPUT_FIRST)
   @R0             
   D=M              // D = first number
(OUTPUT_D)
   @R2
   M=D              // M[2] = D (greatest number)
(INFINITE_LOOP)
   @INFINITE_LOOP
   0;JMP            // infinite loop