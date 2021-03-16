library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;

entity sort_testbench is
end sort_testbench;

architecture Behavioral of sort_testbench is
    signal CLK, RESET, START, DONE : STD_LOGIC;
    type RAM_TYPE is array (15 DOWNTO 0) of STD_LOGIC_VECTOR (7 DOWNTO 0);
    signal ram : RAM_TYPE := ("00110011", "00010010", "01101001", "00000001",
                "00011101", "11111111", "01110111", "10101010",
                "00010100", "00000010", "01010011", "00111111",
                "00000111", "11100011", "10000000", "00101111");
    signal WE : STD_LOGIC;
    signal ADDR : STD_LOGIC_VECTOR (3 DOWNTO 0);
    signal DIN, DOUT : STD_LOGIC_VECTOR (7 DOWNTO 0);
begin
     -- Unit under test --
    uut: entity work.sort_FSMD(Behavioral)
        port map(
            clock => CLK,
            reset => RESET,
            start => START,
            done => DONE,
            we => WE,
            addr => ADDR,
            din => DIN,
            dout => DOUT);
    
    -- Clock generation --
    process begin
        CLK <= '1';
        wait for 5ns;
        CLK <= '0';
        wait for 5ns;
    end process;
    
    -- RAM simulation --
    process(CLK) begin
        if falling_edge(CLK) then
            if (we = '1') then
                RAM(conv_integer(unsigned(ADDR))) <= DOUT;
            end if; 
            DIN <= RAM(conv_integer(unsigned(ADDR)));
        end if; 
    end process;
    
    -- Testbench --
    process begin
        -- Initial Reset -- 
        RESET <= '1';
        wait for 15 ns;
        RESET <= '0';
        wait for 10 ns;     
                 
        -- Start testbench --
        start <= '1';
        wait until DONE = '1';
    end process;
end Behavioral;
