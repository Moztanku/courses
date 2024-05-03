% Z listy 4

hetmany(N, P) :-
    numlist(1, N, L),
    permutation(L, P),

dobra(P).
dobra(P) :-
    \+ zla(P).

zla(P) :-
    append(_, [Wi | L1], P),
    append(L2, [Wj | _], L1),
    length(L2, K),
    abs(Wi - Wj) =:= K + 1.

% Rozwiązanie

board(Hetmany) :-
    length(Hetmany, Len),
    draw_row(Hetmany, Len, 1).

draw_row(Hetmany, Len, Row) :-
    (Row < Len ; Row = Len),
    draw_outline(Len, 1),
    Hetman is Len - Row + 1,
    index_of(Hetmany, Hetman, Index),
    draw_row(Len, Index, 1, Row),
    draw_row(Len, Index, 1, Row),
    C1 is Row + 1,
    draw_row(Hetmany, Len, C1).

draw_row(_, Len, Row) :-
    Row > Len,
    draw_outline(Len, 1).

draw_outline(Len, Counter) :-
    (Counter < Len ; Counter = Len),
    write('+-----'),
    C1 is Counter + 1,
    draw_outline(Len, C1).

draw_outline(Len, Ctr) :-
    Ctr > Len,
    write('+'), nl.

draw_row(Len, Hetman, Counter, Row) :-
    (Counter < Len ; Counter = Len),
    write('|'),
    (even(Row) -> 
        (even(Counter) -> 
            (Counter = Hetman -> write(' ### ') ; write('     ')) ;
            (Counter = Hetman -> write(':###:') ; write(':::::'))
        ) ;
        (even(Counter) ->
            (Counter = Hetman -> write(':###:') ; write(':::::')) ;
            (Counter = Hetman -> write(' ### ') ; write('     '))
        )
    ),
    C1 is Counter + 1,
    draw_row(Len, Hetman, C1, Row).

draw_row(Len, _, Ctr, _) :-
    Ctr > Len,
    write('|'), nl.

even(N) :-
    0 is N mod 2.

index_of([Element | _], Element, 1).
index_of([_ | Tail], Element, Index) :-
    index_of(Tail, Element, Index1),
    Index is Index1 + 1.

% Pomocnicze

main :-
    hetmany(12, H),
    board(H), !,
    write(H), nl.

test :-
    X = [1, 3, 5, 8, 10, 12, 6, 11, 2, 7, 9, 4],
    board(X), !,
    write(X), nl.