----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 05.03.2021 19:34:37
-- Design Name: 
-- Module Name: num_generator - Behavioral
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

entity num_generator is
    Port ( clock : in STD_LOGIC;
           reset : in STD_LOGIC;
           data_valid : out STD_LOGIC;
           data : out STD_LOGIC_VECTOR (7 downto 0);
           ready, done : in STD_LOGIC;
           q : in STD_LOGIC_VECTOR (7 downto 0);
           r : in STD_LOGIC_VECTOR (7 downto 0);
           ack : out STD_LOGIC;
           error : in STD_LOGIC);
end num_generator;

architecture Behavioral of num_generator is
    type STATE_TYPE is (S0, S1, S2, S3, S4);
    signal state : STATE_TYPE;
    signal q_i, r_i : STD_LOGIC_VECTOR (7 DOWNTO 0);
begin
    FSM: process(clock) begin
        if rising_edge(clock) then
            if reset = '1' then
                state <= S0;
            else
                case state is
                when S0 =>
                    data_valid <= '0';
                    data <= (others => '0');
                    ack <= '0';
                    if ready = '0' then
                        state <= S0;
                    else
                        state <= S1;
                    end if;
                when S1 =>
                    data <= "01110000";
                    data_valid <= '1';
                    if ready <= '0' then
                        state <= S0;
                    else
                        state <= S2;
                    end if;
                when S2 =>
                    data <= "00000001";
                    if error = '1' then
                        state <= S0;
                    else 
                        state <= S3;
                    end if;
                when S3 => 
                    if done = '1' then
                        state <= S4;
                    else 
                        state <= S3;
                    end if;
                when S4 =>
                    q_i <= q;
                    r_i <= r;
                    ack <= '1';
                    state <= S0;
                end case;
            end if;
        end if;
    end process;
end Behavioral;
