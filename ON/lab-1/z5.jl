# Jacek Zub, 268490

# Funkcja dotp_a oblicza iloczyn skalarny dwóch wektorów w przód.
function dotp_a(x::Vector{T}, y::Vector{T}) where T
    S::T = 0.0

    for i in 1:length(x)
        S += x[i] * y[i]
    end

    return S
end

# Funkcja dotp_b oblicza iloczyn skalarny dwóch wektorów w tył.
function dotp_b(x::Vector{T}, y::Vector{T}) where T
    S::T = 0.0

    for i in length(x):-1:1
        S += x[i] * y[i]
    end

    return S
end

# Funkcja dotp_c oblicza iloczyn skalarny poprzez dodawanie liczb od największych do najmniejszych.
function dotp_c(x::Vector{T}, y::Vector{T}) where T
    Ss = T[]

    # Obliczenie sum częściowych.
    for i in 1:length(x)
        push!(Ss, x[i] * y[i])
    end

    # Posortowane sumy dodatnie.
    Ss_pos = sort(
        filter(
            x -> x > 0,
            Ss
        ),
        rev = true)

    # Posortowane sumy ujemne.
    Ss_neg = sort(
        filter(
            x -> x < 0,
            Ss
        ),
        rev = false)

    return sum(Ss_pos) + sum(Ss_neg)
end

# Funkcja dotp_d oblicza iloczyn skalarny poprzez dodawanie liczb od najmniejszych do największych.
function dotp_d(x::Vector{T}, y::Vector{T}) where T
    Ss = T[]

    # Obliczenie sum częściowych.
    for i in 1:length(x)
        push!(Ss, x[i] * y[i])
    end

    # Posortowane sumy dodatnie.
    Ss_pos = sort(
        filter(
            x -> x > 0,
            Ss
        ),
        rev = false)

    # Posortowane sumy ujemne.
    Ss_neg = sort(
        filter(
            x -> x < 0,
            Ss
        ),
        rev = true)

    return sum(Ss_pos) + sum(Ss_neg)
end

# Funkcja test przeprowadza testy dla zadanego typu.
function test(T, type_name::String)
    x::Vector{T} =
    [
        2.718281828,
        -3.141592654,
        1.414213562,
        0.5772156649,
        0.3010299957
    ]

    y::Vector{T} =
    [
        1486.2497,
        878366.9879,
        -22.37492,
        4773714.647,
        0.000185049
    ]

    expected::T = -1.00657107e-11

    println("$(type_name):")
    println(" expected     = $(expected)")
    println(" dotp_a(x, y) = $(dotp_a(x, y))")
    println(" dotp_b(x, y) = $(dotp_b(x, y))")
    println(" dotp_c(x, y) = $(dotp_c(x, y))")
    println(" dotp_d(x, y) = $(dotp_d(x, y))")
end

# Funkcja main przeprowadza testy dla typów Float32 i Float64.
function main()
    test(Float32, "Float32")
    test(Float64, "Float64")
end

if abspath(PROGRAM_FILE) == @__FILE__
    main()
end
