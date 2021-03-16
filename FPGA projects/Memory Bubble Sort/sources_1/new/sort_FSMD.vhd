library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity sort_FSMD is
    generic (k : UNSIGNED (4 DOWNTO 0) := "10000");
    Port ( clock : in STD_LOGIC;
           reset : in STD_LOGIC;
           start : in STD_LOGIC;
           done : out STD_LOGIC;
           we : out STD_LOGIC;
           addr : out STD_LOGIC_VECTOR (3 DOWNTO 0);
           dout : out STD_LOGIC_VECTOR (7 DOWNTO 0);
           din : in STD_LOGIC_VECTOR (7 DOWNTO 0));
end sort_FSMD;

architecture Behavioral of sort_FSMD is
    type STATE_TYPE is (S0, S1, S1_2, S2, S2_2, S3, S3_2, S4, S4_2, S5);
    signal state : STATE_TYPE;
    signal A, B : STD_LOGIC_VECTOR (7 DOWNTO 0);
    signal i, j : UNSIGNED (4 DOWNTO 0);
begin
    process(clock)
    begin
        if rising_edge(clock) then
            if reset = '1' then
                state <= S0;
                addr <= (others => '0');
                done <= '0';
                we <= '0';
                dout <= (others => '0');
                i <= (others => '0');
                j <= (others => '0');
                A <= (others => '0');
                B <= (others => '0');
            else
                case state is
                    when S0 =>
                        if start = '1' then
                            state <= S1;
                            i <= (others => '0');
                        end if;
                    when S1 =>
                        if i < k - 1 then
                            addr <= STD_LOGIC_VECTOR(i(3 DOWNTO 0));
                            j <= (others => '0');
                            state <= S1_2;
                        else 
                            done <= '1';
                            state <= S0;
                        end if;
                    when S1_2 =>
                        A <= din;
                        j <= i + 1;
                        state <= S2;
                    when S2 =>
                        if j < k then
                            addr <= STD_LOGIC_VECTOR(j(3 DOWNTO 0));
                            state <= S2_2;
                        else
                            i <= i + 1;
                            state <= S1;
                        end if;
                    when S2_2 =>
                        B <= din;
                        state <= S3;
                    when S3 =>
                        if A > B then
                            addr <= STD_LOGIC_VECTOR(i(3 DOWNTO 0));
                            state <= S3_2;
                        else
                            j <= j + 1;
                            state <= S2;
                        end if;
                    when S3_2 =>
                        dout <= B;
                        we <= '1';
                        state <= S4;
                    when S4 =>
                        addr <= STD_LOGIC_VECTOR(j(3 DOWNTO 0));
                        state <= S4_2;
                    when S4_2 =>
                        dout <= A;
                        state <= S5;
                    when S5 =>
                        we <= '0';
                        A <= B;
                        j <= j + 1;
                        state <= S2;
                end case;
            end if;
        end if;
    end process;
end Behavioral;
