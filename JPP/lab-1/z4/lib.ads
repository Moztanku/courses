package lib is
    type Pair is record
        x : Integer;
        y : Integer;
    end record
    with Convention => C;

    function factorial(n : Integer) return Integer;
    function gcd(a, b : Integer) return Integer;
    function solve(a, b, c : Integer) return Pair;

    pragma Export(C, factorial, "ada_factorial");
    pragma Export(C, gcd, "ada_gcd");
    pragma Export(C, solve, "ada_solve");
private
    procedure swap(a, b : in out Integer);
    function egcd(a, b : Integer) return Pair;
end lib;