#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <float.h>

double legendre(int i, double x) {
    double pj, pj_1, temp;
    int j;
    
    if (i == 0) {
        return 1;
    }
    
    pj_1 = 1;
    pj = x;
    for (j = 2; j <= i; j ++) {
        temp = pj;
        pj = ( ( ((double)(2 * j - 1)) / j ) * x * pj
                - (((double)(j-1))/j) * pj_1);
        pj_1 = temp;
    }
    return pj;
}

double iter_secant(int n, double x1, double x0, double f1, double f0) {
    return (x1 - f1 * ( (x1 - x0)/(f1 - f0)));
}

int secant(int i, double * px0, double * px1, double prec, double nmax) {
    int count;
    double dif;
    double f1, f0, temp, x1, x0;
    
    dif = INFINITY;
    x0  = * px0;
    x1  = * px1;
    f0  = legendre(i, x0);
    f1  = legendre(i, x1);

    count = 0;
    while (fabs(f1) > prec && dif > prec) {
        temp = x1;
        x1 = iter_secant(i, x1, x0, f1, f0);
        x0 = temp;

        f0 = f1;
        f1 = legendre(i, x1);

        dif = fabs(x1 - x0);

        count++; /* hem fet una iteracio mes */
        if (count >= nmax) return 1; /* si count >= nmax no convergeix */
    }

    (* px0) = x0;
    (* px1) = x1;

    return 0;
}


int arrels_legendre(int imax, double prec, int nmax) {
    double x1, x0;
    double **zeros = (double**) malloc(imax * sizeof(double*));
    int i, j, grau;
    
    for(j = 0; j < imax; j++) {
        zeros[j] = (double*) malloc( (j +1) * sizeof(double));
    }

    zeros[0][0] = 0;
    
    for (i = 1; i < imax; i++) {
        if (i == 8) {
            for (j = 0; j < imax - 1; j++) {
                printf("->%d %lf\n", j, zeros[i-1][j]);
            }
        }
        grau = i+1;
        /* primera arrel */
        x0 = -1;
        x1 = zeros[i-1][0];
        secant(grau, &x0, &x1, prec, nmax);
        zeros[i][0] = (x0 + x1) / 2;
        
        for (j = 1; j <= i-1; j++) {
            x0 = zeros[i-1][j-1];
            x1 = zeros[i-1][j];
            secant(grau, &x0, &x1, prec, nmax);
            zeros[i][j] = (x0 + x1) / 2;
        }

        printf("\n");
        /* ultima arrel */
        x0 = zeros[i-1][i-1];
        x1 = 1;
        secant(grau, &x0, &x1, prec, nmax);
        zeros[i][i] = (x0 + x1) / 2;
    }
    
    printf("Arrels del polinomi de grau %d:\n", imax);
    for (j = 0; j < imax; j++) {
        printf("%d.\t%lf\n", j+1, zeros[imax-1][j]);
    }
    
    /* alliberem punters */
    for (j = 0; j < imax; j++) {
        free(zeros[j]);
    } 
    return 0;
}

int main() {
    int i;
    
    arrels_legendre(9, 1e-14, 15);
    arrels_legendre(8, 1e-14, 15);
    return 0;
}
