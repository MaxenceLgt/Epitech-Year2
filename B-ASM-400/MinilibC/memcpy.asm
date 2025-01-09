BITS 64
SECTION .text
GLOBAL memcpy

memcpy:
    XOR RCX, RCX ; assigne la valeur 0 à RCX
    XOR RAX, RAX ; assigne la valeur 0 à RAX
    MOV RAX, RDI ; assigne le pointeur de RDI à RAX
    JMP _copyLoop ; passe à l'instruction _copyLoop

_copyLoop:
    CMP RCX, RDX ; compare la valeur des int RAX et RDX (3 arg de fonction)
    JE _return ; passe à l'instruction _return si les int sont égaux
    MOV BL, BYTE[RSI] ; assigne la valeur de BYTE[RSI] (RSI 2ème arg de fonction) à BL (8-Bit)
    MOV BYTE[RDI], BL ; assigne le byte BL (premier byte de RSI) au premier byte de RDI (8Bit)
    INC RCX ; incrémente la valeur du compteur de boucle
    INC RDI ; incrémente le pointeur de RDI
    INC RSI ; incrémente le pointeur de RSI
    JMP _copyLoop ; passe à l'instruction _copyLoop (boucle)

_return:
    RET ; revoie RAX