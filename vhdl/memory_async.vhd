library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity memory_async is
  -- Constants (bit depth)
  generic (
    DATA_WIDTH :integer := 8;
    ADDR_WIDTH :integer := 8
  );

  port (
    address : in std_logic_vector(ADDR_WIDTH-1 downto 0);
    data : inout std_logic_vector(DATA_WIDTH-1 downto 0);
    cs : in std_logic;
    we : in std_logic;
    oe : in std_logic
  );

end entity;


architecture rtl of memory_async is
  -- Internal variables:
  constant RAM_DEPTH :integer := 2**ADDR_WIDTH;
  signal data_out: std_logic_vector (DATA_WIDTH-1 downto 0);

  type RAM is array (integer range <>) of std_logic_vector (DATA_WIDTH-1 downto 0);
  signal mem: RAM (0 to RAM_DEPTH - 1);
begin

  --- Tri-state Buffer control
  data <= data_out when (cs = '1' and oe = '1' and we = '0') else (others => 'Z');

  -- Memory Write Block:
  MEM_WRITE:
  process (address, data, cs, we) begin
    if (cs='1' and we='1') then 
      mem(conv_integer(address)) <= data;
    end if;
  end process;

  -- Memory Read Block:
  MEM_READ:
  process (address, cs, we, oe, mem) begin
    if (cs='1' and we='0' and oe='1') then
      data_out <= mem(conv_integer(address));
    end if;
  end process;

end architecture;
