library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity shift_reg_4 is
    Port ( clk : in STD_LOGIC;
           reset : in STD_LOGIC;
           din : in STD_LOGIC_VECTOR (3 downto 0);
           load : in STD_LOGIC;
           left : in STD_LOGIC;
           dout : out STD_LOGIC_VECTOR (3 downto 0));
end shift_reg_4;

architecture Behavioral of shift_reg_4 is
    signal reg : STD_LOGIC_VECTOR (3 downto 0);
begin
    process(clk) begin
        if rising_edge(clk) then
            if reset = '1' then
                reg <= (others => '0');
            elsif load = '1' then
                reg <= din;
            elsif left = '1' then
                reg <= reg(2 downto 0) & din(0);
            else
                reg <= din(0) & reg(3 downto 1);
            end if;
        end if;
    end process;
    dout <= reg;
end Behavioral;
