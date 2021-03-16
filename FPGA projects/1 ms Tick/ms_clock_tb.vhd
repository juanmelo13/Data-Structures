library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity ms_clock_tb is
end ms_clock_tb;

architecture Behavioral of ms_clock_tb is
    signal CLK, RESET, TICK : STD_LOGIC;
begin
    -- Unit Under Test -- 
    uut : entity work.ms_clock(behavioral)
        port map(
            clk => CLK,
            reset => RESET,
            tick_1ms => TICK);

    -- Clock generation --
    process begin
        CLK <= '1';
        wait for 5ns;
        CLK <= '0';
        wait for 5ns;
    end process;
    
    -- Initial reset --
    process begin
        RESET <= '1';
        wait for 15ns;
        RESET <= '0';
        wait;
    end process;
end Behavioral;
