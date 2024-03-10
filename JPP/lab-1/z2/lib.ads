package lib is
    type Pair is record
        x : Integer;
        y : Integer;
    end record;

    function factorial(n : Integer) return Integer;
    function gcd(a, b : Integer) return Integer;
    function solve(a, b, c : Integer) return Pair;
private
    procedure swap(a, b : in out Integer);
    function egcd(a, b : Integer) return Pair;
end lib;