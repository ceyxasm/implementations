.text
main:
	li	$a0, 5
	jal	fib
	move 	$a0, $v0
	jal	print_int
	jal	print_newline
	
fib:	
        addiu	$sp, $sp, -12
	sw	$ra, 0($sp)
	sw	$s0, 4($sp)
	sw	$s1, 8($sp)
	
	addiu	$s0, $a0, 0
	beq	$0, $s0, done
	addiu	$t0, $0, 1
	beq	$t0, $s0, done
	
	addiu	$a0, $s0, -1
	jal	fib
	addiu	$s1, $v0, 0
	addiu	$a0, $s0, -2
	jal	fib
	addu	$v0, $v0, $s1
	j	finish
	
done:	
        addu	$v0, $0, $s0
	j	finish
	
finish: 
        lw	$s1, 8($sp)
	lw	$s0, 4($sp)
	lw	$ra, 0($sp)
	addiu	$sp, $sp, 12
	jr	$ra

print_int:
	move	$a0, $v0
	li	$v0, 1
	syscall
	jr	$ra
	
print_newline:
	li	$a0, '\n'
	li	$v0, 11
	syscall
	jr	$ra	
