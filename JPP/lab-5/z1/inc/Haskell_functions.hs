module Haskell_functions where

import Data.List (nub)

binomial :: Int -> Int -> Integer
binomial n k
    | k == 0 = 1
    | k == n = 1
    | otherwise = binomial (n - 1) (k - 1) + binomial (n - 1) k

binomial2 :: Int -> Int -> Integer
binomial2 n k = pascal !! n !! k
    where
        pascal = iterate (\row -> zipWith (+) (0:row) (row ++ [0])) [1]

mergeSort :: [Int] -> [Int]
mergeSort [] = []
mergeSort [x] = [x]
mergeSort xs = merge (mergeSort left) (mergeSort right)
    where
        (left, right) = splitAt (length xs `div` 2) xs

merge :: [Int] -> [Int] -> [Int]
merge xs [] = xs
merge [] ys = ys
merge (x:xs) (y:ys)
  | x <= y    = x : merge xs (y:ys)
  | otherwise = y : merge (x:xs) ys

egcd :: Int -> Int -> (Int, Int, Int)
egcd a 0 = (a, 1, 0)
egcd a b = (g, y, x - (a `div` b) * y)
    where
        (g, x, y) = egcd b (a `mod` b)

diophantineEquation :: Int -> Int -> (Int, Int, Int)
diophantineEquation a b = egcd a b

primeFactors :: Int -> [Int]
primeFactors n = nub (primeFactors' n 2)
    where
        primeFactors' 1 _ = []
        primeFactors' n f
            | n `mod` f == 0 = f : primeFactors' (n `div` f) f
            | otherwise = primeFactors' n (f + 1)

totient :: Int -> Int
totient n = totient' n 2
    where
        totient' 1 _ = 1
        totient' n f
            |   f == n = 1
            |   gcd n f == 1 = 1 + totient' n (f + 1)
            |   otherwise = totient' n (f + 1)

totient2 :: Int -> Int
totient2 n = 
    -- n * product [p `div` (p - 1) | p <- primeFactors n]
    n * product [p - 1 | p <- primeFactors n] `div` product [p | p <- primeFactors n]

primes :: Int -> [Int]
primes n
    | n < 2 = []
    | otherwise = primes' [2..n]
    where
        primes' [] = []
        primes' (x:xs) = x : primes' [y | y <- xs, y `mod` x /= 0]
