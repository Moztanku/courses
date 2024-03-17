member(X, [X | _]).
member(X, [_ | L]) :-
	member(X, L).

append([], L, L).
append([X | L1], L2, [X | L3]) :-
	append(L1, L2, L3).

select(X, [X | L], L).
select(X, [Y | L1], [Y | L2]) :-
	select(X, L1, L2).

# Z1

middle([X], X).
middle(L, X) :-
    append([_ | L1], [_], L),
    middle(L1, X).

# Z2

once(X, L) :-
    select(X, L, L1),
    not(member(X, L1)).

twice(X, L) :-
    append(L1, L2, L),
    once(X, L1),
    once(X, L2).

# Z3
arc(a, b).
arc(b, a).
arc(b, c).
arc(c, d).

path_(X, X, _).
path_(X, Z, T) :-
    arc(X, Y),
    not(member(Y, T)),
    path_(Y, Z, [Y|T]).

path(X, Z) :-
    path_(X, Z, [X]).
    
# Z4

# Check if list:
#   - has 2*N elements
#   - every element appears exactly twice
#   - in between two occurrences of each element there is even number of elements
length_check(N, L) :-
    length(L, N2),
    N2 is 2*N.

twice_check(L) :-
    forall(member(X, L), twice(X, L)).

inbetween_check(L, X) :-
    append(_, [X | L1], L),
    append(L2, [X | _], L1),
    length(L2, N),
    0 is N mod 2.

inbetween_check(L) :-
    forall(member(X, L), inbetween_check(L, X)).

list(N, L) :-
    length_check(N, L),
    twice_check(L),
    inbetween_check(L).