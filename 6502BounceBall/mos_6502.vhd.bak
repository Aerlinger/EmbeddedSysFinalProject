library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
use work.constants.all;

entity mos_6502 is

	-- 32 bits total
	port(
		-- Data and address for data
		A		: out std_logic_vector(15 downto 0);
		DI		: in std_logic_vector(7 downto 0);
		DO		: out std_logic_vector(7 downto 0);

		reset	: in std_logic;
		clk		: in std_logic;
		ready	: in std_logic;
		IRQ_n	: in std_logic;
		NMI_n	: in std_logic;
		SO_n	: in std_logic;
		R_W_n	: out std_logic;
		Sync	: out std_logic
	);
	
end mos_6502;

architecture rtl of mos_6502 is

	-- Registers
	signal AC				: std_logic_vector(7 downto 0);
	signal X, Y				: std_logic_vector(7 downto 0);
	signal P, ADD, DL		: std_logic_vector(7 downto 0);
	signal ABH				: std_logic_vector(7 downto 0);
	signal ABL				: std_logic_vector(8 downto 0);
	signal PC				: unsigned(15 downto 0);
	signal S				: unsigned(7 downto 0);

	signal IR				: std_logic_vector(7 downto 0);

	signal MCycle			: std_logic_vector(2 downto 0);

	signal ALU_Op_r			: std_logic_vector(3 downto 0);
	signal Write_Data_r		: std_logic_vector(2 downto 0);
	signal Set_Addr_To_r	: std_logic_vector(1 downto 0);

	signal PCAdder			: unsigned(8 downto 0);

	-- flags for if we are in RST, IRQ, or NMI cycle:
	signal RstCycle			: std_logic;
	signal IRQCycle			: std_logic;
	signal NMICycle			: std_logic;

	signal B_o				: std_logic;	-- Break?
	signal SO_n_o			: std_logic;	-- Stack Overflow?
	signal IRQ_n_o			: std_logic;	-- IRQ?
	signal NMI_n_o			: std_logic;	-- Non maskable interrupt?
	signal NMIAct			: std_logic;	-- NMI taken?

	signal Break			: std_logic;

	-- ALU signals
	signal BusA				: std_logic_vector(7 downto 0);
	signal BusA_r			: std_logic_vector(7 downto 0);
	signal BusB				: std_logic_vector(7 downto 0);
	signal ALU_Q			: std_logic_vector(7 downto 0);
	signal P_Out			: std_logic_vector(7 downto 0);

	-- Micro code outputs
	signal LCycle			: std_logic_vector(2 downto 0);	-- NextCycle?
	signal ALU_Op			: std_logic_vector(3 downto 0);
	signal Set_BusA_To		: std_logic_vector(2 downto 0);
	signal Set_Addr_To		: std_logic_vector(1 downto 0);
	signal Write_Data		: std_logic_vector(2 downto 0);
	signal Jump				: std_logic_vector(1 downto 0);
	signal BAAdd			: std_logic_vector(1 downto 0);
	signal BreakAtNA		: std_logic;
	signal ADDAdd			: std_logic;
	signal PCAdd			: std_logic;
	signal Inc_S			: std_logic;
	signal Dec_S			: std_logic;
	signal LDA				: std_logic;
	signal LDP				: std_logic;
	signal LDX				: std_logic;
	signal LDY				: std_logic;
	signal LDS				: std_logic;
	signal LDDI				: std_logic;
	signal LDALU			: std_logic;
	signal LDADD			: std_logic;
	signal LDABL			: std_logic;
	signal LDABH			: std_logic;
	signal SaveP			: std_logic;
	signal Write			: std_logic;

	component Control
	port(
		IR				: in std_logic_vector(7 downto 0);
		MCycle			: in std_logic_vector(2 downto 0);
		P				: in std_logic_vector(7 downto 0);

		LCycle			: out std_logic_vector(2 downto 0);	   -- Resulting cycle
		ALU_Op			: out std_logic_vector(3 downto 0);	   -- Opcode for the ALU
		Set_BusA_To		: out std_logic_vector(2 downto 0);    -- DI, A, X, Y, S, P
		Set_Addr_To		: out std_logic_vector(1 downto 0);    -- PC Adder, S, ADD, BA
		Write_Data		: out std_logic_vector(2 downto 0);    -- DL, A, X, Y, S, P, PCL, PCH
		Jump			: out std_logic_vector(1 downto 0);    -- PC, +1, DIDL, Rel
		BAAdd			: out std_logic_vector(1 downto 0);	   -- None, DB Inc, BA Add, BA Adj
		BreakAtNA		: out std_logic;	-- Break at ??
		ADDAdd			: out std_logic;	-- ???
		PCAdd			: out std_logic;	-- Program counter add
		Inc_S			: out std_logic;	-- Increment Stack
		Dec_S			: out std_logic;	-- Decrement Stack
		LDA				: out std_logic;	-- Load Accumulator
		LDP				: out std_logic;	-- Load Processor status register
		LDX				: out std_logic;	-- Load X Register
		LDY				: out std_logic;	-- Load Y Register
		LDS				: out std_logic;	-- Load Stack Register
		LDDI			: out std_logic;	-- Load (I_ADDDC?)
		LDALU			: out std_logic;	-- Load ALU
		LDADD			: out std_logic;	-- Load ADDD register
		LDABL			: out std_logic;	-- Load Address Bus Low
		LDABH			: out std_logic;	-- Load Address Bus High
		SaveP			: out std_logic;	-- Save processor status
		Write			: out std_logic
	);
	end component;

	component ALU
	port(
		Op		: in std_logic_vector(3 downto 0);
		BusA	: in std_logic_vector(7 downto 0);
		BusB	: in std_logic_vector(7 downto 0);
		P_In	: in std_logic_vector(7 downto 0);
		P_Out	: out std_logic_vector(7 downto 0);
		Q		: out std_logic_vector(7 downto 0)
	);
	end component;

