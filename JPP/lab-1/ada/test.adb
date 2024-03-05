with Ada.Text_IO;   use Ada.Text_IO;
with Ada.Integer_Text_IO;   use Ada.Integer_Text_IO;

with lib;

procedure test is
begin
    a : Integer := 18;
    b : Integer := 5;
    c : Integer := 21;

    result : lib.Pair := lib.solve(a, b, c);

    Put_Line(
        "(" & result.x'Image & " x " & a'Image & ") + " &
        "(" & result.y'Image & " x " & b'Image & ") = " &
        c'Image
    );
end test;