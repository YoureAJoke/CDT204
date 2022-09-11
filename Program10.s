.globl main 
.data
Prompt1: .asciiz "Enter first number: "
Prompt2: .asciiz "Enter secound number: "
Result: .asciiz "The greater number is: "
.text

main: 
    jal Read_Int #jump and link to the procedure read_int
    slt $t0, $t2, $t1   #compare if t2 is less than t1 returns true value (1) if t1 is greater than t2
    bne $t0, $zero, Else #check if t0 and zero are not equal if t0 == 1 (true) jumps to label else
    move $s0, $t2 #move t2 value into s0 if equal
    j EndIF #unconditional branch to the label endif
    
Else:
    move $s0, $t1 

EndIF: 
    jal Print_Int #jump and link to the procedure print int
    li $v0, 10  #exit program
    syscall


Read_Int: #this procedure reads integers given from the user

    li $v0, 4 #prints string of the first prompt (first number to enter)
    la $a0, Prompt1 #load address prompt1 string into argument to be printed
    syscall
    
    li $v0, 5 #reads an integer value
    syscall
    move $t1, $v0 #adds the integer value user has given from v0 into t1
    
    
    li $v0, 4 
    la $a0, Prompt2 
    syscall
    
    li $v0, 5 
    syscall
    move $t2, $v0 
    jr $ra #return back to where the jump and link was done to this procedure read_int
    
Print_Int: #this procedure prints the largest integer value
    li $v0, 4 #prints result string
    la $a0, Result #load adress of the result string into argument to be printed
    syscall

    li $v0, 1 #prints integer value 
    move $a0, $s0 #largest integer value move to argument to be printed
    syscall
    jr $ra #return back to where jump and link was done to this procedure
