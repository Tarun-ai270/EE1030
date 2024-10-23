#include <stdio.h>

int main() {
    // Define the points
    int points[3][3] = {
        {2, -1, 3},
        {3, -5, 1},
        {-1, 11, 9}
    };

    // Open the file for writing
    FILE *file = fopen("points.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // Write the points to the file
    for (int i = 0; i < 3; i++) {
        fprintf(file, "(%d, %d, %d)\n", points[i][0], points[i][1], points[i][2]);
    }

    // Close the file
    fclose(file);

    printf("Points have been written to points.txt\n");
    return 0;
}

