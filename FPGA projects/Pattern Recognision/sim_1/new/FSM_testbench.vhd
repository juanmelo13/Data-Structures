----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 05.03.2021 18:34:13
-- Design Name: 
-- Module Name: FSM_testbench - Behavioral
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

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity FSM_testbench is
end FSM_testbench;

architecture Behavioral of FSM_testbench is
    signal CLK, RESET, DIN_VALID, DIN, DONE : STD_LOGIC;
    signal COUNT : STD_LOGIC_VECTOR(7 DOWNTO 0);
    signal reg : STD_LOGIC_VECTOR (31 DOWNTO 0); -- INPUT SIGNAL -- 
begin
    -- Unit under test --
    uut: entity work.FSM(Behavioral)
        port map(
            clock => CLK,
            reset => RESET,
            din_valid => DIN_VALID,
            din => DIN,
            count => COUNT,
            done => DONE);
    
    -- Clock generation --
    process begin
        CLK <= '1';
        wait for 5ns;
        CLK <= '0';
        wait for 5ns;
    end process;
    
    -- Testbench --
    test: process begin
        -- Initial RESET --
        RESET <= '1';
        wait for 15ns;
        RESET <= '0';
        wait for 15ns;
        
        -- Assignment's test --
        reg <= "11001010110100100110101010011101";
        wait for 5ns;
        DIN <= reg(31);
        wait until falling_edge(CLK);
        DIN_VALID <= '1';
        for i in 30 downto 0 loop
            wait until falling_edge(CLK);
            DIN <= reg(i);
        end loop;
        DIN_VALID <= '0';
        
        -- RESET --
        wait for 20ns;
        RESET <= '1';
        wait for 10ns;
        RESET <= '0';
        
        -- My Test #1 --
        -- count should be: 10--
        reg <= "01010101010010110101001110010100";
        wait for 5ns;
        DIN <= reg(31);
        wait until falling_edge(CLK);
        DIN_VALID <= '1';
        for i in 30 downto 0 loop
            wait until falling_edge(CLK);
            DIN <= reg(i);
        end loop;
        DIN_VALID <= '0';
        
        -- RESET --
        wait for 20ns;
        RESET <= '1';
        wait for 10ns;
        RESET <= '0';
        
        -- My Test #2 --
        -- count should be: 2--
        reg <= "01110111010000110101000110011100";
        wait for 5ns;
        DIN <= reg(31);
        wait until falling_edge(CLK);
        DIN_VALID <= '1';
        for i in 30 downto 0 loop
            wait until falling_edge(CLK);
            DIN <= reg(i);
        end loop;
        DIN_VALID <= '0';
    end process;
end Behavioral;
