library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use work.components.all;

entity SRAMCtrl is
port (
		reset, clk, W_R : in  std_logic;
		ROM_data, DOR  : in std_logic_vector(7 downto 0);
		databus    : out std_logic_vector(7 downto 0);
		AddressBus : in std_logic_vector(15 downto 0);
		ROM_address : out std_logic_vector(15 downto 0);
		SRAM_DQ    : inout unsigned(15 downto 0);
		SRAM_ADDR  : out unsigned(17 downto 0);
		SRAM_UB_N,            -- High-byte Data Mask
		SRAM_LB_N,            -- Low-byte Data Mask
		SRAM_WE_N,            -- Write Enable
		SRAM_CE_N,            -- Chip Enable
		SRAM_OE_N : out std_logic  -- Output Enable
);
end SRAMCtrl;

architecture rtl of SRAMCtrl is
	--signal address : unsigned(15 downto 0):=x"0000";
	signal counter1: unsigned(3 downto 0) :=x"0";
begin
	process(reset, clk, W_R, ROM_data, DOR, AddressBus, SRAM_DQ)
		variable address : unsigned(15 downto 0):=x"0000";
		begin
			SRAM_ADDR(17 downto 16)<="00";
			SRAM_CE_N<='0';
			SRAM_LB_N<='0';
			SRAM_UB_N<='1';
			
			if reset='1' then 
				SRAM_WE_N<='0';
				SRAM_OE_N<='1';
				databus<=(others=>'0');
					if rising_edge(clk) then
						if (counter1=x"0" or counter1=x"1") then 
						counter1<=counter1+1;  
						else counter1<=counter1;
						end if;
						--to make sure that address=x"0000" is written correctly
						if (counter1=x"0" or counter1=x"1") then address:=address;
							elsif address=x"ffff" then 
								address:=x"0000";
							else	
								address:=address+1;
						end if;
					end if;
					
					if address(15 downto 8)=x"00" then SRAM_DQ(7 downto 0)<=unsigned(ROM_data);
					--elsif address(15 downto 0)=x"fffe" then SRAM_DQ(7 downto 0)<=x"fd";
					--elsif address(15 downto 0)=x"ffff" then SRAM_DQ(7 downto 0)<=x"ff";
					else SRAM_DQ(7 downto 0)<=x"00";
					end if;
				--SRAM_DQ(15 downto 8)<=x"00";
				SRAM_ADDR(15 downto 0)<=address;
				ROM_address<=std_logic_vector(address);
				
			else
				SRAM_WE_N<=W_R;
				SRAM_OE_N<=not (W_R);
				SRAM_ADDR(15 downto 0)<=unsigned(AddressBus);
					if W_R='0' then 
						SRAM_DQ(7 downto 0)<=unsigned(DOR);
						databus<=(others=>'0');
					else SRAM_DQ(7 downto 0)<=(others=>'Z');
						databus<=std_logic_vector(SRAM_DQ(7 downto 0));
					end if;
				ROM_address<=(others=>'0');
			
			end if;
		end process;
end rtl;

			
			
					
					
			