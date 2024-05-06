#include <string_view>
#include <iostream>
#include <gmpxx.h>

auto get_prime(const char* str) -> mpz_class
{
    mpz_class prime;

    if (mpz_set_str(prime.get_mpz_t(), str, 10) == -1)
    {
        std::cerr << "Invalid prime number: " << str << '\n';
        exit(EXIT_FAILURE);
    }

    if (mpz_probab_prime_p(prime.get_mpz_t(), 25) == 0)
    {
        std::cerr << "Number is not prime: " << prime << '\n';
        exit(EXIT_FAILURE);
    }

    return prime;
}

auto get_e(const char* str) -> mpz_class
{
    mpz_class e;

    if (mpz_set_str(e.get_mpz_t(), str, 10) == -1)
    {
        std::cerr << "Invalid number: " << str << '\n';
        exit(EXIT_FAILURE);
    }

    return e;
}

auto help(int status, const char* exec) -> void
{
    std::cout << "Usage: " << exec << " <N> <E1> <D1>\n";
    exit(status);
}

auto get_p(mpz_class n, mpz_class e1, mpz_class d1) -> mpz_class
{
    mpz_class t = d1 * e1 - 1;
    mpz_class kphi = t;

    while (t % 2 == 0)
        t /= 2;

    mpz_class a = 2;
    while (true)
    {
        mpz_class k = t;
        while (k < kphi)
        {
            mpz_class x = 1;
            mpz_powm(
                x.get_mpz_t(),
                a.get_mpz_t(),
                k.get_mpz_t(),
                n.get_mpz_t()
            );

            if (x != 1 && x != (n - 1) && (x * x) % n == 1)
            {
                mpz_class r;
                mpz_class temp = x - 1;

                mpz_gcd(
                    r.get_mpz_t(),
                    temp.get_mpz_t(),
                    n.get_mpz_t()
                );

                return n / r;
            }

            k *= 2;
        }

        a += 2;
    }
}

auto main(int argc, char* argv[]) -> int
{

    if (argc == 2 && (std::string_view(argv[1]) == "-h" || std::string_view(argv[1]) == "--help"))
        help(EXIT_SUCCESS, argv[0]);

    if (argc != 4)
        help(EXIT_FAILURE, argv[0]);

    mpz_class n = get_e(argv[1]);
    mpz_class e1 = get_e(argv[2]);
    mpz_class d1 = get_e(argv[3]);

    mpz_class p = get_p(n, e1, d1);
    mpz_class q = n / p;

    std::cout << "Cracked private key (p, q): (" << p << ", " << q << ")\n";

    return 0;
}