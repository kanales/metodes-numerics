#ifndef HEADER_FILE
#define HEADER_FILE

#include <stdlib.h>

/* type declarations */
typedef struct {
	double * data;
	int length;
} double_vector;

typedef struct {
	int * data;
	int length;
} int_vector;

typedef struct {
	double_vector * data;
	int height;
	int width;
}double_matrix;

typedef struct {
	int_vector * data;
	int height;
	int width;
}int_matrix;

/* constructores */
double_vector * new_double_vector(int length) {
	double_vector * dv;
	dv = (double_vector*)malloc(sizeof(double_vector));
	dv->length = length;
	dv->data = (double*) malloc(length * sizeof(double));
	return dv;
}

int_vector * new_int_vector(int length) {
	int_vector * dv;
	dv = (int_vector *)malloc(sizeof(int_vector));
	dv->length = length;
	dv->data = (int*) malloc(length * sizeof(int));
	return dv;
}

int_vector * int_matrix_alloc(int height, int width) {
	int i;
	int_vector *A;
	A = (int_vector*) malloc(height * sizeof(int_vector));
	for (i = 0; i < height; i++) {
		A[i] = *new_int_vector(width);
	}
	return A;
}

int_matrix * new_int_matrix(int height, int width) {
	int_matrix * dv = (int_matrix*)malloc(sizeof(int_matrix));

	dv->height = height;
	dv->width = width;
	dv->data = int_matrix_alloc(height, width);
	return dv;
}
double_vector * double_matrix_alloc(int height, int width) {
	int i;
	double_vector *A;
	A = (double_vector*) malloc(height * sizeof(double_vector));
	for (i = 0; i < height; i++) {
		A[i] = *new_double_vector(width);
	}
	return A;
}

double_matrix * new_double_matrix(double height, double width) {
	double_matrix * dv = (double_matrix*)malloc(sizeof(double_matrix));

	dv->height = height;
	dv->width = width;
	dv->data = double_matrix_alloc(height, width);
	return dv;
}


/* destructores */
void free_int_vector(int_vector *i) {
	free(i->data);
	free(i);
}

void free_double_vector(double_vector *d) {
	free(d->data);
	free(d);
}

void free_double_matrix(double_matrix *d) {
	free(d->data);
	free(d);
}

void free_int_matrix(int_matrix *d) {
	free(d->data);
	free(d);
}
/* ---------------- */

/* acceso a datos */
double get_double(int idx, double_vector* v) {
	return v->data[idx];
}

int get_int(int idx, int_vector* v) {
	return v->data[idx];
}
/* ---------------- */

#endif
