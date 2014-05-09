;@Id: boot.tpl#682 @
;=============================================================================
;  FILENAME:   boot.asm
;  VERSION:    4.16
;  DATE:       6 October 2005
;
;  DESCRIPTION:
;  M8C Boot Code for CY8C24x90 microcontroller devices.
;
;  Copyright (C) Cypress Semiconductor 2000-2005. All rights reserved.
;
; NOTES:
; PSoC Designer's Device Editor uses a template file, BOOT.TPL, located in
; the project's root directory to create BOOT.ASM. Any changes made to
; BOOT.ASM will be  overwritten every time the project is generated; therefore
; changes should be made to BOOT.TPL not BOOT.ASM. Care must be taken when
; modifying BOOT.TPL so that replacement strings (such as @PROJECT_NAME)
; are not accidentally modified.
;
;=============================================================================

include ".\lib\GlobalParams.inc"
include "m8c.inc"
include "m8ssc.inc"
include "memory.inc"

;--------------------------------------
; Export Declarations
;--------------------------------------

export __Start
export __bss_start
export __data_start
export __idata_start
export __func_lit_start
export __text_start
export  _bGetPowerSetting
export   bGetPowerSetting


;--------------------------------------
; Optimization flags
;--------------------------------------
;
; To change the value of these flags, modify the file boot.tpl, not
; boot.asm. See the notes in the banner comment at the beginning of
; this file.

; Optimization for Assembly language (only) projects and C-language projects
; that do not depend on the C compiler to initialize the values of RAM variables.
;   Set to 1: Support for C Run-time Environment initialization
;   Set to 0: Support for C not included. Faster start up, smaller code space.
;
C_LANGUAGE_SUPPORT:              equ 1


; For historical reasons, by default the boot code uses an lcall instruction
; to invoke the user's _main code. If _main executes a return instruction,
; boot provides an infinite loop. By changing the following equate from zero
; to 1, boot's lcall will be replaced by a ljmp instruction, saving two
; bytes on the stack which are otherwise required for the return address. If
; this option is enabled, _main must not return. (Beginning with the 4.2
; release, the C compiler automatically places an infinite loop at the end
; of main, rather than a return instruction.)
;
ENABLE_LJMP_TO_MAIN:             equ 0


;-----------------------------------------------------------------------------
; Interrupt Vector Table
;-----------------------------------------------------------------------------
;
; Interrupt vector table entries are 4 bytes long.  Each one contains
; a jump instruction to an ISR (Interrupt Service Routine), although
; very short ISRs could be encoded within the table itself. Normally,
; vector jump targets are modified automatically according to the user
; modules selected. This occurs when the 'Generate Application' opera-
; tion is run causing PSoC Designer to create boot.asm and the other
; configuration files. If you need to hard code a vector, update the
; file boot.tpl, not boot.asm. See the banner comment at the beginning
; of this file.
;-----------------------------------------------------------------------------

    AREA TOP (ROM, ABS, CON)

    org   0                        ;Reset Interrupt Vector
	ljmp BootDefaultStart    
;    jmp   __Start                  ;First instruction executed following a Reset

    org   04h                      ;Supply Monitor Interrupt Vector
    halt                           ;Stop execution if power falls too low

    org   08h                      ;Analog Column 0 Interrupt Vector

   jmp  0x0080
 ;   `@INTERRUPT_2`
    reti

    org   0Ch                      ;Analog Column 1 Interrupt Vector
 ;   ljmp _TickHandler_ISR
    jmp  0x0084
;    `@INTERRUPT_3`
    reti

    org   18h                      ;VC3 Interrupt Vector
    jmp  0x0088
;    `@INTERRUPT_6`
    reti

    org   1Ch                      ;GPIO Interrupt Vector
    jmp  0x008C
;    `@INTERRUPT_7`
    reti

    org   20h                      ;PSoC Block DBB00 Interrupt Vector
    jmp  0x0090
;    `@INTERRUPT_8`
    reti

    org   24h                      ;PSoC Block DBB01 Interrupt Vector
;    ljmp	_Timer16_1_ISR
    jmp  0x0094
;    `@INTERRUPT_9`
    reti

    org   28h                      ;PSoC Block DCB02 Interrupt Vector
    jmp  0x0098
