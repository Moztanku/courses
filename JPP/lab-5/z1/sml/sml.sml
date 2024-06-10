fun binomial n k =
    if k = 0 orelse k = n then 1
    else binomial (n - 1) (k - 1) + binomial (n - 1) k;

(* fun binomial2 n k = *)


print (Int.toString (binomial 5 2) ^ "\n");