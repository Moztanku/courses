with Ada.Strings.Unbounded; use Ada.Strings.Unbounded;

package Problem is
    type Index is range 1 .. 10;
    subtype Name is Unbounded_String;

    type Philosophers
        is array (Index range <>) of Name;

    procedure Dine (phils : in Philosophers);
end Problem;