# Jacek Zub, 268490

# Funkcja epsilon zwraca wartość maszynowego epsilonu dla danego typu.
function epsilon(type)
    return type(3) * (type(4) / type(3) - type(1)) - type(1)
end

# Funkcja main przeprowadza testy dla typów Float16, Float32 i Float64.
function main()
    types =
    [
        (Float16, "Float16"),
        (Float32, "Float32"),
        (Float64, "Float64")
    ]

    for (type, name) in types
        println("Calculated meps for $(name):")
        println("   - expected:   $(eps(type))")
        println("   - calculated: $(epsilon(type))")
    end

end

if abspath(PROGRAM_FILE) == @__FILE__
    main()
end
