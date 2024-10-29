# Jacek Zub, 268490

# Funkcja derivative oblicza przybliżoną wartość pochodnej funkcji f w punkcie x.
function derivative(f, x, h)
    return (f(x + h) - f(x)) / h
end

# Funkcja main przeprowadza testy dla funkcji sin(x) + cos(3x) w punkcie x = 1.
function main()
    # Funkcja f oraz jej pochodna f'.
    f       = x::Float64 -> sin(x) + cos(3 * x)
    f_prime = x::Float64 -> cos(x) - 3 * sin(3 * x)

    x::Float64 = 1.0

    expected = f_prime(x)

    println("h")

    for n in 0:54
        h::Float64 = 2.0^(-n)

        f_approx = derivative(f, x, h)
        diff     = abs(expected - f_approx)

        println("$n $f_approx $diff")
    end

    println("1 + h")

    for n in 0:54
        h::Float64 = 1.0 + 2.0^(-n)

        println("$n $h $(f(h))")
    end
end

if abspath(PROGRAM_FILE) == @__FILE__
    main()
end
