#include <mips/regdef.h>
#include <sys/syscall.h>

#----------------------------   40
#////////////////////////////       |
#----------------------------	36  |
#			ra                      |
#----------------------------	32  } SRA 
#		   $fp                      |
#----------------------------	28  | 
#			gp                      |
#----------------------------	24    
#			                    	|
#----------------------------	20  } LTA
#			                    	|
#----------------------------	16  
#			a3                      |
#----------------------------	12  |
#			a2                      |
#----------------------------	8   } ABA    
#			a1                      |
#----------------------------	4   |
#			a0                      |
#----------------------------	0   

		.text
		.abicalls
		.align 2
		.globl print_string
		.ent print_string
print_string:
		.frame $fp, 40, ra
		.set noreorder
		.cpload t9
		.set reorder

		subu sp,sp,40

		.cprestore 24 #Se encarga del gp
		
		sw $fp,28(sp)
		sw ra,32(sp) 
		move $fp,sp

		sw a0,40($fp) #Guardo el file descriptor
		sw a1,44($fp) #Guardo el comienzo del string

		move a0,a1    #Cargo en a1 el comienzo del string
		la t9,strlen
		jal t9        #Llamado a String Length
		
		#Considerar errores en mystrlen

		move a2,v0    #Cargo el tamaño del buffer
		lw a0,40($fp) #Cargo el file descriptor
		lw a1,44($fp) #Cargo el buffer
		li v0,SYS_write
		syscall       #Llamada para el write

		beq a3,zero,fin #Si a3 es cero, v0 contiene la salida requerida por la funcion 

error:	li v0,-1	  #Si a3 no es cero, cargo en v0 el codigo de error -1

fin:	lw gp,24(sp)  #Reestablezco el gp
		lw $fp,28(sp) #Reestablezco el $fp
		lw ra,32(sp)  #Reestablezco la ra
		addu sp,sp,40 #Destruyo el stackframe

		jr ra         #Vuelvo a la direccion de retorno

.end print_string
