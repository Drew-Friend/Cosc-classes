.text
.globl main
sortme: .word 5, 7, 1, 2, 9, 3, 4, 5, 6, -1

main:
	addi sp, sp, -16
	sd ra, 0(sp)
	
	la a0, sortme
	li a1, 10
	call for
	
	ld ra, 0(sp)
	addi sp, sp, 16
	j do
	
for:
	bge t1 a1, do
	
	add t2, a0, t1
	lb t3, 0(t2)
	lb t4, -1(t2)
	bgt t4, t3, swap
	addi t1, t1, 1
	li t0 0
	j for
	
	
do:
	li t0 0
	li t1 1
	bne t0, x0, for
	j end
	
swap:
	li t0, 1 
	#mv s2, a1
	#mv a1, a2
	#mv a2, s2
	sb t3, -1(t2)
	sb t4, 0(t2)
	addi t1, t1, 1
	j for

end:
