#include <stdio.h>
#include <stdlib.h>

double **createMat(int m, int n) {
    double **a = (double **)malloc(m * sizeof(double *));
    for (int i = 0; i < m; i++) {
        a[i] = (double *)malloc(n * sizeof(double));
    }
    return a;
}

void freeMat(double **mat, int m) {
    for (int i = 0; i < m; i++) {
        free(mat[i]);
    }
    free(mat);
}

void writeMatToFile(double **matrix, int m, int n, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        fprintf(stderr, "Error opening file %s\n", filename);
        return;
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            fprintf(fp, "%lf ", matrix[i][j]);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
}

int main() {
    int m = 3; // Number of points
    int n = 3; // Dimensions of each point (x, y, z)
    double **points = createMat(m, n);

    // Store the points in the matrix
    points[0][0] = 2;   points[0][1] = -1;  points[0][2] = 3;  // Point (2, -1, 3)
    points[1][0] = 3;   points[1][1] = -5;  points[1][2] = 1;  // Point (3, -5, 1)
    points[2][0] = -1;  points[2][1] = 11;  points[2][2] = 9;  // Point (-1, 11, 9)

    // Write the matrix to the file
    writeMatToFile(points, m, n, "points.txt");

    // Free the allocated memory
    freeMat(points, m);

    return 0;
}

