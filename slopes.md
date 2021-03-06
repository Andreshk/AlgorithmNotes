## Брой склонове (и максимална дължина на склон) в масив

За целите на тази задача подмасив ще наричаме последователност от съседни елементи в масив и ще бележим с `A[i..j]`: подмасивът, включващ елементите от индекс `i` до индекс `j`, включително. Под "склон" в масив ще наричаме максимален по включване подмасив, за който всяко следващо число е не по-малко от предишното. Например масивът `А={5,7,7,10,4,5,8}` има точно два склона - подмасивите `A[1..4]` и `A[5..7]` (`{5,7,7,10}` и `{4,5,8}`). `А[5..6]` не е склон, защото може да се "разшири" с елемента `А[7]`, и `A[2..5]` също не е. Очевидно празни склонове няма, а във всеки масив има поне един склон.

### Зад.1

Напишете алгоритъм, който по даден масив от числа намира броя на склоновете в него. Докажете неговата коректност.
Ако желаете, може директно да докажете, че следният алгоритъм решава тази задача:
<details>
  <summary>цък</summary>
  Slopes(A[1..n])<br>
  1. count <- 1<br>
  2. for i <- 2 to n<br>
  3. __if A[i] < A[i-1]<br>
  4. ____count <- count + 1<br>
  5. return count
</details>

### Зад.2
Напишете алгоритъм, който изчислява максималната дължина на склон в даден масив. Докажете и неговата коректност.

_Упътване:_ целта на задачата е да използвате доказателство с инварианта на цикъла. Естествено, можете да предложите и рекурсивен алгоритъм :)
