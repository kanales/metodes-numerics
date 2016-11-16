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

double p_evaluate(double x, polynomial *p) {/* placeholder */} /* Horner! */
polynomial *  p_add(polynomial *p, polynomial *q) {/* placeholder */}
polynomial *  p_sub(polynomial *p, polynomial *q) {/* placeholder */}
polynomial * p_prod(polynomial *p, polynomial *q) {/* placeholder */}
polynomial * p_roots(polynomial *p) {/* placeholder */} /* Avanzado */

/* ------------ */
#endif
