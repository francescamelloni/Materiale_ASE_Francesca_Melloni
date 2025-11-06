				
				
				AREA asm_functions, CODE, READONLY				
                EXPORT  get_and_sort
get_and_sort
				; save current SP for a faster access 
				; to parameters in the stack
				MOV   r12, sp
				; save volatile registers
				STMFD sp!,{r4-r8,r10-r11,lr}				
						
				; r0 = vett
				; r1 = val
				; r2 = n

				; r2 = indirizzo della posizione vuota
				; r3 = indirizzo dell'ultima posizione piena
				
				; r1 = 2 (val)
				; n = 4
				; r2 = r0+3
				; r3 = r2 -1
				;    [r3],[r2]
				; 10, 9,   1,  1, X, X, X, X

				; 28, CE

				add r2, r0, r2	
loop			sub r2, r2, #1  ; indirizzo dove potrei inserire r1 (val)
				sub r3, r2, #1	; indirizzo dell'ultima pos vuota
				cmp r0, r3		; confronto gli indirizzi , la prima volta r3 < r0
				bhi fine
				ldrb r4, [r3]	; carico in r4 il valore dell'ultima posizione vuota
				cmp r4, r1
				bhi fine
				strb r4, [r2]
				b loop
				
fine			strb r1, [r2]
				mov r0, r1


				; restore volatile registers
				LDMFD sp!,{r4-r8,r10-r11,pc}
				
                END