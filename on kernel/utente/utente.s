129,157d128
< 
< # chiamata assembly della funzione intriseca clflush
< 	.global clflush
< clflush:
< 	clflush (%rdi)
< 	ret
< 
< 
< # chiamata assembly della funzione intriseca mfence
< 	.global mfence
< mfence:
< 	mfence
< 	ret
< 
< 
< # chiamata assembly della funzione intriseca rdtsc
< 	.global rdtscp
< rdtscp:
< rdtscp
< 	shl $32, %rdx
< 	MOV %eax, %edx
< 	MOV %rdx, %rax
< 	ret
< 
< # tesi
< 	.global victim_function
< victim_function:
< 	int $TIPO_VICTIM
< 	ret
