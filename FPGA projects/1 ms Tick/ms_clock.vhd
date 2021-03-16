library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity ms_clock is
    Port ( clk : in STD_LOGIC;
           reset : in STD_LOGIC;
           tick_1ms : out STD_LOGIC);
end ms_clock;

architecture behavioral of ms_clock is
    signal count : UNSIGNED(18 DOWNTO 0);
begin
    process(clk) begin
        if rising_edge(clk) then
            if reset = '1' then
                count <= (others => '0');
            elsif count = 100000 then
                count <= (others => '0');
            else 
                count <= count + 1;
            end if;
        end if;
    end process;
    tick_1ms <= '1' when count = 99999 else '0';
end behavioral;
