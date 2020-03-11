/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIESREGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability 
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2011, 2016 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_main.c
* Version      : CodeGenerator for RL78/G13 V2.03.03.03 [07 Mar 2016]
* Device(s)    : R5F100LG
* Tool-Chain   : CCRL
* Description  : This file implements main function.
* Creation Date: 2020/03/11
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_cgc.h"
#include "r_cg_port.h"
#include "r_cg_intc.h"
#include "r_cg_serial.h"
#include "r_cg_adc.h"
#include "r_cg_timer.h"
#include "r_cg_wdt.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
#define LED P7_bit.no2
#define SYNC P5_bit.no4
#define LDAC P5_bit.no2
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
void mywait_ms(uint32_t i)
{
	i*=2000;

	while(i>0){
		i--;
	}
}
extern int on_com;
/* End user code. Do not edit comment generated here */
void R_MAIN_UserInit(void);

/***********************************************************************************************************************
* Function Name: main
* Description  : This function implements main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void main(void)
{
	uint8_t SRESET[3];
	uint8_t UPDATE_DAC[3];

	SRESET[0] = 0x61;
	SRESET[1] = 0x00;
	SRESET[2] = 0x00;
	
	UPDATE_DAC[0] = 0x31;
	UPDATE_DAC[1] = 0x00;
	UPDATE_DAC[2] = 0x00;
	
	R_MAIN_UserInit();
	/* Start user code. Do not edit comment generated here */
	LED=0;
	SYNC=1;
	R_CSI00_Start();

	mywait_ms(1000);
	SYNC=0;
	R_CSI00_Send(SRESET, 3);
	mywait_ms(10);
	SYNC=1;

	/* Start user code. Do not edit comment generated here */
	while (1U)
	{
		R_WDT_Restart();

		// LED=1; 
		if (UPDATE_DAC[1] == 0xFF) UPDATE_DAC[1] = 0x00;
		else UPDATE_DAC[1] += 0x01;
		
		mywait_ms(100);
		SYNC=0;
		R_CSI00_Send(UPDATE_DAC, 3);
		mywait_ms(10);
		SYNC=1;
		
		R_WDT_Restart();
                                
		//LED=0;
		mywait_ms(100);
	}

    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: R_MAIN_UserInit
* Description  : This function adds user code before implementing main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MAIN_UserInit(void)
{
    /* Start user code. Do not edit comment generated here */
    EI();
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
