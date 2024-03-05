package lib is
    function factorial(N : Integer) return Integer;
    function gcd(A, B : Integer) return Integer;

    type Pair is record
        x : Integer;
        y : Integer;
    end record;
    
    function solve(A,B,C : Integer) return Pair;
private
    procedure swap(A, B : in out Integer);
    function egcd(A, B : Integer) return Pair;
end lib;