library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity client_server_tb is
end client_server_tb;

architecture Behavioral of client_server_tb is
    signal RESET, CLK : STD_LOGIC;
begin
    uut : entity work.client_server_interface(Behavioral)
        port map(
            CLOCK => CLK,
            RESET => RESET);

end Behavioral;
