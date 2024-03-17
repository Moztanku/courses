with Interfaces.C; use Interfaces.C;

package wrapper is
    type Pair is record
        x : int;
        y : int;
    end record
    with Convention => C;

    function factorial(n : int) return int
        with
            Import => True,
            Convention => C;

    function gcd(a, b : int) return int
        with
            Import => True,
            Convention => C;

    function solve(a, b , c : int) return Pair
        with
            Import => True,
            Convention => C;
end wrapper;