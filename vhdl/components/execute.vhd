component alu is 
  port(
    a_input : in std_logic(7 downto 0);
    b_input : in std_logic(7 downto 0);
    sums : in std_logic;  -- SUM function input (used for both addition and subtraction)
    ands : in std_logic;  -- 1 bit AND function input
    eors : in std_logic; -- 1 bit EXCLUSIVE OR input
    ors : in std_logic;  -- 1 bit OR input
    srs : in std_logic;  -- 1 bit SR function input
    carry_in : in std_logic; -- 1 bit carry input
    dec : in std_logic;   -- 1 bit decimal enable (MOST LIKELY NOT GOING TO BE USED)

    output : out std_logic(7 downto 0);
    overflow : out std_logic;
    carry_out : out std_logic;
    half_carry_out : out std_logic;  -- ONLY USED IN DECIMAL MODE (MOST LIKELY NOT NEEDED)
  );
end component;