;    `@INTERRUPT_10`
    reti

    org   2Ch                      ;PSoC Block DCB03 Interrupt Vector
    jmp  0x009C
;    `@INTERRUPT_11`
    reti

    org   40h                      ;USB Reset Interrupt Vector
    ljmp	_USB_RESET_ISR    
    reti

    org   44h                      ;USB SOF Interrupt Vector
    ljmp	_USB_SOF_ISR    
    reti

    org   48h                      ;USB EP0 Interrupt Vector
    ljmp	_USB_EP0_ISR
    reti

    org   4Ch                      ;USB EP1 Interrupt Vector
    ljmp	_USB_EP1_ISR
    reti

    org   50h                      ;USB EP2 Interrupt Vector
    ljmp	_USB_EP2_ISR    
    reti

    org   54h                      ;USB EP3 Interrupt Vector
    ljmp	_USB_EP3_ISR    
    reti

    org   58h                      ;USB EP4 Interrupt Vector
    ljmp	_USB_EP4_ISR        
    reti

    org   5Ch                      ;USB Wakeup Interrupt Vector
    ljmp	_USB_WAKEUP_ISR
    reti

    org   60h                      ;PSoC I2C Interrupt Vector
    jmp  0x00C0
;    `@INTERRUPT_24`
    reti

    org   64h                      ;Sleep Timer Interrupt Vector
	ljmp _ShadowSleep
;    ljmp _SleepIntHandler
  
;    `@INTERRUPT_25`
    reti

;-----------------------------------------------------------------------------
;  Start of Execution.
;-----------------------------------------------------------------------------
;  The Supervisory ROM SWBootReset function has already completed the
;  calibrate1 process, loading trim values for 5 volt operation.
;
//------------------------ New interrupt table -------------------

    org   80h                      ;Analog Column 0 Interrupt Vector
    // call	void_handler
    reti

    org   84h                      ;Analog Column 1 Interrupt Vector
 ;   ljmp _TickHandler_ISR
;    // call	void_handler
    reti

    org   88h                      ;VC3 Interrupt Vector
    // call	void_handler
    reti

    org   8Ch                      ;GPIO Interrupt Vector
    ljmp	PSoC_GPIO_ISR
;    // call	void_handler
    reti

    org   90h                      ;PSoC Block DBB00 Interrupt Vector
;    ljmp	_Timer8_ISR    
    // call	void_handler
    reti

    org   94h                      ;PSoC Block DBB01 Interrupt Vector
    ljmp _Timer16_1_ISR
;    // call	void_handler
    reti

    org   98h                      ;PSoC Block DCB02 Interrupt Vector
    // call	void_handler
    reti

    org   9Ch                      ;PSoC Block DCB03 Interrupt Vector
    // call	void_handler
    reti

    org   A0h                      ;USB Reset Interrupt Vector
    // call	void_handler
    reti

    org   A4h                      ;USB SOF Interrupt Vector
    // call	void_handler
    reti

    org   A8h                      ;USB EP0 Interrupt Vector
    // call	void_handler
    reti

    org   ACh                      ;USB EP1 Interrupt Vector
    // call	void_handler
    reti

    org   B0h                      ;USB EP2 Interrupt Vector
   // call	void_handler
    reti

    org   B4h                      ;USB EP3 Interrupt Vector
    // call	void_handler
    reti

    org   B8h                      ;USB EP4 Interrupt Vector
    // call	void_handler
    reti

    org   BCh                      ;USB Wakeup Interrupt Vector
    // call	void_handler
    reti

    org   C0h                      ;PSoC I2C Interrupt Vector
    // call	void_handler
    reti

    org   C4h                      ;Sleep Timer Interrupt Vector
	ljmp	_SleepIntHandler
;    // call	void_handler
    reti

;-----------------------------------------------------------------------------
;  Start of Execution.
;-----------------------------------------------------------------------------
;  The Supervisory ROM SWBootReset function has already completed the
;  calibrate1 process, loading trim values for 5 volt operation.
;
    org C8h
__Start:
    ;-----------------------------------
    ; Initialize C Run-Time Environment
    ;-----------------------------------
IF ( C_LANGUAGE_SUPPORT )
IF ( SYSTEM_SMALL_MEMORY_MODEL )
    mov  A,0                           ; clear the 'bss' segment to zero
    mov  [__r0],<__bss_start
