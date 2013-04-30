library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
--use ieee.std_logic_arith.all;

entity ALU is 

  port( 

  A: in std_logic_vector(7 downto 0);
  B: in std_logic_vector(7 downto 0);
  ADD: out std_logic_vector(7 downto 0);

  DAA: in std_logic;  -- Decimal Enable (Probably not needed)
  I_ADDC: in std_logic;
  
  AVR: out std_logic;  -- Overflow
  ACR: out std_logic;  -- Carry
  HC: out std_logic;   -- Half carry

  -- OUTPUT MODES
  SUMS: in std_logic;
  ANDS: in std_logic;
  EORS: in std_logic;
  ORS: in std_logic;
  SRS: in std_logic
);

end ALU;

architecture rtl of ALU is
signal data : unsigned(7 downto 0);
begin

  process(A, B, SUMS, ANDS, EORS, ORS, SRS)
  begin

    B <= '00000000';
    data <= A + B;

  --   if (SUMS='1') then
		-- if I_ADDC='1' then
		-- 	data<=(('0'&unsigned(A))+('0'&unsigned(B))+1);
		-- 	else
		-- 	data<=(('0'&unsigned(A))+('0'&unsigned(B)));
		-- 	end if;
  --   end if;

  --   if (ANDS='1') then
  --     ADD <= A and B;
  --   end if;

  --   if (EORS='1') then
  --     ADD <= A xor B;
  --   end if;

  --   if (ORS='1')  then
  --     ADD <= A or B;
  --   end if;

  --   if (SRS='1') then
  --     ADD <= A srl 1;
  --   end if;

    -- TODO: Implement Carry, Half Carry, Overflow.
  end process;
	
	Carry_out<=data(8);
	ADD <= data(7 downto 0);
end rtl;
