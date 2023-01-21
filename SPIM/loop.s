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
	
	li $t1,0
	li $t2,0
	
	while:
		bgt $t1, $t0, exit
		add $t1, $t1,1
		add $t2, $t2,$t1
		j while
	
	exit:
		li $v0, 4
		la $a0, msg2
		syscall
		li $v0, 1
		move $a0, $t2
		syscall
		li $v0, 10
		syscall
	

.data
data:
msg1: .asciiz "enter n: "
msg2: .asciiz "sum: "
nl: .asciiz "\n"
