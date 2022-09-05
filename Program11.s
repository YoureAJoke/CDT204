.globl main 
.data
array: .word 10, 1000, 80, 30, 90, 0
Size: 20

NL: .asciiz "\n"
Result: .asciiz "BIGGEST NUMBER IN ARRAY IS: "
.text
main: 
    lw $s0, Size #Max size
    move $t0, $zero #Index counter
    lw $t4, array($t0)
    addi $t0, $t0, 4
    
Loop:
    # index counter < max size
    slt $t1, $s0, $t0
    bne $t1, $zero, Exit_loop
        
    
    lw $t2, array($t0)
    addi $t0, $t0, 4
    slt $t1, $t4, $t2
    bne $t1, $zero, Else
    j Loop
    
Else:
    move $t4, $t2    
    j Loop    
    


Exit_loop: 
    li $v0, 4
    la $a0, Result
    syscall 
    li $v0, 1 
    move $a0, $t4
    syscall

    li $v0, 10
    syscall
