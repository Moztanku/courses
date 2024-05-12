public class Main {
    public static void main(String[] args)
    {
        DHSetup<G1234567891> dh_Setup = new DHSetup<>(G1234567891::create);

        User<G1234567891> Alice = new User<>(dh_Setup);
        User<G1234567891> Bob = new User<>(dh_Setup);

        Alice.set_key(Bob.get_public_key());
        Bob.set_key(Alice.get_public_key());

        G1234567891 message = new G1234567891(42);

        G1234567891 encrypted = Alice.encrypt(message);
        G1234567891 decrypted = Bob.decrypt(encrypted);

        System.out.printf(
            "Message: %s\nEncrypted: %s\nDecrypted: %s\n",
            message.toString(),
            encrypted.toString(),
            decrypted.toString() 
        );
    }   
}