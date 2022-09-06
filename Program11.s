.globl main 
.data
array: .word 10, 1000, 80, 30, 90, 0 #the array
Size: 20 #used as max value to not step out of bounds from the array.

NL: .asciiz "\n" #new line string
Result: .asciiz "BIGGEST NUMBER IN ARRAY IS: " #string for the result
.text
main: 
    lw $s0, Size #Max size stored into a variable
    move $t0, $zero #Index counter
    lw $t4, array($t0) #loading array value into t4
    addi $t0, $t0, 4 #increasing the index from 0 to 1
    
Loop:
    # index counter < max size
    slt $t1, $s0, $t0 #check s0 if less than t0, returns a true or false (1 or 0)
    bne $t1, $zero, Exit_loop #check if t1 is true (1)
       
    lw $t2, array($t0) #load word from memory to register (array to t2)
    addi $t0, $t0, 4 #increment on the index
    slt $t1, $t4, $t2 #compare t4 with t2 returns true or false
    bne $t1, $zero, Else #check if value is true
    j Loop
    
Else:
    move $t4, $t2    #change the value of t4 to t2
    j Loop    
    


Exit_loop: 
    li $v0, 4 #prints the result string
    la $a0, Result #put result string into argument
    syscall 
    li $v0, 1 #print integer value
    move $a0, $t4 #put the integer value into argument
    syscall

    li $v0, 10 #exit
    syscall
