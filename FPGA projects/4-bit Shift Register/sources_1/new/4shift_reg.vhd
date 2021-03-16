----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 22.02.2021 17:47:37
-- Design Name: 
-- Module Name: 4shift_reg - Behavioral
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

entity 4shift_reg is
    Port ( CLK : in STD_LOGIC;
           reset : in STD_LOGIC;
           din : in STD_LOGIC_VECTOR (3 downto 0);
           left : in STD_LOGIC;
           dout : out STD_LOGIC_VECTOR (3 downto 0));
end 4shift_reg;

architecture Behavioral of 4shift_reg is

begin


end Behavioral;
