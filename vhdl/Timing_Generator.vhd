library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity Timing_Generator is
  port(
		clk : in std_logic;
		clk_mask : in std_logic;
		Cycle_num : in std_logic_vector(3 downto 0);
		tcstate : out std_logic_vector(5 downto 0)
  );
end Timing_Generator;

architecture rtl of Timing_Generator is
  signal Din  : std_logic_vector(5 downto 0) :=b"000001";
  signal Dout : std_logic_vector(5 downto 0) :=b"000001";
  signal cycle_total : integer :=0;
  signal cycle       : integer :=0;
begin

	process (Dout, Cycle_num)
	begin
    if Dout(0)='1' then  --end of one opcode operation, load new opcode cycle_num.
      case to_integer(unsigned(Cycle_num)) is
        when 2 => Din <= b"000010"; cycle_total <= 2;    
        when 3 => Din <= b"000100"; cycle_total <= 3;    
        when 4 => Din <= b"001000"; cycle_total <= 4;    
        when 5 => Din <= b"010000"; cycle_total <= 5;    
        when 6 => Din <= b"100000"; cycle_total <= 6;    
        --when 7 => Din <= b"1000000"; cycle_total <= 7;    
        when others => Din <= "000001"; cycle_total <= 1; 
      end case;
    else Din(4 downto 0) <= Dout(5 downto 1); Din(5) <= '0';
    end if;
	end process;
	
	process(clk)
    begin
    if rising_edge(clk) then
      if clk_mask='1' then
        Dout <= Din;
        if Dout(0)='1' then cycle <= cycle_total-1;
        else cycle <= cycle-1;
        end if;
      end if;	
    end if;
	end process;
	
	process (cycle)
  begin
    if (cycle=1) then tcstate <= b"011111";  --T0;
    elsif (cycle=0) then tcstate <= b"101111"; --T1
    elsif (cycle_total-cycle=1) then tcstate <= b"110111";  --T2
    elsif (cycle_total-cycle=2) then tcstate <= b"111011";  --T3
    elsif (cycle_total-cycle=3) then tcstate <= b"111101";  --T4
    elsif (cycle_total-cycle=4) then tcstate <= b"111110";  --T5
    --elsif (cycle_total-cycle=4) then tcstate <= b"111111";  --T6
    --tcstate <= Dout;
    end if;
	end process;
end rtl;
