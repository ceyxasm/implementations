.text
.globl main
main:
	li $v0, 4
	la $a0, msg1
	syscall
	li $v0, 5
	syscall
	move $t0, $v0
	
	li $t3, 2
	
	div $t0, $t3
	mfhi $t1
	
	beq $t1, 0, even
	li $v0, 4
	la $a0, msg3
	syscall
	li $v0, 10
	syscall
even:
	li $v0, 4
	la $a0, msg2
	syscall
	li $v0, 10
	syscall
	
.data
msg1: .asciiz "enter number: "
msg2: .asciiz "number is even\n"
msg3: .asciiz "number is odd\n"
nl: .asciiz "\n"
