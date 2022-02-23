.data
fPrint: .ascii "fizz"
bPrint: .ascii "buzz"
nPrint: .ascii "\n"

.text
.globl main

# T0 is counter
# T1 is 3, T2 is 5

main:
	li t0, 0
	li s1, 3	# Fizz
	li s2, 5	# Buzz
	li a0, 1	# STDout
	j loop
	
loop:
	
	#Print number with colon and whitespace
	
	## fizz if %3
	rem t1, t0, s1
	beqz t1, fizz
	
	# buzz if %5
	rem t1, t0, s2
	beqz t1, buzz
	
	# print
	j nl
	
	
fizz:	
	la a0, fPrint
	li a2, 4
	li a7, 1
	ecall
	
	rem t1, t0, s2
	beqz t1, buzz
	j nl
	
	
buzz:	
	la a0, bPrint
	li a2, 4
	li a7, 1
	ecall
	j nl
	
nl:
	la a0, nPrint
	li a2, 1
	li a7, 1
	ecall
	j iter
	
	
iter:
	ebreak
	addi t0, t0, 1
	j loop
	
	
