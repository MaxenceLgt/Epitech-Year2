BITS 64
SECTION .text
GLOBAL strncmp

BITS 64
SECTION .text
GLOBAL strcmp

strncmp:
    XOR RAX, RAX
    XOR RCX, RCX
    JMP _loop

_loop:
    CMP RDX, RCX
    JE _return
    MOV AL, BYTE[RDI]
    MOV BL, BYTE[RSI]
    CMP BYTE[RDI], 0
    JE _return
    CMP AL, BL
    JNE _return
    JMP _increment

_increment:
    INC RDI
    INC RSI
    INC RCX
    JMP _loop

_return:
    CMP RDX, 0
    JE _returnNull
    MOVZX RAX, AL
    MOVZX RBX, BL
    SUB RAX, RBX
    RET

_returnNull:
    RET