package body lib is
    function test return int is
    begin
        return 42;
    end test;

    function factorial(n : int) return int is
    begin
        if (n < 2) then
            return 1;
        end if;

        return n * factorial(n - 1);
    end factorial;
end lib;