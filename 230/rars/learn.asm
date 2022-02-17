.data
array: .dword 10, 20, 30, 40, 50

.text
.globl main

# long *arr = {10, 20, 30, 40, 50}
# long sum = 0;
#
# for(int i = 0; i<10; i++)
#	sum += arr[i]
#


main:
	#addi t1, zero, 10
	li t1, 5     # Comparator
	li t0, 0     # Step
	li s0, 0     # Sum
	la t2, array # Array
	
	
	
loop:
	bge t0, t1, end # Check if loop will run again
	
	slli t3, t0, 3  # Scale to datasize
	add t3, t3, t2  # Get to start 
	ld t3, 0(t3)    # Value at t2[t0]
	add a0, t3, a0  # Sum += arr[i]
	
	addi t0, t0, 1	# i++
	j loop		# Restart loop

end:
	li a7, 1	# Print
	ecall		# No ce
