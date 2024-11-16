with Ada.Text_IO;         -- Import the Ada Text_IO package for input/output
use Ada.Text_IO;

procedure Example is
   -- Declare a new type for an array of integers
   type Int_Array is array (1 .. 5) of Integer;

   -- Create an instance of the array
   My_Array : Int_Array := (1, 2, 3, 4, 5);

   -- Declare a variable to hold the sum of the array elements
   Sum : Integer := 0;

   -- Declare a procedure to print a message
   procedure Print_Message(Message : String) is
   begin
      -- Print the message to the console
      Put_Line(Message);
   end Print_Message;

begin
   Print_Message("Starting the program...");  -- Notify the start of the program

   -- Iterate over the array and calculate the sum
   for I in My_Array'Range loop
      Sum := Sum + My_Array(I);  -- Add each element to the sum
      -- Print the current element (for debugging purposes)
      Put_Line("Element: " & Integer'Image(My_Array(I)));
   end loop;

   -- Print the result
   Print_Message("The sum of the array elements is: " & Integer'Image(Sum));

   -- Example of a conditional
   if Sum > 10 then
      Print_Message("The sum is greater than 10.");  -- Inform if sum is large
   else
      Print_Message("The sum is 10 or less.");  -- Inform if sum is small
   end if;

   -- End of the program
   Print_Message("Ending the program...");
end Example;
