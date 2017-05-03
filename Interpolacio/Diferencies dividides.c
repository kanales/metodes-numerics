#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define HF_PI 1.5707963267948966 /* HF_PI := PI/2 */

void difdiv(int n, double *x, double *f) {
    int i, k;

    for (k = 1; k < n; k ++) {
        for (i = n; i > k - 1; i --) {
            f[i] = (f[i] - f[i-1]) / (x[i] - x[i - k]); 
       }
    }
}

/* Avalua polinomi:
 * Exemple:
 * - p(z) = c0 + c1(z - x0) + c2(z - x0)(z - x1)
 * - n = 2
 * - coef = [c0, c1, c2]
 * - x = [x0, x1]
 * */
double horner(double z, int n, double * x, double * c) {
    double p;
    int i;

    p = c[n];
    for (i = n - 1; i >= 0; i --) {
        p = p * (z - x[i]) + c[i];
    }

    return p;
}

/* Calcula la i-essima abscissa de chevishev:
 *
 * xi = a + (b - a)/2 * (1 + cos( pi/2 * (2i + 1)/(n+1) )
 * on:
 *      a = lower_bound
 *      b = upper_bound
 */
double cheb(double i, int n, double lower_bound, double upper_bound) {
    return (lower_bound 
            + ((upper_bound - lower_bound) / 2)
            * (1 + cos(HF_PI * (2 * i + 1)/(2*(n+1)))));
}

double runge(double x) {
    return (1/(1 + 25 * x*x));
}

