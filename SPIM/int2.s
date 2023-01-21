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
	la $a0, newline
	syscall
	
	
	li $v0, 4
	la $a0, msg2
	syscall
	li $v0, 5
	syscall
	move $t1, $v0
	
	
	li $v0, 4
	la $a0, newline
	syscall
	
	add $t0, $t0, $t1
	li $v0, 4
	la $a0, msg3
	syscall
	move $a0, $t0
	li $v0, 1
	syscall
	
	
	li $v0, 4
	la $a0, newline
	syscall
	
	li $v0, 10
	syscall
	

.data
msg1: .asciiz "enter first number: "
msg2: .asciiz "enter second number: "
msg3: .asciiz "sum is: " 
newline: .asciiz "\n"
