# Jacek Zub, 268490

# Funkcja epsilon zwraca wartość maszynowego epsilonu dla danego typu.
function epsilon(type)
    one       = type(1.0)
    macheps   = one

    while one + (macheps / 2) > one
        macheps = macheps / 2
    end

    return macheps
end

# Funkcja eta zwraca wartość maszynowego eta dla danego typu.
function eta(type)
    zero = type(0.0)
    eta  = type(1.0)

    while eta / 2 > zero
        eta = eta / 2
    end

    return eta
end

# Funkcja max zwraca maksymalną wartość dla danego typu.
function max(type)
    max = type(1.0)

    while !isinf(max * 2)
        max = max * 2
    end

    add = max / 2
    while !isinf(max + add)
        max = max + add
        add = add / 2
    end

    return max
end

# Funkcja main przeprowadza testy dla typów Float16, Float32 i Float64.
function main()
    # Tuple zawierający typ, jego nazwę, wartość epsilon oraz wartość max wziętą ze skompilowanego programu w C.
    types =
    [
        (
            Float16,
            "Float16",
            "unavailable",
            "unavailable"
        ),
        (
            Float32,
            "Float32",
            "1.1920929e-07",
            "3.4028235e+38"
        ),
        (
            Float64,
            "Float64",
            "2.220446049250313e-16",
            "1.7976931348623157e+308"
        ),
    ]

    println("epsilon")
    for (type, name, c_eps, _) in types
        println(" Calculated meps for $(name):")
        println("  - expected:   $(eps(type))")
        println("  - calculated: $(epsilon(type))")
        println("  - C header:   $(c_eps)")
    end

    println("eta")
    for (type, name, _, _) in types
        println(" Calculated eta for $(name):")
        println("   - expected:   $(nextfloat(type(0.0)))")
        println("   - calculated: $(eta(type))")
    end

    println("min")
    for (type, name, _, _) in types
        println(" Minimum value for $(name): $(floatmin(type))")
    end

    println("max")
    for (type, name, _, c_max) in types
        println(" Calculated max for $(name):")
        println("  - expected:   $(floatmax(type))")
        println("  - calculated: $(max(type))")
        println("  - C header:   $(c_max)")
    end
end

if abspath(PROGRAM_FILE) == @__FILE__
    main()
end
