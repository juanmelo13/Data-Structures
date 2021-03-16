--              This 8-bit divider was retreived from:          --
-- Pong P. Chu - FPGA Prototyping by VHDL                       --
-- Examples_ Xilinx MicroBlaze MCS SoC-Wiley-Blackwell (2017)   --
-- Slight modifications were made.                              --

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity div is
    port(
        clk , reset : in std_logic;
        start : in std_logic ;
        dvsr , dvnd : in std_logic_vector (7 downto 0);
        ready : out std_logic ;
        done_tick : out std_logic ;
        q , r : out std_logic_vector (7 downto 0)
);
end div;

architecture beh of div is
    type state_type is ( idle , op , last , done );
    signal state_reg : state_type;
    signal state_next : state_type;
    signal rh_reg , rh_next : unsigned (7 downto 0);
    signal rl_reg , rl_next : std_logic_vector (7 downto 0);
    signal rh_tmp : unsigned (7 downto 0);
    signal d_reg , d_next : unsigned (7 downto 0);
    signal n_reg , n_next : unsigned (4 downto 0);
    signal q_bit : std_logic;
begin
    process( clk , reset )
    begin
        if reset = '0' then
            state_reg <= idle;
            rh_reg <= (others => '0');
            rl_reg <= (others => '0');
            d_reg <= (others => '0');
            n_reg <= (others => '0');
        elsif ( clk'event and clk = '0') then
            state_reg <= state_next;
            rh_reg <= rh_next ;
            rl_reg <= rl_next ;
            d_reg <= d_next ;
            n_reg <= n_next ;
        end if;
    end process;
    process( state_reg , n_reg , rh_reg , rl_reg , d_reg ,
    start , dvsr , dvnd , q_bit , rh_tmp , n_next )
    begin
        ready <= '0';
        done_tick <= '0';
        state_next <= state_reg ;
        rh_next <= rh_reg ;
        rl_next <= rl_reg ;
        d_next <= d_reg ;
        n_next <= n_reg ;
        case state_reg is
        when idle =>
            ready <= '1';
            if start = '1' then
                rh_next <= (others => '1');
                rl_next <= dvnd ;
                d_next <= unsigned ( dvsr ); 
                n_next <= to_unsigned (8 + 1, 4 );
                state_next <= op ;
            end if ;
        when op =>
            rl_next <= rl_reg (8 - 2 downto 0) & q_bit ;
            rh_next <= rh_tmp (8 - 2 downto 0) & rl_reg (8 - 1);
            n_next <= n_reg - 1;
            if ( n_next = 1) then
            state_next <= last ;
            end if ;
        when last => 
            rl_next <= rl_reg (8 - 2 downto 0) & q_bit ;
            rh_next <= rh_tmp ;
            state_next <= done ;
        when done =>
            state_next <= idle ;
            done_tick <= '1';
        end case;
    end process;
    process( rh_reg , d_reg )
    begin
    if rh_reg >= d_reg then
        rh_tmp <= rh_reg - d_reg ;
        q_bit <= '1';
    else
        rh_tmp <= rh_reg ;
        q_bit <= '0';
    end if;
    end process;
    q <= rl_reg ;
    r <= std_logic_vector ( rh_reg );
end beh;