#include<math.h>
#include<stdlib.h>
#include<stdio.h>

typedef double (* doublef)(double); /* definim tipus funcio doublef */

double richardson1(double a, double h, double q, double pre, const doublef f) {
    double dif, potencia, temp;
    double **m;
    int i, k;
    const int MAX_K = 10;

    /* init matriu */
    m = (double **) malloc(MAX_K * sizeof(double *));
    m[0] = (double *) malloc(MAX_K * sizeof(double));
    /* * * * * * * */

    m[0][0] = (f(a + h) - f(a - h))/ (2 * h);

    h /= q;
    i = 0;
    do {
        i++;

        m[i] = (double *) malloc((MAX_K - i) * sizeof(double));
        potencia *= q;

        m[i][0] = (f(a + h) - f(a - h))/ (2 * h);
        for (k = 1; k <= i; k++) {
            potencia = pow(q, 2*i);
            m[i][k] = ((potencia * m[i-1][k-1] - m[i][k-1]) / (potencia - 1)); 
        }
        dif = fabs(m[i][i] - m[i-1][i-1]);
        h /= q;
    } while (dif > pre && i < MAX_K);

    temp = m[0][0]; /* guardem temporalment el resultat */
    /* dealloc matriu */
    while (i >= 0) {
        free(m[i]);
        i--;
    } free(m);
    
    return temp;
}

double richardson2(double a, double h, double q, double pre, const doublef f) {
    double dif, potencia, temp;
    double **m;
    int i, k;
    const int MAX_K = 10;

    /* init matriu */
    m = (double **) malloc(MAX_K * sizeof(double *));
    m[0] = (double *) malloc(MAX_K * sizeof(double));
    /* * * * * * * */

    m[0][0] = ( (f(a + h) - 2 * f(a) + f(a - h )) / (h * h) );

    h /= q;
    i = 0;
    do {
        i++;

        m[i] = (double *) malloc((MAX_K - i) * sizeof(double));
        potencia *= q;

        m[i][0] = ( (f(a + h) - 2 * f(a) + f(a - h )) / (h * h) );
        for (k = 1; k <= i; k++) {
            potencia = pow(q, 2*i);
            m[i][k] = ((potencia * m[i-1][k-1] - m[i][k-1]) / (potencia - 1)); 
        }
        dif = fabs(m[i][i] - m[i-1][i-1]);
        h /= q;
    } while (dif > pre && i < MAX_K);

    temp = m[0][0]; /* guardem temporalment el resultat */
    /* dealloc matriu */
    while (i >= 0) {
        free(m[i]);
        i--;
    } free(m);
    
    return temp;
}

int main(int argc, char ** argv) {
    double a, h, pre;
    int q, i;

    /* llegir arguments */
    a = 1.; /* punt on s'avalua f'(a) */
    h = 0.001;/* longitud inicial */
    pre = 1e-10; /* precisio del resultat */

    q = 2;

    
    printf("resultat aprox:\t%25.7lf\nresultat real:%25.7lf\n", 
            richardson1(a, h, q, pre, cos), -sin(a));
    
    printf("resultat aprox:\t%25.7lf\nresultat real:%25.7lf\n", 
            richardson2(a, h, q, pre, cos), -cos(a));

    return 0;
}
