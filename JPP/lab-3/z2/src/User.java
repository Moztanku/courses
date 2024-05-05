import java.util.Random;

public class User <GF> {
    private interface GF
    {
        public static final Integer order = 1;
        public static GF zero(){ return null; };
        public static GF one(){ return null; };
        public int get_value();
        public void set(Integer m_value);
        public GF mul(GF other);
    }

    User(DHSetup<GF> setup) {
        this.setup = setup;
        this.private_key = get_random_private_key();
    }

    public GF get_public_key()
    {
        return (GF) setup.power(
            setup.get_generator(),
            private_key.get_value()
        );
    }

    public void set_cipher_key(GF other_public_key)
    {
        cipher_key = setup.power(
            other_public_key,
            private_key.get_value()
        );
    }

    private final DHSetup<GF> setup;
    private final GF private_key;
    private GF cipher_key;

    private GF get_random_private_key()
    {
        Random rand = new Random();

        GF result = GF.zero();
        result.set(rand.nextInt(1, GF.order - 1));

        return result;
    }
}
