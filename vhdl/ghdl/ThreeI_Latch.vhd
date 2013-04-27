library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity ThreeI_Latch is
  port (
		Din_A  : in  std_logic_vector(7 downto 0);
		Din_B  : in  std_logic_vector(7 downto 0);
		Din_C  : in  std_logic_vector(7 downto 0);
		Dout : out std_logic_vector(7 downto 0);
		Load_A : in std_logic;
		Load_B : in std_logic;
		Load_C : in std_logic;
		clk  : in std_logic);
end ThreeI_Latch;

architecture rtl of ThreeI_Latch is
  signal data : std_logic_vector(7 downto 0) := x"00";
  signal q		: std_logic_vector(7 downto 0) := x"00";
begin
	process (clk, Din_A, Din_B, Din_C, Load_A, Load_B, load_C, q)
	begin
		if (Load_A='1') then
      data<=Din_A;
		elsif (Load_B='1') then
      data<=Din_B;
		elsif (Load_C='1') then
      data<=Din_C;
		else 
      data<=q;
		end if;
		
		if rising_edge(clk) then
      q<=data;
		end if;
	end process;
	
	Dout<=q;
end rtl;
