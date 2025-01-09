BITS 64
SECTION .text
GLOBAL strchr
GLOBAL index

index:
strchr:
    XOR RAX, RAX
    JMP .loop

.loop:
    CMP BYTE[RDI], SIL
    JE return
    CMP BYTE[RDI], 0
    JE nullReturn
    INC RDI
    JMP .loop

return:
    MOV RAX, RDI
    RET

nullReturn:
    RET
