BITS 64
SECTION .text
GLOBAL strcasecmp

strcasecmp:
    XOR RAX, RAX
    JMP _compareLoop

_compareLoop:
    MOV AL, BYTE[RDI]
    MOV BL, BYTE[RSI]
    CMP AL, 0
    JE _returnResult
    CMP BL, 0
    JE _returnResult
    CMP AL, 90
    JLE _transformRdi
    CMP BL, 90
    JLE _transformRsi
    JMP _compareValues

_transformRdi:
    CMP AL, 65
    JGE _setLowerRdi
    CMP BL, 90
    JLE _transformRsi
    JMP _compareValues

_setLowerRdi:
    ADD AL, 32
    CMP BL, 90
    JLE _transformRsi
    JMP _compareValues

_transformRsi:
    CMP BL, 65
    JGE _setLowerRsi
    JL _compareValues

_setLowerRsi:
    ADD BL, 32
    JMP _compareValues

_compareValues:
    CMP AL, BL
    JNE _returnResult
    INC RDI
    INC RSI
    JMP _compareLoop

_returnResult:
    MOVZX RAX, AL
    MOVZX RBX, BL
    SUB RAX, RBX
    RET