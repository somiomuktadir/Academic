/**
 * @file knapsack_problem.c
 * @brief Solves the 0/1 Knapsack Problem using Dynamic Programming.
 *
 * This program demonstrates:
 * 1. Dynamic Programming approach
 * 2. 2D Array for memoization
 * 3. Optimization problem solving
 */

#include <stdio.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

/**
 * @brief Returns the maximum value that can be put in a knapsack of capacity W.
 */
int knapSack(int W, int wt[], int val[], int n) {
    int i, w;
    int K[n + 1][W + 1];

    // Build table K[][] in bottom up manner
    for (i = 0; i <= n; i++) {
        for (w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                K[i][w] = 0;
            else if (wt[i - 1] <= w)
                K[i][w] = max(val[i - 1] + K[i - 1][w - wt[i - 1]], K[i - 1][w]);
            else
                K[i][w] = K[i - 1][w];
        }
    }

    return K[n][W];
}

int main() {
    int val[] = {60, 100, 120};
    int wt[] = {10, 20, 30};
    int W = 50;
    int n = sizeof(val) / sizeof(val[0]);
    
    printf("Value array: ");
    for(int i=0; i<n; i++) printf("%d ", val[i]);
    printf("\nWeight array: ");
    for(int i=0; i<n; i++) printf("%d ", wt[i]);
    printf("\nKnapsack Capacity: %d\n", W);

    printf("\nMaximum value that can be obtained is %d\n", knapSack(W, wt, val, n));
    return 0;
}
