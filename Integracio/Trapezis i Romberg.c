#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef double (*doublef) (double);

double sfis(double a, double h, int n, doublef f) {
    /* retorna la suma de f(x_1)...f(x_{n-1}) imparells */
    double xi, acc;
    int i;
    
    xi = a + h;
    acc= f(xi);
    for (i = 3; i < n; i += 2) {
        xi += 2 * h;
        acc += f(xi);
    }
    
    return acc;
}

double trapezis(double a, double b, double prec, doublef f) {
    /* Input:
     * - a: lower bound de l'interval
     * - b: upper bound
     * - 
     */
    double T0, T1, h, dif;
    int counter, n;
    const int MAX = 12;
    
    h = (b - a);
    /* calcul de t inicial */
    T1 = 0.5 * h * (f(a) + f(b));
    n = 1;

    do {
        T0 = T1;
        n *= 2;
        h /= 2;
        T1 = (T0 / 2) + h * sfis(a, h, n, f);
        dif = fabs(T1 - T0);
    } while (++counter < MAX && dif > prec);

    return T1;
}

double romberg(double a, double b, double prec, doublef f) {
    /* aplica extrapolacio de richardson als trapezis 
     * requereix: sfis
     * */
    double ** T;
    double tn, dif, h, potencia, temp;
    int i, i_, j, n;
    const int MAX = 15;

    /* * init * */
    T = (double **) malloc(MAX * sizeof(double *));
    h = b - a; 
    i = 0;
    n = 1;

    T[0] = (double *) malloc(MAX * sizeof(double));
    /* * * * * * */
    T[0][0] = h * 0.5 * (f(a) + f(b)); /* calcul inicial */

    do {
        i++;
        /* iniT el vecTor */
        T[i] = (double *) malloc((MAX - i) * sizeof(double));
        n *= 2; h /= 2;
        T[i][0] = 0.5 * T[i-1][0] + h * sfis(a, h, n, f);
        for (j = 1; j <= i; j++) {
            potencia = pow(4, j);
            T[i][j] = ((potencia * T[i-1][j-1] - T[i][j-1])
                        / (potencia - 1));
        }         
        dif = fabs(T[i][i] - T[i][i-1]);
    } while (i < MAX && dif > prec);
    printf("i: %d\n", i);
    temp = T[i][i]; /* emmagatzem temporalment la solucio */

    while (i >= 0) {
        free(T[i--]);
    }

    return temp;
}

double f(double x) { return ( 1. / (1. + x)); }

int main(int argc, char ** argv) {
    printf("Exercici 1:\nvalor real:\t%25.10lf\nvalor aprox.:\t%25.10lf\n",
            log(2),
            trapezis(0, 1, 1e-10, f));

    printf("Exercici 2:\nvalor real:\t%25.10lf\nvalor aprox.:\t%25.10lf\n",
            log(2),
            romberg(0, 1, 1e-10, f));
}

