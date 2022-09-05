.globl main 
.data
Prompt1: .asciiz "Enter first number: "
Prompt2: .asciiz "Enter secound number: "
Result: .asciiz "The greater number is: "
.text

main: 
    jal Read_Int
    slt $t0, $t2, $t1   
    bne $t0, $zero, Else 
    move $s0, $t2
    j EndIF
    
Else:
    move $s0, $t1
    

EndIF: 
    jal Print_Int
    li $v0, 10 
    syscall


Read_Int:
    li $v0, 4
    la $a0, Prompt1
    syscall
    
    li $v0, 5
    syscall
    move $t1, $v0
    
    
    li $v0, 4
    la $a0, Prompt2
    syscall
    
    li $v0, 5
    syscall
    move $t2, $v0
    jr $ra
    
Print_Int:
    li $v0, 4
    la $a0, Result
    syscall

    li $v0, 1
    move $a0, $s0
    syscall
    jr $
