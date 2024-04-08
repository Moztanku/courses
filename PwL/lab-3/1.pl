% zad. 1

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

% zad. 2

max_sum_([],X,_,X).

max_sum_([I|L], Max, Curr, X) :-
    J is Curr + I,
    (J > 0 -> (
        Next is J,
        (Next > Max -> M1 is Next ; M1 is Max)
    ); (
        Next is 0,
        M1 is Max
    )),
    max_sum_(L, M1, Next, X).
    
max_sum(L,X) :-
    max_sum_(L,0,0,X).

% zad. 3

inversions([], 0).
inversions([X | L], N) :-
    findall(Y, (member(Y, L), Y < X), L1),
    length(L1, N1),
    inversions(L, N2),
    N is N1 + N2.

permutation([], []).
permutation([X | L], P) :-
    permutation(L, P1),
    select(X, P, P1).

even_permutation(L, R) :-
    permutation(L, R),
    inversions(R, N),
    0 is N mod 2.

odd_permutation(L, R) :-
    permutation(L, R),
    inversions(R, N),
    1 is N mod 2.
