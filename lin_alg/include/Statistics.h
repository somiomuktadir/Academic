#ifndef STATISTICS_H
#define STATISTICS_H

#include "Matrix.h"
#include <vector>
#include <utility>

namespace LinAlg {

class Statistics {
public:
    // Basic statistics
    // axis: 0 for column-wise, 1 for row-wise
    static std::vector<double> mean(const Matrix& data, int axis = 0);
    static std::vector<double> variance(const Matrix& data, int axis = 0);
    static std::vector<double> stdDev(const Matrix& data, int axis = 0);
    
    // Covariance matrix (assumes rows are samples, columns are features)
    static Matrix covarianceMatrix(const Matrix& data);
    
    // Correlation matrix
    static Matrix correlationMatrix(const Matrix& data);
    
    // Principal Component Analysis
    // Returns pair {Principal Components (Eigenvectors), Explained Variance (Eigenvalues)}
    static std::pair<Matrix, std::vector<double>> PCA(const Matrix& data, int numComponents);
    
    // Standardize data (subtract mean, divide by std dev)
    static Matrix standardize(const Matrix& data);
};

} // namespace LinAlg

#endif // STATISTICS_H
