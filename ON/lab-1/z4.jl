# Jacek Zub, 268490

# Funkcja search przeszukuje zadany interwał i zwraca pierwszą wartość, dla której x * 1/x != 1.
function search(start::Float64, stop::Float64)::Float64
    one::Float64 = 1.0

    if start > stop
        start, stop = stop, start
    end

    curr = start

    while curr < stop
        curr = nextfloat(curr)
        
        inv = one / curr

        if curr * inv != one
            return curr
        end
    end

    return 0.0
end

# Funkcja main przeprowadza eksperymenty dla funkcji search.
function main()
    println(search(1.0, 2.0))
end

if abspath(PROGRAM_FILE) == @__FILE__
    main()
end
