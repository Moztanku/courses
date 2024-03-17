with Ada.Text_IO; use Ada.Text_IO;
with wrapper; use wrapper;

procedure Main is
begin
    Put_Line("factorial(5) = " & factorial(5)'Image);
    Put_Line("Gcd(27, 18) = " & gcd(27, 18)'Image);

    result : Pair := solve(2, 3, 1);
    Put_Line("2 * " & result.x'Image & " + 3 * " & result.y'Image & " = 1");
end Main;