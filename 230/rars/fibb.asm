.text
.globl main
main:
	li t0, 1
	li s0 10
	blt s1, s0, loop
	ebreak
loop:
	ble s0, s1, end
	
	addi s1, s1, 1
	
	add ra, t0, t1
	addi t1, t0, 0
	addi t0, ra, 0
	j loop
end: