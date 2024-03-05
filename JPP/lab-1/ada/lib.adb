package body lib is
    function factorial(n : in Integer) return Integer is
    begin
        result : Integer := 1;
        for i in 2 .. n loop
            result := result * i;
        end loop;
        return result;
    end factorial;

    function gcd(a, b : in Integer) return Integer is
    varA : Integer := a;
    varB : Integer := b;
    begin
        if (varA < varB) then
            swap(varA, varB);
        end if;

        while (varB /= 0) loop
            varA := varA mod varB;
            swap(varA, varB);
        end loop;

        return varA;
    end gcd;

    


    function solve(a,b,c : Integer) return Pair is
    result : Pair := (0, 0);
    begin
        d : Integer := gcd(a, b);

        if (c mod d = 0) then
            result := egcd(a, b);
            result.x := result.x * (c / d);
            result.y := result.y * (c / d);
        end if;

        return result;
    end solve;

    procedure swap (a, b : in out Integer) is
    temp : Integer := a;
    begin
        a := b;
        b := temp;
    end swap;

    function egcd (a, b : Integer) return Pair is
    result : Pair := (0, 0);
    begin
        if (b = 0) then
            result.x := 1;
        else
            result := egcd(b, a mod b);
            swap(result.x, result.y);
            result.y := result.y - (a / b) * result.x;
        end if;

        return result;
    end egcd;
end lib;