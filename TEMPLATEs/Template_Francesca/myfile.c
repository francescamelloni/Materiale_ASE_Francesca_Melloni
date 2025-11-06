
/***********************************************************
************************************************************
************************************************************

FILE DA CANCELLARE

************************************************************
************************************************************
***********************************************************
~
UTILIZZO TIMER
LPC_SC -> PCONP |= (1<<22);	// abilita TIMER2
LPC_SC -> PCONP |= (1<<23); // abilita TIMER3
init_timer(num_timer, prescaler, matchreg, SRI, Period*25M); 	
enable_timer(num_timer);

val_decimi = val_tc / 2500000;  x averto in decimi (6 zeri->secondi, 3->milli)

PRENDI VALORE DA TIMER
disable_timer(0);
val_tc = LCP_TIM0->TC; //prende il valore di Timer0 
enable_timer(0);

SHIFT(vedi prova esame)
val_char = ( val_int & 0x00FF0000) >> 16; prende dal bit 23 a 16
val_led = ( val_tim3 & 0x0000FF00) >> 8;prende dal bit 15 a 8
val = (uint8_t)( val_tim >> 3) & 0xFF;  //prendO dal bit 3 a 10

var_31_24 = (var & 0xFF000000) >> 24;
var_23_16 = (var & 0x00FF0000) >> 16;
var_15_8  = (var & 0x0000FF00) >> 8;
var_7_0   = var & 0x000000FF;

BLINKING DEI LED
int led_areON=0;

	if(led_areON){
		LED_Out(0);
		led_areON=0;
	}
	else if(!led_areON){
		LED_Out(7);
		led_areON=1;
	}

		
NEL RIT, SE PREMUTO PER PIU DI TOT SEC
	if (down_x<40){
			
		}
	else if(down_x>40 && down_x<60){
				
	}
	else if(down_x>60){
		
	}

AREA nome, DATA, READWRITE
	nomevettore SPACE #byte
					
	END
		
ARM
r0->vett, r4->i
char/unsigned char (8 bit) 	LDRB Rx, [R0, R4] - STRB Rx, [R0, R4]
int/unsigned int (32 bit)		LDR Rx, [R0, R4, lsl #2] - STR Rx, [R0, R4, lsl #2]
unsigned short int (16 bit) LDRH Rx, [R0, R4, lsl #1] - STRH Rx, [R0, R4, lsl #1]
cambiare un puntatore STR R2, [R8] dove r2 è il puntatore


LDRx R4,[SP,#0] 1° dello stack
LDRx R5,[SP,#x] 2° dello stack (x=1 se 8 bit, x=2 se 16 bit, x=4 se 32 bit)

AND R8,R7,#1 ultimo bit pari
EOR R8,R0,#1 scambiare 1-0 
********************************************************************************************************************+

****ASM_FUNCT in generale:

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

********************************************************************************************************************+
*******DIFF_MAX_MIN di un buffer che ha elementi fino al final_index

				AREA asm_functions, CODE, READONLY				
                EXPORT  diff_max_min
diff_max_min
				; save current SP for a faster access 
				; to parameters in the stack
				MOV   r12, sp
				; save volatile registers
				STMFD sp!,{r4-r8,r10-r11,lr}				
						
				; r0 = buffer
				; r1 = final_index
			
				MOV R2,#0		;i=0
				MOV R4,#0		;min=0
				MOV R5,#0		;max=0
				
loop			LDR R3,[R0,R2,lsl#2]		;carico il primo valore
				CMP R3,R4					; R3<R4?
				MOVLT R4,R3					; SI? R3 � il minimo
				CMP R3,R5					; R3>R5?
				MOVGT R5,R3					; SI? R3 � il massimo
				
				ADD R2,R2,#1				; i++
				CMP R2,R1					; i<=final_index
				BLE loop					; SI? loop
					
end_func		SUB R6, R5, R4				; NO? Fine. Sub
				MOV R0, R6

				; restore volatile registers
				LDMFD sp!,{r4-r8,r10-r11,pc}
				
                END
				
********************************************************************************************************************+							
***GET_AND_SORT: i valori maggiori devono occupare le posizioni meno significative
			del vettore, alla posizione 0 risulta essere memorizzato il massimo attuale.
				
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



********************************************************************************************************************+
;CONTATORE_INRANGE
;tale funzione riceve come parametri il vettore VETT, N e serve a elaborare i valori in VETT.
;La funzione restituisce il numero dei valori registrati che cadono strettamente tra i valori memorizzati in VETT[0] e VETT[N-1] 
;(che vanno esclusi dal conteggio). Tale valore è espresso su 8 bit.

    AREA asm_functions, CODE, READONLY				
				EXPORT  contatore_inrange	
contatore_inrange
				; Salva lo stack pointer corrente per un accesso più rapido ai parametri nello stack
				MOV   r12, sp
				; Salva i registri volatili
				STMFD sp!,{r4-r8,r10-r11,lr}				
				
				; r0 = vett
				; r1 = N
				
				MOV r3, #0                  ; r3 -> cnt = 0
				MOV r4, #0                  ; r4 -> i = 0
				
				ADD r9, r1, #-1             ; r9 = N - 1
				
				LDR r5,[r0, r4, lsl #2]     ; r5 = vett[0]
				LDR r6,[r0, r9, lsl #2]     ; r6 = vett[N-1]
				
				; Determina il minimo e massimo tra vett[0] e vett[N-1]
				CMP r5, r6
				BLT skip_swap
				MOV r7, r5                  ; temp = r5
				MOV r5, r6                  ; r5 = r6
				MOV r6, r7                  ; r6 = temp
skip_swap

				; Ora r5 contiene il minimo e r6 il massimo
loop
				ADD r4, r4, #1              ; i++
				CMP r4, r9                  ; Controlla se siamo arrivati a N-1
				BGE end_loop                ; Se i >= N-1, esce dal ciclo
				
				LDR r7, [r0, r4, lsl #2]    ; r7 = vett[i]
				CMP r7, r5
				BLE loop                    ; Se r7 <= r5, salta alla prossima iterazione
				CMP r7, r6
				BGE loop                    ; Se r7 >= r6, salta alla prossima iterazione
				
				ADD r3, r3, #1              ; Altrimenti, incrementa cnt

				B loop                      ; Ripeti il ciclo
end_loop
				MOV r0, r3                  ; Ritorna il valore di cnt
				
				; Ripristina i registri volatili
				LDMFD sp!,{r4-r8,r10-r11,pc}

				END

*********************************************************************************************************************
;ANALISI_ACCURATEZZA
;tale funzione riceve come parametri i vettori VETT e VETT2, N, e RES,  con N lunghezza massima dei vettori. 
;La funzione serve a calcolare l’accuratezza nelle pressioni da parte dell’utente. 
;La funzione restituisce in RES[i] la distanza temporale (in decimi di secondo e in valore assoluto) tra VETT[i] e VETT2[i], 
;cioè la differenza tra il tempo di pressione richiesto e il tempo di pressione effettivo. 
;Inoltre, la funzione deve ritornare come valore di ritorno la media aritmetica dei valori contenuti in RES.

				AREA asm_functions, CODE, READONLY				
                EXPORT  analisi_accuratezza

analisi_accuratezza
				; save current SP for a faster access 
				; to parameters in the stack
				MOV   r12, sp
				; save volatile registers
				STMFD sp!,{r4-r8,r10-r11,lr}				
						
				; r0 = vett
				; r1 = vett2
				; r2 = N
				; r3 = res
				MOV R4, #0	; i=0
				MOV R6, #0	; sumRES=0
			
loop 			LDRB R7, [R0, R4] 	; prendo vett[i]
				LDRB R8, [R1, R4] 	; prendo vett2[i]
				CMP R7, R8			; vedo se R7<R8
				BLT switch			; SI? scambiali
				
				SUB R7,R7, R8		; NO? Fai sottrazione 
				B continue			; e continua
switch			SUB R7,R8, R7		; li scambio se R7<R8

continue		STRB R7, [R3, R4]	; carico la SUB in res[i]
				ADD R6,R6,R7		; Aggiorno sumRES
				ADD R4,R4,#1		; i++
				
				CMP R4, R2			; i==N?
				BNE loop			; NO? torna a loop
				

end_loop		UDIV R0,R6,R2		; val_return = avg	(sumRES/N)
				; restore volatile registers
				LDMFD sp!,{r4-r8,r10-r11,pc}
				
                END

*********************************************************************************************************************
;CALCOLA_SOMMA_PRODOTTO
				AREA asm_functions, CODE, READONLY				
                EXPORT  calcola_somma_prodotto
					
calcola_somma_prodotto

				; save current SP for a faster access 
				; to parameters in the stack
				MOV   r12, sp
				; save volatile registers
				STMFD sp!,{r4-r8,r10-r11,lr}				
						
				; r0 = vett
				; r1 = N
				; r2 = alarm

				MOV R3,#0		;result
				MOV R4,#0		;i=0
				
loop			LDR R5,[R0,R4,lsl#2]
				ADD R4,R4,#1
				LDR R6,[R0,R4,lsl#2]
				ADD R4,R4,#1
				
				MUL R7, R5, R6
				ADD R3, R3, R7
				
				
				CMP R4,R1
				BNE loop
				
				
				CMP R3, #255
				
				ADDLT R4,R4,#-1
				ADDGT R4,R4,#1
				STRB R4,[r2]
				MOV R0,R3		; restituisco result
				
				; restore volatile registers
				LDMFD sp!,{r4-r8,r10-r11,pc}
				
                END
				

*********************************************************************************************************************
;PRESSIONE CON FILTRO

				AREA asm_functions, CODE, READONLY				
                EXPORT  totale_pressioni_con_filtro
					
totale_pressioni_con_filtro
				; save current SP for a faster access 
				; to parameters in the stack
				MOV   r12, sp
				; save volatile registers
				STMFD sp!,{r4-r8,r10-r11,lr}				
						
				; r0 = vett
				; r1 = numero_misure
				; r2 = max
				; r3 = min
				
				MOV R4, #0			; i=0
				MOV R5, #0			; result
				
loop			LDRB R6, [R0, R4]	; vett[i]
				CMP R6,R3			; vett[i] < min
				BLT back_to_loop
				
				CMP R6,R2			; vett[i] > max
				BGT back_to_loop
				
				ADD R5,R5,R6		; result =+ vett[i]	
back_to_loop	ADD R4,R4,#1		; i++
				CMP R4,R1			; i<N
				BLT loop
				
end_loop		MOV R0, R5

				; restore volatile registers
				LDMFD sp!,{r4-r8,r10-r11,pc}
				
                END
								
*********************************************************************************************************************
;STAT_SATISFACTION
	AREA asm_functions, CODE, READONLY				
                EXPORT  stat_satisfaction	;change function name
stat_satisfaction
				; save current SP for a faster access 
				; to parameters in the stack
				MOV   r12, sp
				; save volatile registers
				STMFD sp!,{r4-r8,r10-r11,lr}				
						
				; r0 = S
				; r1 = N
				; r2 = I
				; r3 = *PS
				; r4 = *PI				
				; r5 = *PN
				
				; extract argument 4 and 5 into R4 and R5
				LDR   r4, [r12] ; r4 = PN
				LDR   r5, [r12,#4]; r5 = PI
				
				ADD r6,r0,r1
				ADD r6,r6,r2		; r6 = s+n+i
				
				MOV r10, #100
				
				MUL r0,r0,r10
				UDIV r7,r0,r6
				STRB r7, [r3]
				
				MUL r1,r1,r10
				UDIV r7,r1,r6
				STRB r7, [r4]
				
				MUL r2,r2,r10
				UDIV r7,r2,r6
				STRB r7, [r5]
				
				MOV r0,r6

							
; restore volatile registers
				LDMFD sp!,{r4-r8,r10-r11,pc}
				
                END
								
*********************************************************************************************************************
;CONCAT_SUM

				AREA asm_functions, CODE, READONLY				
                EXPORT  concat_sum

concat_sum
				;save current SP for a faster access 
				; to parameters in the stack
				MOV   r12, sp
				; save volatile registers
				STMFD sp!,{r4-r8,r10-r11,lr}				
						
				; r0 = vett
				; r1 = i
				; r2 = alarm
				MOV R3, #0 	; result
				MOV R4, #0	; index
				
				
loop 			LDRH R5, [R0,R4,lsl#1]  ; carico elemento
				ADD R4,R4,1				;i++
				
				CMP R4, R1
				BGE handle_odd
				
				LDRH R6, [R0,R4,lsl#1]  ; carico elemento
				ADD R4,R4,1
				ORR R5, R5, R6, lsl #16
				
				CMP R4, R1
				BGE end_loop
				
handle_odd      MOV R7, #0        
				ORR R5, R5, R7, lsl #16  

end_loop		controllo overflow??
				
				STRB OVERFLOW,[R2]
				MOV R0,R3
				; restore volatile registers
				LDMFD sp!,{r4-r8,r10-r11,pc}
				
                END
								
*********************************************************************************************************************
;COMPRESS

				AREA asm_functions, CODE, READONLY				
                EXPORT  compress
compress
				; save current SP for a faster access 
				; to parameters in the stack
				MOV   r12, sp
				; save volatile registers
				STMFD sp!,{r4-r8,r10-r11,lr}				
						
				; r0 = vett
				; r1 = N
				; r2 = res
				
				MOV R3, #0	; i=0 per vett
				MOV R4, #0	; j=0 per res
				MOV R5, #0	; val_return=0
			
loop			LDR R6,[R0,R3,lsl#2]	;prendo vett[i]
				ADD R3,R3,#1			;i++
				LDR R7,[R0,R3,lsl#2]	;prendo vett[i+1]
				
				SUBS R6,R6,R7			; diff vett[i] e vett[i+1]
				
				CMP R6,#0				; sub<0
				ADDLT R5,R5,#1			; val_return ++
				
				STR R6,[R2,R4,lsl#2]
				ADD R4,R4,#1
				
end_loop		MOV R0,R4
				
				; restore volatile registers
				LDMFD sp!,{r4-r8,r10-r11,pc}
				
                END
								
*********************************************************************************************************************
;AVG_VETT
							AREA asm_functions, CODE, READONLY				
                EXPORT  avg_vett
avg_vett
				; save current SP for a faster access 
				; to parameters in the stack
				MOV   r12, sp
				; save volatile registers
				STMFD sp!,{r4-r8,r10-r11,lr}				
						
				; r0 = vett
				; r1 = dim
				; r2 = flag
				
				MOV R4, #0	; i=0
				MOV R5, #0 	; sum=0
				MOV R6, #0	; count=0 da return
				
				
loop			LDR R7, [R0, R4, lsl #2]	;prendo vett[i]
				ADD R5,R5,R7
				ADD R4,R4,#1
				CMP R4,R1
				BNE loop
				MOV R4, #0		; i=0
				UDIV R5,R5,R1	; r5 avg	
				
check_avg		LDR R7, [R0, R4, lsl #2]
				CMP R7, R5
				ADDGT R6,R6,#1
				ADD R4,R4,#1				
				CMP R4,R1
				BNE check_avg
	
end_loop		MOV R0,R5
				AND R8,R7,#1
				EOR R8,R0,#1
				STR R2, [R8]
				
				; restore volatile registers
				LDMFD sp!,{r4-r8,r10-r11,pc}
				
                END
*********************************************************************************************************************
;CONCAT_SUM
*********************************************************************************************************************
;CONCAT_SUM
								
								

void LED_Out_Neg(unsigned int value) {
  int i;

  for (i = 0; i < LED_NUM; i++) {
    if (value & (1<<i)) {
      LED_Off (i);
    } else {
      LED_On(i);
    }
  }
	led_value = value;
}


void LED_Out_Inverted(unsigned int value){
	int i;
	
  for (i = 0; i < LED_NUM; i++) {
    if (value & (1<<(LED_NUM - 1 - i ) )) {
      LED_On(i);
    } else {
      LED_Off(i);
    }
  }
	led_value = value;
}

*/


