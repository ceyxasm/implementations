--function that checks if a given number is perfect integer or not--
    isPerfect :: Int -> Bool
    isPerfect n = do
        let sum_div = sum [i | i <- [1..n-1], n `mod` i == 0]
        if (sum_div == n)
            then do
                True
                -- print ( " is a perfect number")
            else do
                False
                -- print ( "is not perfect number")



    nextPerfect :: Int -> Int
    nextPerfect n | isPerfect n = n   -- don't need to compare to True here
                | otherwise = nextPerfect (n+1)