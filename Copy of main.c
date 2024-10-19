#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_SIZE 100
#define THRESHOLD 1e-6 // Threshold for residual check
#define MAX_ITERATIONS 10000 // Maximum number of iterations to prevent infinite loop

void inputMatrix(float A[MAX_SIZE][MAX_SIZE], int n) {
    printf("Enter the coefficients of the matrix A:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%f", &A[i][j]);
        }
    }
}

void inputVector(float b[MAX_SIZE], int n) {
    printf("Enter the constants of the vector b:\n");
    for (int i = 0; i < n; i++) {
        scanf("%f", &b[i]);
    }
}

void inputInitialVector(float x[MAX_SIZE], int n) {
    printf("Enter the initial values of the vector x:\n");
    for (int i = 0; i < n; i++) {
        scanf("%f", &x[i]);
    }
}

void printVector(float x[MAX_SIZE], int n) {
    for (int i = 0; i < n; i++) {
        printf("%f ", x[i]);
    }
    printf("\n");
}

int main() {
    int n;
    printf("Enter the size of the matrix and vectors: ");
    scanf("%d", &n);

    float A[MAX_SIZE][MAX_SIZE], b[MAX_SIZE], x[MAX_SIZE], x_new[MAX_SIZE], r[MAX_SIZE], temp[MAX_SIZE];

    inputMatrix(A, n);
    inputVector(b, n);
    inputInitialVector(x, n);

    int iteration = 0;
    while (iteration < MAX_ITERATIONS) {
        iteration++;

        // Calculate the residual vector r = b - Ax
        for (int i = 0; i < n; i++) {
            temp[i] = 0;
            for (int j = 0; j < n; j++) {
                temp[i] += A[i][j] * x[j];
            }
            r[i] = b[i] - temp[i];
        }

        // Calculate the projection and reflection
        for (int i = 0; i < n; i++) {
            x_new[i] = 0;
            for (int j = 0; j < n; j++) {
                x_new[i] += A[i][j] * r[i];
            }
            x_new[i] /= (pow(A[i][i], 2));
        }

        // Update x with the new values
        for (int i = 0; i < n; i++) {
            x[i] += x_new[i];
        }

        // Calculate the residual to check for convergence
        float residual = 0.0;
        for (int i = 0; i < n; i++) {
            float sum = 0.0;
            for (int j = 0; j < n; j++) {
                sum += A[i][j] * x[j];
            }
            residual += fabs(b[i] - sum);
        }

        if (residual < THRESHOLD) {
            break; // Converged, exit the loop
        }
    }

    if (iteration == MAX_ITERATIONS) {
        printf("Maximum iterations reached. Solution may not have converged.\n");
    } else {
        printf("The final approximation x is: ");
        printVector(x, n);
    }

    return 0;
}
