library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity FSM is
    Port ( clock : in STD_LOGIC;
           reset : in STD_LOGIC;
           din_valid : in STD_LOGIC;
           din : in STD_LOGIC;
           count : out STD_LOGIC_VECTOR (7 downto 0);
           done : out STD_LOGIC);
end FSM;

architecture Behavioral of FSM is
    type state_type is (S0, S1, S2, S3, S4, S5, S6, S7, S8);
    signal state : state_type;
    signal reg : unsigned(7 DOWNTO 0);
    signal tdone : STD_LOGIC;
begin
    Moore_FSM: process(clock) begin
        if rising_edge(clock) then
            if reset = '1' then
                state <= S0;
            else
                if din_valid = '1' then
                    -- FSM -- 
                    case state is
                        when S0 =>
                            reg <= (others => '0');
                            tdone <= '0';
                            if din = '0' then
                                state <= S1;
                            else
                                state <= S2;
                            end if;
                        when S1 =>
                            if din = '0' then
                                state <= S1;
                            else
                                state <= S3;
                            end if;
                        when S2 =>
                            if din = '0' then
                                state <= S5;
                            else
                                state <= S2;
                            end if;
                        when S3 =>
                            if din = '0' then
                                state <= S4;
                            else
                                state <= S2;
                            end if;
                        when S4 =>
                            if din = '0' then
                                state <= S6;
                            else
                                state <= S7;
                            end if;
                        when S5 => 
                            if din = '0' then
                                state <= S6;
                            else
                                state <= S3;
                            end if;
                        when S6 =>
                            if din = '0' then
                                state <= S1;
                            else
                                state <= S8;
                            end if;
                        when S7 =>
                            reg <= reg + 1;
                            if din = '0' then
                                state <= S4;
                            else
                                state <= S2;
                            end if;
                        when S8 =>
                            reg <= reg + 1;
                            if din = '0' then
                                state <= S4;
                            else
                                state <= S2;
                            end if;
                    end case; 
                else
                    tdone <= '1';
                end if;
            end if;        
        end if;
    end process;
    count <= STD_LOGIC_VECTOR(reg) when tdone = '1' else (others => '0');
    done <= tdone;
end Behavioral;