BssLoop:
    cmp  [__r0],<__bss_end
    jz   BssDone
    mvi  [__r0],A
    jmp  BssLoop
BssDone:
    mov  A,>__idata_start              ; copy idata to data segment
    mov  X,<__idata_start
    mov  [__r0],<__data_start
IDataLoop:
    cmp  [__r0],<__data_end
    jz   C_RTE_Done
    push A
    romx
    mvi  [__r0],A
    pop  A
    inc  X
    adc  A,0
    jmp  IDataLoop

ENDIF ; SYSTEM_SMALL_MEMORY_MODEL

IF ( SYSTEM_LARGE_MEMORY_MODEL )
    mov   reg[CUR_PP], >__r0           ; force direct addr mode instructions
                                       ; to use the Virtual Register page.

    ; Dereference the constant (flash) pointer pXIData to access the start
    ; of the extended idata area, "xidata." Xidata follows the end of the
    ; text segment and may have been relocated by the Code Compressor.
    ;
    mov   A, >__pXIData                ; Get the address of the flash
    mov   X, <__pXIData                ;   pointer to the xidata area.
    push  A
    romx                               ; get the MSB of xidata's address
    mov   [__r0], A
    pop   A
    inc   X
    adc   A, 0
    romx                               ; get the LSB of xidata's address
    swap  A, X
    mov   A, [__r0]                    ; pXIData (in [A,X]) points to the
                                       ;   XIData structure list in flash
    jmp   .AccessStruct

    ; Unpack one element in the xidata "structure list" that specifies the
    ; values of C variables. Each structure contains 3 member elements.
    ; The first is a pointer to a contiguous block of RAM to be initial-
    ; ized. Blocks are always 255 bytes or less in length and never cross
    ; RAM page boundaries. The list terminates when the MSB of the pointer
    ; contains 0xFF. There are two formats for the struct depending on the
    ; value in the second member element, an unsigned byte:
    ; (1) If the value of the second element is non-zero, it represents
    ; the 'size' of the block of RAM to be initialized. In this case, the
    ; third member of the struct is an array of bytes of length 'size' and
    ; the bytes are copied to the block of RAM.
    ; (2) If the value of the second element is zero, the block of RAM is
    ; to be cleared to zero. In this case, the third member of the struct
    ; is an unsigned byte containing the number of bytes to clear.

.AccessNextStructLoop:
    inc   X                            ; pXIData++
    adc   A, 0
.AccessStruct:                         ; Entry point for first block
    ;
    ; Assert: pXIData in [A,X] points to the beginning of an XIData struct.
    ;
    M8C_ClearWDT                       ; Clear the watchdog for long inits
    push  A
    romx                               ; MSB of RAM addr (CPU.A <- *pXIData)
    mov   reg[MVW_PP], A               ;   for use with MVI write operations
    inc   A                            ; End of Struct List? (MSB==0xFF?)
    jz    .C_RTE_WrapUp                ;   Yes, C runtime environment complete
    pop   A                            ; restore pXIData to [A,X]
    inc   X                            ; pXIData++
    adc   A, 0
    push  A
    romx                               ; LSB of RAM addr (CPU.A <- *pXIData)
    mov   [__r0], A                    ; RAM Addr now in [reg[MVW_PP],[__r0]]
    pop   A                            ; restore pXIData to [A,X]
    inc   X                            ; pXIData++ (point to size)
    adc   A, 0
    push  A
    romx                               ; Get the size (CPU.A <- *pXIData)
    jz    .ClearRAMBlockToZero         ; If Size==0, then go clear RAM
    mov   [__r1], A                    ;             else downcount in __r1
    pop   A                            ; restore pXIData to [A,X]

.CopyNextByteLoop:
    ; For each byte in the structure's array member, copy from flash to RAM.
    ; Assert: pXIData in [A,X] points to previous byte of flash source;
    ;         [reg[MVW_PP],[__r0]] points to next RAM destination;
    ;         __r1 holds a non-zero count of the number of bytes remaining.
    ;
    inc   X                            ; pXIData++ (point to next data byte)
    adc   A, 0
    push  A
    romx                               ; Get the data value (CPU.A <- *pXIData)
    mvi   [__r0], A                    ; Transfer the data to RAM
    tst   [__r0], 0xff                 ; Check for page crossing
    jnz   .CopyLoopTail                ;   No crossing, keep going
    mov   A, reg[ MVW_PP]              ;   If crossing, bump MVW page reg
    inc   A
    mov   reg[ MVW_PP], A
