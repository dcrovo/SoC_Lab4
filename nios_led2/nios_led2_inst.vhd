	component nios_led2 is
		port (
			btn_export    : in  std_logic_vector(3 downto 0)  := (others => 'X'); -- export
			clk_clk       : in  std_logic                     := 'X';             -- clk
			ledr_export   : out std_logic_vector(9 downto 0);                     -- export
			reset_reset_n : in  std_logic                     := 'X';             -- reset_n
			sseg_export   : out std_logic_vector(31 downto 0);                    -- export
			switch_export : in  std_logic_vector(9 downto 0)  := (others => 'X')  -- export
		);
	end component nios_led2;

	u0 : component nios_led2
		port map (
			btn_export    => CONNECTED_TO_btn_export,    --    btn.export
			clk_clk       => CONNECTED_TO_clk_clk,       --    clk.clk
			ledr_export   => CONNECTED_TO_ledr_export,   --   ledr.export
			reset_reset_n => CONNECTED_TO_reset_reset_n, --  reset.reset_n
			sseg_export   => CONNECTED_TO_sseg_export,   --   sseg.export
			switch_export => CONNECTED_TO_switch_export  -- switch.export
		);

