;/**************************************************************************//**
; * @file     startup_LPC17xx.s
; * @brief    CMSIS Cortex-M3 Core Device Startup File for
; *           NXP LPC17xx Device Series
; * @version  V1.10
; * @date     06. April 2011
; *
; * @note
; * Copyright (C) 2009-2011 ARM Limited. All rights reserved.
; *
; * @par
; * ARM Limited (ARM) is supplying this software for use with Cortex-M
; * processor based microcontrollers.  This file can be freely distributed
; * within development tools that are supporting such ARM based processors.
; *
; * @par
; * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
; * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
; * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
; * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
; * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
; *
; ******************************************************************************/

; *------- <<< Use Configuration Wizard in Context Menu >>> ------------------

; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00000200

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000200

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3	; 2*3
				
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit


                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors

__Vectors       DCD     __initial_sp              ; Top of Stack
                DCD     Reset_Handler             ; Reset Handler
                DCD     NMI_Handler               ; NMI Handler
                DCD     HardFault_Handler         ; Hard Fault Handler
                DCD     MemManage_Handler         ; MPU Fault Handler
                DCD     BusFault_Handler          ; Bus Fault Handler
                DCD     UsageFault_Handler        ; Usage Fault Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     SVC_Handler               ; SVCall Handler
                DCD     DebugMon_Handler          ; Debug Monitor Handler
                DCD     0                         ; Reserved
                DCD     PendSV_Handler            ; PendSV Handler
                DCD     SysTick_Handler           ; SysTick Handler

                ; External Interrupts
                DCD     WDT_IRQHandler            ; 16: Watchdog Timer
                DCD     TIMER0_IRQHandler         ; 17: Timer0
                DCD     TIMER1_IRQHandler         ; 18: Timer1
                DCD     TIMER2_IRQHandler         ; 19: Timer2
                DCD     TIMER3_IRQHandler         ; 20: Timer3
                DCD     UART0_IRQHandler          ; 21: UART0
                DCD     UART1_IRQHandler          ; 22: UART1
                DCD     UART2_IRQHandler          ; 23: UART2
                DCD     UART3_IRQHandler          ; 24: UART3
                DCD     PWM1_IRQHandler           ; 25: PWM1
                DCD     I2C0_IRQHandler           ; 26: I2C0
                DCD     I2C1_IRQHandler           ; 27: I2C1
                DCD     I2C2_IRQHandler           ; 28: I2C2
                DCD     SPI_IRQHandler            ; 29: SPI
                DCD     SSP0_IRQHandler           ; 30: SSP0
                DCD     SSP1_IRQHandler           ; 31: SSP1
                DCD     PLL0_IRQHandler           ; 32: PLL0 Lock (Main PLL)
                DCD     RTC_IRQHandler            ; 33: Real Time Clock
                DCD     EINT0_IRQHandler          ; 34: External Interrupt 0
                DCD     EINT1_IRQHandler          ; 35: External Interrupt 1
                DCD     EINT2_IRQHandler          ; 36: External Interrupt 2
                DCD     EINT3_IRQHandler          ; 37: External Interrupt 3
                DCD     ADC_IRQHandler            ; 38: A/D Converter
                DCD     BOD_IRQHandler            ; 39: Brown-Out Detect
                DCD     USB_IRQHandler            ; 40: USB
                DCD     CAN_IRQHandler            ; 41: CAN
                DCD     DMA_IRQHandler            ; 42: General Purpose DMA
                DCD     I2S_IRQHandler            ; 43: I2S
                DCD     ENET_IRQHandler           ; 44: Ethernet
                DCD     RIT_IRQHandler            ; 45: Repetitive Interrupt Timer
                DCD     MCPWM_IRQHandler          ; 46: Motor Control PWM
                DCD     QEI_IRQHandler            ; 47: Quadrature Encoder Interface
                DCD     PLL1_IRQHandler           ; 48: PLL1 Lock (USB PLL)
                DCD     USBActivity_IRQHandler    ; 49: USB Activity interrupt to wakeup
                DCD     CANActivity_IRQHandler    ; 50: CAN Activity interrupt to wakeup


                IF      :LNOT::DEF:NO_CRP
                AREA    |.ARM.__at_0x02FC|, CODE, READONLY
CRP_Key         DCD     0xFFFFFFFF
                ENDIF


				AREA    My_data, NOINIT, READWRITE, ALIGN=2
Best_times_ordered SPACE 4*7
Failed_runs_ordered SPACE 4*7	
Temp_best_times SPACE 4*7
Temp_failed_runs SPACE 4*7
	
                AREA    |.text|, CODE, READONLY
				
				
; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]                                            
                
				;your code here

        MOV     R10, #0                  ; Init total failed runs
        MOV     R11, #0                  ; Init qualified days counter
        
        ; Pointers to data 
        LDR     R0, =Best_times          ; R0 points to Best_times array
        LDR     R1, =Failed_runs         ; R1 points to Failed_runs array
        LDR     R2, =Num_days            ; Load the number of days in the week
        LDR     R9, =Best_times_ordered  ; Pointer to the ordered Best_times array
        LDR     R12, =Failed_runs_ordered; Pointer to the ordered Failed_runs array

        ; Temporary arrays for sorting
        LDR     R3, =Temp_best_times
        LDR     R4, =Temp_failed_runs

		LDRB    R2, [R2]                 ; R2 now contains Num_days
        
best_times_loop
        CMP     R2, #0                   ; Check if there are no more days to process
        BEQ     sort_results             ; Exit loop and sort results

        LDR     R5, [R0], #4             ; Load day ID from Best_times
        LDR     R6, [R0], #4             ; Load best time from Best_times
        
        STR     R5, [R3], #4			; Store day ID in Temp_best_times
        STR     R6, [R3], #4			; Store times in Temp_best_times

        MOV     R7, #1300                
        CMP     R6, R7                   ; Compare best time with threshold
        BLT     skip_day                 ; Skip if best time > 1300

        ADD     R11, R11, #1             ; Increment qualified days counter
  
        SUB     SP, SP, #8               ; Save registers into stack
        STR     R0, [SP, #0]
        STR     R2, [SP, #4]
		STR 	R1, [SP, #8] 	

failed_runs_loop
        LDR     R7, [R1], #4             ; Load day ID from Failed_runs
        LDR     R8, [R1], #4             ; Load failed runs for the day
        
        STR     R7, [R4], #4             ; Store day ID in Temp_failed_runs
        STR     R8, [R4], #4             ; Store failed runs in Temp_failed_runs
        
        CMP     R7, R5                   ; Compare IDs
        BNE     failed_runs_loop         ; Continue if IDs do not match

        ADD     R10, R10, R8			; Match found, add to total failed runs
		
        LDR     R0, [SP, #0]			 ; Restore registers from stack
        LDR     R2, [SP, #4]
		LDR 	R1, [SP, #8] 
        ADD     SP, SP, #8

skip_day
        SUBS    R2, R2, #1               ; Decrement number of days
        BNE     best_times_loop          ; Repeat if more days left




sort_results
        ; Sort temporary Best_times array in descending order
        LDR     R3, =Temp_best_times
        MOV     R0, R3                   ; Pass the array pointer
        MOV     R1, #7                   ; Pass the number of elements (Num_days)
        BL      bubble_sort_descending   ; Sort best times

        ; Copy sorted results to Best_times_ordered
        LDR     R3, =Temp_best_times
        LDR     R9, =Best_times_ordered
		
copy_best_times
        LDR     R5, [R3], #4             ; Copy sorted day IDs
        STR     R5, [R9], #4
        LDR     R6, [R3], #4             ; Copy sorted best times
        STR     R6, [R9], #4
        CMP     R2, #0
        BNE     copy_best_times

        ; Sort temporary Failed_runs array in descending order
        LDR     R4, =Temp_failed_runs
        MOV     R0, R4                   ; Pass the array pointer
        MOV     R1, #7                   ; Pass the number of elements (Num_days)
        BL      bubble_sort_descending   ; Sort failed runs

        ; Copy sorted results to Failed_runs_ordered
        LDR     R4, =Temp_failed_runs
        LDR     R12, =Failed_runs_ordered
		
copy_failed_runs
        LDR     R7, [R4], #4             ; Copy sorted day IDs
        STR     R7, [R12], #4
        LDR     R8, [R4], #4             ; Copy sorted failed runs
        STR     R8, [R12], #4
        CMP     R2, #0
        BNE     copy_failed_runs

terminate
	
				LDR     R0, =stop
				
stop            BX      R0
                ENDP


; Bubble Sort Subroutine
bubble_sort_descending
        PUSH    {R4-R7, LR}              ; Save registers
        MOV     R4, R0                   ; R4 points to the array
        MOV     R5, R1                   ; R5 is the number of elements

sort_outer_loop
        SUBS    R5, R5, #1               ; Outer loop count
        BEQ     sort_done                ; Exit if no more passes needed

        MOV     R6, R4                   ; Pointer to the start of the array
        MOV     R7, R5                   ; Inner loop count

sort_inner_loop
        LDR     R0, [R6]                 ; Load current value
        LDR     R1, [R6, #4]             ; Load next value
        CMP     R0, R1                   ; Compare current and next
        BHS     no_swap                  ; Skip swap if already in order

        ; Swap values
        STR     R1, [R6]                 ; Store next in current position
        STR     R0, [R6, #4]             ; Store current in next position

no_swap
        ADD     R6, R6, #4               ; Move to the next pair
        SUBS    R7, R7, #1               ; Decrement inner loop count
        BNE     sort_inner_loop          ; Continue inner loop

        B       sort_outer_loop          ; Repeat outer loop

sort_done
        POP     {R4-R7, PC}              ; Restore registers and return
			

				LTORG
				
				ALIGN 2
					
boundary1 SPACE 4096

Days                DCB 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07

Best_times          DCD 0x06, 1300, 0x03, 1700, 0x02, 1200, 0x04, 1900, 0x05, 1110, 0x01, 1670, 0x07, 1000

Failed_runs         DCD 0x02, 50, 0x05, 30, 0x06, 100, 0x01, 58,0x03, 40, 0x04, 90, 0x07, 25

Num_days           DCB 7


boundary2 SPACE 4096

; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler               [WEAK]

                B       .
				
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler         [WEAK]
                ; your code
				orr r0,r0,#1
				mov r1, r2
				BX	r0
                ENDP
MemManage_Handler\
                PROC
                EXPORT  MemManage_Handler         [WEAK]
                B       .
                ENDP
BusFault_Handler\
                PROC
                EXPORT  BusFault_Handler          [WEAK]
                B       .
                ENDP
UsageFault_Handler\
                PROC
                EXPORT  UsageFault_Handler        [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler               [WEAK]
                B       .
                ENDP
DebugMon_Handler\
                PROC
                EXPORT  DebugMon_Handler          [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler            [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler           [WEAK]
                B       .
                ENDP

Default_Handler PROC

                EXPORT  WDT_IRQHandler            [WEAK]
                EXPORT  TIMER0_IRQHandler         [WEAK]
                EXPORT  TIMER1_IRQHandler         [WEAK]
                EXPORT  TIMER2_IRQHandler         [WEAK]
                EXPORT  TIMER3_IRQHandler         [WEAK]
                EXPORT  UART0_IRQHandler          [WEAK]
                EXPORT  UART1_IRQHandler          [WEAK]
                EXPORT  UART2_IRQHandler          [WEAK]
                EXPORT  UART3_IRQHandler          [WEAK]
                EXPORT  PWM1_IRQHandler           [WEAK]
                EXPORT  I2C0_IRQHandler           [WEAK]
                EXPORT  I2C1_IRQHandler           [WEAK]
                EXPORT  I2C2_IRQHandler           [WEAK]
                EXPORT  SPI_IRQHandler            [WEAK]
                EXPORT  SSP0_IRQHandler           [WEAK]
                EXPORT  SSP1_IRQHandler           [WEAK]
                EXPORT  PLL0_IRQHandler           [WEAK]
                EXPORT  RTC_IRQHandler            [WEAK]
                EXPORT  EINT0_IRQHandler          [WEAK]
                EXPORT  EINT1_IRQHandler          [WEAK]
                EXPORT  EINT2_IRQHandler          [WEAK]
                EXPORT  EINT3_IRQHandler          [WEAK]
                EXPORT  ADC_IRQHandler            [WEAK]
                EXPORT  BOD_IRQHandler            [WEAK]
                EXPORT  USB_IRQHandler            [WEAK]
                EXPORT  CAN_IRQHandler            [WEAK]
                EXPORT  DMA_IRQHandler            [WEAK]
                EXPORT  I2S_IRQHandler            [WEAK]
                EXPORT  ENET_IRQHandler           [WEAK]
                EXPORT  RIT_IRQHandler            [WEAK]
                EXPORT  MCPWM_IRQHandler          [WEAK]
                EXPORT  QEI_IRQHandler            [WEAK]
                EXPORT  PLL1_IRQHandler           [WEAK]
                EXPORT  USBActivity_IRQHandler    [WEAK]
                EXPORT  CANActivity_IRQHandler    [WEAK]

WDT_IRQHandler
TIMER0_IRQHandler
TIMER1_IRQHandler
TIMER2_IRQHandler
TIMER3_IRQHandler
UART0_IRQHandler
UART1_IRQHandler
UART2_IRQHandler
UART3_IRQHandler
PWM1_IRQHandler
I2C0_IRQHandler
I2C1_IRQHandler
I2C2_IRQHandler
SPI_IRQHandler
SSP0_IRQHandler
SSP1_IRQHandler
PLL0_IRQHandler
RTC_IRQHandler
EINT0_IRQHandler
EINT1_IRQHandler
EINT2_IRQHandler
EINT3_IRQHandler
ADC_IRQHandler
BOD_IRQHandler
USB_IRQHandler
CAN_IRQHandler
DMA_IRQHandler
I2S_IRQHandler
ENET_IRQHandler
RIT_IRQHandler
MCPWM_IRQHandler
QEI_IRQHandler
PLL1_IRQHandler
USBActivity_IRQHandler
CANActivity_IRQHandler

                B       .

                ENDP


                ALIGN


; User Initial Stack & Heap

                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit                

                END