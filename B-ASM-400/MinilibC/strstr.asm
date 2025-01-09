BITS 64
SECTION .text
GLOBAL strstr

strstr:
    XOR RAX, RAX
    MOV R8, RSI
    MOV R9B, BYTE[RSI]
    JMP _parsingLoop

_parsingLoop:
    CMP R9B, 0
    JE _returnPointer
    CMP BYTE[RDI], 0
    JE _return
    CMP BYTE[RDI], R9B
    JE _setupCheck
    INC RDI
    JMP _parsingLoop

_setupCheck:
    MOV R10, RDI
    JMP _checkLoop

_checkLoop:
    MOV R9B, BYTE[R8]
    CMP R9B, 0
    JE _returnPointer
    CMP BYTE[R10], 0
    JE _return
    CMP R9B, BYTE[R10]
    JNE _resetParsing
    INC R8
    INC R10
    JMP _checkLoop

_resetParsing:
    MOV R8, RSI
    MOV R9B, BYTE[RSI]
    INC RDI
    JMP _parsingLoop

_returnPointer:
    MOV RAX, RDI
    RET

_return:
    RET
