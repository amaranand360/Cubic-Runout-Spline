#include <stdio.h>
#include <stdlib.h>

void cubic_runout_spline(double *x_values, double *y_values, double *M_values, int n) {
    double h_values[n - 1];

    // Calculate h values
    for (int i = 0; i < n - 1; i++) {
        h_values[i] = x_values[i + 1] - x_values[i];
    }

    // Construct the tridiagonal matrix
    double matrix[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = 0.0;
        }
    }

    matrix[0][0] = 6 / (h_values[0] * h_values[0]);
    matrix[0][1] = 0;
    matrix[n - 1][n - 1] = 6 / (h_values[n - 2] * h_values[n - 2]);
    matrix[n - 1][n - 2] = 0;

    for (int i = 1; i < n - 1; i++) {
        matrix[i][i - 1] = 1;
        matrix[i][i] = 4;
        matrix[i][i + 1] = 1;
    }

    // Construct the right-hand side vector
    double rhs[n];
    rhs[0] = 6 / (h_values[0] * h_values[0]) * (y_values[1] - 2 * y_values[0] + y_values[2]);
    rhs[n - 1] = 6 / (h_values[n - 2] * h_values[n - 2]) * (y_values[n - 3] - 2 * y_values[n - 2] + y_values[n - 1]);

    for (int i = 1; i < n - 1; i++) {
        rhs[i] = 6 / (h_values[i] * h_values[i]) * (y_values[i - 1] - 2 * y_values[i] + y_values[i + 1]);
    }

    // Solve the linear system of equations
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                double ratio = matrix[j][i] / matrix[i][i];
                for (int k = 0; k < n; k++) {
                    matrix[j][k] -= ratio * matrix[i][k];
                }
                rhs[j] -= ratio * rhs[i];
            }
        }
    }

    // Back substitution
    for (int i = n - 1; i >= 0; i--) {
        double sum = 0;
        for (int j = i + 1; j < n; j++) {
            sum += matrix[i][j] * M_values[j];
        }
        M_values[i] = (rhs[i] - sum) / matrix[i][i];
    }
}

double cubic_spline_interpolation(double x, double *x_values, double *y_values, double *M_values, int n) {
    for (int i = 0; i < n - 1; i++) {
        if (x_values[i] <= x && x <= x_values[i + 1]) {
            double h = x_values[i + 1] - x_values[i];
            double t = (x - x_values[i]) / h;
            double a = M_values[i + 1] - M_values[i];
            double b = 2 * M_values[i] - M_values[i + 1];
            return (1 - t) * y_values[i] + t * y_values[i + 1] + t * (1 - t) * (a * (1 - t) + b * t);
        }
    }
    return 0.0; 
}
int main() {
    int n;
    printf("Enter the number of data points: ");
    scanf("%d", &n);

    double *x_values = malloc(n * sizeof(double));
    double *y_values = malloc(n * sizeof(double));
    double *M_values = malloc(n * sizeof(double));

    if (x_values == NULL || y_values == NULL || M_values == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("Enter the data points (X-axis Y-axis):\n");
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf", &x_values[i], &y_values[i]);
    }

    cubic_runout_spline(x_values, y_values, M_values, n);

    while (1) {
        double test_x;
        printf("Enter the value of x for interpolation (or enter a non-numeric value to exit): ");
        if (scanf("%lf", &test_x) != 1) {
            break; // Exit the loop if non-numeric input is provided
        }

        double result = cubic_spline_interpolation(test_x, x_values, y_values, M_values, n);
        printf("Interpolated value at x = %.2f: %.4f\n", test_x, result);
    }

    free(x_values);
    free(y_values);
    free(M_values);

    return 0;
}
