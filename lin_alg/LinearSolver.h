#ifndef LINEAR_SOLVER_H
#define LINEAR_SOLVER_H

#include "Matrix.h"
#include <vector>
#include <cmath>
#include <stdexcept>

class LinearSolver {
public:
    // Solves Ax = b using Gaussian Elimination
    static std::vector<double> solve(const Matrix& A, const std::vector<double>& b);
    
    // Iterative refinement for better accuracy
    static std::vector<double> solveRefined(const Matrix& A, const std::vector<double>& b, int maxIter = 5);

    // Least Squares: Solve A * x = b (approx) for overdetermined systems
    static std::vector<double> leastSquares(const Matrix& A, const std::vector<double>& b);
    
    // Calculates determinant using Gaussian Elimination to upper triangular form
    static double determinant(const Matrix& A);
    
    // Calculates inverse using Gauss-Jordan Elimination
    static Matrix inverse(const Matrix& A);

    // Matrix power
    static Matrix power(const Matrix& A, int n);

private:
    // Helper to augment matrix A with vector b
    static Matrix augment(const Matrix& A, const std::vector<double>& b);
    
    // Helper to augment matrix A with Identity matrix
    static Matrix augmentIdentity(const Matrix& A);
};

#endif // LINEAR_SOLVER_H
