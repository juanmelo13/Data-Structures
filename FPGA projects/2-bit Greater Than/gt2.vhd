library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity gt2 is
    port(
        a, b : in std_logic_vector(1 downto 0); 
        agtb : out std_logic);
end gt2;

architecture sop_arch of gt2 is
    signal p0, p1, p2, p3, p4, p5 : std_logic;
begin
    agtb <= p0 or p1 or p2 or p3 or p4 or p5;
    -- minterms --
    p0 <= (not a(1)) and a(0) and (not b(1)) and (not b(0));
    p1 <= a(1) and (not a(0)) and (not b(1)) and (not b(0));
    p2 <= a(1) and (not a(0)) and (not b(1)) and b(0);
    p3 <= a(1) and a(0) and (not b(1)) and (not b(0));
    p4 <= a(1) and a(0) and (not b(1)) and b(0);
    p5 <= a(1) and a(0) and b(1) and (not b(0)); 
end sop_arch;

architecture struct_arch of gt2 is
    signal d0, d1, d2 : std_logic;
begin
    gt_bit1 : entity work.gt1(sop_arch)
        port map(
            a => a(1),
            b => b(1),
            agtb => d1);
            
    gt_bit0 : entity work.gt1(sop_arch)
        port map(
            a => a(0),
            b => b(0),
            agtb => d0);
    
    -- This component computes b(1) > a(1) for the LSB check. --
    gt_bit_b : entity work.gt1(sop_arch)
        port map(
            a => b(1),
            b => a(1),
            agtb => d2);
            
    -- agtb --
    agtb <= d1 or (d0 and (not d2));
end struct_arch;