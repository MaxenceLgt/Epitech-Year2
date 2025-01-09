BITS 64
SECTION .text
GLOBAL strpbrk

strpbrk:
    XOR RAX, RAX
    JMP _parsingLoop

_parsingLoop:
    CMP BYTE[RDI], 0
    JE _return
    MOV R8, RSI
    MOV R9B, BYTE[RDI]
    JMP _compareLoop

_compareLoop:
    CMP BYTE[R8], 0
    JE _noValidCompare
    CMP BYTE[R8], R9B
    JE _findValidCompare
    INC R8
    JMP _compareLoop

_noValidCompare:
    INC RDI
    JMP _parsingLoop

_findValidCompare:
    MOV RAX, RDI
    JMP _return

_return:
    RET