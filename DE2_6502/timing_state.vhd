library IEEE;
use ieee.std_logic_1164.all;

entity Timing_State is
end entity;

architecture rtl of Timing_State is
begin
	-- process (clk, reset)
	-- then

	-- 	if reset = '0' then
	-- 		MCycle 		<= "001";
	-- 		reset_cycle <= '1';		-- Flag indicating if CPU has been reset this cycle (We begin with reset).
	-- 		irq_cycle 	<= '0';		-- IRQ this cycle
	-- 		nmi_cycle 	<= '0';
	-- 		nmi_act 	<= '0';
	-- 	elsif rising_edge(clk) and clk='1' then
	-- 		if ready = '1' then
	-- 			if MCycle = LCycle or break = '1' then
	-- 				MCycle 		<= "000";
	-- 				reset_cycle <= '0';
	-- 				irq_cycle 	<= '0';
	-- 				nmi_cycle	<= '0';

	-- 				if nmi_act = '1' then
	-- 					nmi_cycle <= '1';
	-- 				elsif irq_n_o = '0' and P(Flag_I) = '0' then
	-- 					irq_cycle <= '1';
	-- 				end if;
	-- 			end if;

	-- 			if nmi_cycle = '1' then
	-- 				nmi_act <= '0';
	-- 			end if;

	-- 			if nmi_n_o = '1' and nmi_n = '0' then
	-- 				nmi_act <= '1';
	-- 			end if;
	-- 		end if;
	-- 	end if;

	-- end process;
end architecture;