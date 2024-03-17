package body lib is
    function factorial(n : Integer) return Integer is
    begin
        result : Integer := 1;
        for i in 2 .. n loop
            result := result * i;
        end loop;
        return result * n;
    end factorial;

    function gcd(a, b : Integer) return Integer is
    vA : Integer := a;
    vB : Integer := b;
    begin
        if (vA < vB) then
            swap(vA, vB);
        end if;

        while (vB /= 0) loop
            vA := vA mod vB;
            swap(vA, vB);
        end loop;

        return vA;
    end gcd;

    function solve(a, b, c : Integer) return Pair is
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

    procedure swap(a, b : in out Integer) is
    temp : Integer := a;
    begin
        a := b;
        b := temp;
    end swap;

    function egcd(a, b : Integer) return Pair is
    result : Pair := (1, 0);
    prev : Pair := (0, 1);
    vA : Integer := a;
    vB : Integer := b;
    begin
        while (vB /= 0) loop
            q : Integer := vA / vB;

            temp : Pair := result;
            result := prev;
            prev.x := temp.x - q * prev.x;
            prev.y := temp.y - q * prev.y;

            tempA : Integer := vA;
            vA := vB;
            vB := tempA - q * vB;
        end loop;

        return result;
    end egcd;
end lib;