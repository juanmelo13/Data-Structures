----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 05.03.2021 19:34:37
-- Design Name: 
-- Module Name: divider_top - Behavioral
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

entity divider_top is
    Port ( clock : in STD_LOGIC;
           reset : in STD_LOGIC;
           data_valid : in STD_LOGIC;
           data : in STD_LOGIC_VECTOR (7 downto 0);
           ready : out STD_LOGIC;
           q : out STD_LOGIC_VECTOR (7 downto 0);
           r : out STD_LOGIC_VECTOR (7 downto 0);
           done : out STD_LOGIC;
           ack : in STD_LOGIC;
           error : out STD_LOGIC);
end divider_top;

architecture Behavioral of divider_top is
    type STATE_TYPE is (S0, S1, S2, S3, S4, S404);
    signal state : STATE_TYPE;
    signal START, DONE_b : STD_LOGIC;
    signal divisor, dividend, q_b, r_b : STD_LOGIC_VECTOR(7 DOWNTO 0);
begin
    div: entity work.div(beh)
        port map(
            clk => clock,
            reset => reset,
            start => START,
            dvsr => divisor,
            dvnd => dividend,
            done_tick => DONE_b,
            q => q_b,
            r => r_b);

    FSM: process(clock) begin
        if rising_edge(clock) then
            if reset = '1' then
                state <= S0;
            else
                case state is
                when S404 => -- Error condition
                    error <= '1';
                    state <= S0;
                when S0 =>  -- Ready to receive
                    divisor <= (others => '0');
                    dividend <= (others => '0');
                    START <= '0';
                    ready <= '1';
                    if data_valid = '0' then
                        state <= S0;
                    else
                        state <= S1;
                    end if;
                when S1 =>  -- Read dividend
                    dividend <= data;
                    ready <= '0';
                    if data_valid = '0' then
                        state <= S0;
                    else
                        state <= S2;
                    end if;
                when S2 =>  -- Read divisor
                    divisor <= data;
                    if divisor = "00000000" then
                        state <= S404;
                    else
                        state <= S3;
                    end if;
                when S3 => -- Start division
                    START <= '1';
                    if DONE_b = '1' then
                        q <= q_b;
                        r <= r_b;
                        state <= S4;
                    else
                        state <= S3;   
                    end if;
                when S4 =>
                    if ack = '1' then
                        state <= S0;
                    else
                        state <= S4;
                    end if;
                end case;
            end if;
        end if;
    end process;
end Behavioral;
