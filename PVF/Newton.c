#include<stdio.h>
#include<stdlib.h>
#include<math.h>

double normainf(int n, double * v);
int palu_d3(int n, double *a, double *b, double *c, double tol);
void fwd_subs_d3(int n, double *l, double *b);
int bwd_subs_d3(int n, double *a, double *b, double *y, double tol);


double f(double x, double y, double z) {
    return 0;
}

double d2f(double x, double y, double z) {
    return 0;
}

double d3f(double x, double y, double z) {
    return 0;
}

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

int newton(double a, double b, double alfa, double beta, int n, double prec) {
    int i, j, k;
    double h, l0, l1, ratio, temp, dtemp, norma;
    double *x, *y, *e, *inf, *mid, *sup;

    const int kmax = 10;

    h = (b - a) / (n+1); /* calcul del pas */

    /* init dels vectors */
    x = (double *) malloc((n+2) * sizeof(double));
    y = (double *) malloc((n+2) * sizeof(double));    
    e = (double *) malloc(n * sizeof(double));
    inf = (double *) malloc(n * sizeof(double));
    mid = (double *) malloc(n * sizeof(double));
    sup = (double *) malloc(n * sizeof(double));

    
    /* carreguem els nodes */
    x[0] = a;
    for (i = 1; i < n+1; i++) {
        x[i] = x[i-1] + h;
    }
    x[n+1] = b;

    /* carreguem y aprox */
    l0 = b - a;
    l1 = beta - alfa;
    ratio = l1 / l0;

    y[0] = alfa;
    for (i = 1; i < n+1; i++) {
        y[i] = alfa + ratio * (x[i] - a);
    }
    y[n+1] = beta;

    /* main loop */
    k = 0;
    do {
        for (i = 0; i < n; i ++) {
            j = i+1; /* corregim diferencia */
            temp = (y[j+1] - y[j-1])/ (2*h);

            /* calcul dels elements de les diagonals */
            inf[i] = -1 - (h/2) * d3f(x[j], y[j], temp);
            mid[i] = 2 + h*h * d2f(x[j], y[j], temp);
            sup[i] = -1 + (h/2) * d3f(x[j], y[j], temp);

            /* calcul del error */
            e[i] = y[j-1] - 2*y[j] + y[j+1] - h * h * f(x[i+1], y[i+1], temp);
        }

        if (d3(n, inf, mid, sup, e, prec)) return 1; /* acabem si falla */
        norma = normainf(n, e);
        printf("Iteracio nº %d\nnorma = %25.16lf\n", k+1, norma);

        /* calculem y(k) */
        for (i = 0; i < n; i++) {
            y[i] += e[i];
        }

        k++;

    } while (k < kmax && norma > prec);

    printf("Resultat:\nx\ty\n");
    for(i = 0; i < n+2; i++) {
            printf("%25.16lf %25.16lf\n", x[i], y[i]);
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

double normainf(int n, double * v) {
    int i;
    double acc, temp;
    
    acc = 0;
    for(i = 0; i < n; i++) {
        temp = fabs(v[i]);
        if (temp > acc) {
            acc = temp;
        }
    }
    return acc;
}

