#include "LinearSolver.h"
#include "Logger.h"
#include "VectorOps.h"
#include "Decomposer.h"
#include "Analysis.h"
#include <sstream>
#include <iomanip>

namespace LinAlg {

std::vector<double> LinearSolver::solve(const Matrix& A, const std::vector<double>& b) {
    int n = A.getRows();
    if (A.getCols() != n) throw std::invalid_argument("Matrix must be square");
    if (b.size() != static_cast<size_t>(n)) throw std::invalid_argument("Vector dimension mismatch");

    // Create augmented matrix [A|b]
    Matrix M = augment(A, b);
    
    // Gaussian Elimination with partial pivoting
    Logger::getInstance().log("Starting Gaussian Elimination");
    Logger::getInstance().logStep("Initial Augmented Matrix:");

    for (int i = 0; i < n; ++i) {
        // Pivot
        int pivot = i;
        for (int j = i + 1; j < n; ++j) {
            if (std::abs(M(j, i)) > std::abs(M(pivot, i))) {
                pivot = j;
            }
        }
        
        // Swap rows
        if (pivot != i) {
            std::ostringstream oss;
            oss << "Swapping row " << i << " with row " << pivot;
            Logger::getInstance().log(oss.str());
            for (int k = 0; k <= n; ++k) {
                std::swap(M(i, k), M(pivot, k));
            }
        }
        
        if (std::abs(M(i, i)) < 1e-10) {
            throw std::runtime_error("Matrix is singular or nearly singular");
        }
        
        // Eliminate
        for (int j = i + 1; j < n; ++j) {
            double factor = M(j, i) / M(i, i);
            if (std::abs(factor) > 1e-10) {
                std::ostringstream oss;
                oss << "R" << j << " = R" << j << " - (" << factor << ") * R" << i;
                Logger::getInstance().log(oss.str());
                for (int k = i; k <= n; ++k) {
                    M(j, k) -= factor * M(i, k);
                }
            }
        }
    }
    
    // Back substitution
    Logger::getInstance().log("Starting Back Substitution");
    std::vector<double> x(n);
    for (int i = n - 1; i >= 0; --i) {
        double sum = 0;
        for (int j = i + 1; j < n; ++j) {
            sum += M(i, j) * x[j];
        }
        x[i] = (M(i, n) - sum) / M(i, i);
    }
    
    return x;
}

double LinearSolver::determinant(const Matrix& A) {
    int n = A.getRows();
    if (A.getCols() != n) throw std::invalid_argument("Matrix must be square");
    
    Matrix M = A; // Copy
    double det = 1.0;
    Logger::getInstance().log("Calculating Determinant using Gaussian Elimination");
    
    for (int i = 0; i < n; ++i) {
        int pivot = i;
        for (int j = i + 1; j < n; ++j) {
            if (std::abs(M(j, i)) > std::abs(M(pivot, i))) {
                pivot = j;
            }
        }
        
        if (pivot != i) {
            std::ostringstream oss;
            oss << "Swapping row " << i << " with row " << pivot << " (det sign flips)";
            Logger::getInstance().log(oss.str());
            for (int k = 0; k < n; ++k) {
                std::swap(M(i, k), M(pivot, k));
            }
            det *= -1;
        }
        
        if (std::abs(M(i, i)) < 1e-10) return 0.0;
        
        det *= M(i, i);
        
        for (int j = i + 1; j < n; ++j) {
            double factor = M(j, i) / M(i, i);
            for (int k = i; k < n; ++k) {
                M(j, k) -= factor * M(i, k);
            }
        }
    }
    
    return det;
}

Matrix LinearSolver::inverse(const Matrix& A) {
    int n = A.getRows();
    if (A.getCols() != n) throw std::invalid_argument("Matrix must be square");
    
    Matrix M = augmentIdentity(A);
    int cols = 2 * n;
    
    // Gauss-Jordan
    Logger::getInstance().log("Starting Gauss-Jordan for Inverse");
    for (int i = 0; i < n; ++i) {
        int pivot = i;
        for (int j = i + 1; j < n; ++j) {
            if (std::abs(M(j, i)) > std::abs(M(pivot, i))) {
                pivot = j;
            }
        }
        
        if (pivot != i) {
            Logger::getInstance().log("Swapping row " + std::to_string(i) + " with row " + std::to_string(pivot));
            for (int k = 0; k < cols; ++k) {
                std::swap(M(i, k), M(pivot, k));
            }
        }
        
        double pivotVal = M(i, i);
        if (std::abs(pivotVal) < 1e-10) throw std::runtime_error("Matrix is singular");
        
        for (int k = 0; k < cols; ++k) {
            M(i, k) /= pivotVal;
        }
        Logger::getInstance().log("Dividing row " + std::to_string(i) + " by " + std::to_string(pivotVal));
        
        for (int j = 0; j < n; ++j) {
            if (i != j) {
                double factor = M(j, i);
                for (int k = 0; k < cols; ++k) {
                    M(j, k) -= factor * M(i, k);
                }
            }
        }
    }
    
    // Extract inverse
    Matrix Inv(n, n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            Inv(i, j) = M(i, j + n);
        }
    }
    
