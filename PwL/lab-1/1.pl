# ojciec(X, Y)
# matka(X, Y)
# mezczyzna(X)
# kobieta(X)
# rodzic(X, Y)
# diff(X, Y)

# Z1

jest_matka(X) :- matka(X, _).
jest_ojcem(X) :- ojciec(X, _).
jest_synem(X) :- mezczyzna(X), rodzic(_, X).
siostra(X, Y) :- kobieta(X), rodzic(Z, X), rodzic(Z, Y), X \= Y.
dziadek(x, Y) :- mezczyzna(X), rodzic(X, Z), rodzic(Z, Y).
rodzenstwo(X, Y) :- rodzic(Z, X), rodzic(Z, Y), X \= Y.

# Z2

# on(Block1, Block2) - Block1 stoi na Block2

above(Block1, Block2) :-
    on(Block1, Block2);
    on(Block1, X) , above(X, Block2).

# Z3

isPrime(N) :-
    N > 1,
    J is floor(sqrt(N)),
    forall(between(2, J, X), N mod X =\= 0).

prime(Lo, Hi, N) :-
    between(Lo, Hi, N),
    isPrime(N).


