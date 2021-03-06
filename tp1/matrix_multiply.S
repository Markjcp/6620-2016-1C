#include <mips/regdef.h>
#include <sys/syscall.h>

#----------------------------	64
#			FP
#----------------------------	60
#			GP
#----------------------------	56
#
#			SECOND
#----------------------------	48
#
#			FIRST
#----------------------------	40
#
#			AUX
#----------------------------	32
#			AUX3
#---------------------------- 	28
#			AUX2
#----------------------------	24
#			AUX1
#----------------------------	20
#			COL
#----------------------------	16
#			ROWS
#----------------------------	12
#			X
#----------------------------	8
#			J
#----------------------------	4
#			I
#----------------------------	0


		.text
		.align 2
		.globl matrix_multiply
		.ent matrix_multiply
matrix_multiply:
		.frame $fp, 64, ra
		.set noreorder
		.cpload t9
		.set reorder

		subu sp,sp,64

		.cprestore 56
		sw $fp,60(sp)
		move $fp,sp

		sw a0, 64($fp)
		sw a1, 68($fp)
		sw a2, 72($fp)

		li t1,0
		sw t1,0($fp) 					# i=0
		li t1,0
		sw t1,4($fp) 					# j=0
		li.d $f4,0
		s.d $f4,32($fp)					# aux=0.0
		lw t1,0(a0)
		sw t1,12($fp) 					# rows=m1->rows
		lw t1,4(a0)
		sw t1,16($fp) 					# cols=m1->cols

loop_1: lw t1,0($fp) 					# cargo i
		lw t2,12($fp)					# cargo rows
		bge t1,t2,end					# i>= rows -> end
		li t1,0
		sw t1,4($fp)					# j=0
loop_2:	lw t1,4($fp)					# cargo j
		lw t2,16($fp)					# cargo cols
		bge t1,t2,before_loop_1			# j>=cols -> before_loop_1
		li.d $f4,0
		s.d $f4,32($fp)					# aux=0.0
		li t1,0
		sw t1,8($fp)					# x=0
loop_3:	lw t1,8($fp)					# cargo x
		lw t2,16($fp)					# cargo cols
		bge t1,t2,store_values			# x>=cols -> store_values

		lw t1,0($fp) 					# cargo i
		lw t2,16($fp)					# cargo cols
		mul t3,t1,t2
		sw t3, 20($fp)					# aux1 = i*cols
		lw t1, 20($fp)					# cargo aux1
		lw t2,8($fp)					# cargo x
		addu t3, t1, t2
		sw t3, 24($fp)					# aux2 = aux1 + x
		lw t1, 24($fp)					# cargo aux2
		mul t1, t1, 8					# multiplico por 8 para correrme cada double
		sw t1, 24($fp)

		lw t1,8(a0)						# obtengo la direccion del array

		lw t2, 24($fp)					# cargo aux2
		addu t3,t1,t2
		sw t3,28($fp)
		lw t1, 28($fp)					# cargo aux3
		l.d $f4,0(t1)						# cargo el elemento de la matriz
		s.d $f4,40($fp)					# first = m[...]

		lw t1,8($fp) 					# cargo x
		lw t2,16($fp)					# cargo cols
		mul t3,t1,t2
		sw t3, 20($fp)					# aux1 = x*cols
		lw t1, 20($fp)					# cargo aux1
		lw t2,4($fp)					# cargo j
		addu t3, t1, t2
		sw t3, 24($fp)					# aux2 = aux1 + j
		lw t1, 24($fp)					# cargo aux2
		mul t1, t1, 8					# multiplico por 8 para correrme cada double
		sw t1, 24($fp)

		lw t1,8(a1)						# obtengo la direccion del array

		lw t2, 24($fp)					# cargo aux2
		addu t3,t1,t2
		sw t3,28($fp)
		lw t1, 28($fp)					# cargo aux3
		l.d $f4,0(t1)						# cargo el elemento de la matriz
		s.d $f4,48($fp)					# second = m[...]

		l.d $f4, 40($fp)					# cargo first
		l.d $f6, 48($fp)					# cargo second
		mul.d $f8,$f4,$f6
		l.d $f4, 32($fp)					# cargo aux
		add.d $f4,$f4,$f8
		s.d $f4,32($fp)					# aux = aux + (first*second)

		lw t1,8($fp)					# cargo x
		addu t1,t1,1
		sw t1,8($fp)					# x++
		b loop_3

before_loop_1:
		lw t1,0($fp) 					# cargo i
		addu t1,t1,1
		sw t1,0($fp)					#i++
		b loop_1

store_values:
		lw t1,0($fp) 					# cargo i
		lw t2,16($fp)					# cargo cols
		mul t3,t1,t2
		sw t3,20($fp)					# aux1 = i * cols
		lw t1,20($fp)
		lw t2,4($fp)					# cargo j
		addu t1,t1,t2
		mul t1,t1,8
		sw t1,20($fp)					# aux1 = (aux1 + j)*8
		lw t1,72($fp)					# cargo a2
		addu t1,t1,8					# apunto al array
		lw t1,0(t1)
		lw t2,20($fp)					# cargo aux1
		l.d $f4,32($fp)					# cargo aux
		addu t3,t1,t2
		s.d $f4,0(t3)						# result[aux1]=aux
		lw t1,4($fp)					# cargo j
		addu t1,t1,1
		sw t1,4($fp)
		b loop_2

end:
		lw $fp,60(sp)					# restablezco sp
		addu sp,sp,64					# restablezco stack pointer
		j ra 							# jump and return

.end	matrix_multiply