begin

	Break 	<= (BreakAtNA and not ABL(8)) or (PCAdd and not PCAdder(8));
	PCAdder <= 	resize(PC(7 downto 0),9) + resize(unsigned(DL(7) & DL),9) when PCAdd = '1' else "0" & PC(7 downto 0);
	Sync 	<= '1' 	when MCycle = "000" else '0';

	C_CTL : Control
		port map(
			IR 			=> IR,
			MCycle 		=> MCycle,
			P 			=> P,
			LCycle 		=> LCycle,
			ALU_Op 		=> ALU_Op,
			Set_BusA_To => Set_BusA_To,
			Set_Addr_To => Set_Addr_To,
			Write_Data 	=> Write_Data,
			Jump 		=> Jump,
			BAAdd 		=> BAAdd,
			BreakAtNA 	=> BreakAtNA,
			ADDAdd 		=> ADDAdd,
			PCAdd 		=> PCAdd,
			Inc_S 		=> Inc_S,
			Dec_S 		=> Dec_S,
			LDA 		=> LDA,
			LDP 		=> LDP,
			LDX 		=> LDX,
			LDY 		=> LDY,
			LDS 		=> LDS,
			LDDI 		=> LDDI,
			LDALU 		=> LDALU,
			LDADD 		=> LDADD,
			LDABL 		=> LDABL,
			LDABH 		=> LDABH,
			SaveP 		=> SaveP,
			Write 		=> Write
		);

	C_ALU : ALU
		port map(
			Op 		=> ALU_Op_r,
			BusA 	=> BusA_r,
			BusB 	=> BusB,
			P_In 	=> P,
			P_Out 	=> P_Out,
			Q 		=> ALU_Q
		);

	process (reset, clk)
	begin
		if reset = '0' then
			PC 	<= (others => '0');  -- Program Counter
			IR 	<= "00000000";		-- Simulate a BRK

			S 	<= (others => '0');

			ALU_Op_r 		<= "1100";	-- ALU is bit by default
			Write_Data_r 	<= "000";	-- Write to DL by default
			Set_Addr_To_r 	<= "00";	-- PC by default

			R_W_n <= '1';

		elsif rising_edge(clk) and clk = '1' then
			if ready = '1' then
				R_W_n <= not Write or RstCycle;

				if MCycle  = "000" then
					if IRQCycle = '0' and NMICycle = '0' then
						PC <= PC + 1;
					end if;

					if IRQCycle = '1' or NMICycle = '1' then
						IR <= "00000000";
					else
						IR <= DI;
					end if;
				end if;

				ALU_Op_r 		<= ALU_Op;
				Write_Data_r 	<= Write_Data;

				if Break = '1' then
					Set_Addr_To_r <= "00";
				else
					Set_Addr_To_r <= Set_Addr_To;
				end if;

				if Inc_S = '1' then
					S <= S + 1;
				end if;
				if Dec_S = '1' and RstCycle = '0' then
					S <= S - 1;
				end if;
				if LDS = '1' then
					S(7 downto 0) <= unsigned(ALU_Q);
				end if;

				if IR = "00000000" and MCycle = "001" and IRQCycle = '0' and NMICycle = '0' then
					PC <= PC + 1;
				end if;
				case Jump is
					when "01" =>
						PC <= PC + 1;
					when "10" =>
						PC <= unsigned(DI & DL);
					when "11" =>
						if PCAdder(8) = '1' then
							if DL(7) = '0' then
								PC(15 downto 8) <= PC(15 downto 8) + 1;
							else
								PC(15 downto 8) <= PC(15 downto 8) - 1;
							end if;
						end if;
						PC(7 downto 0) <= PCAdder(7 downto 0);
					when others =>
				end case;
			end if;
		end if;
	end process;

	process (clk)
	begin
		if rising_edge(clk) and clk = '1' then
			if ready = '1' then

				-- T0?
				if MCycle = "000" then
					if LDA = '1' then
						AC(7 downto 0) <= ALU_Q;
					end if;
					if LDX = '1' then
						X(7 downto 0) <= ALU_Q;
					end if;
					if LDY = '1' then
						Y(7 downto 0) <= ALU_Q;
					end if;
					if (LDA or LDX or LDY) = '1' then
						P <= P_Out;
					end if;
				end if;

				if SaveP = '1' then
					P <= P_Out;
				end if;

				if LDP = '1' then
					P <= ALU_Q;
				end if;

				if IR(4 downto 0) = "11000" then
					case IR(7 downto 5) is
					when "000" =>
						P(Flag_C) <= '0';
					when "001" =>
						P(Flag_C) <= '1';
					when "010" =>
						P(Flag_I) <= '0';
					when "011" =>
						P(Flag_I) <= '1';
					when "101" =>
						P(Flag_V) <= '0';
					when "110" =>
						P(Flag_D) <= '0';
					when "111" =>
						P(Flag_D) <= '1';
					when others =>
					end case;
				end if;

				if IR = "00000000" and MCycle = "011" and RstCycle = '0' and NMICycle = '0' then
					P(Flag_B) <= '1';
				end if;

				if IR = "00000000" and MCycle = "100" and RstCycle = '0' and NMICycle = '0' then
					P(Flag_I) <= '1';
					P(Flag_B) <= B_o;
				end if;

				if SO_n_o = '1' and SO_n = '0' then
					P(Flag_V) <= '1';
				end if;

				P(Flag_1) <= '1';

				B_o		<= P(Flag_B);
				SO_n_o 	<= SO_n;
				IRQ_n_o <= IRQ_n;
				NMI_n_o <= NMI_n;
			end if;
		end if;
	end process;

