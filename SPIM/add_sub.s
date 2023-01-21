.text
.globl main
main:
	li $t0,5
	li $t1,2
	add $t2,$t0,$t1
	sub $t3,$t0,$t1
	mul $t4,$t0,$t1
	mult $t0,$t1
	li $v0,10
	syscall
