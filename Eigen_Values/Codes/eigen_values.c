#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

void qr_decomposition(int n, double complex A[n][n], double complex Q[n][n], double complex R[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            Q[i][j] = 0;
            R[i][j] = 0;
        }
    }

    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n; i++) {
            Q[i][j] = A[i][j];
        }

        for (int k = 0; k < j; k++) {
            double complex dot = 0;
            for (int i = 0; i < n; i++) {
                dot += conj(Q[i][k]) * A[i][j];
            }
            R[k][j] = dot;
            for (int i = 0; i < n; i++) {
                Q[i][j] -= dot * Q[i][k];
            }
        }

        double complex norm = 0;
        for (int i = 0; i < n; i++) {
            norm += conj(Q[i][j]) * Q[i][j];
        }
        norm = csqrt(norm);
        
        if (cabs(norm) > 1e-10) {
            R[j][j] = norm;
            for (int i = 0; i < n; i++) {
                Q[i][j] /= norm;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double complex dot = 0;
            for (int k = 0; k < n; k++) {
                dot += conj(Q[k][i]) * A[k][j];
            }
            R[i][j] = dot;
        }
    }
}

void qr_algorithm(int n, double complex A[n][n], double complex eigenvalues[n]) {
    double complex (*Q)[n] = malloc(n * sizeof(*Q));
    double complex (*R)[n] = malloc(n * sizeof(*R));
    double tol = 1e-10;
    int max_iter = 10000;
    int iter = 0;
    double off_diag_sum;

    do {
        double complex shift = A[n-1][n-1];
        for (int i = 0; i < n; i++) {
            A[i][i] -= shift;
        }

        qr_decomposition(n, A, Q, R);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                double complex sum = 0;
                for (int k = 0; k < n; k++) {
                    sum += R[i][k] * Q[k][j];
                }
                A[i][j] = sum;
                if (i == j) {
                    A[i][i] += shift;
                }
            }
        }

        off_diag_sum = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    off_diag_sum += cabs(A[i][j]);
                }
            }
        }

        iter++;
    } while (off_diag_sum > tol && iter < max_iter);

    for (int i = 0; i < n; i++) {
        eigenvalues[i] = A[i][i];
    }

    free(Q);
    free(R);
}

int main() {
    int n;
    printf("Enter matrix order: ");
    scanf("%d", &n);

    double complex (*A)[n] = malloc(n * sizeof(*A));
    double complex *eigenvalues = malloc(n * sizeof(double complex));

    printf("Enter matrix elements (real and imaginary parts for each element):\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            double real, imag;
            scanf("%lf %lf", &real, &imag);
            A[i][j] = real + imag * I;
        }
    }

    qr_algorithm(n, A, eigenvalues);

    printf("\nEigenvalues:\n");
    for (int i = 0; i < n; i++) {
        if (cimag(eigenvalues[i]) >= 0) {
            printf("λ%d = %.6f + %.6fi\n", i + 1, creal(eigenvalues[i]), cimag(eigenvalues[i]));
        } else {
            printf("λ%d = %.6f - %.6fi\n", i + 1, creal(eigenvalues[i]), -cimag(eigenvalues[i]));
        }
    }

    free(A);
    free(eigenvalues);
    return 0;
}
