library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity bcd_2_bin_tb is
end bcd_2_bin_tb;

architecture tb_arch of bcd_2_bin_tb is
    signal tb_bcd_0, tb_bcd_1 : STD_LOGIC_VECTOR (3 downto 0);
    signal tb_bin : STD_LOGIC_VECTOR (7 downto 0);
begin
    uut : entity work.bcd_2_bin(dataflow)
        port map(
            bcd_0 => tb_bcd_0,
            bcd_1 => tb_bcd_1,
            bin_out => tb_bin);
            
    process begin
        -- initialization --
        tb_bcd_0 <= "0000";
        tb_bcd_1 <= "0000";
        wait for 200ns;
        
        tb_bcd_0 <= "1001";
        tb_bcd_1 <= "1001";
        wait for 200ns;
        
        tb_bcd_0 <= "0110";
        tb_bcd_1 <= "0010";
        wait for 200ns;
        
        tb_bcd_0 <= "1100";
        tb_bcd_1 <= "0001";
        wait for 200ns;
        
        tb_bcd_0 <= "0111";
        wait;
        
        -- terminate simulation --
        assert false;
            report "Simulation complete";
    end process;
end tb_arch;
