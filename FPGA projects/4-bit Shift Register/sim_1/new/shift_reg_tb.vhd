----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 22.02.2021 18:45:11
-- Design Name: 
-- Module Name: shift_reg_tb - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity shift_reg_tb is
end shift_reg_tb;

architecture Behavioral of shift_reg_tb is
    signal CLK, RESET, LOAD, LEFT : STD_LOGIC;
    signal DIN, DOUT : STD_LOGIC_VECTOR (3 downto 0);
begin
    -- Unit Under Test --
    uut : entity work.shift_reg_4(behavioral)
        port map(
            clk => CLK,
            reset => RESET,
            load => LOAD,
            left => LEFT,
            din => DIN,
            dout => DOUT);
            
    -- Clock generation --
    process begin
        CLK <= '0';
        wait for 10ns;
        CLK <= '1';
        wait for 10ns;
    end process;
    
    -- Initial reset --
    process begin
        RESET <= '1';
        wait for 20ns;
        RESET <= '0';
        wait;
    end process;

    -- Testbench --
    process begin
        -- Initial state --
        LOAD <= '0';
        LEFT <= '0';
        DIN <= (others => '0');
        wait for 20ns;
        
        -- test serial load --
        for i in 1 to 8 loop
            DIN <= "0001";
            wait until falling_edge(CLK);
            DIN <= "0000";
            wait until falling_edge(CLK);
        end loop;
        
        -- test serial left load --
        LEFT <= '1';
        for i in 1 to 8 loop
            DIN <= "0001";
            wait until falling_edge(CLK);
            DIN <= "0000";
            wait until falling_edge(CLK);
        end loop;
        
        -- test parallel load -- 
        LEFT <= '0';
        LOAD <= '1';
        DIN <= "1100";
        wait until falling_edge(CLK);
        DIN <= "0011";
        wait until falling_edge(CLK);
        DIN <= "1000";
        wait until falling_edge(CLK);
        DIN <= "1111";
        wait until falling_edge(CLK);
        wait;
    end process;
end Behavioral;
