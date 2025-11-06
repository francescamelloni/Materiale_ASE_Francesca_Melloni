				AREA asm_functions, CODE, READONLY				
                EXPORT  nome_funct
nome_funct
				; save current SP for a faster access 
				; to parameters in the stack
				MOV   r12, sp
				; save volatile registers
				STMFD sp!,{r4-r8,r10-r11,lr}				
						
				; r0 = buffer
				; r1 = final_index
			
loop

end_loop
				; restore volatile registers
				LDMFD sp!,{r4-r8,r10-r11,pc}
				
                END
