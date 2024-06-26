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

auto help(int status, const char* exec) -> void
{
    std::cout << "Usage: " << exec << " <P> <Q> <E?>\n";
    exit(status);
}

auto main(int argc, char* argv[]) -> int
{
    if (argc == 2 && (std::string_view(argv[1]) == "-h" || std::string_view(argv[1]) == "--help"))
        help(EXIT_SUCCESS, argv[0]);

    if (argc != 3 && argc != 4)
        help(EXIT_FAILURE, argv[0]);

    mpz_class p = get_prime(argv[1]);
    mpz_class q = get_prime(argv[2]);

    if (mpz_cmp(p.get_mpz_t(), q.get_mpz_t()) <= 0)
    {
        std::cerr << "P must be greater than Q\n";
        exit(EXIT_FAILURE);
    }

    mpz_class n = p * q;
    
    mpz_class ϕp = p - 1;
    mpz_class ϕq = q - 1;

    mpz_class gcd;
    mpz_gcd(gcd.get_mpz_t(), ϕp.get_mpz_t(), ϕq.get_mpz_t());

    mpz_class λ = (ϕp * ϕq) / gcd;

    mpz_class e = 65537;

    if (mpz_cmp(e.get_mpz_t(), λ.get_mpz_t()) >= 0)
        e = 3;

    if (argc == 4)
    {
        e = get_prime(argv[3]);

        if (mpz_cmp(e.get_mpz_t(), λ.get_mpz_t()) >= 0)
        {
            std::cerr << "E must be less than λ\n";
            exit(EXIT_FAILURE);
        }
    }

    mpz_class d;
    mpz_invert(d.get_mpz_t(), e.get_mpz_t(), λ.get_mpz_t());

    std::cout << "Public key (n, e): (" << n << ", " << e << ")\n";
    std::cout << "Private key (n, d): (" << n << ", " << d << ")\n";
        
    return 0;
}

// ./bin/make_keys 5675389 2236183 11 ->
//      Public key (n, e): (12691208400187, 11)
//      Private key (n, d): (12691208400187, 961454582471)

// ./bin/make_keys 5675389 2236183 65537 ->
//      Public key (n, e): (12691208400187, 65537)
//      Private key (n, d): (12691208400187, 2013695522849)

// ./bin/crack 12691208400187 11 961454582471 ->
//      Cracked private key (p, q): (5675389, 2236183)

// ./bin/make_keys 5675389 2236183 65537 ->
//      Public key (n, e): (12691208400187, 65537)
//      Private key (n, d): (12691208400187, 2013695522849)
