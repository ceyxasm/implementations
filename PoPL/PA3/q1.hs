main :: IO()
main = do

   print ("Enter 2 space separated integers:")
   line <- getLine
   let a = (read (takeWhile (/= ' ') line) :: Int)
   let b = (read (drop 1 (dropWhile (/= ' ') line)) :: Int)
   print ("The Addition of two numbers is:")
   putStrLn (show (a+b)) 
