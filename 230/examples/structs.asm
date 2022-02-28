#N	O	S
#a	0	1	
#c	2	2	
#b	4	4
#d	8	8
#Size of array: 16 bytes

#N	O	S
#d	0	8	
#b	8	4	
#c	12	2
#a	14	1
#Size of array: 16 bytes

#N	O	S
#a	0	1	
#b	4	4	
#c	8	2
#d	16	8
#Size of array: 24 bytes

#S = {1,2,3,4}
#return s.a + s.b * s.c / s.d
lb t0, 0(a0)
lw t1, 4(a0)
lh t2, 8(a0)
ld t3, 16(a0)
mul t4, t1, t2
div t5, t4, t3
add a0, t0, t5