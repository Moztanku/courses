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
    std::cout << "Usage: " << exec << " <P> <Q> <E>\n";
    exit(status);
}

auto main(int argc, char* argv[]) -> int
{

    if (argc == 2 && (std::string_view(argv[1]) == "-h" || std::string_view(argv[1]) == "--help"))
        help(EXIT_SUCCESS, argv[0]);

    if (argc != 4)
        help(EXIT_FAILURE, argv[0]);

    mpz_class p = get_prime(argv[1]);
    mpz_class q = get_prime(argv[2]);
    mpz_class e = get_e(argv[3]);

    if (mpz_cmp(p.get_mpz_t(), q.get_mpz_t()) <= 0)
    {
        std::cerr << "P must be greater than Q\n";
        exit(EXIT_FAILURE);
    }

    mpz_class n = p * q;
    mpz_class ϕ = (p - 1) * (q - 1);

    mpz_class d;
    mpz_gcdext(
        /* gcd */ mpz_class().get_mpz_t(), // Ignored
        /*  s  */ d.get_mpz_t(),
        /*  t  */ mpz_class().get_mpz_t(), // Ignored
        /*  a  */ e.get_mpz_t(),
        /*  b  */ ϕ.get_mpz_t()
    );

    // if (mpz_sgn(d.get_mpz_t()) < 0)
    //     d += ϕ;

    std::cout << "Public key (n, e): (" << n << ", " << e << ")\n";
    std::cout << "Private key (n, d): (" << n << ", " << d << ")\n";

    return 0;
}