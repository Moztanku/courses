# Jacek Zub, 268490

# Funkcja check_interval sprawdza czy liczby z przedziału [start, stop] są rozmieszczone równomiernie co step.
#  sprawdzenie jest dokonywane dla iter liczby punktów z przedziału [start, stop].
function check_interval(start::Float64, stop::Float64, step::Float64, iter::Int = 3333)
    if start > stop
        start, stop = stop, start
    end
    middle = (start + stop) / 2

    # Sprawdzenie na początku przedziału
    iter_start::Int = 1
    iter_end::Int   = floor(iter / 3)

    curr = start

    for _ in iter_start:iter_end
        next = curr + step

        if nextfloat(curr) != next
            return false
        end

        curr = next
    end

    # Sprawdzenie w środku przedziału
    iter_start = iter_end + 1
    iter_end   = floor(2 * iter / 3)

    curr = middle

    for _ in iter_start:iter_end
        next = curr + step

        if nextfloat(curr) != next
            return false
        end

        curr = next
    end

    # Sprawdzenie na końcu przedziału
    iter_start = iter_end + 1
    iter_end   = iter

    curr = stop

    for _ in iter_start:iter_end
        prev = curr - step

        if prevfloat(curr) != prev
            return false
        end

        curr = prev
    end

    return true
end

# Funkcja main przeprowadza testy dla funkcji check_interval.
function main()
    interval::Pair{Float64, Float64} = Pair(1.0, 2.0)
    delta::Float64 = 2.0^(-52)

    r::Bool = check_interval(interval.first, interval.second, delta)
    println("check_interval([1.0, 2.0], 2⁻⁵²): ", r ? "OK" : "FAIL")

    interval = Pair(0.5, 1.0)
    delta = 2.0^(-53)

    r = check_interval(interval.first, interval.second, delta)
    println("check_interval([0.5, 1.0], 2⁻⁵³): ", r ? "OK" : "FAIL")

    interval = Pair(2.0, 4.0)
    delta = (2.0^(-51))

    r = check_interval(interval.first, interval.second, delta)
    println("check_interval([2.0, 4.0], 2⁻⁵¹): ", r ? "OK" : "FAIL")
end

if abspath(PROGRAM_FILE) == @__FILE__
    main()
end
