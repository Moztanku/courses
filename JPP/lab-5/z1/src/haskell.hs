import System.Environment (getProgName, getArgs)
import System.FilePath (takeFileName)
import Text.Read
import System.Exit (exitWith, ExitCode(..))

import Haskell_functions

print_help :: Int -> IO ()
print_help status = do
    exec <- getProgName
    let prefix = " ./" ++ exec ++ " "

    putStrLn $ "Usage: "
    putStrLn $ prefix   ++ "binomial N K   " ++ "\t" ++ "-- Calculate binomial coefficient."
    putStrLn $ prefix   ++ "binomial2 N K  " ++ "\t" ++ "-- Calculate binomial coefficient using Euler's triangle."
    putStrLn $ "\t"     ++ "-- N and K are non-negative integers, and N >= K."

    putStrLn $ prefix   ++ "mergesort      " ++ "\t" ++ "-- Sort a list using merge sort."
    putStrLn $ "\t"     ++ "-- the list is read from standard input. # TODO: Implement"

    putStrLn $ prefix   ++ "de A B         " ++ "\t" ++ "-- Solve a linear Diophantine equation Ax + By = GCD(A,B)."
    putStrLn $ "\t"     ++ "-- A and B are integers. # TODO: Implement"
    
    putStrLn $ prefix   ++ "prime_factors N" ++ "\t" ++ "-- Calculate prime factors of N."
    putStrLn $ prefix   ++ "totient N      " ++ "\t" ++ "-- Calculate Euler's totient function of N."
    putStrLn $ prefix   ++ "totient2 N     " ++ "\t" ++ "-- Calculate Euler's totient function of N using prime factors."
    putStrLn $ prefix   ++ "primes N       " ++ "\t" ++ "-- Calculate N prime numbers."
    putStrLn $ "\t"     ++ "-- N is a non-negative integer and N >= 2."
    
    putStrLn $ prefix   ++ "--help/-h      " ++ "\t" ++ "-- Print this help message."

    exitWith $  if status == 0
                    then ExitSuccess
                    else ExitFailure status

parse_stdin :: IO [Int]
parse_stdin = do
    input <- getContents
    return $ map read $ words input

process_n :: Show a => (Int -> a) -> String -> IO ()
process_n fun arg = do
    let n = readMaybe arg :: Maybe Int

    case n of
        Just n' -> do
            if n' <= 1
                then print_help 1
            else do
                let res = fun n'
                putStrLn $ show res
        _ -> print_help 1

process_nk :: Show a => (Int -> Int -> a) -> String -> String -> IO ()
process_nk fun arg1 arg2 = do
    let n = readMaybe arg1 :: Maybe Int
    let k = readMaybe arg2 :: Maybe Int

    case (n, k) of
        (Just n', Just k') -> do
            if n' < 0 || k' < 0 || n' < k'
                then print_help 1
            else do
                let res = fun n' k'
                putStrLn $ show res
        _ -> print_help 1

process_ab :: Show a => (Int -> Int -> a) -> String -> String -> IO ()
process_ab fun arg1 arg2 = do
    let a = readMaybe arg1 :: Maybe Int
    let b = readMaybe arg2 :: Maybe Int

    case (a, b) of
        (Just a', Just b') -> do
            let res = fun a' b'
            putStrLn $ show res
        _ -> print_help 1

process_stdin :: Show a => ([Int] -> a) -> IO ()
process_stdin fun = do
    input <- parse_stdin
    let res = fun input
    putStrLn $ show res

main :: IO ()
main = do
    args <- getArgs

    case args of
        [] -> print_help 1
        ("--help":_) -> print_help 0
        ("-h":_) -> print_help 0
        ("binomial":n:k:_) -> process_nk binomial n k
        ("binomial2":n:k:_) -> process_nk binomial2 n k
        ("mergesort":_) -> process_stdin mergeSort
        ("de":a:b:_) -> process_ab diophantineEquation a b
        ("prime_factors":n:_) -> process_n primeFactors n
        ("totient":n:_) -> process_n totient n
        ("totient2":n:_) -> process_n totient2 n
        ("primes":n:_) -> process_n primes n
        _ -> print_help 1