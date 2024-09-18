section .rodata
rojo:
 dd 0.2126, 0.2126, 0.2126, 0.2126
azul:
 dd 0.7152, 0.7152, 0.7152, 0.7152
verde:
 dd 0.0722, 0.0722, 0.0722, 0.0722
; Poner acá todas las máscaras y coeficientes que necesiten para el filtro
shuffle:
	db 0x00, 0x00, 0x00, 0x80, 0x01, 0x01, 0x01, 0x80, 0x02, 0x02, 0x02, 0x80 , 0x03, 0x03, 0x03, 0x80

alfas:
    db 0, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0, 255
 
section .text

; Marca un ejercicio como aún no completado (esto hace que no corran sus tests)
FALSE EQU 0
; Marca un ejercicio como hecho
TRUE  EQU 1

; Marca el ejercicio 1 como hecho (`true`) o pendiente (`false`).
;
; Funciones a implementar:
;   - ej1
global EJERCICIO_1_HECHO
EJERCICIO_1_HECHO: db TRUE ; Cambiar por `TRUE` para correr los tests.

; Convierte una imagen dada (`src`) a escala de grises y la escribe en el
; canvas proporcionado (`dst`).
;
; Para convertir un píxel a escala de grises alcanza con realizar el siguiente
; cálculo:
; ```
; luminosidad = 0.2126 * rojo + 0.7152 * verde + 0.0722 * azul 
; ```
;
; Como los píxeles de las imágenes son RGB entonces el píxel destino será
; ```
; rojo  = luminosidad
; verde = luminosidad
; azul  = luminosidad
; alfa  = 255
; ```
;
; Parámetros:
;   - dst:    La imagen destino. Está a color (RGBA) en 8 bits sin signo por
;             canal.
;   - src:    La imagen origen A. Está a color (RGBA) en 8 bits sin signo por
;             canal.
;   - width:  El ancho en píxeles de `src` y `dst`.
;   - height: El alto en píxeles de `src` y `dst`.
global ej1
ej1:
    ; rdi = dst
	; rsi = src
	; rdx = width
	; rcx = heigth
	; epilogo
	push rbp
	;quiero calcular la cantidad de pixeles
	mov r8, rdx
	mov r9, rcx
	imul r8, r9 ; Cant. de pixeles
	imul r8, 4 ; Cant. de pixeles * sizeof(pixel) (4 bytes)	== cant. de bytes que tengo que procesar
	add r10, 0
loop:
	; computo. 
	movaps xmm0, [rsi] ; rojo
	; xmm0 := 127 [A,B,G,R,
	;			   A,B,G,R,
	; 			   A,B,G,R,
	; 			   A,B,G,R] 0

	;NOO xmm0 := 127 [R,G,B,A,
    ;			   R,G,B,A,
	;			   r,g,b,a,
	;			]
	movaps xmm1, xmm0 ; verde
	movaps xmm2, xmm0 ; azul
	

	;shifteos elemntwise

    PSLLD xmm0, 24
    PSRLD xmm0, 24 ; solo tengo rojos
	
	

	PSLLD xmm1, 16
	PSRLD xmm1, 24 ; solo tengo verdes

	PSLLD xmm2, 8
	PSRLD xmm2, 24 ; solo tengo azules


	;me faltan conversiones
	
	CVTDQ2PS xmm0, xmm0 ; Convierto de ints a floats
	CVTDQ2PS xmm1, xmm1 ; Convierto de ints a floats
	CVTDQ2PS xmm2, xmm2 ; Convierto de ints a floats
	CVTDQ2PS xmm3, xmm3 ; Convierto de ints a floats
    movups xmm4, [rojo] ;cargo los coefs ;ORIGINAL rojo
	mulps xmm0, xmm4 ; multiplico por los coefs.
	movups xmm4, [azul] ;repito x2 ;original VERDE
	mulps xmm1, xmm4
	movups xmm4, [verde] ;repito x3 ;origianl AZUL
	mulps xmm2, xmm4

	

	; ahora sumo elementwise
	addps xmm0, xmm1
	addps xmm0, xmm2 ; acá tengo la Luminosidad
    ; xmm0 := 127[L3,L2,L1,L0]0
	CVTTPS2DQ xmm0, xmm0 ; convierto de floats a ints. ahora son ints32
	; xmm0 := [l_int3,l_int2,l_int1,l_int0] 
	VPMOVDB xmm0, xmm0 ; convierto a signedy bytes con truncación.
	movups xmm4, [shuffle]
	PSHUFB xmm0, xmm4
	movups xmm4, [alfas]
	por xmm0, xmm4


	
	movaps [rdi], xmm0
	
	; computo
	add rdi, 16
	add rsi, 16
	add r10, 16
	cmp r10, r8
	jb loop

	terminar_funcion:
	; epilogo
	pop rbp
	ret