.CopyLoopTail:
    pop   A                            ; restore pXIData to [A,X]
    dec   [__r1]                       ; End of this array in flash?
    jnz   .CopyNextByteLoop            ;   No,  more bytes to copy
    jmp   .AccessNextStructLoop        ;   Yes, initialize another RAM block

.ClearRAMBlockToZero:
    pop   A                            ; restore pXIData to [A,X]
    inc   X                            ; pXIData++ (point to next data byte)
    adc   A, 0
    push  A
    romx                               ; Get the run length (CPU.A <- *pXIData)
    mov   [__r1], A                    ; Initialize downcounter
    mov   A, 0                         ; Initialize source data

.ClearRAMBlockLoop:
    ; Assert: [reg[MVW_PP],[__r0]] points to next RAM destination and
    ;         __r1 holds a non-zero count of the number of bytes remaining.
    ;
    mvi   [__r0], A                    ; Clear a byte
    tst   [__r0], 0xff                 ; Check for page crossing
    jnz   .ClearLoopTail               ;   No crossing, keep going
    mov   A, reg[ MVW_PP]              ;   If crossing, bump MVW page reg
    inc   A
    mov   reg[ MVW_PP], A
    mov   A, 0                         ; Restore the zero used for clearing
.ClearLoopTail:
    dec   [__r1]                       ; Was this the last byte?
    jnz   .ClearRAMBlockLoop           ;   No,  continue
    pop   A                            ;   Yes, restore pXIData to [A,X] and
    jmp   .AccessNextStructLoop        ;        initialize another RAM block

.C_RTE_WrapUp:
    pop   A                            ; balance stack

ENDIF ; SYSTEM_LARGE_MEMORY_MODEL

C_RTE_Done:

ENDIF ; C_LANGUAGE_SUPPORT



IF ENABLE_LJMP_TO_MAIN
    ljmp  _main                    ; goto main (no return)
ELSE
    lcall _main                    ; call main
.Exit:
    jmp  .Exit                     ; Wait here after return till power-off or reset
ENDIF

    ;---------------------------------
    ; Library Access to Global Parms
    ;---------------------------------
    ;
 bGetPowerSetting:
_bGetPowerSetting:
    ; Returns value of POWER_SETTING in the A register.
    ; No inputs. No Side Effects.
    ;
    mov   A, POWER_SETTING          ; Supply voltage and internal main osc
    ret

    ;---------------------------------
    ; Order Critical RAM & ROM AREAs
    ;---------------------------------
    ;  'TOP' is all that has been defined so far...

    ;  ROM AREAs for C CONST, static & global items
    ;
    AREA lit               (ROM, REL, CON)   ; 'const' definitions
    AREA idata             (ROM, REL, CON)   ; Constants for initializing RAM
__idata_start:

    AREA func_lit          (ROM, REL, CON)   ; Function Pointers
__func_lit_start:

IF ( SYSTEM_LARGE_MEMORY_MODEL )
    ; We use the func_lit area to store a pointer to extended initialized
    ; data (xidata) area that follows the text area. Func_lit isn't
    ; relocated by the code compressor, but the text area may shrink and
    ; that moves xidata around.
    ;
__pXIData:         word __text_end           ; ptr to extended idata
ENDIF

    AREA psoc_config       (ROM, REL, CON)   ; Configuration Load & Unload
    AREA UserModules       (ROM, REL, CON)   ; User Module APIs

    ; CODE segment for general use
    ;
    AREA text (ROM, REL, CON)
__text_start:

    ; RAM area usage
    ;
    AREA data              (RAM, REL, CON)   ; initialized RAM
__data_start:

    AREA virtual_registers (RAM, REL, CON)   ; Temp vars of C compiler
    AREA InterruptRAM      (RAM, REL, CON)   ; Interrupts, on Page 0
    AREA bss               (RAM, REL, CON)   ; general use
__bss_start:

; end of file boot.asm
