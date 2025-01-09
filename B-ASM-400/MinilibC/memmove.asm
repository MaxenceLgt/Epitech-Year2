BITS 64
SECTION .text
GLOBAL memmove

memmove:
    XOR RAX, RAX ; assigne la valeur 0 à RAX
    XOR RCX, RCX ; assigne la valeur 0 à RCX
    MOV RAX, RDI ; assigne le pointeur de RDI à RAX
    MOV R8, RSI ; assigne le pointeur de RSI à R8
    JMP _checkDirection ; passe à l'instruction _checkDirection qui vérifie si on copy de droite à gauche (cas ou src écris dans dest) 
                        ; ou de gauche à droite

_checkDirection:
    CMP RCX, RDX ; compare la veur des int RDX et RCX
    JE _instantiateRight ; int égaux -> passe à l'instruction pour initialiser la copy de gauche à droite
    CMP R8, RDI ; compare le pointeur r8 à celui de RDI
    JE _instantiateLeft ; pointeur égaux -> passe à l'instruction pour initialiser la copy de droite à gauche
    INC RCX ; incrémente l'int RCX
    INC R8 ; incrémente le pointeur R8
    JMP _checkDirection ; passe à l'instruction _checkDirection (loop)

_instantiateRight:
    XOR RCX, RCX ; set RCX à 0
    JMP _copyRightLoop ; passe à l'instruction de copy de gauche à droite

_instantiateLeft:
    ADD RDI, RDX ; ajoute RDX au pointeur de RDI
    ADD RSI, RDX ; ajoute RDX au pointeur de RSI
    MOV RCX, RDX ; assigne la valeur de RDX à RCX
    DEC RDI ; décrémente le pointeur de RDI (sinon copy décalé de 1 sur la droite)
    DEC RSI ; décrémente le pointeur de RSI (sinon copy décalé de 1 sur la droite)
    JMP _copyLeftLoop ; passe à l'instruction de copy de droite à gauche

_copyRightLoop:
    CMP RCX, RDX ; compare la valeur de  RCX et RDX
    JE _return ; valeurs égales -> passe à l'instruction return
    MOV BL, BYTE[RSI] ; assigne la valeur de BYTE[RSI] (RSI 2ème arg de fonction) à BL (8-Bit)
    MOV BYTE[RDI], BL ; assigne le byte BL (premier byte de RSI) au premier byte de RDI (8Bit)
    INC RCX ; incrémente la valeur du compteur de boucle
    INC RDI ; incrémente le pointeur de RDI
    INC RSI ; incrémente le pointeur de RSI    
    JMP _copyRightLoop ; passe à l'instruction _copyRightLoop (boucle)

_copyLeftLoop:
    CMP RCX, 0 ; compare la valeur de RCX et 0
    JE _return ; valeurs égales -> passe à l'instruction return
    MOV BL, BYTE[RSI] ; assigne la valeur de BYTE[RSI] (RSI 2ème arg de fonction) à BL (8-Bit)
    MOV BYTE[RDI], BL ; assigne le byte BL (premier byte de RSI) au premier byte de RDI (8Bit)
    DEC RCX ; décrémente la valeur du compteur de boucle
    DEC RDI ; décrémente le pointeur de RDI
    DEC RSI ; décrémente le pointeur de RSI 
    JMP _copyLeftLoop ; passe à l'instruction _copyLeftLoop (boucle)

_return:
    RET ; retourne RAX