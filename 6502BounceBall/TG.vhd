library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity TG is

	port(
		clk		 : in	std_logic;
		cycle_number	 : in	unsigned(3 downto 0);
		RMW    : in std_logic;  --read-modify-write instruction
		ACR	 : in std_logic;  --carry in from ALU
		BRC	 : in std_logic;  --branch flag
		reset	 : in	std_logic;
		tcstate	 : out	std_logic_vector(5 downto 0);
		SYNC, SD1, SD2	 : out std_logic;
		VEC1 	 : out std_logic
	);

end TG;

architecture rtl of TG is

	-- Build an enumerated type for the state machine
	--type state_type is (s0, s1, s2, s3);
	type state_type is (T0, T1F_T1, T2_T0, T2_3, T2_4, T3_4, T2_5, T3_5, T4_5,
							  T2_6, T3_6, T4_6, T5_6, T2_7, T3_7, T4_7, T5_7, T6_7, 
							  T2_B, T3_B, T1F,
							  T2_RMW5, T3_RMW5, T4_RMW5, T2_RMW6, T3_RMW6, T4_RMW6, T5_RMW6, 
							  T2_RMW7, T3_RMW7, T4_RMW7_a, T5_RMW7_a, T6_RMW7_a,
							  T4_RMW7_b, T5_RMW7_b);
	
	-- Register to hold the current state
	signal state   : state_type;

