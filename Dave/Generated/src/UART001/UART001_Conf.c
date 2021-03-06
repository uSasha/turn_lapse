/*******************************************************************************
**  DAVE App Name : UART001       App Version: 1.0.22               
**  This file is generated by DAVE, User modification to this file will be    **
**  overwritten at the next code generation.                                  **
*******************************************************************************/


/*CODE_BLOCK_BEGIN[UART001_Conf.c]*/
/*******************************************************************************
 Copyright (c) 2013, Infineon Technologies AG                                 **
 All rights reserved.                                                         **
                                                                              **
 Redistribution and use in source and binary forms, with or without           **
 modification,are permitted provided that the following conditions are met:   **
                                                                              **
 *Redistributions of source code must retain the above copyright notice,      **
 this list of conditions and the following disclaimer.                        **
 *Redistributions in binary form must reproduce the above copyright notice,   **
 this list of conditions and the following disclaimer in the documentation    **
 and/or other materials provided with the distribution.                       **
 *Neither the name of the copyright holders nor the names of its              **
 contributors may be used to endorse or promote products derived from this    **
 software without specific prior written permission.                          **
                                                                              **
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"  **
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE    **
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE   **
 ARE  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE   **
 LIABLE  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR         **
 CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF         **
 SUBSTITUTE GOODS OR  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS    **
 INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN      **
 CONTRACT, STRICT LIABILITY,OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)       **
 ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE   **
 POSSIBILITY OF SUCH DAMAGE.                                                  **
                                                                              **
 To improve the quality of the software, users are encouraged to share        **
 modifications, enhancements or bug fixes with Infineon Technologies AG       **
 dave@infineon.com).                                                          **
                                                                              **
********************************************************************************
**                                                                            **
** PLATFORM : Infineon XMC4000/XMC1000 Series                                 **
**                                                                            **
** COMPILER : Compiler Independent                                            **
**                                                                            **
** AUTHOR   : App Developer                                                   **
**                                                                            **
** NOTE     : Any Changes made to this file will be overwritten during Code   **
**            Generation                                                      **
**                                                                            **
********************************************************************************
** VERSION HISTORY:
********************************************************************************
** 04 Dec 2012 v1.0.4   Changes from 1.0.2 are
**                      1. Modified the handle parameters for macros from
**                      numbers.
**                      2. Modified as per coding guidelines and MISRA checks                
** 26 Mar 2013 v1.0.10  1. Updated for the alignment in revision history.
**                      2. Updated to support XMC1000 devices. 
**                      3. Modified the structure UART001_HandleType to add
**                      baud parameters for the configured baud rate.
** 29 Nov 2013 v1.0.20  1. Created Array of handle pointers to store the handle
**                      base addresses.
**                      2. Added UART001.h inclusion in the UART001_Conf.c, to 
**                      get the handle type declarations.
**                      3. Added Tx & RX pin handle configurations in the 
**                      UART001_HandleType, to configure the mapped port base 
**                      address and the pin number.
**                      4. Removed DAVE3.h inclusion to fix the MISR warning for
**                      multiple includes.                 
*******************************************************************************/ 
/**
 * @file   UART001_Conf.c
 * 
 * @App Version UART001 <1.0.22>
 *
 * @brief  Configuration file generated based on UI settings 
 *         of UART001 App
 *
 */

/*******************************************************************************
 ** INCLUDE FILES                                                             **
 ******************************************************************************/
#include "../../inc/UART001/UART001.h"
const UART001_HandleType UART001_Handle0  = 
{
   .UartRegs = USIC0_CH0, /* Usic Channel offset value */
   .PinHandle = {   
                 /* Tx port pin base address & pin no.*/
                 (UART001_PORTS_TypeDef *) PORT2_BASE, (uint8_t) 1,   
                 /* Rx port pin base address & pin no.*/
                 (UART001_PORTS_TypeDef *) PORT2_BASE, (uint8_t) 2
   				},  			
   .Mode = UART_FULLDUPLEX, /* Mode */
   .StopBit = UART_ONE_STOPBIT,/* StopBit */
   .Parity  = UART_PARITY_NONE,/* Parity */ 
   .DataBits = (uint16_t)7,/* Word Length */
   .BaudRate  = (uint32_t)115200,/*Baud Rate */
   .TxFifoEn = (bool) 1, /* Additional Transmit FIFO buffer capability enable */
   .RxFifoEn = (bool) 1, /* Additional Receive FIFO buffer capability enable */
   .TxLimit = (uint8_t)0,/* FIFO Tigger Level */
   .RxLimit = (uint8_t)0,/* FIFO Tigger Level */
   .TxFifoSize = (uint8_t)1,/* Tx FIFO Size */
   .RxFifoSize = (uint8_t)1,/* Rx FIFO Size */
   .RecvNoiseEn = (bool)0, /* Protocol specific interrupt enable */
   .FormatErrEn = (bool)0, /* Protocol specific interrupt enable */
   .FrameFinEn = (bool)0, /* Protocol specific interrupt enable */
   .BGR_STEP = (uint16_t)811,  /* Baud Rate Generation step value */
   .BGR_PDIV = (uint16_t)21,   /* Baud Rate Generation  pdiv value */
   .BGR_DCTQ = (uint16_t)9, /* Baud Rate Generation dctq value */   
   .BGR_SP = (uint16_t)6, /* Baud Rate Generation sampling point */
   .BGR_PCTQ = (uint8_t)0  /* Baud Rate Generation pctq value */
};

const UART001_HandleType *UART001_HandleArray[UART001_NUM_HANDLES] = 
{  		
   &UART001_Handle0 
};

/*CODE_BLOCK_END*/

