-- Contains specification for registers

component index_register is
  port(
    bus_enable : in std_logic;
    load_enable : in std_logic;

    data_in : in std_logic_vector(7 downto 0);
    data_in : in std_logic_vector(7 downto 0);
  );
end component;


component accumulator is
  port(
    d_bus_enable : in std_logic; -- AC/DB
    s_bus_enable : in std_logic; -- AC/SB
    load_enable : in std_logic;  -- SB/AC

    data_in : in std_logic_vector(7 downto 0);     -- Data input from D bus
    dec_data_in : in std_logic_vector(7 downto 0); -- Data input from Decimal Adder
    data_out : in std_logic_vector(7 downto 0);    -- Data output to S bus
  );
end component;

-- 
-- Defines the status of seven states of the processor
--   Z: zero
--   I: interrupt
--   C: Carry
--   V: ?
--   N:
component processor_status_register is
  port(
    d_bus_enable : in std_logic; -- P/DB
    ir5: in std_logic; -- AC/SB
    acr: in std_logic;  -- SB/AC
    avr: in std_logic;  -- SB/AC
    dbz: in std_logic;  -- SB/AC

    data_in : in std_logic_vector(7 downto 0);     -- Data input from D bus
    data_out : in std_logic_vector(7 downto 0);    -- Data output to D bus
  );
end component;


component stack_pointer_register is
  port(
    d_bus_enable : in std_logic; -- P/DB
    ir5: in std_logic; -- AC/SB
    acr: in std_logic;  -- SB/AC
    avr: in std_logic;  -- SB/AC
    dbz: in std_logic;  -- SB/AC

    data_in : in std_logic_vector(7 downto 0);     -- Data input from D bus
    data_out_s: in std_logic_vector(7 downto 0);    -- Data output to D bus
    data_out_d: in std_logic_vector(7 downto 0);    -- Data output to D bus
  );
end component;
