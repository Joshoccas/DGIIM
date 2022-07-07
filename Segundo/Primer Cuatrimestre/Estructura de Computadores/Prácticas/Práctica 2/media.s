.section .data
#ifndef TEST
#define TEST 20
#endif
.macro linea
	#if TEST==1
		.int 1,2,1,2
	#elif TEST==2
		.int -1,-2,-1,-2
	#elif TEST==3
		.int 0x7fffffff,0x7fffffff,0x7fffffff,0x7fffffff
	#elif TEST==4
		.int 0x80000000,0x80000000,0x80000000,0x80000000
	#elif TEST==5
		.int 0xffffffff,0xffffffff,0xffffffff,0xffffffff
	#elif TEST==6
		.int 2000000000,2000000000,2000000000,2000000000
	#elif TEST==7
		.int 3000000000,3000000000,3000000000,3000000000
	#elif TEST==8
		.int -2000000000,-2000000000,-2000000000,-2000000000
	#elif TEST==9
		.int -3000000000,-3000000000,-3000000000,-3000000000
	#elif TEST>=10 && TEST<=14
		.int 1,1,1,1
	#elif TEST>=15 && TEST<=19
		.int -1,-1,-1,-1
	#else
		.error "Definir TEST entre 1 y 19"
	#endif
.endm

.macro linea0
	#if TEST>=1 && TEST <=9
		linea
	#elif TEST==10
		.int 0,2,1,1
	#elif TEST==11
		.int 1,2,1,1
	#elif TEST==12
		.int 8,2,1,1
	#elif TEST==13
		.int 15,2,1,1
	#elif TEST==14
		.int 16,2,1,1
	#elif TEST==15
		.int 0,-2,-1,-1
	#elif TEST==16
		.int -1,-2,-1,-1
	#elif TEST==17
		.int -8,-2,-1,-1
	#elif TEST==18
		.int -15,-2,-1,-1
	#elif TEST==19
		.int -16,-2,-1,-1
	#else
		.error "Definir TEST entre 1 y 19"
	#endif
		
.endm

lista:		linea0		
		.irpc i,123
			linea
		.endr
	
longlista:	.int   (.-lista)/4
cociente:	.int   0
resto:		.int   0
formato: .ascii "cociente \t = %11d \t resto \t = %11d   \n" 
  .asciz  "\t = 0x %08x \t    \t = 0x %08x\n" 
.section .text
main: .global main

	call trabajar	# subrutina de usuario
	call imprim_C
	call acabar_C	# exit()   del kernel Linux
	ret

trabajar:
	mov     $lista, %ebx
	mov  longlista, %ecx
	call media		# == suma(&lista, longlista);
	mov  %eax, cociente
	mov  %edx, resto
	ret

media:
	mov  $0, %eax # registro sobre el que se va sumando
	mov  $0, %edx # registro para acumular los acarreos
	mov  $0, %esi # índice que permite recorrer la lista
	mov  $0, %ebp # ebp y edi son acumuladores, en edi se van almacenando los acarreos
	mov  $0, %edi
bucle:
	mov   (%ebx,%esi,4),%eax # se van moviendo los elementos de la lista en eax
	cltd  # se pasa a doble precisión el elemento recién leído
	add   %eax,%ebp # se suma el contenido de eax al acumulador ebp
	adc   %edx,%edi # se suma el acarreo al acumulador edi
	inc   %esi      # se actualiza el contador
	cmp   %esi,%ecx # si el índice llega al final de la lista, se termina el bucle
	jne   bucle
	mov   %ebp,%eax # finalmente se guardan los valores de los acumuladores en los registros eax y edx
	mov   %edi,%edx
	idiv  %ecx      # se divide por el número de elementos de la lista, guardándose en eax el cociente y en edx el resto
	ret

imprim_C:			# requiere libC
	mov   $formato, %rdi
	mov   cociente,%rsi
	mov   resto,%rdx
	mov   cociente,%rcx
	mov   resto,%r8
	mov          $0,%eax	# varargin sin xmm
	call  printf		# == printf(formato, res, res);
	ret

acabar_C:			# requiere libC
	mov cociente, %edi
	call _exit		# ==  exit(resultado)
	ret
