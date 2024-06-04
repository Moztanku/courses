import System.Environment
import Text.Read
import System.Exit (exitWith, ExitCode(..))

-- TODO: Implement binomial function using Euler's triangle
binomial :: Integer -> Integer -> Integer
binomial n k = 0

print_help :: Int -> IO ()
print_help status = do
    exec <- getProgName

    putStrLn $ "Usage: "
    putStrLn $ "\t./" ++ exec ++ " N K"
    putStrLn $ "\t" ++ "where N and K are non-negative integers, and N >= K."

    exitWith $  if status == 0
                    then ExitSuccess
                    else ExitFailure status

main :: IO ()
main = do
    args <- getArgs

    if (args !! 0) == "--help" || (args !! 0) == "-h"
        then print_help 0

    else if length args /= 2
        then print_help 1
        
    else do
        let n = readMaybe (args !! 0) :: Maybe Integer
        let k = readMaybe (args !! 1) :: Maybe Integer

        case (n, k) of
            (Just n', Just k') -> do
                if n' < 0 || k' < 0 || n' < k'
                    then print_help 1
                    else putStrLn $ show $ binomial n' k'
            _ -> print_help 1