---------------------------------------------------------------------------
--
-- Bus Control Lines:
--
---------------------------------------------------------------------------

	process (reset, clk)
	begin
		if reset = '0' then
			BusA_r 	<= (others => '0');
			BusB 	<= (others => '0');
			ADD 	<= (others => '0');
			ABL 	<= (others => '0');
			ABH 	<= (others => '0');
			DL 		<= (others => '0');

		elsif rising_edge(clk) and clk = '1' then
			if ready = '1' then
				BusA_r 	<= BusA;
				BusB 	<= DI;

				case BAAdd is
					when "01" =>
						-- BA Inc
						ADD <= std_logic_vector(unsigned(ADD) + 1);
						ABL <= std_logic_vector(unsigned(ABL) + 1);
					when "10" =>
						-- BA Add
						ABL <= std_logic_vector(resize(unsigned(ABL(7 downto 0)),9) + resize(unsigned(BusA),9));
					when "11" =>
						-- BA Adj
						if ABL(8) = '1' then
							ABH <= std_logic_vector(unsigned(ABH) + 1);
						end if;
					when others =>
				end case;

				if ADDAdd = '1' then
					ADD <= std_logic_vector(unsigned(ADD) + unsigned(X(7 downto 0)));
				end if;

				-- BRK
				if IR = "00000000" then
					ABL <= (others => '1');
					ABH <= (others => '1');
					if RstCycle = '1' then
						ABL(2 downto 0) <= "100";
					elsif NMICycle = '1' then
						ABL(2 downto 0) <= "010";
					else
						ABL(2 downto 0) <= "110";
					end if;
					if Set_addr_To_r = "11" then
						ABL(0) <= '1';
					end if;
				end if;

				if LDDI = '1' then
					DL <= DI;
				end if;
				if LDALU = '1' then
					DL <= ALU_Q;
				end if;
				if LDADD = '1' then
					ADD <= DI;
				end if;
				if LDABL = '1' then
					ABL(7 downto 0) <= DI;
				end if;
				if LDABH = '1' then
					ABH <= DI;
				end if;
			end if;
		end if;
	end process;


	with Set_BusA_To select
		BusA <= DI 	when "000",
				AC 	when "001",
				X 	when "010",
				Y 	when "011",
				std_logic_vector(S) when "100",
				P when "101",
				(others => '-') when others;

	with Set_Addr_To_r select
		A <= 	"00000001" & std_logic_vector(S) 	when "01",
		 		"00000000" & ADD 					when "10",
				"00000000" & ABH & ABL	 			when "11",
				std_logic_vector(PC(15 downto 8)) & std_logic_vector(PCAdder(7 downto 0)) when others;
			
	with Write_Data_r select
		DO <= 	DL 					when "000",
				AC(7 downto 0) 		when "001",
				X(7 downto 0) 		when "010",
				Y(7 downto 0) 		when "011",
				std_logic_vector(S) when "100",
				P 									when "101",
				std_logic_vector(PC(7 downto 0)) 	when "110",
				std_logic_vector(PC(15 downto 8)) 	when others;

-------------------------------------------------------------------------
--
-- Main state machine
--
-------------------------------------------------------------------------

	process (reset, clk)
	begin
		if reset = '0' then
			MCycle <= "001";
			RstCycle <= '1';
			IRQCycle <= '0';
			NMICycle <= '0';
			NMIAct <= '0';

		elsif rising_edge(clk) and clk = '1' then
			if ready = '1' then

				-- T <= 000 when CURENT CYCLE FINISHED
				if MCycle = LCycle or Break = '1' then
					MCycle <= "000";
					RstCycle <= '0';
					IRQCycle <= '0';
					NMICycle <= '0';
					if NMIAct = '1' then
						NMICycle <= '1';
					elsif IRQ_n_o = '0' and P(Flag_I) = '0' then
						IRQCycle <= '1';
					end if;

				-- OTHERWISE, NEXT CYCLE
				else
					MCycle <= std_logic_vector(unsigned(MCycle) + 1);
				end if;

				if NMICycle = '1' then
					NMIAct <= '0';
				end if;

				if NMI_n_o = '1' and NMI_n = '0' then
					NMIAct <= '1';
				end if;
			end if;
		end if;
	end process;

end architecture;
