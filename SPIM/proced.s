.text
.globl main
main:
	li $a0,10
	li $a1, 10
	jal maths
	move $a0, $v0
	li $v0, 1
	syscall
	li $v0, 10
	syscall

	maths:
	add $v0, $a0, $a1
	jr $ra
