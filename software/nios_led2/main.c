#include "system.h"
#include <stdio.h>
#include "gpio.h"


typedef struct flash_cmd{
	int pause;
	int prd;
} cmd_type;

int main()
{

	cmd_type sw_cmd={0,100}; //initial value: not pause, 100 ms interval
	flashsys_init_v1(BTN_BASE, USR_TIMER_BASE);


	while(1){
		sw_get_command_v1(BTN_BASE, SWITCH_BASE, &sw_cmd);
		jtaguart_disp_msg_v1(JTAG_UART_BASE, sw_cmd);
		sseg_disp_msg_v1(SSEG_BASE, sw_cmd);
		led_flash_v1(LEDR_BASE, USR_TIMER_BASE, sw_cmd);
	}
  return 0;
}


void flashsys_init_v1(alt_u32 btn_base, alt_u32 timer_base){
	btn_clear(btn_base); // clear button edge-capture reg
	timer_wr_prd(timer_base, 50000); // set 1-ms timeout period
}

void sw_get_command_v1(alt_u32 btn_base, alt_32 sw_base, cmd_type *cmd){
	alt_u8 btn;
	btn = (alt_u8) btn_read(btn_base) & 0xF; //read 4 pushbuttons
	if(btn != 0){ // button pressed
		if(btn & 0x01){ // btn 0 pressed
			cmd->pause = cmd->pause ^ 1; // toogle pause bit
			printf("%s", "0 preessed\n");
			btn_clear(btn_base); //clear edge-capture reg

		}
		if (btn & 0x02){ //btn 1 pressed
			cmd->prd = pio_read(sw_base) & 0x03FF; // load new interval
			btn_clear(btn_base); //clear edge-capture reg
			printf("%s", "1 preessed\n");

		}
	}
}

void jtaguart_disp_msg_v1(alt_u32 jtag_base, cmd_type cmd){
	static int current = 0 ; //current interval
	char msg[] = "Interval: 0000 ms\n";

	if(cmd.prd != current){//new interval detected
		msg[13] = cmd.prd%10 + '0'; //ascii code for 0 digit
		msg[12] = (cmd.prd/10)%10 +'0'; //ascii code for 10 digit
		msg[11] = (cmd.prd/100)%10 +'0'; //ascii code for 100 digit
		msg[10] = cmd.prd/1000 + '0'; //ascii code for 1000 digit
		jtaguart_wr_str(jtag_base, msg); //send string to console
		current = cmd.prd; //update current interval

	}
}

void sseg_disp_msg_v1(alt_u32 sseg_base, cmd_type cmd){
	int pd;
	alt_u8 hex, msg[4];
	if(cmd.prd > 999){ //999 is max # to be displayed
		pd = 999;
	}else{
		pd = cmd.prd;
	}
	hex = pd%10; // units digit
	msg[3] = sseg_conv_hex(hex);
	hex = (pd/10)%10; //tens digit
	msg[2] = sseg_conv_hex(hex);
	hex = pd/100;//100 digit
	msg[1] = sseg_conv_hex(hex);
	// specify pattern for the most significant digit
	if(cmd.pause){
		msg[0] = 0x0C; // pattern for letter P
	}else{
		msg[0] = 0xFF; // blank
	}
	sseg_disp_ptn(sseg_base, msg);
}

void led_flash_v1(alt_u32 led_base, alt_u32 timer_base, cmd_type cmd){

	static alt_u8 led_pattern = 0x01;
	int ntick=0;
	if(cmd.pause){ // no toggle if paused asserted
		return;
	}
	led_pattern ^= 0x03; //toggle 2 LSBs of LEDs
	pio_write(led_base, led_pattern); // write LEDs

	while(ntick < cmd.prd){
		if(timer_read_tick(timer_base) == 1){
			timer_clear_tick(timer_base);
			ntick++;
		}
	}
}