begin

	-- Logic to advance to the next state
	process (clk, reset)
	begin
		if reset = '1' then
			state <= T1F_T1;  --yuchen0513
		elsif (rising_edge(clk)) then
			case state is
				when T0=>
					state <= T1F_T1;
				when T1F_T1=>
				if RMW='0' then	--not read-modify-write instruction
					if    cycle_number = 2 then
						state <= T2_T0;
					elsif cycle_number = 3 then
						state <= T2_3;
					elsif cycle_number = 4 then
						state <= T2_4;
					elsif cycle_number = 5 then
						state <= T2_5;
					elsif cycle_number = 6 then
						state <= T2_6;
					elsif cycle_number = 7 then
						state <= T2_7;
					elsif cycle_number = 0 then --input =0 stands for the branch instruction
						state <= T2_B; 
					elsif cycle_number = 1 then
						state <= T1F_T1; --yuchen0513
					end if;
				
				elsif RMW='1' then  --read-modify-write instruction
					if    cycle_number = 2 then
						state <= T2_T0;
					elsif cycle_number = 5 then
						state <= T2_RMW5;
					elsif cycle_number = 6 then
						state <= T2_RMW6;
					elsif cycle_number = 7 then
						state <= T2_RMW7;
					end if;
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
					if    cycle_number = 2 then
						state <= T2_T0;
					elsif cycle_number = 3 then
						state <= T2_3;
					elsif cycle_number = 4 then
						state <= T2_4;
					elsif cycle_number = 5 then
						state <= T2_5;
					elsif cycle_number = 6 then
						state <= T2_6;
					elsif cycle_number = 7 then
						state <= T2_7;
					elsif cycle_number = 0 then --input =0 stands for the branch instruction
						state <= T2_B;
					end if;
				--Read-modify-write instruction
				when T2_RMW5 =>
					state <= T3_RMW5;
				when T3_RMW5 =>
					state <= T4_RMW5;
				when T4_RMW5 =>
					state <= T0;
				when T2_RMW6 =>
					state <= T3_RMW6;
				when T3_RMW6 =>
					state <= T4_RMW6;
				when T4_RMW6 =>
					state <= T5_RMW6;
				when T5_RMW6 =>
					state <= T0;
				when T2_RMW7 =>
					state <= T3_RMW7;
				when T3_RMW7 =>
					if ACR ='1' then state <= T4_RMW7_a;  --page crossing
					else state <= T4_RMW7_b; --no page crossing
					end if;
				when T4_RMW7_a =>
					state <= T5_RMW7_a;
				when T5_RMW7_a =>
					state <= T6_RMW7_a;
				when T6_RMW7_a =>
					state <= T0;
				when T4_RMW7_b =>
					state <= T5_RMW7_b;
				when T5_RMW7_b =>
					state <= T0;
				when others =>
					state <= T0;
			end case;
		end if;
	end process;

	-- Output depends solely on the current state
	process (state)
	begin
		case state is
			when T0 =>
				tcstate <= "111110";
				SYNC <= '0';
				VEC1 <= '0';
				SD1 <= '0';
				SD2 <= '0';
			when T1F_T1 =>
				tcstate <= "111101";
				SYNC <= '1';
				VEC1 <= '0';
				SD1 <= '0';
				SD2 <= '0';
			when T2_T0	=>
				tcstate <= "111010";
				SYNC <= '0';
				VEC1 <= '0';
				SD1 <= '0';
				SD2 <= '0';
			when T2_3 =>
				tcstate <= "111011";
				SYNC <= '0';
				VEC1 <= '0';
				SD1 <= '0';
				SD2 <= '0';
			when T2_4 =>
				tcstate <= "111011";
				SYNC <= '0';
				VEC1 <= '0';
				SD1 <= '0';
				SD2 <= '0';
			when T3_4 =>
				tcstate <= "110111";
				SYNC <= '0';
				VEC1 <= '0';
				SD1 <= '0';
				SD2 <= '0';
			when T2_5 =>
				tcstate <= "111011";
				SYNC <= '0';
				VEC1 <= '0';
				SD1 <= '0';
				SD2 <= '0';
			when T3_5 =>
				tcstate <= "110111";
				SYNC <= '0';
				VEC1 <= '0';
				SD1 <= '0';
				SD2 <= '0';
			when T4_5 =>
				tcstate <= "101111";
				SYNC <= '0';
				VEC1 <= '0';
				SD1 <= '0';
				SD2 <= '0';
			when T2_6 =>
				tcstate <= "111011";
				SYNC <= '0';
				VEC1 <= '0';
				SD1 <= '0';
				SD2 <= '0';
			when T3_6 =>
				tcstate <= "110111";
				SYNC <= '0';
				VEC1 <= '0';
				SD1 <= '0';
				SD2 <= '0';
			when T4_6 =>
				tcstate <= "101111";
				SYNC <= '0';
				VEC1 <= '0';
				SD1 <= '0';
				SD2 <= '0';
			when T5_6 =>
				tcstate <= "011111";
				SYNC <= '0';
				VEC1 <= '0';
				SD1 <= '0';
				SD2 <= '0';
			when T2_7 =>
				tcstate <= "111011";
				SYNC <= '0';
				VEC1 <= '0';
				SD1 <= '0';
				SD2 <= '0';
			when T3_7 =>
				tcstate <= "110111";
				SYNC <= '0';
				VEC1 <= '0';
				SD1 <= '0';
				SD2 <= '0';
			when T4_7 =>
				tcstate <= "101111";
				SYNC <= '0';
				VEC1 <= '0';
				SD1 <= '0';
				SD2 <= '0';
			when T5_7 =>
				tcstate <= "011111";
				SYNC <= '0';
				VEC1 <= '0';
				SD1 <= '0';
				SD2 <= '0';
			when T6_7 =>
				tcstate <= "111111";
				SYNC <= '0';
				VEC1 <= '1';
				SD1 <= '0';
				SD2 <= '0';
			when T2_B =>
				tcstate <= "111011";
				SYNC <= '0';
				VEC1 <= '0';
				SD1 <= '0';
				SD2 <= '0';
			when T3_B => 
				tcstate <= "110111";
				SYNC <= '0';
				VEC1 <= '0';
				SD1 <= '0';
				SD2 <= '0';
			when T1F =>
				tcstate <= "111111";
				SYNC <= '1';
				VEC1 <= '0';
				SD1 <= '0';
				SD2 <= '0';
			when T2_RMW5 =>
				tcstate <= "111011";
				SYNC <= '0';
				VEC1 <= '0';
				SD1 <= '0';
				SD2 <= '0';
			when T3_RMW5 =>
				tcstate <= "110111";
				SYNC <= '0';
				VEC1 <= '0';
				SD1 <= '1';
				SD2 <= '0';
			when T4_RMW5 =>
				tcstate <= "101111";
				SYNC <= '0';
				VEC1 <= '0';
				SD1 <= '0';
				SD2 <= '1';
			when T2_RMW6 =>
				tcstate <= "111011";
				SYNC <= '0';
				VEC1 <= '0';
				SD1 <= '0';
				SD2 <= '0';
			when T3_RMW6 =>
				tcstate <= "110111";
				SYNC <= '0';
				VEC1 <= '0';
				SD1 <= '0';
				SD2 <= '0';
			when T4_RMW6 =>
				tcstate <= "101111";
				SYNC <= '0';
				VEC1 <= '0';
				SD1 <= '1';
				SD2 <= '0';
			when T5_RMW6 =>
				tcstate <= "011111";
				SYNC <= '0';
				VEC1 <= '0';
				SD1 <= '0';
				SD2 <= '1';
			when T2_RMW7 =>
				tcstate <= "111011";
				SYNC <= '0';
				VEC1 <= '0';
				SD1 <= '0';
				SD2 <= '0';
			when T3_RMW7 =>
				tcstate <= "110111";
				SYNC <= '0';
				VEC1 <= '0';
				SD1 <= '0';
				SD2 <= '0';
			when T4_RMW7_a =>
				tcstate <= "101111";
				SYNC <= '0';
				VEC1 <= '0';
				SD1 <= '0';
				SD2 <= '0';
			when T5_RMW7_a =>
				tcstate <= "011111";
				SYNC <= '0';
				VEC1 <= '0';
				SD1 <= '1';
				SD2 <= '0';
			when T6_RMW7_a =>
				tcstate <= "111111";
				SYNC <= '0';
				VEC1 <= '0';
				SD1 <= '0';
				SD2 <= '1';
			when T4_RMW7_b =>
				tcstate <= "101111";
				SYNC <= '0';
				VEC1 <= '0';
				SD1 <= '1';
				SD2 <= '0';
			when T5_RMW7_b =>
				tcstate <= "011111";
				SYNC <= '0';
				VEC1 <= '0';
				SD1 <= '0';
				SD2 <= '1';
			when others =>
				tcstate <= "111110";
				SYNC <= '0';
				VEC1 <= '0';
				SD1 <= '0';
				SD2 <= '0';
				
		end case;
	end process;

end rtl;
