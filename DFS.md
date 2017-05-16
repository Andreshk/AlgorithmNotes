```
DFS(G(V,E): graph)
1. foreach u in V
2.   color[u] <- White
3.   pred[u] <- NIL
4. time <- 0
5. foreach u in V
6.   if color[u] = White
7.     DFSVisit(G,v)

DFSVisit(G(V,E): graph, v: vertex from V)
1. color[v] <- Gray
2. time <- time + 1
3. d[v] <- time
4. foreach u in Adj(v)
5.   if color[u] = White
6.     pred[u] <- v
7.     DFSVisit(G,u)
8. color[v] <- Black
9. time <- time + 1
10. f[u] <- time
```
