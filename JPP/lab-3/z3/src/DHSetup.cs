using Galois;

public class DHSetup<T> where T : struct
{
    private Field<T> m_generator;
    public DHSetup()
    {
        m_generator = get_random_generator();
    }

    public Field<T> power(Field<T> base_value, long exp)
    {
        Field<T> result = new Field<T>(1);

        while (exp > 0)
        {
            if (exp % 2 == 1)
                result *= base_value;

            base_value *= base_value;
            exp /= 2;
        }

        return result;
    }

    public Field<T> Generator { get { return m_generator; } }

    private Field<T> get_random_generator()
    {
        Field<T> generator = new Field<T>(1);

        Random random = new Random();

        do generator = new Field<T>(random.NextInt64(2, Field<T>.order));
        while (!is_generator(generator));

        return generator;
    }

    private bool is_generator(Field<T> candidate)
    {
        const long phi = Field<T>.order - 1;

        List<long> primeFactors = get_prime_factors(phi);

        foreach (long factor in primeFactors)
            if (power(candidate, phi / factor).Value == 1)
                return false;

        return true;
    }

    static List<long> get_prime_factors(long phi)
    {
        List<long> primeFactors = new List<long>();

        for (long i = 2; i * i <= phi; i++)
        {
            while (phi % i == 0)
            {
                if (!primeFactors.Contains(i))
                    primeFactors.Add(i);

                phi /= i;
            }
        }

        if (phi > 1)
            primeFactors.Add(phi);

        return primeFactors;
    }
}