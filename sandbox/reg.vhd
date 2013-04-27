library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity reg is
  port(
    data_in: in std_logic_vector(7 downto 0);
    data_out: out std_logic_vector(7 downto 0);
    clk: in std_logic;
  );
end reg;


architecture rtl of reg is
  signal value: std_logic_vector(7 downto 0);
begin

  process(data_in, clk)
  begin
    if (clock='1' and clock'event) then
      value <= data_in;
    end if;
  end process;

  -- Concurrent statement:
  data_out <= value;

end behav;
