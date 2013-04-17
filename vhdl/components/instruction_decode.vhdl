-- Decode stage



component predecode_register is
	port (
		data_in : in std_logic_vector(7 downto 0);
		data_out : out std_logic_vector(7 downto 0);

		clk2_in : in std_logic;
	);
end component;

component predecode_logic is
	port (
		data_in : in std_logic_vector(7 downto 0);
		assert_interrupt_control : in std_logic;

		data_out : in std_logic_vector(7 downto 0);
	);
end component;	

component timing_generation_logic is
	port (
		tzpre : in std_logic;
		
		sync : out std_logic;

		t0 : out std_logic;
		t1 : out std_logic;
		t2 : out std_logic;
		t3 : out std_logic;
		t4 : out std_logic;
		t5 : out std_logic;
		t6 : out std_logic;
	);
end component;	

component decode_rom is
	port (
		instruction_register_in : in std_logic(14 downto 0);
		
		sync : out std_logic;

		t0 : out std_logic;
		t1 : out std_logic;
		t2 : out std_logic;
		t3 : out std_logic;
		t4 : out std_logic;
		t5 : out std_logic;
		t6 : out std_logic;
	);
end component;	

component random_control_logic is
	port (
		instruction_register_in : in std_logic(14 downto 0);
		
		sync : out std_logic;

		t0 : out std_logic;
		t1 : out std_logic;
		t2 : out std_logic;
		t3 : out std_logic;
		t4 : out std_logic;
		t5 : out std_logic;
		t6 : out std_logic;
	);
end component;	


