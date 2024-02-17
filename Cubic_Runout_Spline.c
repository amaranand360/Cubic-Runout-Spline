#include <stdio.h>
#include <stdlib.h>

void calculate_spline(double *x, double *y, double *M, int n)
{
    double h[n - 1];

    for (int i = 0; i < n - 1; i++)
    {
        h[i] = x[i + 1] - x[i];
    }

    double A[n][n];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            A[i][j] = 0.0;
        }
    }

    A[0][0] = 6 / (h[0] * h[0]);
    A[0][1] = 0;
    A[n - 1][n - 1] = 6 / (h[n - 2] * h[n - 2]);
    A[n - 1][n - 2] = 0;

    for (int i = 1; i < n - 1; i++)
    {
        A[i][i - 1] = 1;
        A[i][i] = 4;
        A[i][i + 1] = 1;
    }

    double b[n];
    b[0] = 6 / (h[0] * h[0]) * (y[1] - 2 * y[0] + y[2]);
    b[n - 1] = 6 / (h[n - 2] * h[n - 2]) * (y[n - 3] - 2 * y[n - 2] + y[n - 1]);

    for (int i = 1; i < n - 1; i++)
    {
        b[i] = 6 / (h[i] * h[i]) * (y[i - 1] - 2 * y[i] + y[i + 1]);
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i != j)
            {
                double ratio = A[j][i] / A[i][i];
                for (int k = 0; k < n; k++)
                {
                    A[j][k] -= ratio * A[i][k];
                }
                b[j] -= ratio * b[i];
            }
        }
    }

    for (int i = n - 1; i >= 0; i--)
    {
        double sum = 0;
        for (int j = i + 1; j < n; j++)
        {
            sum += A[i][j] * M[j];
        }
        M[i] = (b[i] - sum) / A[i][i];
    }
}

double interpolate(double x, double *x_values, double *y_values, double *M_values, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        if (x_values[i] <= x && x <= x_values[i + 1])
        {
            double h = x_values[i + 1] - x_values[i];
            double t = (x - x_values[i]) / h;
            double a = M_values[i + 1] - M_values[i];
            double b = 2 * M_values[i] - M_values[i + 1];
            return (1 - t) * y_values[i] + t * y_values[i + 1] + t * (1 - t) * (a * (1 - t) + b * t);
        }
    }
    return 0.0;
}

int main()
{
    int n;
    printf("Enter the number of data points: ");
    scanf("%d", &n);

    double *x_values = malloc(n * sizeof(double));
    double *y_values = malloc(n * sizeof(double));
    double *M_values = malloc(n * sizeof(double));

    if (x_values == NULL || y_values == NULL || M_values == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("Enter the data points (X-axis Y-axis):\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%lf %lf", &x_values[i], &y_values[i]);
    }

    calculate_spline(x_values, y_values, M_values, n);

    while (1)
    {
        double test_x;
        printf("Enter the value of x for interpolation (or enter a non-numeric value to exit): ");
        if (scanf("%lf", &test_x) != 1)
        {
            break; // Exit the loop if non-numeric input is provided
        }

        double result = interpolate(test_x, x_values, y_values, M_values, n);
        printf("Interpolated value at x = %.2f: %.4f\n", test_x, result);
    }

    free(x_values);
    free(y_values);
    free(M_values);

    return 0;
}
