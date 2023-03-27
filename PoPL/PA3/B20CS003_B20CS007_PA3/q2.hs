qE :: Float->Float->Float->IO()
qE a b c = do
   let d = b^2 - 4*a*c
   if (d < 0)
      then do
         print ("This quadratic equation has imaginary roots")
      else do
         let root1 = (-(b) + sqrt (d))/2 * (a)
         let root2 = (-(b) - sqrt (d))/2 * (a)
         print ("The roots for this quadratic are:")
         print (root1)
         print (root2)


main :: IO()
main = do
   putStrLn "Enter a, b, c of the quadratic function in 3 lines:"  
   a <- getLine
   b <- getLine
   c <- getLine
   let x= (read a :: Float)
   let y= (read b :: Float)
   let z= (read c :: Float)
   qE (x) (y) (z)  