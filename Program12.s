.globl main 
.data
array: .space 28 #array and its size
Size: 24 #used to track index

NL: .asciiz "\n" #new line string
Result: .asciiz "BIGGEST NUMBER IN ARRAY IS: " #string used for result
.text

main: 
    lw $s0, Size #Max size
    move $t0, $zero #Index counter
    lw $t4, array($t0) #load first element into t4
    addi $t0, $t0, 4 # increase index
    
Loop1:
    # index counter < max size
    slt $t9, $s0, $t0 #compare s0 to t0 then store true or false value into t9
    bne $t9, $zero, Prepare #jump to prepare if t9 is true
    li $v0, 5 # read integer 
    syscall
    sw $v0, array($t0) #store integer in array
    addi $t0, $t0, 4 #increase index
    j Loop1
    
Prepare:
	li $t0, 0 #init index to 0
	lw $s0, Size #Max size
    	move $t0, $zero #Index counter
   	lw $t4, array($t0) #store first value of index into t4
    	addi $t0, $t0, 4 #increase index size
	j Loop
Loop:
			
    slt $t1, $s0, $t0	#compare s0 to t0 store true or false value in t1
    bne $t1, $zero, Exit_loop # if value is true junp to exit loop
        
    
    lw $t2, array($t0) #load from array into t2
    addi $t0, $t0, 4 #increase index 
    slt $t1, $t4, $t2 #compare t4 to t2 gets true or false value stored in t1
    bne $t1, $zero, Else #if true jumps to else
    j Loop
    
Else:
    move $t4, $t2    #stores value of t2 into t4
    j Loop    
    
   
         
Exit_loop: 
    li $v0, 4 #prints the result string
    la $a0, Result #store string into argument
    syscall 
    li $v0, 1 #prints integer value
    move $a0, $t4 #store integer value into argument
    syscall

    li $v0, 10 #exit
    syscall
