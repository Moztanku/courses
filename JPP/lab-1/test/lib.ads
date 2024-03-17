with Interfaces.C; use Interfaces.C;

package lib is
    function test return int;
    function factorial(n : int) return int;

    pragma Export (C, test, "ada_test");
    pragma Export(C, factorial, "ada_factorial");
end lib;