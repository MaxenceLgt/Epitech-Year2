BITS 64
SECTION .text
GLOBAL strrchr
GLOBAL rindex

rindex:
strrchr:
    XOR RAX, RAX
    JMP _loop

_loop:
    CMP BYTE[RDI], SIL
    JE movOccurence
    CMP BYTE[RDI], 0
    JE return
    INC RDI
    JMP _loop

movOccurence:
    MOV RAX, RDI
    CMP BYTE[RDI], 0
    JE return
    INC RDI
    JMP _loop

return:
    RET
