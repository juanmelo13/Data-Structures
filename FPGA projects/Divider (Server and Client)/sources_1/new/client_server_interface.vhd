library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity client_server_interface is
    Port (
        CLOCK : in STD_LOGIC;
        RESET : in STD_LOGIC);
end client_server_interface;

architecture Behavioral of client_server_interface is
    signal DATA, Q, R : STD_LOGIC_VECTOR (7 DOWNTO 0);
    signal DATA_VALID, READY, DONE, ACK, ERROR : STD_LOGIC;
begin
    client : entity work.num_generator(Behavioral)
        port map(
            clock => CLOCK,
            reset => RESET,
            data_valid => DATA_VALID,
            data => DATA,
            ready => READY,
            done => DONE,
            q => Q,
            r => R,
            ack => ACK,
            error => ERROR);

    server : entity work.divider_top(Behavioral)
        port map(
            clock => CLOCK,
            reset => RESET,
            data_valid => DATA_VALID,
            data => DATA,
            ready => READY,
            done => DONE,
            q => Q,
            r => R,
            ack => ACK,
            error => ERROR);
            
end Behavioral;
