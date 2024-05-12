import javax.management.RuntimeErrorException;

public class User<T extends Galois> 
{
    private final DHSetup<T> dh_setup;
    private final T private_key;
    private T cipher_key;

    public User(DHSetup<T> dh_setup)
    {
        this.dh_setup = dh_setup;
        this.private_key = dh_setup.get_random_private_key();
    }

    public T get_public_key()
    {
        return dh_setup.power(
            dh_setup.get_generator(),
            private_key.get_value()
        );
    }

    public void set_key(T key)
    {
        this.cipher_key = dh_setup.power(
            key,
            private_key.get_value()
        );

        System.out.printf(
            "%s ^ %s = %s\n",
            key.toString(),
            private_key.toString(),
            cipher_key.toString()
        );
    }

    public T encrypt(T m)
    {
        if (cipher_key.get_value() == 0)
            throw new RuntimeErrorException(null);

        T res = dh_setup.get_random_private_key();
        res.set(
            m.mul(cipher_key)
        );

        return res;
    }

    public T decrypt(T c)
    {
        if (cipher_key.get_value() == 0)
            throw new RuntimeErrorException(null);

        T res = dh_setup.get_random_private_key();
        res.set(
            c.div(cipher_key)
        );

        return res;
    }
}
