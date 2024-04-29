% zad. 2 zagadka einsteina

% - Norweg zamieszkuje pierwszy dom
% - Anglik mieszka w czerwonym domu.
% - Zielony dom znajduje się bezpośrednio po lewej stronie domu białego.
% - Duńczyk pija herbatkę.
% - Palacz papierosów light mieszka obok hodowcy kotów.
% - Mieszkaniec żółtego domu pali cygara.
% - Niemiec pali fajkę.
% - Mieszkaniec środkowego domu pija mleko.
% - Palacz papierosów light ma sąsiada, który pija wodę.
% - Palacz papierosów bez filtra hoduje ptaki.
% - Szwed hoduje psy.
% - Norweg mieszka obok niebieskiego domu.
% - Hodowca koni mieszka obok żółtego domu.
% - Palacz mentolowych pija piwo.
% W zielonym domu pija się kawę.

% Dom: [numer, kolor, kraj, zwierze, co pije, co pali]
% [_,_,_,_,_,_]

po_lewej(X,Y,[X,Y|_]).
po_lewej(X,Y,[_|Z]):-
    po_lewej(X,Y,Z).

obok(X,Y,Domy):-
    po_lewej(X,Y,Domy);
    po_lewej(Y,X,Domy).

rybki(Kto):-
    Domy = [
        [1,_,_,_,_,_],
        [2,_,_,_,_,_],
        [3,_,_,_,_,_],
        [4,_,_,_,_,_],
        [5,_,_,_,_,_]
    ],
    member([1,_,norweg,_,_,_], Domy),
    member([_,czerwony,anglik,_,_,_], Domy),
    po_lewej([_,zielony,_,_,_,_],[_,bialy,_,_,_,_],Domy),
    member([_,_,dunczyk,_,herbatka,_], Domy),
    obok([_,_,_,_,_,light],[_,_,_,koty,_,_],Domy),
    member([_,zolty,_,_,_,cygara],Domy),
    member([_,_,niemiec,_,_,fajka],Domy),
    member([3,_,_,_,mleko,_], Domy),
    obok([_,_,_,_,_,light],[_,_,_,_,woda,_], Domy),
    member([_,_,_,ptaki,_,bezfiltra], Domy),
    member([_,_,szwed,psy,_,_], Domy),
    obok([_,_,norweg,_,_,_], [_,niebieski,_,_,_,_], Domy),
    obok([_,_,_,konie,_,_], [_,zolty,_,_,_,_], Domy),
    member([_,_,_,_,piwo,mentolowe], Domy),
    member([_,zielony,_,_,kawa,_], Domy),
    member([_,_,Kto,rybki,_,_], Domy).

