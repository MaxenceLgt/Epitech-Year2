BITS 64
SECTION .text
GLOBAL memset

memset:
    XOR RCX, RCX
    MOV RAX, RDI
    JMP _setLoop

_setLoop:
    CMP RCX, RDX
    JE _return
    MOV BYTE[RDI], SIL
    INC RCX
    INC RDI
    JMP _setLoop

_return:
    RET
