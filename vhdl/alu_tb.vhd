library ieee;
use ieee.std_logic_1165.all;
use ieee.numeric_std.all;

entity alu_tb is
end alu_tb;

architecture rtl of alu_tb is
  signal Op: std_logic_vector(7 downto 0);
  signal A: std_logic_vector(7 downto 0);
  signal B: std_logic_vector(7 downto 0);
  signal P_In: std_logic_vector(7 downto 0);
  signal P_Out: std_logic_vector(7 downto 0);
  signal Q: std_logic_vector(7 downto 0);
begin
  

  U_ALU: alu port_map(Op, A, B, P_In, P_Out, Q)
  -- 15 possible ALU operations:

  process
    begin
      -- ORA ----------------------------------------------
      Op <= "0000";  
      A <= "01010101";
      B <= "00110000";

      assert(Q="01110101")
      report "ERROR: ORA" severity error;

      -- AND ----------------------------------------------
      Op <= "0001"
      A <= "01010101";      
      B <= "00111111";

      assert(Q="00010101")
      report "ERROR: ORA" severity error;

      -- EOR ----------------------------------------------
      Op <= "0010"  -- EOR 
      A <= "01010101";      
      B <= "00110000";

      assert(Q="01100101")
      report "ERROR: EOR" severity error;

      -- ADC ----------------------------------------------
      Op <= "0011"  -- ADC  (Flags ADC_N ADC_V, or ADC_Z)

      A <= "11110000";
      B <= "00001111";

      assert(Q="11111111")
      report "Error ADC FF + F0 doesn't equal FF.";

      
      -- Zero? --
      A <= "00000000";
      B <= "00000000";

      assert(Q="00000000")
      report "Error ADC 0 + 0 doesn't equal 0.";

      A <= "11111111";
      B <= "11000000";

      assert(Q="00000000")
      report "Error ADC FF + F0 doesn't equal FF.";

      -- Overflow? -- 
      assert(P_Out)
      report "Error ADC FF + F0 doesn't set overflow flag";
      

      -- Unused? ----------------------------------------------      
      Op <= "0100"  -- Unused? (Flags Z=1 if A and B are all 0)
      A <= "01010101";
      B <= "00110000";

      assert(Q="01110101")
      report "ERROR: ORA" severity error;

      -- LDA ---------------------------------------------- 
      Op <= "0101"  -- LDA 
      A <= "01010101";
      B <= "00110000";

      assert(Q="01110101")
      report "ERROR: ORA" severity error;

      -- CMP ---------------------------------------------- 
      Op <= "0110"  -- CMP (Flags SBC_N or SBC_Z)
      A <= "01010101";
      B <= "00110000";

      assert(Q="01110101")
      report "ERROR: ORA" severity error;

      -- SBC ---------------------------------------------- 
      Op <= "0111"  -- SBC (Flags SBC_N or SBC_Z)

      -- ASL ----------------------------------------------
      Op <= "1000"  -- ASL

      -- ROL ----------------------------------------------
      Op <= "1001"  -- ROL

      -- LSR ----------------------------------------------
      Op <= "1010"  -- LSR 

      -- ROR ----------------------------------------------
      Op <= "1011"  -- ROR Q := P_In(Flag_C) & BusA(7 downto 1);

      -- BIT ----------------------------------------------
      Op <= "1100"  -- BIT (Flags Z=1 if A and B are all 0)

      -- DEC ----------------------------------------------
      Op <= "1110"  -- DEC (A-1)

      -- INC ----------------------------------------------
      Op <= "1111"  -- INC (A+1)


      -- PS Register State
      Op <= "0011"




end rtl;
