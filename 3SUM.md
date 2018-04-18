```
3SUM(A[1..n] : array of different integers)
 1. Sort(A[1..n])
 2. for i <- 1 to n-2
 3.   if A[i] >= 0
 4.     return
 5.   j <- i+1, k <- n
 6.   while j<k
 7.     s <- A[i]+A[j]+A[k]
 8.     if s = 0
 9.       print i,j,k
10.       j <- j+1, k <- k-1
11.     else if s < 0
12.       j <- j+1
13.     else
14.       k <- k-1
```
