
sum([], 0).
sum([X | L], S) :-
    sum(L, S1),
    S is S1 + X.

sum_var([], _, 0).
sum_var([X | L], A, S) :-
    sum_var(L, A, S1),
    S is S1 + (X - A) * (X - A).

average(L, X) :-
    sum(L, S),
    length(L, N),
    X is S / N.

variance(L, X) :-
    average(L, A),
    sum_var(L, A, S),
    length(L, N),
    X is S / N.

sublist(L, X) :-
    append(_, L1, L),
    append(X, _, L1).

max_sum(L, X) :-
    sublist(L, L1),
    sum(L1, X),
    forall(sublist(L,L2),(sum(L2,S), X >= S)).

# even_permutation(L, X) :-

permutation(L, 0, L).
permutation(L, 1, L) :-
    fail.

permutation(L, N, X) :-
    forall(member(L, M), member(X, M)),
    
