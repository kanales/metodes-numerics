# polynomial.h
En el mòdul _polynomial.h_ s'inclouen estructures de dades i funcions per a facilitar la manipulació de polinomis en les práctiques de mètodes numèrics.

## Estructures de dades
* `polynomial`: aquesta **struct** emmagatzema els coeficients i el grau d'un polinomi donat.

## Funcions
* `polynomial * new_polynomial(int degree, double * coefficients)`: retorna un polinomi de grau _degree_ a partir d'una llista de coeficients.
* `void free_polynomial(polynomial * p)`: allibera la memòria del polinomi i els seus coeficients.
* `double p_get_at_degree(int degree, polynomial * p)`: retorna el coeficient de grau _degree_ del polinomi. 
* `double p_evaluate(double x, polynomial * p)`: avalua _p(x)_. **Cal comprovar**
* `polynomial * p_add(polynomial * p, polynomial * q)`: retorna el polinomi suma de p i q, i.e. _r(x) = p(x) + q(x)_  **Cal comprovar**
* `polynomial * p_sub(polynomial * p, polynomial * q)`: retorna el polinomi resta de p i q, i.e. _r(x) = p(x) - q(x)_  **Cal comprovar**
