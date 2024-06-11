% 1. mergesort

% mergesort(+List, -Result)

split([], [], []).
split([X], [X], []).
split(List, Left, Right) :-
    append(Left, Right, List),
    length(Left, L),
    length(Right, R),
    (L =:= R; L =:= R + 1).

merge([], Right, Right).
merge(Left, [], Left).
merge([X | Left], [Y | Right], [X | Result]) :-
    X =< Y,
    merge(Left, [Y | Right], Result).
merge([X | Left], [Y | Right], [Y | Result]) :-
    X > Y,
    merge([X | Left], Right, Result).

mergesort([], []).
mergesort([X], [X]).
mergesort(List, Result) :-
    split(List, Left, Right),
    mergesort(Left, SortedLeft),
    mergesort(Right, SortedRight),
    merge(SortedLeft, SortedRight, Result), !.

% 2. de (diophantine equation)

egcd(A, 0, A, 1, 0).

egcd(A, B, G, X, Y) :-
    B > 0,
    Q is A // B,
    R is A mod B,
    egcd(B, R, G, X1, Y1),
    X is Y1,
    Y is X1 - Q * Y1.

de(A, B, D, X, Y) :-
    egcd(A, B, D, X, Y), !.

% 3. prime_factors

prime_factors(N, L) :-
    N > 0,
    findall(P, (factor(N, P), is_prime(P)), Ls),
    sort(Ls, L).

factor(N, F) :-
    between(2, N, F),
    N mod F =:= 0.

is_prime(2).
is_prime(N) :-
    N > 2,
    Limit is floor(sqrt(N)),
    not((between(2, Limit, X), N mod X =:= 0)).

% 4. totient

product_1([], 1).
product_1([X | L], P) :-
    product_1(L, P1),
    P is (X - 1) * P1.

product_2([], 1).
product_2([X | L], P) :-
    product_2(L, P1),
    P is X * P1.

totient(X, Y) :-
    prime_factors(X, L),
    product_1(L, P1),
    product_2(L, P2),
    Y is X * P1 / P2.


% 5. primes

primes(N, L) :-
    findall(P, (between(2, N, P), is_prime(P)), L).

