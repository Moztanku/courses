public class DHSetup<T>
{
    private T generator;

    public DHSetup()
    {

    }

    public T get_generator()
    {
        return generator;
    }

    public T power(T a, Int64 exp)
    {
        T result;

        while (exp > 0)
        {
            if (exp % 2 == 1)
            {
                result = result * a;
            }

            a = a * a;
            exp = exp / 2;
        }

        return result;
    }

    private T get_random_generator()
    {
        T generator = 0;

        Random rand = new Random();

        do {
        }
    }
}