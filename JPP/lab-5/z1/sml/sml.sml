fun binomial n k =
    if k = 0 orelse k = n then 1
    else binomial (n - 1) (k - 1) + binomial (n - 1) k;

fun pascal n =
    if n = 0 then [1]
    else
        let
            val lastRow = pascal (n - 1)
        in
            1 :: ListPair.map op+ (List.take (lastRow, n), List.drop (lastRow, 1)) @ [1]
        end;

fun binomial2 n k =
    List.nth (pascal n, k);

fun merge (left, right) =
    let
        fun merge' ([], right) = right
          | merge' (left, []) = left
          | merge' (left as l :: ls, right as r :: rs) =
            if l < r then l :: merge' (ls, right)
            else r :: merge' (left, rs)
    in
        merge' (left, right)
    end;

fun mergeSort list =
    if List.length list <= 1 then list
    else
        let
            val mid = List.length list div 2
            val left = List.take (list, mid)
            val right = List.drop (list, mid)
            val leftSorted = mergeSort left
            val rightSorted = mergeSort right
        in
            merge (leftSorted, rightSorted)
        end;

fun diophantineEquation a b =
    let
        fun egcd a b =
            if b = 0 then (a, 1, 0)
            else
                let
                    val (d, x, y) = egcd b (a mod b)
                in
                    (d, y, x - (a div b) * y)
                end
    in
        egcd a b
    end;

fun nub [] = []
    | nub (x :: xs) = if List.exists (fn y => x = y) xs then nub xs else x :: nub xs;

fun primeFactorsHelper n d =
    if n <= 1 then []
    else
        if n mod d = 0 then d :: primeFactorsHelper (n div d) d
        else primeFactorsHelper n (d + 1);

fun primeFactors n = nub (primeFactorsHelper n 2);

fun gcd a b =
    if b = 0 then a
    else gcd b (a mod b);

fun totient n =
    let
        fun totient' n d =
            if n <= 1 then 1
            else if n = d then 1
            else if gcd n d = 1 then 1 + totient' n (d + 1)
            else totient' n (d + 1)
    in
        totient' n 2
    end;

fun totient2 n =
    let
        val primes = primeFactors n
    in
        n * List.foldl (fn (x, acc) => acc * (x - 1)) 1 primes div List.foldl op* 1 primes
    end;

fun primes n =
    let
        fun primes' list =
            if list = [] then []
            else
                let
                    val x = List.hd list
                in
                    x :: primes' (List.filter (fn y => y mod x <> 0) (List.tl list))
                end
    in
        primes' (List.tabulate (n - 1, fn x => x + 2))
    end;


fun ListToString [] = ""
    | ListToString [x] = Int.toString x
    | ListToString (x :: xs) = Int.toString x ^ ", " ^ ListToString xs;

fun main () =
    let
        val bin = binomial 5 2
        val bin2 = binomial2 5 2
        val mrg = mergeSort [9, 9, 2, 3, 1]
        val (d, y, x) = diophantineEquation 10 6
        val pf = primeFactors 27
        val tot = totient 10
        val tot2 = totient2 10
        val pr = primes 50
    in (
            print ("binomial(5, 2) = " ^ Int.toString bin ^ "\n");
            print ("binomial2(5, 2) = " ^ Int.toString bin2 ^ "\n");
            print ("mergeSort([9, 9, 2, 3, 1]) = [" ^ ListToString mrg ^ "]\n");
            print ("diophantineEquation(10, 6) = "
                ^ "(" ^ Int.toString d ^ ") "
                ^ ",(" ^ Int.toString y ^ ") "
                ^ ",(" ^ Int.toString x ^ ") "
                ^ " \n");
            print ("primeFactors(27) = [" ^ ListToString pf ^ "]\n");
            print ("totient(10) = " ^ Int.toString tot ^ "\n");
            print ("totient2(10) = " ^ Int.toString tot2 ^ "\n");
            print ("primes(50) = [" ^ ListToString pr ^ "]\n")
        )
    end;

val _ = main ();


