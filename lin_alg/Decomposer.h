#ifndef DECOMPOSER_H
#define DECOMPOSER_H

#include "Matrix.h"
#include "VectorOps.h"
#include <vector>
#include <cmath>
#include <utility>
#include <stdexcept>

namespace LinAlg {

class Decomposer {
public:
    // LU Decomposition: A = L * U (with partial pivoting)
    // Returns pair {L, U}
    static std::pair<Matrix, Matrix> LU(const Matrix& A);

    // Cholesky Decomposition: A = L * L^T
    // Returns L. Matrix must be symmetric positive-definite.
    static Matrix Cholesky(const Matrix& A);

    // QR Decomposition: A = Q * R
    // Returns pair {Q, R} using Modified Gram-Schmidt
    static std::pair<Matrix, Matrix> QR(const Matrix& A);

    // Eigen Decomposition: A * v = lambda * v
    // Returns pair {Eigenvalues (diagonal matrix), Eigenvectors (columns)}
    // Uses QR Algorithm
    static std::pair<Matrix, Matrix> Eigen(const Matrix& A, int maxIter = 1000, double tol = 1e-10);

    // Singular Value Decomposition: A = U * S * V^T
    // Returns tuple {U, S, V}
    // Uses Eigen decomposition of A^T * A
    // NOTE: This implementation squares the condition number and may lose precision
    // for ill-conditioned matrices. For production use, consider Golub-Kahan-Reinsch algorithm.
    static std::tuple<Matrix, Matrix, Matrix> SVD(const Matrix& A);
    
    // Power Iteration: Finds dominant eigenvalue and eigenvector
    // Returns pair {eigenvalue, eigenvector}
    static std::pair<double, std::vector<double>> PowerIteration(const Matrix& A, int maxIter = 1000, double tol = 1e-10);
};

} // namespace LinAlg

#endif // DECOMPOSER_H
