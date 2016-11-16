#ifndef HEADER_FILE
#define HEADER_FILE

#include <stdlib.h>
#include <stdio.h>

/* * * * * * * * * * *
 * TYPE DECLARATIONS *
 * * * * * * * * * * */

/* vector type */
typedef struct {
	double * items;
	int length;
} vector;

/* matrix type */
typedef struct {
	vector * vectors;
	int height;
	int width;
} matrix;

/* * * * * * * * *
 *  CONSTRUCTORS *
 * * * * * * * * */ 

/* vector constructor */
vector * new_vector(int length) {
    vector * dv;
    dv = (vector*) malloc(sizeof(vector));
    dv->length = length;
    dv->items = (double*) malloc(length * sizeof(double));
    return dv;
}

/* helper for matrix construction */
vector * matrix_alloc(int height, int width) {
    int i;
    vector *vectors;
    vectors = (vector*) malloc(height * sizeof(vector));
    for (i = 0; i < height; i++) {
            vectors[i] = *new_vector(width);
    }
    return vectors;
}

/* matrix constructor */
matrix * new_matrix(double height, double width) {
    matrix * dv = (matrix*)malloc(sizeof(matrix));

    dv->height = height;
    dv->width = width;
    dv->vectors = matrix_alloc(height, width);
    return dv;
}


/* * * * * * * *
 * DESTRUCTORS *
 * * * * * * * */ 
void free_vector(vector *d) {
    free(d->items);
    free(d);
}

void free_matrix(matrix *d) {
    int it;
    
    for (it = 0; it < d->height; it++) {
        free_vector(&d->vectors[it]);
    }
    free(d);
}


/* * * * * * * * * *
 * TYPE  FUNCTIONS *
 * * * * * * * * * */

/* VECTOR */

double vget(int idx, vector * v) {
    /* return item at index idx
     * if idx > n raise error */    

    if (idx >= v->length) {
        perror("Out of range.");
        exit(EXIT_FAILURE);
    } else return v->items[idx];
}

void vset(double x, int idx, vector * v) {
    if (idx >= v->length) {
        perror("Out of range.");
        exit(EXIT_FAILURE);
    } else v->items[idx] = x;
}
/* ------------ */

/* MATRIX */

double mget(int row, int col, matrix * m) {
    if (row >= m->height || col >= m->width) {
        printf("h: %d, w: %d",row, col);
        perror("Out of range.");
        exit(EXIT_FAILURE);
    } else return m->vectors[row].items[col];
}

void mset(double x, int row, int col, matrix * m) {
    if (row >= m->height || col >= m->width) {
        perror("Out of range.");
        exit(EXIT_FAILURE);
    } else m->vectors[row].items[col] = x;	
}
/* ------------ */
#endif
