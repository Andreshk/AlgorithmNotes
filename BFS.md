```
BFS(G(V,E): graph)
 1. foreach u in V
 2.   visited[u] <- False
 3.   pred[u] <- NIL
 4. Q <- празна опашка
 5. foreach u in V
 6.   if !visited[u]
 7.     visited[u] <- True
 8.     Q.push(u)
 9.   while Q не е празна
10.     v <- Q.pop()
11.     foreach w in Adj(v)
12.       if !visited[w]
13.         visited[w] <- True
14.         pred[w] <- v
15.         Q.push(w)
```

За този алгоритъм `T(n,m) = Θ(n+m)`, а `M(n,m) = Θ(n)`. Тук всеки връх може да влезе точно веднъж в опашката, затова нейният размер е `O(n)` (може да е по-малък в зависимост от графа), докато масивите visited и pred все така заемат `Θ(n)` памет.
