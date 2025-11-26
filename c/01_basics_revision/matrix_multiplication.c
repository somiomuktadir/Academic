/**
 * @file matrix_multiplication.c
 * @brief Multiplies two matrices after validating their dimensions.
 *
 * This program demonstrates:
 * 1. 2D Array (Matrix) manipulation
 * 2. Nested loops
 * 3. Dimension validation for matrix multiplication
 * 4. Dynamic memory allocation for matrices
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Allocates memory for a matrix of size rows x cols.
 *
 * @param rows Number of rows
 * @param cols Number of columns
 * @return int** Pointer to the allocated matrix
 */
int** allocate_matrix(int rows, int cols) {
    int **matrix = (int **)malloc(rows * sizeof(int *));
    if (matrix == NULL) return NULL;

    for (int i = 0; i < rows; i++) {
        matrix[i] = (int *)malloc(cols * sizeof(int));
        if (matrix[i] == NULL) {
            // Free previously allocated rows on failure
            for (int j = 0; j < i; j++) free(matrix[j]);
            free(matrix);
            return NULL;
        }
    }
    return matrix;
}

/**
 * @brief Frees the memory allocated for a matrix.
 *
 * @param matrix Pointer to the matrix
 * @param rows Number of rows
 */
void free_matrix(int **matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

/**
 * @brief Reads matrix elements from standard input.
 *
 * @param matrix Pointer to the matrix
 * @param rows Number of rows
 * @param cols Number of columns
 * @param name Name of the matrix (for prompt)
 */
void read_matrix(int **matrix, int rows, int cols, const char *name) {
    printf("Enter elements for Matrix %s (%dx%d):\n", name, rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("Element [%d][%d]: ", i, j);
            scanf("%d", &matrix[i][j]);
        }
    }
}

/**
 * @brief Prints matrix elements to standard output.
 *
 * @param matrix Pointer to the matrix
 * @param rows Number of rows
 * @param cols Number of columns
 */
void print_matrix(int **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int r1, c1, r2, c2;

    // Input dimensions for first matrix
    printf("Enter rows and columns for first matrix: ");
    scanf("%d %d", &r1, &c1);

    // Input dimensions for second matrix
    printf("Enter rows and columns for second matrix: ");
    scanf("%d %d", &r2, &c2);

    // Validate dimensions: Columns of first must equal rows of second
    if (c1 != r2) {
        fprintf(stderr, "Error: Matrix multiplication not possible. "
                        "Columns of first matrix (%d) must equal rows of second matrix (%d).\n", c1, r2);
        return 1;
    }

    // Allocate memory
    int **m1 = allocate_matrix(r1, c1);
    int **m2 = allocate_matrix(r2, c2);
    int **result = allocate_matrix(r1, c2);

    if (!m1 || !m2 || !result) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    // Read matrices
    read_matrix(m1, r1, c1, "A");
    read_matrix(m2, r2, c2, "B");

    // Perform multiplication
    // Result[i][j] = Sum(m1[i][k] * m2[k][j]) for k=0 to c1-1
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            result[i][j] = 0; // Initialize
            for (int k = 0; k < c1; k++) {
                result[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }

    // Output result
    printf("\nResultant Matrix:\n");
    print_matrix(result, r1, c2);

    // Free memory
    free_matrix(m1, r1);
    free_matrix(m2, r2);
    free_matrix(result, r1);

    return 0;
}
