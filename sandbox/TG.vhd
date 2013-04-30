library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity TG is

	port(
		clk		 : in	std_logic;
		cycle_number	 : in	std_logic_vector(3 downto 0);
		ACR	 : in std_logic;  --carry in from ALU
		BRC	 : in std_logic;  --branch flag
		reset	 : in	std_logic;
		tcstate	 : out	std_logic_vector(5 downto 0);
		SYNC	 : out std_logic;
		VEC1 	 : out std_logic
	);

end entity;

architecture rtl of TG is

	-- Build an enumerated type for the state machine
	--type state_type is (s0, s1, s2, s3);
	type state_type is (T0, T1F_T1, T2_T0, T2_3, T2_4, T3_4, T2_5, T3_5, T4_5,
							  T2_6, T3_6, T4_6, T5_6, T2_7, T3_7, T4_7, T5_7, T6_7, 
							  T2_B, T3_B, T1F);
	
	-- Register to hold the current state
	signal state   : state_type;

begin

	-- Logic to advance to the next state
	process (clk, reset)
	begin
		if reset = '1' then
			state <= T0;
		elsif (rising_edge(clk)) then
			case state is
				when T0=>
					state <= T1F_T1;
				when T1F_T1=>
					if unsigned(cycle_number) = 2 then
						state <= T2_T0;
					elsif unsigned(cycle_number) = 3 then
						state <= T2_3;
					elsif unsigned(cycle_number) = 4 then
						state <= T2_4;
					elsif unsigned(cycle_number) = 5 then
						state <= T2_5;
					elsif unsigned(cycle_number) = 6 then
						state <= T2_6;
					elsif unsigned(cycle_number) = 7 then
						state <= T2_7;
					elsif unsigned(cycle_number) = 0 then --input =0 stands for the branch instruction
						state <= T2_B;
					end if;
				when T2_T0=>
					state <= T1F_T1;
				when T2_3 =>
					state <= T0;
				when T2_4 =>
					state <= T3_4;
				when T3_4 =>
					state <= T0;
				when T2_5 =>
					state <= T3_5;
				when T3_5 =>
					if ACR='1' then    --judge page crossing or not
						state <= T4_5;
					else 
						state <= T0;
					end if;
				when T4_5 =>
					state <= T0;
				when T2_6 =>
					state <= T3_6;
				when T3_6 =>
					state <= T4_6;
				when T4_6 =>
					if ACR='1' then	--judge page crossing or not
						state <= T5_6;
					else 
						state <= T0;
					end if;
				when T5_6 =>
					state <= T0;
				when T2_7 =>
					state <= T3_7;
				when T3_7 =>
					state <= T4_7;
				when T4_7 =>
					state <= T5_7;
				when T5_7 => 
					state <= T6_7;
				when T6_7 =>
					state <= T0;
				when T2_B =>
					if BRC = '1' then
						state <= T3_B;
					else
						state <= T1F;
					end if;
				when T3_B =>
					if ACR='1' then	--judge page crossing or not
						state <= T0;
					else 
						state <= T1F;
					end if;
				when T1F =>
					if unsigned(cycle_number) = 2 then
						state <= T2_T0;
					elsif unsigned(cycle_number) = 3 then
						state <= T2_3;
					elsif unsigned(cycle_number) = 4 then
						state <= T2_4;
					elsif unsigned(cycle_number) = 5 then
						state <= T2_5;
					elsif unsigned(cycle_number) = 6 then
						state <= T2_6;
					elsif unsigned(cycle_number) = 7 then
						state <= T2_7;
					elsif unsigned(cycle_number) = 0 then --input =0 stands for the branch instruction
						state <= T2_B;
					end if;
			end case;
		end if;
	end process;

	-- Output depends solely on the current state
	process (state)
	begin
		case state is
			when T0 =>
				tcstate <= "011111";
				SYNC <= '0';
				VEC1 <= '0';
			when T1F_T1 =>
				tcstate <= "101111";
				SYNC <= '1';
				VEC1 <= '0';
			when T2_T0	=>
				tcstate <= "010111";
				SYNC <= '0';
				VEC1 <= '0';
			when T2_3 =>
				tcstate <= "110111";
				SYNC <= '0';
				VEC1 <= '0';
			when T2_4 =>
				tcstate <= "110111";
				SYNC <= '0';
				VEC1 <= '0';
			when T3_4 =>
				tcstate <= "111011";
				SYNC <= '0';
				VEC1 <= '0';
			when T2_5 =>
				tcstate <= "110111";
				SYNC <= '0';
				VEC1 <= '0';
			when T3_5 =>
				tcstate <= "111011";
				SYNC <= '0';
				VEC1 <= '0';
			when T4_5 =>
				tcstate <= "111101";
				SYNC <= '0';
				VEC1 <= '0';
			when T2_6 =>
				tcstate <= "110111";
				SYNC <= '0';
				VEC1 <= '0';
			when T3_6 =>
				tcstate <= "111011";
				SYNC <= '0';
				VEC1 <= '0';
			when T4_6 =>
				tcstate <= "111101";
				SYNC <= '0';
				VEC1 <= '0';
			when T5_6 =>
				tcstate <= "111110";
				SYNC <= '0';
				VEC1 <= '0';
			when T2_7 =>
				tcstate <= "110111";
				SYNC <= '0';
				VEC1 <= '0';
			when T3_7 =>
				tcstate <= "111011";
				SYNC <= '0';
				VEC1 <= '0';
			when T4_7 =>
				tcstate <= "111101";
				SYNC <= '0';
				VEC1 <= '0';
			when T5_7 =>
				tcstate <= "111110";
				SYNC <= '0';
				VEC1 <= '0';
			when T6_7 =>
				tcstate <= "111111";
				SYNC <= '0';
				VEC1 <= '1';
			when T2_B =>
				tcstate <= "110111";
				SYNC <= '0';
				VEC1 <= '0';
			when T3_B => 
				tcstate <= "111011";
				SYNC <= '0';
				VEC1 <= '0';
			when T1F =>
				tcstate <= "111111";
				SYNC <= '1';
				VEC1 <= '0';				
		end case;
	end process;

end rtl;
