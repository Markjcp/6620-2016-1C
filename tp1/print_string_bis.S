#include <mips/regdef.h>
#include <sys/syscall.h>

#----------------------------   48
#////////////////////////////       |
#----------------------------	44  |
#			ra #Si es leaf no hace falta|
#----------------------------	40  } SRA 
#		   $fp                      |
#----------------------------	36  | 
#			gp                      |
#----------------------------	32  
#			                    |
#---------------------------- 	28  |
#			                    |
#----------------------------	24  } LTA 
#			                    |
#----------------------------	20  |
#			                    |
#----------------------------	16  
#			a3                      |
#----------------------------	12  |
#			a2                      |
#----------------------------	8   } ABA   Si es leaf no hace falta 
#			a1                      |
#----------------------------	4   |
#			a0                      |
#----------------------------	0   

		.text
		.abicalls
		.align 2
		.global print_string
		.ent print_string
print_string:
		.frame $fp, 68, ra
		.set noreorder
		.cpload t9
		.set reorder

		subu sp,sp,68

		.cprestore 60 #Se encarga del gp
		
		sw $fp,64(sp)
		sw ra,68(sp) 
		move $fp,sp

		sw a0,72($fp) #file descriptor
		sw a1,76($fp) #string

		li t0,0		  #t0 = 0 offset del string
		lw t1,72($fp) #t1 <- Comienzo del string
		lb t2,fin_string #t2 <- simbolo fin_string
loop:	add t3,t0,t1  #t3 <- posicion actual del string en memoria
		lb t4,t3	  #t4 <- caracter correspondiente a la posicion actual
		addi t0,t0,1  #incremento el offset
		bne t2,t4,loop#Si el caracter es distinto a fin de string sigo en el loop

		sub t0,t0,1 #Guardo en t0 el offset correspondiente al fin de string que coincide con el tamaño del string

		#lw a0,68($fp) #Cargo el file descriptor
		#lw a1,72($fp) #Cargo el buffer
		move a2,t0    #Cargo el tamaño del buffer
		li v0,sys_write
		syscall       #Llamada para el write

		be a3,zero,fin #Si a3 es cero, v0 contiene la salida requerida por la funcion 

error:	li v0,-1	  #Si a3 no es cero, cargo en v0 el codigo de error -1

fin:	lw gp,60(sp)  #Reestablezco el gp
		lw $fp,64(sp) #Reestablezco el $fp
		lw ra,68(sp)  #Reestablezco la ra
		addu sp,sp,68 #Destruyo el stackframe

		jr ra         #Vuelvo a la direccion de retorno

		.end print_string

		.rdata
		.align 2
fin_string: .ascii "/0"