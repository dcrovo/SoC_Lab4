#include "system.h"
#include <stdio.h>

typedef struct flash_cmd{
	int pause;
	int prd;
} cmd_type;

int main()
{

	cmd_type sw_cmd={0,100} //initial value: not pause, 100 ms interval
	flashsys_init_v1(BTN_BASE, USR_TIMER_BASE);

	while(1){
		sw_get_command_v1(BTN_BASE, SWITCH_BASE, &sw_cmd);
		jtaguart_disp_msg_v1(JTAG_UART_BASE, sw_cmd);
		sseg_disp_msg_v1(SSEG_BASE, sw_cmd);
	}
  return 0;
}
