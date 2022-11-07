/*
 * gpio.c
 *
 *  Created on: Nov 6, 2022
 *      Author: danielcrovo
 */
#include "gpio.h"


/**
 * Function: sseg_conv_hex
 * Purpose:convert a hex digit to a 7-segment pattern
 **/

alt_u8 sseg_conv_hex(int hex){
	// active-low hex digit 7-seg patterns(0-9, a-f); MSB ignored
	static const alt_u8 SSEG_HEX_TABLE [16] = {
			0x40, 0x79, 0x24, 0x30, 0x19, 0x92, 0x02, 0x78, 0x00, 0x10, //0-9
			0x88, 0x03, 0x46, 0x21, 0x06, 0x0E};
	alt_u8 ptn;
	if(hex < 16){
		ptn = SSEG_HEX_TABLE[hex];
	} else{
		ptn = 0xFF; //blank
	}

	return ptn;
}

/**
 * Function: sseg_disp_ptn
 * Purpose: display pattern in four 7-seg displays
 **/

void sseg_disp_ptn(alt_u32 base, alt_u8 *ptn){
	alt_u32 sseg_data;
	int i;
	// form a 32 bit data

	for (i=0; i<4; i++){
		sseg_data = (sseg_data << 8 ) | *ptn;
		ptn++;
	}
	pio_write(base, sseg_data);
}


void jtaguart_wr_str(alt_u32 jtag_base, char* msg){
	alt_u32 data32;
	while(*msg){
		data32 = (alt_u32) *msg;
		if(jtaguart_rd_wspace(jtag_base) != 0){
			jtaguart_wr_ch(jtag_base, data32);
			msg++;
		}
	}
}

void timer_wr_prd(alt_u32 timer_base, alt_u32 prd){
	alt_u16 high, low;
	// unpack 32-bit timeout period into two 16-bit half words
	high = (alt_u16)(prd>>16);
	low = (alt_16)(prd & 0x0000ffff);
	//write timeout period
	IOWR(timer_base, TIMER_PRDH_REG_OFT, high);
	IOWR(timer_base, TIMER_PRDL_REG_OFT, low);
	//configure timer to start continous mode, enabling interrupt
	IOWR(timer_base, TIMER_CTRL_REG_OFT, 0x0007);
}
