.text
.globl main
main:
	li $t1, 5
	li $t2, 3
	bgt $t1, $t2, add
	sub $t1, $t1, $t2
add:
	add $t1, $t1, $t2
exit:
	li $v0, 10
	syscall
