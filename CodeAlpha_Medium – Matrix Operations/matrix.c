#include <stdio.h>
#include <stdlib.h>

#define MAX 10  // Maximum matrix size

// --- Function Prototypes ---
void inputMatrix(int matrix[MAX][MAX], int row, int col);
void printMatrix(int matrix[MAX][MAX], int row, int col);
void addMatrices(int m1[MAX][MAX], int m2[MAX][MAX], int result[MAX][MAX], int row, int col);
void multiplyMatrices(int m1[MAX][MAX], int m2[MAX][MAX], int result[MAX][MAX], int r1, int c1, int r2, int c2);
void transposeMatrix(int matrix[MAX][MAX], int result[MAX][MAX], int row, int col);

int main() {
    int mat1[MAX][MAX], mat2[MAX][MAX], result[MAX][MAX];
    int r1, c1, r2, c2, choice;

    while(1) {
        printf("\n--- Matrix Operations Menu ---\n");
        printf("1. Matrix Addition\n");
        printf("2. Matrix Multiplication\n");
        printf("3. Transpose of a Matrix\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 4) break;

        switch(choice) {
            case 1: // Addition
                printf("Enter rows and columns for matrices: ");
                scanf("%d %d", &r1, &c1);
                
                printf("Enter elements for First Matrix:\n");
                inputMatrix(mat1, r1, c1);
                printf("Enter elements for Second Matrix:\n");
                inputMatrix(mat2, r1, c1); // Rows/Cols must be same for addition
                
                addMatrices(mat1, mat2, result, r1, c1);
                printf("Result of Addition:\n");
                printMatrix(result, r1, c1);
                break;

            case 2: // Multiplication
                printf("Enter rows and cols for First Matrix: ");
                scanf("%d %d", &r1, &c1);
                printf("Enter rows and cols for Second Matrix: ");
                scanf("%d %d", &r2, &c2);

                if (c1 != r2) {
                    printf("\nError: Multiplication not possible. Cols of A must equal Rows of B.\n");
                } else {
                    printf("Enter elements for First Matrix:\n");
                    inputMatrix(mat1, r1, c1);
                    printf("Enter elements for Second Matrix:\n");
                    inputMatrix(mat2, r2, c2);

                    multiplyMatrices(mat1, mat2, result, r1, c1, r2, c2);
                    printf("Result of Multiplication:\n");
                    printMatrix(result, r1, c2);
                }
                break;

            case 3: // Transpose
                printf("Enter rows and cols for Matrix: ");
                scanf("%d %d", &r1, &c1);
                
                printf("Enter elements for Matrix:\n");
                inputMatrix(mat1, r1, c1);
                
                transposeMatrix(mat1, result, r1, c1);
                printf("Transpose of the Matrix:\n");
                printMatrix(result, c1, r1); // Note: Rows and Cols are swapped
                break;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

// --- Function Definitions ---

// Function to take matrix input
void inputMatrix(int matrix[MAX][MAX], int row, int col) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf("Element [%d][%d]: ", i, j);
            scanf("%d", &matrix[i][j]);
        }
    }
}

// Function to print a matrix
void printMatrix(int matrix[MAX][MAX], int row, int col) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}

// Function for Matrix Addition
void addMatrices(int m1[MAX][MAX], int m2[MAX][MAX], int result[MAX][MAX], int row, int col) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            result[i][j] = m1[i][j] + m2[i][j];
        }
    }
}

// Function for Matrix Multiplication
void multiplyMatrices(int m1[MAX][MAX], int m2[MAX][MAX], int result[MAX][MAX], int r1, int c1, int r2, int c2) {
    // Initialize result matrix to 0
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            result[i][j] = 0;
        }
    }

    // Multiply
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            for (int k = 0; k < c1; k++) {
                result[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }
}

// Function for Transpose
void transposeMatrix(int matrix[MAX][MAX], int result[MAX][MAX], int row, int col) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            result[j][i] = matrix[i][j]; // Swap indices
        }
    }
}