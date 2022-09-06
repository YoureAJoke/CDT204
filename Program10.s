.globl main 
.data
Prompt1: .asciiz "Enter first number: " #string for the first number
Prompt2: .asciiz "Enter secound number: " #string for the second number
Result: .asciiz "The greater number is: " #string for the largest number
.text

main: 
    jal Read_Int #jump and link to the procedure
    slt $t0, $t2, $t1   #compare t2 and t1 if t2 is less than t1 returns a true value (1) or false (0) if its larger
    bne $t0, $zero, Else #check if t0 and zero are not equal if true means t0 == 1 (true) jumps to label else
    move $s0, $t2 #move t2 value into s0
    j EndIF 
    
Else:
    move $s0, $t1 #stores t1 value into s0
    

EndIF: 
    jal Print_Int #jump and link to the procedure
    li $v0, 10  #exit
    syscall


Read_Int:
    li $v0, 4 #prints string of the first prompt (first number to enter)
    la $a0, Prompt1 #add prompt1 string into argument 
    syscall
    
    li $v0, 5 #reads an integer value
    syscall
    move $t1, $v0 #store the result into t1
    
    
    li $v0, 4 #prints string of second prompt (second number to enter)
    la $a0, Prompt2 #add prompt2 string into argument
    syscall
    
    li $v0, 5 #reads an interger value
    syscall
    move $t2, $v0 #store the result into t2
    jr $ra
    
Print_Int:
    li $v0, 4 #prints result string
    la $a0, Result #store the result string into argument
    syscall

    li $v0, 1 #prints integer value 
    move $a0, $s0 #integer value from the largest value is stored into s0 then put into argument to be printed
    syscall
    jr $ra
