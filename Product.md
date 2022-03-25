Докажете, че следният алгоритъм връща произведението на всички числа в дадения масив:
```
Product(A[1..n] : array of integers, n >= 2)
1. i <- 1, j <- n, p <- 1
2. while i < j
3.   p <- p*A[i]*A[j]
4.   i <- i + 1, j <- j - 1
5. if n is odd
6.   p <- p*A[(n+1)/2]
7. return p
```
