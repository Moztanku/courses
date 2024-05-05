import java.util.ArrayList;
import java.util.Random;

public class DHSetup<GF>
{
    private interface GF
    {
        public static final Integer order = 1;
        public static GF zero(){ return null; };
        public static GF one(){ return null; };
        public int get_value();
        public void set(Integer m_value);
        public GF mul(GF other);
    }

    public DHSetup(){}

    public GF get_generator()
    {
        return generator;
    }

    public GF power(GF base, int exp)
    {
        GF result = GF.one();

        while (exp > 0)
        {
            if (exp % 2 == 1)
                result = result.mul(base);

            exp >>= 1;
            base = base.mul(base);
        }

        return result;
    }

    private final GF generator = get_random_generator();

    private GF get_random_generator()
    {
        Random rand = new Random();
        int phi = GF.order - 1;

        GF generator = GF.zero();

        do
        {
            generator.set(rand.nextInt(2, phi));
        } while (!is_generator(generator));

        return generator;
    }

    private boolean is_generator(GF generator)
    {
        final Integer phi = GF.order - 1;
        final ArrayList<Integer> prime_factors = get_prime_factors(phi);

        for (Integer prime : prime_factors)
            if (power(generator, phi / prime).equals(GF.one()))
                return false;

        return true;
    }

    private static ArrayList<Integer> get_prime_factors(Integer phi)
    {
        ArrayList<Integer> prime_factors = new ArrayList<Integer>();

        for (Integer i = 2; i * i <= phi; i++)
        {
            while (phi % i == 0)
            {
                if (binary_search(prime_factors, i) == false)
                    prime_factors.add(i);

                phi /= i;
            }
        }

        if (phi > 1)
            prime_factors.add(phi);

        return prime_factors;
    }

    private static boolean binary_search(ArrayList<Integer> arr, Integer x)
    {
        int l = 0;
        int r = arr.size() - 1;

        while (l <= r)
        {
            int m = l + (r - l) / 2;

            if (arr.get(m) == x)
            {
                return true;
            }

            if (arr.get(m) < x)
            {
                l = m + 1;
            }
            else
            {
                r = m - 1;
            }
        }

        return false;
    }
}
