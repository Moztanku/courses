package body lib is
    function factorial(n : Integer) return Integer is
    begin
        if (n < 2) then
            return 1;
        end if;

        return n * factorial(n - 1);
    end factorial;

    function gcd(a, b : Integer) return Integer is
    begin
        if (b = 0) then
            return a;
        end if;

        return gcd(b, a mod b);
    end gcd;

    function solve(a, b, c : Integer) return Pair is
    result : Pair := (0, 0);
    begin
        d : Integer := gcd(a, b);

        if (c mod d = 0) then
            st : Pair := egcd(a, b);

            s : Integer := st.x;
            t : Integer := st.y;
            k : Integer := c / d;

            result.x := s*k;
            result.y := t*k;
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
    begin
        if (b /= 0) then
            result := egcd(b, a mod b);
            temp : Integer := result.x;

            result.x := result.y;
            result.y := temp - (a / b) * result.y;
        end if;

        return result;
    end egcd;
end lib;