with Ada.Text_IO; use Ada.Text_IO;
with lib; use lib;

procedure Main is
    begin
        result : lib.Pair := lib.solve(23,5,17);
        Put_Line("x = " & Integer'Image(result.x));
        Put_Line("y = " & Integer'Image(result.y));
    end Main;