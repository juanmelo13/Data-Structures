library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity gt2_sop_arch_tb is
end gt2_sop_arch_tb;

architecture tb_arch of gt2_sop_arch_tb is
    signal tb_a, tb_b : STD_LOGIC_VECTOR (1 downto 0);
    signal tb_agtb : STD_LOGIC;
begin
    uut : entity work.gt2(sop_arch)
        port map(
            a => tb_a,
            b => tb_b,
            agtb => tb_agtb);
            
    process begin 
        -- initialize --
        tb_a <= "00";
        tb_b <= "00";
        wait for 200ns;
        
        tb_a <= "01";
        wait for 200ns;
        
        tb_b <= "01";
        wait for 200ns;
        
        tb_b <= "10";
        wait for 200ns;
        
        tb_a <= "10";
        wait for 200ns;
        
        tb_a <= "11";
        wait for 200ns;
        
        -- terminate -- 
        assert false;
            report "Simulation Complete"
            severity failure;
    end process;
end tb_arch;
