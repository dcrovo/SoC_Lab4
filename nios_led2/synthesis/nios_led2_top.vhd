LIBRARY IEEE;
USE ieee.std_logic_1164.all;
------------------------------------------------
ENTITY nios_led2_top IS
PORT	(		clk			:	IN		STD_LOGIC;
				sw				:	IN		STD_LOGIC_VECTOR(9 DOWNTO 0);
				key			:	IN		STD_LOGIC_VECTOR(3 DOWNTO 0);
				ledr			:	OUT	STD_LOGIC_VECTOR(9 DOWNTO 0);
				hex3			:	OUT	STD_LOGIC_VECTOR(6 DOWNTO 0);
				hex2			:	OUT	STD_LOGIC_VECTOR(6 DOWNTO 0);
				hex1			:	OUT	STD_LOGIC_VECTOR(6 DOWNTO 0);
				hex0			:	OUT	STD_LOGIC_VECTOR(6 DOWNTO 0));
END ENTITY nios_led2_top;
-------------------------------------------------
ARCHITECTURE arch OF nios_led2_top IS
	SIGNAL	sseg_s	:	STD_LOGIC_VECTOR(31 DOWNTO 0);
	
	COMPONENT nios_led2 IS
	PORT	(
		clk_clk			:	IN		STD_LOGIC;
		ledr_export		:	OUT	STD_LOGIC_VECTOR(9 DOWNTO 0);
		sseg_export		:	OUT	STD_LOGIC_VECTOR(31 DOWNTO 0);
		switch_export	:	IN		STD_LOGIC_VECTOR(9 DOWNTO 0);
		btn_export		:	IN		STD_LOGIC_VECTOR(3 DOWNTO 0);
		reset_reset_n	:	IN		STD_LOGIC);
END COMPONENT nios_led2;
BEGIN
	nios_unit:	COMPONENT	nios_led2
		PORT MAP	(	clk_clk			=>	clk,
						ledr_export 	=> ledr,
						sseg_export 	=> sseg_s,
						switch_export	=>	sw,
						btn_export		=> key,
						reset_reset_n	=>	'1');
		hex3	<=	sseg_s(30 DOWNTO 24);
		hex2	<=	sseg_s(22 DOWNTO 16);
		hex1	<=	sseg_s(14 DOWNTO 8);
		hex0	<=	sseg_s(6 DOWNTO 0);
END ARCHITECTURE arch;