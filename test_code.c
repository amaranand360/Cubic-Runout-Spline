#include <stdio.h>
#include <assert.h>

extern void calculate_spline(double *x_values, double *y_values, double *M_values, int n);
extern double interpolate(double x, double *x_values, double *y_values, double *M_values, int n);

void test() {
    int n1 = 3;
    double x_values1[] = {2.04, 3.04, 4.04};
    double y_values1[] = {0.0, 0.5, 1.0};
    double M_values1[3];
    calculate_spline(x_values1, y_values1, M_values1, n1);

    double result1 = interpolate(2.5, x_values1, y_values1, M_values1, n1);
    assert(result1 == 0.25);

    int n2 = 10;
    double x_values2[] = {2.04, 2.05, 2.06, 2.07, 2.08, 2.09, 2.1, 2.11, 2.12, 2.13, 2.14};
    double y_values2[] = {0, 0.005, 0.01, 0.015, 0.02, 0.025, 0.03, 0.035, 0.04, 0.045, 0.05};
    double M_values2[10];
    calculate_spline(x_values2, y_values2, M_values2, n2);

    double result2 = interpolate(2.085, x_values2, y_values2, M_values2, n2);
    assert(result2 == 0.0173);

    printf("All test cases passed successfully!\n");

}
