library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity memory_sync is
  port( 
    clk: in std_logic;
    enable: in std_logic;
    read: in std_logic;
    write: in std_logic;
    read_addr: in std_logic_vector(7 downto 0);
    write_addr: in std_logic_vector(7 downto 0);
    Data_in: in std_logic_vector(7 downto 0);
    Data_out: out std_logic_vector(7 downto 0)
  );
end memory_sync;


architecture behav of memory_sync is
  type ram_type is array (0 to 255) of std_logic_vector(7 downto 0);
  signal tmp_ram: ram_type;
begin

  -- READ:
  process(clk, read)
  begin
    if (clk'event and clk='1') then
      if enable='1' then
        if read='1' then
          -- conv_integer changes the type from std_logic_vector to integer
          Data_out <= tmp_ram(conv_integer(read_addr));
        else
          Data_out <= (Data_out'range => 'Z');
        end if;
      end if;
    end if;
  end process;

  -- WRITE:
  process(clk, write)
  begin
    if (clk'event and clk='1') then
      if enable = '1' then
        if write='1' then
          tmp_ram(conv_integer(write_addr)) <= Data_in;
        end if;
      end if;
    end if;
  end process;

end behav;
