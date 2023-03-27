import Data.List
import System.IO

-- write a function to add two numbers and double the result
add_and_double :: Int -> Int -> Int
add_and_double x y = 2*(x+y)

-- write a function to solve a quadratic equation
solve_quadratic_equation :: Double -> Double -> Double -> (Double, Double)
solve_quadratic_equation a b c = (x1, x2)
    where dis = b*b - 4*a*c
          x1 = (-b + sqrt dis) / (2*a)
          x2 = (-b - sqrt dis) / (2*a)

-- write a function to check if a number is perfect or not

    -- finding the proper divisors of a number
proper_divisors :: Int -> [Int]
proper_divisors n = [x | x <- [1..n-1], n `mod` x == 0]

    -- checking if a number is perfect or not
isPerfect :: Int -> Bool
isPerfect 0 = False
isPerfect n = sum (proper_divisors n) == n

-- write a function to find the next perfect number
nextPerfect :: Int -> Int
nextPerfect n = if isPerfect (n+1) then n+1 else nextPerfect (n+1)

--write a function to check if a list of integers is paritioned or not (a list is paritioned if there is a number n such that all numbers before n are smaller and all numbers after n are greater)

idxSmaller :: [Int] -> Int -> Bool
idxSmaller [] _ = True
idxSmaller (x:xs) n = if x <= n then idxSmaller xs n else False

idxGreater :: [Int] -> Int -> Bool
idxGreater [] _ = True
idxGreater (x:xs) n = if x > n then idxGreater xs n else False

partitioned :: [Int] -> Int -> Bool
partitioned [] _ = False
partitioned [x] _ = True

partitioned x n = do
    let (a, b) = (take n x, drop (n+1) x)

    if n < length x then
        if idxSmaller a (x!!n) && idxGreater b (x!!n) then
            True
        else
            partitioned x (n+1)
    else
        False

-- write a function to check if a list of strings is connected or not (a string is connected to another if they differ by only one character and are unique)
ifUnique :: [String] -> Bool
ifUnique [] = True
ifUnique (x:xs) = if x `elem` xs then False else ifUnique xs

ifOnlyOneCharDiffer :: String -> String -> Bool
ifOnlyOneCharDiffer [] [] = False
ifOnlyOneCharDiffer (x:xs) (y:ys) = if x == y then ifOnlyOneCharDiffer xs ys else if xs == ys then True else False

connected :: [String] -> Bool
connected [] = True
connected [x] = True
connected (x:xs) = if ifOnlyOneCharDiffer x (head xs) && ifUnique (x:xs) then connected xs else False

-- main

main = do
    -- add_and_double
    putStrLn " "
    putStrLn "Program 1: add_and_double"
    putStrLn "add_and_double 3 4"
    putStr "Output: "
    print (add_and_double 3 4)

    putStrLn " "
    putStrLn "Program 2: solve_quadratic_equation"
    putStrLn "solve_quadratic_equation 1 -5 6"
    putStr "Output: "
    print (solve_quadratic_equation 1 (-5) 6)

    putStrLn " "
    putStrLn "Program 3: isPerfect"
    putStrLn "isPerfect 496"
    putStr "Output: "
    print (isPerfect 496)

    putStrLn " "
    putStrLn "Program 4: nextPerfect"
    putStrLn "nextPerfect 240"
    putStr "Output: "
    print (nextPerfect 240)

    putStrLn " "
    putStrLn "Program 5: partitioned"
    putStrLn "partitioned [19,13,16,15,25,19,22]"
    putStr "Output: "
    print(partitioned [19,13,16,15,25,19,22] 0)

    putStrLn " "
    putStrLn "Program 6: connected"
    putStrLn "connected [\"abc\", \"bbc\", \"bcc\", \"bcd\"]"
    putStr "Output: "
    print(connected ["abc", "bbc", "bcc", "bcd"])


