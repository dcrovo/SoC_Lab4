
module nios_led2 (
	btn_export,
	clk_clk,
	ledr_export,
	reset_reset_n,
	sseg_export,
	switch_export);	

	input	[3:0]	btn_export;
	input		clk_clk;
	output	[9:0]	ledr_export;
	input		reset_reset_n;
	output	[31:0]	sseg_export;
	input	[9:0]	switch_export;
endmodule
