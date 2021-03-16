library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity gt1 is
    Port ( a : in STD_LOGIC;
           b : in STD_LOGIC;
           agtb : out STD_LOGIC);
end gt1;

architecture sop_arch of gt1 is
begin
    agtb <= a and (not b);
end sop_arch;
