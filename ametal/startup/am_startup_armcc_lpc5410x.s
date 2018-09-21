;/*******************************************************************************
;*                                 Apollo
;*                       ----------------------------
;*                       innovating embedded platform
;*
;* Copyright (c) 2001-2014 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
;* All rights reserved.
;*
;* Contact information:
;* web site:    http://www.zlg.cn/
;* e-mail:      apollo.support@zlg.cn
;*******************************************************************************/

;/**
; * \file
; * \brief LPC5410x startup code for ARMCC compiler
; * 
; * \internal
; * \par Modification History
; * - 1.00 14-12-11  tee, first implementation.
; * \endinternal
; */
 
; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x000001000

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000100

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_LIMIT

                PRESERVE8
                THUMB

; Vector Table Mapped to Address 0 at Reset
                AREA    RESET, DATA, READONLY
                EXPORT  gc_vectors

gc_vectors      DCD     __initial_sp              ; Top of Stack
                DCD     Reset_Handler             ; Reset Handler

                DCD     NMI_Handler
                DCD     HardFault_Handler
                DCD     MemManage_Handler
                DCD     BusFault_Handler
                DCD     UsageFault_Handler
__vector_table_0x1c
                DCD     0                         ; Checksum of the first 7 words
                DCD     0
                DCD     0                         ; Enhanced image marker, set to 0x0 for legacy boot
                DCD     0                         ; Pointer to enhanced boot block, set to 0x0 for legacy boot
                DCD     SVC_Handler
                DCD     DebugMon_Handler
                DCD     0
                DCD     PendSV_Handler
                DCD     SysTick_Handler

        ; External Interrupts
                DCD     am_exc_eint_handler         ; Watchdog
                DCD     am_exc_eint_handler         ; Brown Out Detect
                DCD     Reserved_IRQHandler         ; Reserved
                DCD     am_exc_eint_handler         ; DMA Controller
                DCD     am_exc_eint_handler         ; GPIO Group0 Interrupt
                DCD     am_exc_eint_handler         ; PIO INT0
                DCD     am_exc_eint_handler         ; PIO INT1
                DCD     am_exc_eint_handler         ; PIO INT2
                DCD     am_exc_eint_handler         ; PIO INT3
                DCD     am_exc_eint_handler         ; UTICK timer 
                DCD     am_exc_eint_handler         ; Multi-Rate Timer
                DCD     am_exc_eint_handler         ; CT32B0
                DCD     am_exc_eint_handler         ; CT32B1
                DCD     am_exc_eint_handler         ; CT32B2
                DCD     am_exc_eint_handler         ; CT32B3
                DCD     am_exc_eint_handler         ; CT32B4
                DCD     am_exc_eint_handler         ; Smart Counter Timer 
                DCD     am_exc_eint_handler         ; usart0             
                DCD     am_exc_eint_handler         ; usart1            
                DCD     am_exc_eint_handler         ; usart2
                DCD     am_exc_eint_handler         ; usart3
                DCD     am_exc_eint_handler         ; I2C0 controller  
                DCD     am_exc_eint_handler         ; I2C1 controller  
                DCD     am_exc_eint_handler         ; I2C2 controller  
                DCD     am_exc_eint_handler         ; SPI0 controller
                DCD     am_exc_eint_handler         ; SPI1 controller
                DCD     am_exc_eint_handler         ; ADC0 A sequence (A/D Converter) interrupt
                DCD     am_exc_eint_handler         ; ADC0 B sequence (A/D Converter) interrupt
                DCD     am_exc_eint_handler         ; ADC THCMP and OVERRUN ORed
                DCD     am_exc_eint_handler         ; RTC Timer
                DCD     Reserved_IRQHandler         ; Reserved
                DCD     am_exc_eint_handler         ; Mailbox 
                DCD     am_exc_eint_handler         ; GPIO Group1 Interrupt
                DCD     am_exc_eint_handler         ; PIO INT4
                DCD     am_exc_eint_handler         ; PIO INT5
                DCD     am_exc_eint_handler         ; PIO INT6
                DCD     am_exc_eint_handler         ; PIO INT7
                DCD     Reserved_IRQHandler         ; Reserved 
                DCD     Reserved_IRQHandler         ; Reserved 
                DCD     Reserved_IRQHandler         ; Reserved
                DCD     am_exc_eint_handler         ; RITimer
                DCD     Reserved41_IRQHandler       ; Reserved                         
                DCD     Reserved42_IRQHandler       ; Reserved                         
                DCD     Reserved43_IRQHandler       ; Reserved                         
                DCD     Reserved44_IRQHandler       ; Reserved      

;//   <h> Code Read Protection level (CRP)
;//     <o>    CRP_Level:
;//                     <0xFFFFFFFF=> Disabled
;//                     <0x4E697370=> NO_ISP
;//                     <0x12345678=> CRP1
;//                     <0x87654321=> CRP2
;//                     <0x43218765=> CRP3 (Are you sure?)
;//   </h>
CRP_Level       EQU     0xFFFFFFFF

                IF      :LNOT::DEF:NO_CRP
                AREA    |.ARM.__at_0x02FC|, CODE, READONLY
CRP_Key         DCD     0xFFFFFFFF
                ENDIF

                AREA    |.text|, CODE, READONLY

cpu_id          EQU     0xE000ED00
cpu_ctrl        EQU     0x40000300
coproc_boot     EQU     0x40000304
coproc_stack    EQU     0x40000308

