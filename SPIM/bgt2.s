.text
.globl main
main:
	li $t0, 10
	li $t1, 8
	bgt $t0, $t1, addition
	sub $t0, $t0, $t1
addition:
	add $t0, $t0, $t1
exit:
	li $v0, 10
	syscall
