.text
.globl main
main:
	li $v0, 4
	la $a0, msg1
	syscall
	li $v0, 5
	syscall
	move $t0, $v0
	
	li $v0, 4
	la $a0, nl
	syscall	
	
	li $t2, 0
	li $t3, 10
	
	while:
		div $t0, $t3
		mfhi $t1
		add $t2, $t2, $t1
		mflo $t0
		bgt $t0, 0, while
		
	li $v0, 4
	la $a0, msg2
	syscall	 
	li $v0, 1
	move $a0, $t2
	syscall	 
		

.data
msg1: .asciiz "enter number: "
msg2: .asciiz "the sum of digits is: "
nl: .asciiz "\n"
