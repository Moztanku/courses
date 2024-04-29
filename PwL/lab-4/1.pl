% zad. 1

wyrazenie([X], X, X).

wyrazenie(X, Y, Result):-
    append(X1, X2, X),
    X1 \= [],
    X2 \= [],
    wyrazenie(X1, W1, R1),
    wyrazenie(X2, W2, R2),
    (
        (Y is W1 + W2, Result = R1 + R2);
        (Y is W1 - W2, Result = R1 - R2);
        (Y is W1 * W2, Result = R1 * R2);
        (Y is W1 / W2, Result = R1 / R2)
    ).