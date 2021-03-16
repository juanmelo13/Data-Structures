library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity bcd_2_bin is
    Port ( bcd_0 : in STD_LOGIC_VECTOR (3 downto 0);
           bcd_1 : in STD_LOGIC_VECTOR (3 downto 0);
           bin_out : out STD_LOGIC_VECTOR (7 downto 0));
end bcd_2_bin;

architecture dataflow of bcd_2_bin is
    signal d0, d1 : UNSIGNED (3 downto 0);
    signal bin : UNSIGNED (7 downto 0);
begin
    d0 <= unsigned(bcd_0);
    d1 <= unsigned(bcd_1);
    
    -- if any input is invalid, bin will not be overwriten --
    bin <=  d0 + (d1 * 10) WHEN (d0 <= 9) and (d1 <= 9);
            
    bin_out <= std_logic_vector(bin);
end dataflow;
