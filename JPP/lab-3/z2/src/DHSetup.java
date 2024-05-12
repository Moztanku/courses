import java.util.function.Supplier;
import java.util.ArrayList;
import java.util.Collections;
import java.util.concurrent.ThreadLocalRandom;

public class DHSetup<T extends Galois>
{
    private Supplier<T> supplier;
    private final T generator;

    public DHSetup(Supplier<T> supplier)
    {
        this.supplier = supplier;
        this.generator = get_random_generator();
    }

    public T get_generator()
    {
        return generator;
    }

    public boolean flag = false;

    public T power(T _base, long exp)
    {
        T result = supplier.get();
        T base = supplier.get();
        
        base.set(_base.get_value());
        result.set(1);

        while (exp > 0)
        {
            // if (flag)
            // System.out.printf(
            //     "Base: %s, exp: %s, res: %s\n",
            //     base.toString(),
            //     Integer.toString(exp),
            //     result.toString()
            // );
            if (exp % 2 == 1)
                result.set(
                    result.mul(base)
                );

            base.set(
                base.mul(base)
            );

            exp /= 2;
        }

        return result;
    }

    public T get_random_private_key()
    {
        T key = supplier.get();

        key.set(
            ThreadLocalRandom.current().nextLong(2, generator.order() - 1)
        );

        return key;
    }

    private T get_random_generator()
    {
        T generator = supplier.get();

        do {
            // long random = ThreadLocalRandom.current().nextInt(2, generator.order());
            long random = ThreadLocalRandom.current().nextLong(2, generator.order());
            generator.set(
                random
            );
        } while (!is_generator(generator));

        return generator;
    }

    private boolean is_generator(T generator)
    {
        final long phi = generator.order() - 1;

        final ArrayList<Long> prime_factors = get_prime_factors(phi);

        for (Long factor : prime_factors)
        {
            if (power(generator, phi / factor).get_value() == 1)
                return false;
        }

        return true;
    }

    static ArrayList<Long> get_prime_factors(Long phi)
    {
        ArrayList<Long> prime_factors = new ArrayList<>();

        for (Long i = 2l; i * i <= phi; i++)
        {
            while (phi % i == 0)
            {
                if (!prime_factors.contains(i))
                    prime_factors.add(i);
                phi /= i;
            }
        }

        if (phi > 1)
            prime_factors.add(phi);

        Collections.sort(prime_factors);

        return prime_factors;
    }
}
