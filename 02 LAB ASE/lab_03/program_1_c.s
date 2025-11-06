.data

v1: .double 2.3, 7.1, 4.8, 9.6, 1.2
    .double 3.7, 8.4, 2.9, 5.1, 6.3
    .double 7.8, 1.5, 4.2, 9.0, 3.6
    .double 5.4, 2.7, 8.1, 6.9, 1.3
    .double 4.5, 7.2, 3.9, 5.8, 2.1
    .double 6.7, 1.4, 9.3, 4.6, 8.5
    .double 3.2, 7.9

v2: .double 5.4, 2.8, 7.1, 3.6, 9.2
    .double 1.5, 4.7, 8.3, 6.1, 2.9
    .double 5.8, 7.4, 3.2, 9.0, 1.7
    .double 4.5, 8.6, 6.3, 2.1, 5.9
    .double 7.3, 3.8, 9.1, 1.4, 4.6
    .double 8.2, 6.5, 2.7, 5.1, 7.6
    .double 3.4, 9.5

v3: .double 6.2, 3.5, 8.1, 4.7, 9.3
    .double 2.4, 7.6, 5.8, 1.9, 6.4
    .double 3.7, 8.5, 4.1, 9.7, 2.3
    .double 7.9, 5.2, 1.6, 6.8, 3.9
    .double 8.4, 4.3, 9.6, 2.5, 7.1
    .double 5.4, 1.8, 6.9, 3.2, 8.7
    .double 4.6, 9.8

v4: .space 256
v5: .space 256
v6: .space 256

m:  .word 1

a:  .space 8
b:  .double 2.0

.text
daddi R1, R0, 31            ; i=31 R1 o f10
daddi R2, R0, 248           ; indice array
daddi R3, R0, 3             ; divisor

loop:
    l.d      f1, v1(R2)        ; Carica v1[i]
    l.d      f2, v2(R2)        ; Carica v2[i]
    l.d      f3, v3(R2)        ; Carica v3[i]
    lb       R6, m(R0)         ; Carico m 
    mtc1     R1, f10           ; move i to FP register
    cvt.d.l  f10, f10           ; convert f10 to 64-bit double

    check_div:    
    ddiv     R4, R1, R3         ; resto di v1/3 in R4
    dmul     R4, R4, R3
    beq      R4, R1, multiple_of_3 ; Se R3 == 0, divisibile
    j        not_multiple_of_3      ; Se R3 != 0, NON divisibile

multiple_of_3:   
    dsllv    R7, R6, R1         ; m<<i
    mtc1     R7, f7             ; move R7 to FP register
    cvt.d.l  f7, f7              ; convert f7 to 64-bit double
    div.d    f9, f1, f7          ; f9=v1[i]/(double)m<<i
    j        for

not_multiple_of_3:
    mtc1     R6, f7              ; move m to FP register
    cvt.d.l  f7, f7              ; convert f10 to 64-bit double    
    mul.d    f8, f7, f10         ; m*i
    mul.d    f9, f1, f8          ; f9=v1[i]*(double)m*i    
    j        for

for:    
    s.d      f9, a(R0)          ; a=f9
    cvt.l.d  f9, f9              ; (int)a, convert f9 to 64-bit int
    mul.d    f4, f9, f1          ; a*v1[i]
    s.d      f9, m(R0)          ; m=(int)a    
    sub.d     f4, f4, f2         ; -v2[i]
    s.d      f4, v4(R2)          ; v4[i]=        
    div.d    f5, f4, f3          ; v4[i]/v3[i]
    l.d      f12, b(R0)          ; Carica b
    sub.d    f5, f5, f12          ; -b
    s.d      f5, v5(R2)          ; v5[i]=
    sub.d    f6, f4, f1          ; v4[i]-v1[i]
    mul.d    f6, f6, f5          ; *v5[i]
    s.d      f6, v6(R2)          ; v6[i]=

    # Unroll for second iteration
    daddi 	  R2, R2,-8
    daddi R1,R1,-1
    l.d      f1, v1(R2)        ; Carica v1[i-1]
    l.d      f2, v2(R2)        ; Carica v2[i-1]
    l.d      f3, v3(R2)        ; Carica v3[i-1]
    lb       R6, m(R0)          ; Carico m 
    mtc1     R1, f10             ; move i-1 to FP register
    cvt.d.l  f10, f10            ; convert f10 to 64-bit double

    check_div2:    
    ddiv     R4, R1, R3          ; resto di v1[i-1]/3 in R4
    dmul     R4, R4, R3
    beq      R4, R1, multiple_of_32 ; Se R3 == 0, divisibile
    j        not_multiple_of_32      ; Se R3 != 0, NON divisibile

