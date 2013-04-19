library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity LDA_steptest is
port(
		Databus :in std_logic_vector(7 downto 0);
		Addrbus :out std_logic_vector(15 downto 0);
      clk      :in std_logic);
end LDA_steptest;

architecture imp of LDA_steptest is
signal Clk_mask, Clk_mask_bar : std_logic;

component Two_Phase_CLK
port(
		Clk  : in std_logic;
		Clk_mask : out std_logic );
end component;

begin
TwoPhaseClk: Two_Phase_CLK port map(clk=>clk, clk_mask=>clk_mask);
end imp;
