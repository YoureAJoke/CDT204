.globl main 
.data
array: .space 28 #array and its size
Size: 24 #maxsize
Result: .asciiz "BIGGEST NUMBER IN ARRAY IS: " #string used for result
.text

main: 
	#init registers for the first loop to get input from user then store into array
    lw $s0, Size
    move $t0, $zero 
    lw $t4, array($t0) 
    addi $t0, $t0, 4 
    
Loop_input: #gets user input which then stores it into array
    # index counter < max size 
    slt $t5, $s0, $t0 
    bne $t5, $zero, Prepare #branch to label prepare if t5 not equal to zero (0) false
    li $v0, 5  
    syscall
    sw $v0, array($t0) #store integer in array
    addi $t0, $t0, 4 #increase index
    j Loop_input
    
Prepare: #re-init registers for second loop to find the largest value in the array
    li $t0, 0
    move $t0, $zero 
    lw $t4, array($t0) #load first element into t4
    addi $t0, $t0, 4 
    j Loop_find_largest #unconditional branch to label loop_find_largest
    
    		
Loop_find_largest: #loops through array to find the largest integer value in the array
    slt $t1, $s0, $t0	
    bne $t1, $zero, Exit_loop # if value is true branches to exit loop
    lw $t2, array($t0) #load from array into t2
    addi $t0, $t0, 4 
    slt $t1, $t4, $t2 #compare t4 to t2 gets true or false value stored in t1
    bne $t1, $zero, Else #if true jumps to else
    j Loop_find_largest #unconditional branch to label loop_find_largest
    
Else:
    move $t4, $t2
    j Loop    
    
   
         
Exit_loop:  #label is used to print the largest value found and end the program
    li $v0, 4 #prints the result string
    la $a0, Result 
    syscall 
    li $v0, 1 #prints integer value
    move $a0, $t4 
    syscall

    li $v0, 10 
    syscall
