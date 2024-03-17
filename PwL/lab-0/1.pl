true.                           # -> true
fail.                           # -> false
true, fail.                     # -> false      , = and
true; fail.                     # -> true       ; = or
(true, fail); (fail; true).     # -> true
X = 1.                          # -> X = 1
X = 1, X = 2.                   # -> false
X = 1; X = 1.                   # -> X = 1 | X = 2
X is 1, Y is X+1.               # -> X = 1, Y = 2
(X is 1; X is 2), 2*X > 3.      # -> X = 2
between(7, 11, K), K =\= 9.     # -> K = 7 | K = 8 | K = 10 | K = 11
halt.                           # -> exit