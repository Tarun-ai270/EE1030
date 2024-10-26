#include <stdio.h>
#include "home/tarun-reddy-pakala/Assignment/mathfun.h"


int main() {
    // Define points
    double points[3][3] = {
        {2.0, -1.0, 3.0},
        {3.0, -5.0, 1.0},
        {-1.0, 11.0, 9.0}
    };

    // Open file for writing
    FILE *file = fopen("points.txt", "w");
    if (file == NULL) {
        return 1;  // Exit if file cannot be opened
    }

    // Write points to the file
    for (int i = 0; i < 3; i++) {
        fprintf(file, "%lf %lf %lf\n", points[i][0], points[i][1], points[i][2]);
    }

    fclose(file);
    return 0;
}

