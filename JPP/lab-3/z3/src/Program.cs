// See https://aka.ms/new-console-template for more information
using Galois;
using Order = Galois.Order1234567891;

class Program
{
    static void Main(string[] args)
    {
        // using Order = Galois.Order1234567891;

// Now you can use the alias instead of the full struct name
        var dh_setup = new DHSetup<Order>();

        var Alice = new User<Order>(dh_setup);
        var Bob = new User<Order>(dh_setup);

        Alice.set_key(Bob.get_public_key());
        Bob.set_key(Alice.get_public_key());

        var message = new Field<Order>(42);

        var encrypted = Alice.encrypt(message);
        var decrypted = Bob.decrypt(encrypted);

        System.Console.WriteLine($"Message: {message}");
        System.Console.WriteLine($"Encrypted: {encrypted}");
        System.Console.WriteLine($"Decrypted: {decrypted}");
    }
}