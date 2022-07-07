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
cociente:	.quad   0
resto:		.quad   0
formato: .ascii "cociente \t = %11d \t resto \t = %11d   \n" 
  .asciz  "\t = 0x %08x \t    \t = 0x %08x\n" 
formatoq:	.ascii "cociente \t = %11d \t resto \t = %11d   \n" 
  		.asciz  "\t = 0x %016llx \t    \t = 0x %016llx\n"
.section .text
main: .global main

	call trabajar	# subrutina de usuario
	call imprim_C
	call trabajarq
	call imprim_Cq
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
	mov  $0, %eax
	mov  $0, %edx
	mov  $0, %esi 
	mov  $0, %ebp
	mov  $0, %edi
bucle:
	mov   (%ebx,%esi,4),%eax
	cltd
	add   %eax,%ebp
	adc   %edx,%edi
	inc   %esi
	cmp   %esi,%ecx
	jne   bucle
	mov   %ebp,%eax
	mov   %edi,%edx
	idiv  %ecx
	ret

trabajarq:
	mov     $lista, %ebx
	mov  longlista, %ecx
	call mediaq		# == suma(&lista, longlista);
	mov  %rax, cociente
	mov  %rdx, resto
	ret
mediaq:
	mov  $0, %rax
	mov  $0, %rdx
	mov  $0, %esi 
	mov  $0, %rdi
bucleq:
	mov   (%rbx,%rsi,4),%rax # se van moviendo los elementos de la lista en eax
	cltq  # se extiende el signo de eax --> rax
	add   %rax,%rdi # se van sumando los elementos en el acumulador rdi
	inc   %rsi # se actualiza el contador
	cmp   %rsi,%rcx # si el índice llega al final de la lista, se termina el bucle
	jne   bucleq
	mov   %rdi,%rax # tras haber sumado todos los elementos en rdi, se pasa su valor a rax
	cqto  # se extiende el signo de rax --> rdx:rax
	idiv  %rcx # se divide por el número de elementos de la lista, guardándose en rax el cociente y en rdx el resto
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

imprim_Cq:			# requiere libC
	mov   $formatoq, %rdi
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
