// See https://aka.ms/new-console-template for more information
class Program
{
    static void Main(string[] args)
    {
        try {
            FieldTests.testOperations();
        } catch (System.Exception e) {
            System.Console.WriteLine(e.Message);
            return;
        }


        System.Console.WriteLine("All tests passed");
    }
}