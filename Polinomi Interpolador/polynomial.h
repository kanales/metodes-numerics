#ifndef HEADER_FILE
#define HEADER_FILE

#include <stdlib.h>

/* * * * * * * * * * * * * * * * * * * * *
 *             DESCRIPTION               *
 * * * * * * * * * * * * * * * * * * * * *
 
 This module offers tools to ease the burden of working
 with polynomials in c.
 */

/* * * * * * * * * * * * * * * * * * * * *
 *             TYPE DECLARATIONS         *
 * * * * * * * * * * * * * * * * * * * * */

/* 
 * Polynomial type
 * ==============
 *
 * Considerations:
 *   coefficients are represented in
 *   increasing degree. 
 **/

typedef struct {
    double * coef;
    int degree;
} polynomial;

/* * * * * * * * * * * * * * * * * * * *
 *             CONSTRUCTORS            *
 * * * * * * * * * * * * * * * * * * * */ 

/* matrix constructor */
polynomial * new_polynomial(int degree, double * coefficients) {
    polynomial * temp; 
        
    if (degree < 0) {
       perror("A polynomial degree must be positive. Exiting...\n");
       exit(EXIT_FAILURE);
    }

    temp = (polynomial*)malloc(sizeof(polynomial));

    if (temp == NULL) {
        perror("Memory could not be allocated. Exiting...\n");
        exit(EXIT_FAILURE);
    }

    temp->coef = coefficients; /* note: arguments are assigned and not copied */
    temp->degree = degree;
    return temp;
}

/* * * * * * * * * * * * * * * * * * * *
 *               DESTRUCTORS           *
 * * * * * * * * * * * * * * * * * * * */ 
void free_polynomial(polynomial *p) {
    free(p->coef); /* note: arguments are destroyed, if you need to keep them
                      consider using free(p) */
    free(p);
}

/* * * * * * * * * * * * * * * * * * * *
 *             TYPE  FUNCTIONS         *
 * * * * * * * * * * * * * * * * * * * */

double get_at_degree(int degree, polynomial * p) {
    /* Returns item with a given degree in {0, ..., p.degree} */
    if (degree > p->degree) {
        perror("Out of range.");
        exit(EXIT_FAILURE);
    } else return v->coef[degree];
}

/* Avalua un polinomi en un valor, i.e. p(a) */
double p_evaluate(double a, polynomial *p) {/* placeholder */
    int i = p->degree;
    double temp;
    
    /* Horner */
    temp = get_at_degree(i, p);
    while ( i >= 0) {
        temp *= a;
        temp += get_at_degree(i, p);
    }
    return temp;
}

/* Retorna el polinomi suma de dos polinomis */
polynomial * p_add(polynomial *p, polynomial *q) {
    int idx, min_degree, max_degree, new_degree;
    polynomial * temp;
    double *v;
    
    /* prenem el grau mes gran */
    if (p->degree < q->degree) {
        max_degree = q->degree;
        min_degree = p->degree;
    } else {
        max_degree = p->degree;
        min_degree = q->degree;
        temp = p;
        p = q;
        q = temp;
    }
    /* ---------------------- */

    /* si al sumar els polinomis baixa el grau maxim 
     * cal reflectir-ho en la solucio */
    if (max_degree == min_degree) {
        new_degree = (get_at_degree(max_degree, p) 
                == -get_at_degree(max_degree, q) 
                ? max_degree - 1 
                : max_degree);
    /* ---------------------------------------------- */

    /* suma dels polinomis */
    v = (double*) malloc(new_degree * sizeof(double));
    for (idx = 0; idx <= min_degree; idx ++) {
        /* suma propiament dita */
        v[idx] = get_at_degree(idx, p) + get_at_degree(idx, q);
    }
    /* q(x) es el polinomi amb mes grau */
    for (idx = min_degree + 1; idx < max_degree; idx ++) {
        /* afegim els coeficients restants */
        v[idx] = get_at_degree(idx, q);
    }
    /* -------------------- */

    return new_polynomial(new_degree, v); 
}

/* Retorna el polinomi resta de dos polinomis */
polynomial *  p_sub(polynomial *p, polynomial *q) {
    int idx, min_degree, max_degree, new_degree, mulp, mulq;
    polynomial * temp;
    double *v;
    bool swap = 0;
    
    /* prenem el grau mes gran */
    if (p->degree < q->degree) {
        max_degree = q->degree;
        min_degree = p->degree;
    } else {
        max_degree = p->degree;
        min_degree = q->degree;
        temp = p;
        p = q;
        q = temp;
        swap = 1;
    }
    /* ---------------------- */

    /* si al sumar els polinomis baixa el grau maxim 
     * cal reflectir-ho en la solucio */
    if (max_degree == min_degree) {
        new_degree = (get_at_degree(max_degree, p) 
                == get_at_degree(max_degree, q) 
                ? max_degree - 1 
                : max_degree);
    /* ---------------------------------------------- */

    /* suma dels polinomis */
    v = (double*) malloc(new_degree * sizeof(double));
    mulp = (swap ? -1 : 1);
    mulq = - mul1;
    for (idx = 0; idx <= min_degree; idx ++) {
        /* suma propiament dita */
        v[idx] = mulp * get_at_degree(idx, p) + mulq * get_at_degree(idx, q);
    }
    /* q(x) es el polinomi amb mes grau */
    for (idx = min_degree + 1; idx < max_degree; idx ++) {
        /* afegim els coeficients restants */
        v[idx] = mulq * get_at_degree(idx, q);
    }
    /* -------------------- */

    return new_polynomial(new_degree, v); 
}

/* Retorna el polinomi producte de un polinomi per
 * una constant, i.e. r(x) = lambda * p(x) */
polynomial * const_prod(int lambda, polynomial * p) {
    int it, new_degree;
    double * temp;

    if (lambda == 0) {
        /* si la constant es 0 el polinomi nou
         * sera q(x) = 0 */
        temp = (double*) malloc(sizeof(double));
        temp[0] = 0;
        new_degree = 0;
    } else {
        temp = (double*) malloc((p->degree + 1) * sizeof(double));
        new_degree = p->degree;
        for (it = 0; it <= new_degree; it ++) {
            temp[it] = lambda * get_at_degree(it, p);
        }
    }
    return new_polynomial(new_degree, temp);
}

    
polynomial * p_prod(polynomial *p, polynomial *q) {/* placeholder */}
polynomial * p_roots(polynomial *p) {/* placeholder */} /* Avanzado */

/* ------------ */
#endif
