.text
.globl main
main:
	li $t0,10
	lw $t1,value
	add $t2,$t0,$t1
	li $v0,10
	syscall

value: .word 10
