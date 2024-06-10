(defun binomial (n k)
    (if (or (= k 0) (= k n))
        1
        (+ (binomial (- n 1) (- k 1)) (binomial (- n 1) k))
    )
)

(defun binomial2 (n k)
    (let ((triangle (list (list 1))))
        (dotimes (i n)
            (let* (
                    (last-row (first triangle))
                    (new-row (list 1))
                )
                (dotimes (j i)
                    (push (+ (nth j last-row) (nth (1+ j) last-row)) new-row))
                (push 1 new-row)
                (push (nreverse new-row) triangle)
            )
        )
        (nth k (first triangle))
    )
)

(defun egcd (A B)
    (if (= B 0)
        (values A 1 0)
        (multiple-value-bind (D X1 Y1) (egcd B (mod A B))
            (values D Y1 (- X1 (* Y1 (floor A B))))
        )
    )
)

(defun mergeSort (List)
    (if (<= (length List) 1)
        (return-from mergeSort List)
    )

    (let* (
            (mid (floor (length List) 2))
            (Left (subseq List 0 mid))
            (Right (subseq List mid))

            (LeftSorted (mergeSort Left))
            (RightSorted (mergeSort Right))
        )

        (merge 'list LeftSorted RightSorted #'<)
    )
)

(defun de (A B)
    (multiple-value-bind (D X Y) (egcd A B)
        (list D X Y)
    )
)

(defun prime_factors_helper (N D)
    (if (<= N 1)
        (return-from prime_factors_helper (list))
    )

    (if (= (mod N D) 0)
        (cons D (prime_factors_helper (floor N D) D))
        (prime_factors_helper N (+ D 1))
    )
)

(defun prime_factors (N)
    (remove-duplicates (prime_factors_helper N 2))
)

(defun totient_helper (N D)
    (if (= N 1)
        (return-from totient_helper 1))

    (if (= N D)
        (return-from totient_helper 1))

    (if (= (gcd N D) 1)
        (+ 1 (totient_helper N (+ D 1)))
        (totient_helper N (+ D 1))
    )
)

(defun totient (N)
    (totient_helper N 2)
)

(defun totient2 (N)
    (* N (apply #'* 
        (mapcar (lambda (x) (/ (- x 1) x)) (prime_factors N))
        ))
)

(defun primes_helper (List)
    (if (= (length List) 0)
        (return-from primes_helper (list)))

    (let* (
            (P (first List))
            (List (remove-if (lambda (x) (= (mod x P) 0)) List))
        )
        (cons P (primes_helper List))
    )
)

(defun iota (Start Step End)
    (if (> Start End)
        (return-from iota (list)))

    (cons Start (iota (+ Start Step) Step End))
)

(defun primes (N)
    (if (<= N 1)
        (return-from primes (list)))

    (primes_helper (iota 2 1 N))
)

(defun test ()
    (terpri)
    (format t "binomial(5, 2) = ~d~%" (binomial 5 2))
    (format t "binomial2(5, 2) = ~d~%" (binomial2 5 2))
    (format t "de(15, 10) = ~a~%" (de 15 10))
    (format t "mergeSort(10, 4, 3, 2, 1) = ~a~%" (mergeSort (list 10 4 3 2 1)))
    (format t "prime_factors(45) = ~a~%" (prime_factors 45))
    (format t "totient(11) = ~d~%" (totient 11))
    (format t "totient2(11) = ~d~%" (totient2 11))
    (format t "primes(10) = ~a~%" (primes 10))
    (terpri)
)

(test)