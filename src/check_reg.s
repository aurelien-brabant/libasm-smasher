; **************************************************************************** ;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    check_reg.s                                        :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: abrabant <abrabant@student.42.fr>          +;+  +:+       +;+         ;
;                                                 +;+;+;+;+;+   +;+            ;
;    Created: 2021/04/10 10:19:04 by abrabant          ;+;    ;+;              ;
;    Updated: 2021/04/10 10:19:04 by abrabant         ;;;   ;;;;;;;;.fr        ;
;                                                                              ;
; **************************************************************************** ;

section .data
	rbx_tostring	db `rbx\0`
	r12_tostring	db `r12\0`
	r13_tostring	db `r13\0`
	r14_tostring	db `r14\0`
	r15_tostring	db `r15\0`

section .bss
	rbx_preserved	resq 1
	r12_preserved	resq 1
	r13_preserved	resq 1
	r14_preserved	resq 1
	r15_preserved	resq 1

section .text
global	save_preserved_reg
global	check_preserved_reg

; void save_preserved_reg(); 
save_preserved_reg:
	; Save all the callee saved into global variables to make sure
	; their value is well restored after each function call.
	mov [rbx_preserved], rbx
	mov [r12_preserved], r12
	mov [r13_preserved], r13
	mov [r14_preserved], r14
	mov [r15_preserved], r15
	ret

; Check if registers have been successfully preserved from the previous call
; to save_preserved_reg.
; The address of an t_unpreserved_reg object must be passed in rdi.
; If an unpreserved register is found, the object will be populated with
; informations about the register that has been detected as unpreserved.
; If everything went well, the reg member will be set to NULL.

check_preserved_reg:
	; logic for rbx
	mov r10, [rbx_preserved]
	mov qword [rdi], r10 
	mov	qword [rdi + 8], rbx
	mov qword [rdi + 16], rbx_tostring
	cmp rbx, qword [rbx_preserved]
	jne ret_error

	; logic for r12
	mov r10, [r12_preserved]
	mov qword [rdi], r10 
	mov	qword [rdi + 8], r12
	mov qword [rdi + 16], r12_tostring
	cmp r12, qword [r12_preserved]
	jne ret_error

	; logic for r13
	mov r10, [r13_preserved]
	mov qword [rdi], r10 
	mov	qword [rdi + 8], r13
	mov qword [rdi + 16], r13_tostring
	cmp r13, qword [r13_preserved]
	jne ret_error

	; logic for r14
	mov r10, [r14_preserved]
	mov qword [rdi], r10 
	mov	qword [rdi + 8], r14
	mov qword [rdi + 16], r14_tostring
	cmp r14, qword [r14_preserved]
	jne ret_error

	; logic for r15
	mov r10, [r15_preserved]
	mov qword [rdi], r10 
	mov	qword [rdi + 8], r15
	mov qword [rdi + 16], r15_tostring
	cmp r15, qword [r15_preserved]
	jne ret_error

	mov qword [rdi + 16], 0	; no error occured, then all the registers have been preserved.
	ret

ret_error:
	ret
