.model small
.stack 256
.data
    firstInput dw ?
	secondInput dw ?
	error1  db 'Error!', 13, 10, '$'
.code
  output proc
        push ax
        push cx
        push dx
        push bx
        xor cx,cx  
        mov bx,10

    count:
        xor dx,dx
        div bx
        add dl,'0'
        push dx
        inc cx
        test ax,ax
        jnz count
	
    fromStackLast:
        pop dx
        mov ah, 02h
        int 21h
        loop fromStackLast
        mov dl, ' '
        mov ah, 02h
        int 21h
        pop bx
        pop dx
        pop cx
        pop ax
    ret
	output endp

	input proc
	PUSH AX
	PUSH CX
	PUSH DX
        begin:
            MOV AH,01h
            int 21h;
            xor ah, ah
            CMP AL,13;end of the input 
            JZ end1
            sub al,'0'
            MOV CH,0
            MOV CL,AL
            cmp CX,0 
            jl error
            cmp CX,9
            jg error
            MOV AX,BX
            MOV BX,10
            MUL BX
            jc error
            XOR DX,DX
            ADD AX, CX
            jc error
            XCHG AX,BX
            XOR AX,AX
            JMP begin
        end1:
            POP AX
            POP CX
            POP DX
        ret
            input endp

        error: 
            mov ah, 9
            mov dx, offset error1
            int 21h
            POP AX
            POP CX
            POP DX
            JMP endProgramm
main:
    mov ax, @data
    mov ds, ax    
    XOR BX,BX; first input
    CALL input 
    XCHG AX,BX
    mov firstInput, AX
    call output
    XOR BX,BX; second input
    CALL input 
    XCHG AX,BX	
    mov secondInput, AX
    call output
    cmp secondInput,0
    jz error
    XOR AX,AX
    XOR dx,dx
    mov Ax, firstInput
    div secondInput
    call output
    JMP endProgramm

 	endProgramm:
	mov ax, 4c00h
    int 21h   
end main	