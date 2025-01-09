BITS 64
SECTION .text
GLOBAL strcmp

strcmp:
    XOR RAX, RAX
    JMP _loop

_loop:
    MOV AL, BYTE[RDI]
    MOV BL, BYTE[RSI]
    CMP BYTE[RDI], 0
    JE _return
    CMP AL, BL
    JNE _return
    INC RDI
    INC RSI
    JMP _loop

_return:
    MOVZX RAX, AL
    MOVZX RBX, BL
    SUB RAX, RBX
    RET