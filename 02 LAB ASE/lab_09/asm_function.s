			AREA asm_funct, CODE, READONLY
            EXPORT next_state

			; INPUT:
			; r0 : current_state
			; r1 : taps
			; r2 : &output_bit
			
			; OUTPUT:
			; r0 : new_state
			; r2 : *output_bit

next_state
            PUSH {r4-r7, LR}        ; Save registers and return address
            
            AND r4, r0, #1          ; r4 = current_state & 1
            STR r4, [r2]            ; *output_bit = current_state & 1
			; il risultato va passato per riferimento, quindi lo metto in R1
	
			MOV r7, #0			;inizializzo contatore a 0 

cicle		AND r6, r1, #1		;leggo un elemento dell'array tabs
			LSR r1, r1, #1		;elimino l'elemento letto dall'array taps
			CMP r6, #0			;controllo se il tap va preso in considerazio se != 0
			
			BEQ is_zero			;se diverso da 0 eseguo l'operazione
			LSR r10, r0, r7		;(current_state >> r1.elemento)
			EOR r5, r5, r10  	; r5 = r5 ^ r10
			
is_zero
			ADD r7, r7, #1		; aumento il contatore i
			CMP r7, #8
			BNE cicle
			
			AND r5, r5, #1
			
            ; Compute new_state
            MOV r0, r0, LSR #1      ; r0 = current_state >> 1
            ORR r0, r0, r5, LSL #7  ; new_state = (r0) | (input_bit << 7)
			; inserisco nella 1a posizione a sx, il valore calcolato
			
			
            POP {r4-r7, PC}         ; Restore registers and return
			
			END