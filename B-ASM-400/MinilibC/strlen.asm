BITS 64
SECTION .text
GLOBAL strlen

strlen:
    XOR RAX, RAX
    JMP .loop

.loop:
    CMP BYTE[RDI], 0
    JE return
    INC RAX
    INC RDI
    JMP .loop

return:
    RET