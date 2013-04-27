-- Embedded Systems final project 
-- Team DoubleOFour
--   Anthony Erlinger
--   Arthy
--   Yu Chen
--   Jaebin Choi


library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
use IEEE.std_logic_unsigned.all;

package mos_6502 is
  component core_6502
    port(
    addr : out std_logic_vector(23 downto 0);
    data_in : in std_logic_vector(7 downto 0);
    data_out : out std_logic_vector(7 downto 0);

    clk : in std_logic;
    reset : in std_logic;
    irq_in : in std_logic;
    nmi_in : in std_logic;
    data_out_oe : out std_logic;
    we_pin : out std_logic;
    rd_pin : out std_logic;
    sync : out std_logic;
  );
  end component
end package;