----------------------------------------------------------------------------
----------------------------------------------------------------------------
--  The Free IP Project
--  VHDL Free-6502 Core
--  (c) 1999, The Free IP Project and David Kessner
--
--
--  FREE IP GENERAL PUBLIC LICENSE
--  TERMS AND CONDITIONS FOR USE, COPYING, DISTRIBUTION, AND MODIFICATION
--
--  1.  You may copy and distribute verbatim copies of this core, as long
--      as this file, and the other associated files, remain intact and
--      unmodified.  Modifications are outlined below.  Also, see the
--      import/export warning above for further restrictions on
--      distribution.
--  2.  You may use this core in any way, be it academic, commercial, or
--      military.  Modified or not.  
--  3.  Distribution of this core must be free of charge.  Charging is
--      allowed only for value added services.  Value added services
--      would include copying fees, modifications, customizations, and
--      inclusion in other products.
--  4.  If a modified source code is distributed, the original unmodified
--      source code must also be included (or a link to the Free IP web
--      site).  In the modified source code there must be clear
--      identification of the modified version.
--  5.  Visit the Free IP web site for additional information.
--      http://www.free-ip.com
--
----------------------------------------------------------------------------
----------------------------------------------------------------------------
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

package test_lib is
  component testsuite
  end component;
  
  component timer
    port (
			clk	:in std_logic;
      reset :in std_logic;
      enable:in std_logic;
      data  :in std_logic_vector (7 downto 0);
      addr  :in std_logic;  -- one bit only
      irq   :out std_logic
    );
  end component;
end test_lib;


-----------------------------------------------------------------------------
-----------------------------------------------------------------------------
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;
library work;
use work.test_lib.all;

entity timer is
    port (clk	:in std_logic;
          reset :in std_logic;
          enable:in std_logic;
          data  :in std_logic_vector (7 downto 0);
          addr  :in std_logic;  -- one bit only
          irq   :out std_logic
         );
end timer;

architecture arch_timer of timer is
  type STATES is (IDLE, RUNNING, TRIGGERED);
  signal state :STATES := IDLE;
  signal count :std_logic_vector (7 downto 0) := "00000000";

begin

  process (reset, clk, enable, data, addr)
  begin
    if reset='1' then
      state <= IDLE;
      count <= "00000000";
      irq <= '0';
    elsif clk'event and clk='1' then
      case state is
        when IDLE =>
            if enable='1' and addr='0' then
              count <= data;
              state <= RUNNING;
            end if;
          
        when RUNNING =>
            if count="00000000" then
              state <= TRIGGERED;
              irq <= '1';
            else
              count <= count - '1';
            end if;
          
        when TRIGGERED =>
            if enable='1' and addr='1' then
              state <= IDLE;
              irq <= '0';
            end if;
            
        when others =>
            state <= IDLE;
            irq <= '0';
            
      end case;
    end if;
  end process;

end arch_timer;

  


-----------------------------------------------------------------------------
-----------------------------------------------------------------------------
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

use work.components.all;
use work.ram_lib.all;
use work.test_lib.all;
use work.test_suite.all;


entity testsuite is
end testsuite;


architecture arch_testsuite of testsuite is
  signal clk		:std_logic := '1';
  signal reset		:std_logic := '1';
  signal irq		:std_logic := '0';
  signal nmi		:std_logic := '0';
  signal addr		:std_logic_vector (15 downto 0) := "0000000000000000";
  signal din		:std_logic_vector (7 downto 0) := "00000000";
  signal dout		:std_logic_vector (7 downto 0) := "00000000";
  signal dout_oe	:std_logic := '0';
  signal we		:std_logic := '0';
  signal re		:std_logic := '0';
  signal sync		:std_logic := '0';

  signal rom_data	:std_logic_vector (7 downto 0) := "00000000";
  signal ram_data	:std_logic_vector (7 downto 0) := "00000000";
  signal ram_we		:std_logic  := '0';

  signal postcode	:std_logic_vector (7 downto 0) := "00000000";

  signal irq_timer_sel  :std_logic := '0';
  signal nmi_timer_sel  :std_logic := '0';
 
  type log_file is file of integer;
  file log :log_file open write_mode is "testsuite.log";

  type opcode_file is file of integer;
  file opcode_log :log_file open write_mode is "opcode.log";
begin
  process (clk)
  begin
    if clk='1' then
      clk <= '0' after 20 ns, '1' after 40 ns;
    end if;
  end process;

  reset <= '1' after 0 ns, '0' after 125 ns;

--  U1: mos_6502 port map (
--		clk => clk,
--		reset, 
--		irq, 
--		nmi, 
--		addr, 
--		din, 
--		dout, 
--		dout_oe, 
--		we, 
--		re, 
--		sync
--	);
	
	CPUConnect: mos_6502 port map(
		clk 	=> clk,
		
		A			=> addr,
		DI 		=> din, 
		DO 		=> dout,
		
		reset => reset,
		ready => '1',
		
		IRQ_n => irq,
		NMI_n	=> nmi,
		SO_n  => '0',
		R_W_n	=> re
	);

  ROM0: test_rom port map (addr(11 downto 0), rom_data);
  RAM0:  ram_dp
           generic map (
							15, ram_data'high+1, 
							0, 
							0
						)
           port map (
						reset, 
						clk, 
						ram_we, 
						addr(14 downto 0), 
            dout, 
						clk, 
						addr(14 downto 0), 
						ram_data
					);

  ram_we <= '1' when addr(15)='0' and we='1' else '0';
  din <= ram_data when addr(15)='0' and re='1' else
         rom_data when addr(15)='1' and re='1' else
         "00000000";

  irq_timer_sel <= '1' when addr(15 downto 1)="100000000000010" and we='1' else '0';
  nmi_timer_sel <= '1' when addr(15 downto 1)="100000000000011" and we='1' else '0';

  IRQ_TIMER0:  timer port map (clk, reset, irq_timer_sel, dout, addr(0), irq);
  NMI_TIMER0:  timer port map (clk, reset, nmi_timer_sel, dout, addr(0), nmi);


  -- Handle the special registers
  -- 0x8000 = HALT
  -- 0x8001 = POSTCODE
  -- 0x8002 = LOGFILE
  process (clk)
    variable d	:integer := 0;
    variable i	:integer range 0 to 10 := 0;
  begin
    if clk'event and clk='0' then
      if we='1' then
        case addr is
          when "1000000000000000" => 	-- HALT simulation
                assert 1=0
                    report "Simulation Ended via 6502 software command"
                    severity failure;
                  
          when "1000000000000001" => 	-- Postcode write
              postcode <= dout;
              
          when "1000000000000010" => 	-- Log file output
	      case i is
        	  when 0 =>		d := conv_integer(dout);
          			        i := i + 1;
	          when 1 =>             d := d + (conv_integer(dout) * 256);
        	  		        i := i + 1;
	          when 2 =>             d := d + (conv_integer(dout) * 256 * 256);
        	  		        i := i + 1;
	          when 3 =>             d := d + (conv_integer(dout) * 256 * 256 * 256);
        	                        i := 0;
                	                write (log, d);
	          when others =>	d := 0;
        	                        i := 0;
	        end case;

          when others =>
        end case;
      end if;
    end if;
  end process;

  -- Output the opcode + address of all instuctions executed
  process (clk)
    variable a :integer :=0;
    variable b :integer :=0;
  begin
    if clk'event and clk='1' then
      if sync='1' then
        a := conv_integer(din);
        b := conv_integer(addr)*256 + a;
        write (opcode_log, b);
      end if;
    end if;
  end process;
  
end arch_testsuite;