    return Inv;
}

Matrix LinearSolver::power(const Matrix& A, int n) {
    if (A.getRows() != A.getCols()) throw std::invalid_argument("Matrix must be square");
    if (n < 0) return power(inverse(A), -n);
    if (n == 0) return Matrix::identity(A.getRows());
    
    Matrix res = Matrix::identity(A.getRows());
    Matrix base = A;
    while (n > 0) {
        if (n % 2 == 1) res = res * base;
        base = base * base;
        n /= 2;
    }
    return res;
}

Matrix LinearSolver::augment(const Matrix& A, const std::vector<double>& b) {
    int r = A.getRows();
    int c = A.getCols();
    Matrix M(r, c + 1);
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            M(i, j) = A(i, j);
        }
        M(i, c) = b[i];
    }
    return M;
}

Matrix LinearSolver::augmentIdentity(const Matrix& A) {
    int n = A.getRows();
    Matrix M(n, 2 * n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            M(i, j) = A(i, j);
            M(i, j + n) = (i == j) ? 1.0 : 0.0;
        }
    }
    return M;
}

std::vector<double> LinearSolver::solveRefined(const Matrix& A, const std::vector<double>& b, int maxIter) {
    // Initial solution using standard Gaussian elimination
    std::vector<double> x = solve(A, b);
    
    Logger::getInstance().log("Starting iterative refinement");
    
    for (int iter = 0; iter < maxIter; ++iter) {
        // Compute residual: r = b - Ax
        std::vector<double> r(b.size());
        for (size_t i = 0; i < b.size(); ++i) {
            double sum = 0;
            for (int j = 0; j < A.getCols(); ++j) {
                sum += A(i, j) * x[j];
            }
            r[i] = b[i] - sum;
        }
        
        // Check if residual is small enough
        double residual_norm = VectorOps::norm(r);
        if (residual_norm < 1e-14) {
            Logger::getInstance().log("Converged at iteration " + std::to_string(iter) + ", residual: " + std::to_string(residual_norm));
            break;
        }
        
        // Solve A * delta_x = r
        std::vector<double> delta_x = solve(A, r);
        
        // Update solution: x = x + delta_x
        for (size_t i = 0; i < x.size(); ++i) {
            x[i] += delta_x[i];
        }
        
        Logger::getInstance().log("Iteration " + std::to_string(iter + 1) + ", residual norm: " + std::to_string(residual_norm));
    }
    
    return x;
}

std::vector<double> LinearSolver::leastSquares(const Matrix& A, const std::vector<double>& b) {
    // Solve Ax = b using QR decomposition
    // A = Q * R
    // Rx = Q^T * b
    
    int m = A.getRows();
    int n = A.getCols();
    
    if (m < n) throw std::invalid_argument("Underdetermined system (rows < cols) not supported by this least squares implementation");
    if (b.size() != static_cast<size_t>(m)) throw std::invalid_argument("Vector dimension mismatch");
    
    auto [Q, R] = Decomposer::QR(A);
    
    // Compute y = Q^T * b
    std::vector<double> y = Analysis::transform(Q.transpose(), b);
    
    // Solve Rx = y
    return solve(R, y);
}

std::vector<double> LinearSolver::solveCholesky(const Matrix& A, const std::vector<double>& b) {
    // For symmetric positive-definite systems: Ax = b
    // 1. Compute Cholesky decomposition: A = L * L^T
    // 2. Solve L * y = b (forward substitution)
    // 3. Solve L^T * x = y (back substitution)
    
    int n = A.getRows();
    if (A.getCols() != n) throw std::invalid_argument("Matrix must be square");
    if (b.size() != static_cast<size_t>(n)) throw std::invalid_argument("Vector dimension mismatch");
    
    Logger::getInstance().log("Solving using Cholesky decomposition");
    
    Matrix L = Decomposer::Cholesky(A);
    
    // Forward substitution: L * y = b
    std::vector<double> y(n);
    for (int i = 0; i < n; ++i) {
        double sum = 0;
        for (int j = 0; j < i; ++j) {
            sum += L(i, j) * y[j];
        }
        y[i] = (b[i] - sum) / L(i, i);
    }
    
    // Back substitution: L^T * x = y
    Matrix Lt = L.transpose();
    std::vector<double> x(n);
    for (int i = n - 1; i >= 0; --i) {
        double sum = 0;
        for (int j = i + 1; j < n; ++j) {
            sum += Lt(i, j) * x[j];
        }
        x[i] = (y[i] - sum) / Lt(i, i);
    }
    
    return x;
}

} // namespace LinAlg
