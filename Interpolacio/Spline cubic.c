#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<float.h>

int palu_d3(int n, double *a, double *b, double *c, double tol);
void fwd_subs_d3(int n, double *l, double *b);
int bwd_subs_d3(int n, double *a, double *b, double *y, double tol);

int d3(int n, double *a, double *b, double *c, double *f, double tol) {
	/* 
	 * Suposem que a és la diagonal superior, b la central
	 * i c la inferior 
	 * Suposem que el vector c comença en c[1] i que a
	 * acaba en a[n-1]
	 */
	
	if (palu_d3(n, a, b, c, tol)) return 1;
	fwd_subs_d3(n, c, f);
	if (bwd_subs_d3(n, a, b, f, tol)) return 1;

	return 0;
}

int splines3(int n, const double * X, const double *Y, double *h, double * M, 
        double * A, double * B, double tol) {
    /* h, M, A, B son punters buits
     *
     * len(delta) = n+1
     * len(y) = n+1
     */
    int j, i;
    double * a, * b, * c; /* vectors del sistema lineal */

    a  = (double *) malloc((n+1) * sizeof(double));
    b  = (double *) malloc((n+1) * sizeof(double));
    c  = (double *) malloc((n+1) * sizeof(double));

    /* trobem moments h */
    for (j = 0; j < n; j++) {
        h[j+1] = X[j+1] - X[j];
    }  

    /* valors inicials */
    b[0] = b[n] = 1;
    a[0]   = 0;
    c[n-1] = 0;
    M[0] = M[n] = 0;

    for (i = 1; i < n; i ++) {
        j = i - 1;
        c[i-1] = h[j] / 6.;
        b[i]   = (h[j] + h[j+1]) / 3.;
        c[i]   = h[i+1] / 6;
        M[i]   = (Y[i+1] - Y[i])/h[i+1] - (Y[i] - Y[i-1])/h[i];
    }

    /* resolem el sistema i comprovem que no hi hagi cap error */
    if (d3(n, a, b, c, M, tol)) {
        /* si retorna 1 hi ha hagut un error */
        free(a); free(b); free(c);
        return 1;
    }

    for (j = 0; j < n; j++) {
        A[j] = ((Y[j+1] - Y[j]) / h[j+1])  - (M[j+1] - M[j])*h[j+1]/6.;
        B[j] = Y[j] - M[j] * pow(h[j+1], 2) / 6.;
    }

    return 0;
}

double eval_spline3(double x, const double* xs, const double * h,
        const double * A, const double * B, const double * M) {

    int i;
    double h_temp;

    /* trobem la i
     * nota: si x no es en cap interval donara seg. fault 
     * */
    i = 0;
    while (x > xs[i]) { /* trobem i | x < xi => x in [x{i-1}, xi] */
        i++;
    } i--; /* => x in [xi, x{i+1}] */
    
    h_temp = 6 * h[i+1];
    return (M[i]*pow(xs[i+1] - x, 3)/h_temp
            + M[i+1] * pow(x - xs[i], 3) / h_temp
            + A[i] * (x - xs[i])
            + B[i]);
}

int main(int arcg, char ** argv) {
    double * A, * B, * M, * h, * X, *Y;
    double ev;
    int i;

    const int n = 5;

    X  = (double *) malloc((n+1) * sizeof(double));
    Y  = (double *) malloc((n+1) * sizeof(double));
    h  = (double *) malloc( n    * sizeof(double)); /* len(h) = n */
    M  = (double *) malloc((n+1) * sizeof(double)); /* moments */
    A  = (double *) malloc((n+1) * sizeof(double)); 
    B  = (double *) malloc((n+1) * sizeof(double)); 

    if (X == NULL || Y == NULL || h == NULL || M == NULL
            || A == NULL || B == NULL) {
        printf("Error allocating.");
        exit(1);
    }
    
    X[0] = 0.000000; Y[0] = 1.000000;
    X[1] = 0.500000; Y[1] = 0.800000;
    X[2] = 1.000000; Y[2] = 0.500000;
    X[3] = 2.000000; Y[3] = 0.200000;
    X[4] = 3.000000; Y[4] = 0.100000;
    X[5] = 5.000000; Y[5] = 0.038460;

    /* calculem M, A i B */
    splines3(n, X, Y, h, M, A, B, 1e-14);

    /* Test: */
    for (i =0; i < n+1; i++){
        ev = eval_spline3(X[i], X, h, A, B, M);
        printf("x=%lf\tS3(x)=%lf\tf(x)=%lf\n", X[i], ev, Y[i]);
    }

    return 0;
}
/* funcions d'ajuda */
int palu_d3(int n, double *a, double *b, double *c, double tol) {
    int k;
    double m;

    for ( k = 0; k < n - 1; k++) {
    	if (fabs(c[k+1]) < tol) return 1; /* si se intenta dividir
						    por 0 el programa acaba
						    con un 1 */
    	m = b[k]/c[k+1];
    	c[k+1] = m;
    	b[k+1] -= m*a[k];
    }

    return 0;
}

void fwd_subs_d3(int n, double *l, double *b) {
	/* supongamos l la diagonal inferior (la diagonal central esta
	 * compuesta de 1s, y b el vector de los coeficientes.
	 *
	 * supongamos que l empieza en l[1] y acaba en l[-1] */
	int k;

	for (k = 1; k < n; k++) {
		b[k] = b[k] - l[k]*b[k-1];
	}
}
		
int bwd_subs_d3(int n, double *a, double *b, double *y, double tol) {
	int k;

	y[n-1] = y[n-1]/b[n-1];
	for (k = n-2; k >= 0; k--) {
		if (fabs(b[k]) < tol) return 1;
		y[k] = (y[k] - a[k]*y[k-1])/b[k];
	}
	return 0;
}