multiple_of_32:   
    dsllv    R7, R6, R1          ; m<<i
    mtc1     R7, f7              ; move R7 to FP register
    cvt.d.l  f7, f7               ; convert f7 to 64-bit double
    div.d    f9, f1, f7           ; f9=v1[i-1]/(double)m<<i
    j        for2

not_multiple_of_32:
    mtc1     R6, f7              ; move m to FP register
    cvt.d.l  f7, f7              ; convert f10 to 64-bit double    
    mul.d    f8, f7, f10         ; m*i
    mul.d    f9, f1, f8          ; f9=v1[i-1]*(double)m*i    
    j        for2

for2:    
    s.d      f9, a(R0)          ; a=f9
    cvt.l.d  f9, f9              ; (int)a, convert f9 to 64-bit int
    mul.d    f4, f9, f1          ; a*v1[i-1]
    s.d      f9, m(R0)          ; m=(int)a    
    sub.d     f4, f4, f2         ; -v2[i-1]
    s.d      f4, v4(R2)        ; v4[i-1]=        
    div.d    f5, f4, f3          ; v4[i-1]/v3[i-1]
    l.d      f12, b(R0)          ; Carica b
    sub.d    f5, f5, f12          ; -b
    s.d      f5, v5(R2)        ; v5[i-1]=
    sub.d    f6, f4, f1          ; v4[i-1]-v1[i-1]
    mul.d    f6, f6, f5          ; *v5[i-1]
    s.d      f6, v6(R2)        ; v6[i-1]=

    # Unroll for third iteration
daddi 	  R2, R2,-8
daddi R1,R1,-1
    l.d      f1, v1(R2)       ; Carica v1[i-2]
    l.d      f2, v2(R2)       ; Carica v2[i-2]
    l.d      f3, v3(R2)       ; Carica v3[i-2]
    lb       R6, m(R0)           ; Carico m 
    mtc1     R1, f10              ; move i-2 to FP register
    cvt.d.l  f10, f10             ; convert f10 to 64-bit double

    check_div3:    
    ddiv     R4, R1, R3          ; resto di v1[i-2]/3 in R4
    dmul     R4, R4, R3
    beq      R4, R1, multiple_of_33 ; Se R3 == 0, divisibile
    j        not_multiple_of_33      ; Se R3 != 0, NON divisibile

multiple_of_33:   
    dsllv    R7, R6, R1          ; m<<i
    mtc1     R7, f7              ; move R7 to FP register
    cvt.d.l  f7, f7               ; convert f7 to 64-bit double
    div.d    f9, f1, f7           ; f9=v1[i-2]/(double)m<<i
    j        for3

not_multiple_of_33:
    mtc1     R6, f7              ; move m to FP register
    cvt.d.l  f7, f7              ; convert f10 to 64-bit double    
    mul.d    f8, f7, f10         ; m*i
    mul.d    f9, f1, f8          ; f9=v1[i-2]*(double)m*i    
    j        for3

for3:    
    s.d      f9, a(R0)          ; a=f9
    cvt.l.d  f9, f9              ; (int)a, convert f9 to 64-bit int
    mul.d    f4, f9, f1          ; a*v1[i-2]
    s.d      f9, m(R0)          ; m=(int)a    
    sub.d     f4, f4, f2         ; -v2[i-2]
    s.d      f4, v4(R2)       ; v4[i-2]=        
    div.d    f5, f4, f3          ; v4[i-2]/v3[i-2]
    l.d      f12, b(R0)          ; Carica b
    sub.d    f5, f5, f12          ; -b
    s.d      f5, v5(R2)       ; v5[i-2]=
    sub.d    f6, f4, f1          ; v4[i-2]-v1[i-2]
    mul.d    f6, f6, f5          ; *v5[i-2]
    s.d      f6, v6(R2)       ; v6[i-2]=
	daddi R1,R1,-1
	daddi R2,R2,-8
    slt      R3, R2, R0          ; Controlla se siamo a zero
    beqz     R3, loop            ; Se non è zero ricomincio
    
halt