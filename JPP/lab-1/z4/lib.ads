package lib is
    type Pair is record
        x : Integer;
        y : Integer;
    end record;

    function factorial(n : Integer) return Integer;
    function gcd(a, b : Integer) return Integer;
    function solve(a, b, c : Integer) return Pair;


    type Pair_Ptr is access Pair;
    pragma Convention(C, Pair_Ptr);

    function solve_C(a, b, c : Integer) return Pair_Ptr;
    pragma Export(C, factorial, "ada_factorial");
    pragma Export(C, gcd, "ada_gcd");
    pragma Export(C, solve_C, "ada_solve");
private
    procedure swap(a, b : in out Integer);
    function egcd(a, b : Integer) return Pair;
end lib;