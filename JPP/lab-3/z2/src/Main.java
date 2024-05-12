public class Main {
    public static void main(String[] args)
    {
        DHSetup<G1234567891> dh_setup = new DHSetup<>(G1234567891::create);
        User<G1234567891> user = new User<>(dh_setup);

        user.set_key(new G1234567891(1001));
    
        G1234567891 message = new G1234567891(42);

        G1234567891 encrypted = user.encrypt(message);
        G1234567891 decrypted = user.decrypt(encrypted);

        System.out.printf(
            "Message: %s\nEncrypted: %s\nDecrypted: %s\n",
            message.toString(),
            encrypted.toString(),
            decrypted.toString()
        );

        // dh_setup.flag = true;
        // G1234567891 result = dh_setup.power(new G1234567891(2), 241542);
        // System.err.println(result.toString());
    }   
}