rel_vals
                DCD     cpu_id, cpu_ctrl, coproc_boot, coproc_stack
                DCW     0xFFF, 0xC24

; Reset Handler - shared for both cores
Reset_Handler   PROC
                EXPORT  Reset_Handler               [WEAK]
                EXPORT  SystemInit                  [WEAK]
                IMPORT  __main

                IF      :LNOT::DEF:SLAVEBOOT
                ; Both the M0+ and M4 core come via this shared startup code,
                ; but the M0+ and M4 core have different vector tables.
                ; Determine if the core executing this code is the master or
                ; the slave and handle each core state individually.
shared_boot_entry
                LDR     r6, =rel_vals
                MOVS    r4, #0                          ; Flag for slave core (0)
                MOVS    r5, #1

                ; Determine which core (M0+ or M4) this code is running on
                ; r2 = (((*cpu_id) >> 4) & 0xFFF); (M4 core == 0xC24)
get_current_core_id
                LDR     r0, [r6, #0]
                LDR     r1, [r0]                        ; r1 = CPU ID status
                LSRS    r1, r1, #4                      ; Right justify 12 CPU ID bits
                LDRH    r2, [r6, #16]                   ; Mask for CPU ID bits
                ANDS    r2, r1, r2                      ; r2 = ARM COrtex CPU ID
                LDRH    r3, [r6, #18]                   ; Mask for CPU ID bits
                CMP     r3, r2                          ; Core ID matches M4 identifier
                BNE     get_master_status
                MOV     r4, r5                          ; Set flag for master core (1)

                ; Determine if M4 core is the master or slave
                ; r3 = ((*cpu_ctrl) & 1); (0 == m0+, 1 == M4)
get_master_status
                LDR     r0, [r6, #4]
                LDR     r3, [r0]                        ; r3 = SYSCON co-processor CPU control status
                ANDS    r3, r3, r5                      ; r3 = (Bit 0: 1 = M4 is master, 0 = M4 is slave)

                ; Select boot based on selected master core and core ID
select_boot
                EORS    r3, r3, r4                      ; r4 = (Bit 0: 0 = master, 1 = slave)
                BNE     slave_boot
                B       normal_boot

                ; Slave boot
slave_boot
                LDR     r0, [r6, #8]
                LDR     r2, [r0]                        ; r1 = SYSCON co-processor boot address
                CMP     r2, #0                          ; Slave boot address = 0 (not set up)?
                BEQ     cpu_sleep
                LDR     r0, [r6, #12]
                LDR     r1, [r0]                        ; r5 = SYSCON co-processor stack address
                MOV     sp, r1                          ; Update slave CPU stack pointer
                ; Be sure to update VTOR for the slave MCU to point to the
                ; slave vector table in boot memory
                BX      r2                              ; Jump to slave boot address

                ; Slave isn't yet setup for system boot from the master
                ; so sleep until the master sets it up and then reboots it
cpu_sleep
                MOV     sp, r5                          ; Will force exception if something happens
cpu_sleep_wfi
                WFI                                     ; Sleep forever until master reboots
                B       cpu_sleep_wfi
                ENDIF

                ; Normal boot for master/slave
normal_boot
                LDR     r0, =SystemInit
                BLX     r0
                LDR     r0, =__main
                BX      r0
                ENDP

; For cores with SystemInit() or __main(), the code will sleep the MCU
SystemInit        PROC
                EXPORT  SystemInit                [WEAK]
                BX      lr
                ENDP

; Dummy Exception Handlers (infinite loops which can be modified)                
NMI_Handler     PROC
                EXPORT  NMI_Handler               [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler         [WEAK]
                B       .
                ENDP
MemManage_Handler     PROC
                EXPORT  MemManage_Handler         [WEAK]
                B       .
                ENDP
BusFault_Handler PROC
                EXPORT  BusFault_Handler          [WEAK]
                B       .
                ENDP
UsageFault_Handler PROC
                EXPORT  UsageFault_Handler        [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler               [WEAK]
                B       .
                ENDP
DebugMon_Handler PROC
                EXPORT  DebugMon_Handler          [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler            [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler           [WEAK]
                B       .
                ENDP

Default_Handler PROC
               EXPORT am_exc_eint_handler         [WEAK] ; 
               EXPORT Reserved41_IRQHandler       [WEAK] ; Reserved
               EXPORT Reserved42_IRQHandler       [WEAK] ; Reserved
               EXPORT Reserved43_IRQHandler       [WEAK] ; Reserved
               EXPORT Reserved44_IRQHandler       [WEAK] ; Reserved
               EXPORT Reserved_IRQHandler         [WEAK] ; Reserved

am_exc_eint_handler         ; 
Reserved41_IRQHandler       ; Reserved
Reserved42_IRQHandler       ; Reserved
Reserved43_IRQHandler       ; Reserved
Reserved44_IRQHandler       ; Reserved
Reserved_IRQHandler         ; Reserved

                B       .

                ENDP


                ALIGN


; User Initial Stack & Heap

                IF      :DEF:__MICROLIB
                
                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_LIMIT
                
                ELSE
                
                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap
__user_initial_stackheap

                LDR     R0, =  Heap_Mem
                LDR     R1, =(Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem +  Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR

                ALIGN

                ENDIF


                END
