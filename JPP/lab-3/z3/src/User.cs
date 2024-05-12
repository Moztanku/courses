using Galois;

public class User<T> where T : struct
{
    private readonly DHSetup<T> dh_setup;
    private readonly Field<T> private_key;
    private Field<T>? cipher_key;

    public User(DHSetup<T> dh_setup)
    {
        this.dh_setup = dh_setup;
        private_key = get_random_private_key();
    }

    public Field<T> get_public_key()
    {
        return dh_setup.power(dh_setup.Generator, private_key.Value);
    }

    public void set_key(Field<T> public_key)
    {
        cipher_key = dh_setup.power(public_key, private_key.Value);
    }

    public Field<T> encrypt(Field<T> m)
    {
        if (cipher_key == null)
            throw new System.Exception("Key not set");

        return m * cipher_key;
    }

    public Field<T> decrypt(Field<T> c)
    {
        if (cipher_key == null)
            throw new System.Exception("Key not set");

        return c / cipher_key;
    }

    static private Field<T> get_random_private_key()
    {
        Random random = new Random();
        return new Field<T>(random.NextInt64(2, Field<T>.order));
    }
}