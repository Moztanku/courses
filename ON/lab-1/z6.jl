# Jacek Zub, 268490

function f(x::Float64)
    one::Float64 = 1.0

    return sqrt(x^2 + one) - one
end

function g(x::Float64)
    one::Float64 = 1.0

    return x^2 / (sqrt(x^2 + one) + one)
end

function main()
    base::Float64 = 8.0

    for exp in -1:-1:-10
        x::Float64 = base^exp

        println("x = $x")
        println(" f(x) = $(f(x))")
        println(" g(x) = $(g(x))")
        println()
    end
end

if abspath(PROGRAM_FILE) == @__FILE__
    main()
end
