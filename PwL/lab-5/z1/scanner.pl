scanner(In, Out) :-
    read_file(In, Codes),
    remove_whitespaces(Codes, NoWSCodes),
    tokenize(NoWSCodes, Out).

read_file(In, Out) :-
    read_stream_to_codes(In, Codes),
    atom_codes(Out, Codes).

remove_whitespaces(In, Out) :-
    atom_codes(In, Codes),
    exclude(is_whitespace, Codes, NoWhitespaceCodes),
    atom_codes(Out, NoWhitespaceCodes).

is_whitespace(Code) :-
    member(Code, [9, 10, 32]).

tokenize(In, Out) :-
    get_token(In, Token, Rest), !,
    Out = [Token | Rest1],
    tokenize(Rest, Rest1).

tokenize('', []).

get_token(In, Token, Rest) :-
        atom_length(In, Len),
        get_token(In, Token, Rest, Len).

get_token(In, Token, Rest, Len) :-
    sub_atom(In, 0, Len, _, T),
    (
        key(T) -> Token = key(T) ;
        id(T) -> Token = id(T) ;
        int(T) -> Token = int(T) ;
        sep(T) -> Token = sep(T)
    ),
    atom_concat(T, Rest, In).

get_token(In, Token, Rest, Len) :-
    Len > 0,
    Len1 is Len - 1,
    get_token(In, Token, Rest, Len1).

key(K) :-
    member(K, ['read','write','if','then','else','fi','while','do','od','and','or','mod']), !.

id(ID) :-
    ID \= [],
    ID \= '',
    atom_chars(ID, Chars),
    forall(
        member(Char, Chars), member(Char, [
            'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
            'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
            'U', 'V', 'W', 'X', 'Y', 'Z'
        ])
    ), !.

int(Int) :-
    Int \= [],
    Int \= '',
    atom_chars(Int, Chars),
    (Int = '0' -> true ;
        Chars = [First | _],
        First \= '0',
        forall(
            member(Char, Chars), member(Char, [
                '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
            ])
        )
    ), !.

sep(Sep) :-
    member(Sep, [';', '+', '-', '*', '/', '(', ')', '<', '>', '=<', '>=', ':=', '=', '/=']), !.

main :-
    open('ex1.prog', read, X), scanner(X, Y), close(X), write(Y).

% main.