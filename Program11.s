.globl main 
.data
array: .word 10, 1000, 80, 30, 90, 0 #the array
Size: 20 #used as max size to not step out of bounds from the array.
Result: .asciiz "BIGGEST NUMBER IN ARRAY IS: " #string for the result
.text
main: 
    lw $s0, Size #Max size stored into a variable
    move $t0, $zero #Index counter
    lw $t4, array($t0) #loading array value into t4
    addi $t0, $t0, 4 #increasing the index from first element to second element
    
	Loop:   # index counter < max size
   		beq $t0, $s0, Exit_loop #compare if t0 is equal to maxsize of array if its not continue with loop if it is exit from the loop
       
   		lw $t2, array($t0) #load word from memory to register (array to t2)
    		addi $t0, $t0, 4 #increment the index
    		slt $t1, $t4, $t2 #compare t4 with t2 if it is less than t2 return truevalue (1) if its greater return false value (0)
    		bne $t1, $zero, Else #branch if not equal, if t1 has value 1 go to else if is equal to 0 continue loop.
    		j Loop
    
Else:
    move $t4, $t2    #move the value of t2 to t4
    j Loop    
    


Exit_loop: 
    li $v0, 4 #prints the result string
    la $a0, Result #load the adress of result into argument to be printed out
    syscall 
    li $v0, 1 #print integer value
    move $a0, $t4 #put the integer value into argument to be printed
    syscall

    li $v0, 10 #quit program
    syscall
