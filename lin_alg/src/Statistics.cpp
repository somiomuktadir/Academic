#include "Statistics.h"
#include "Decomposer.h"
#include <cmath>
#include <numeric>

namespace LinAlg {

std::vector<double> Statistics::mean(const Matrix& data, int axis) {
    int rows = data.getRows();
    int cols = data.getCols();
    
    if (axis == 0) { // Column-wise
        std::vector<double> means(cols, 0.0);
        for (int j = 0; j < cols; ++j) {
            for (int i = 0; i < rows; ++i) {
                means[j] += data.at(i, j);
            }
            means[j] /= rows;
        }
        return means;
    } else { // Row-wise
        std::vector<double> means(rows, 0.0);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                means[i] += data.at(i, j);
            }
            means[i] /= cols;
        }
        return means;
    }
}

std::vector<double> Statistics::variance(const Matrix& data, int axis) {
    std::vector<double> means = mean(data, axis);
    int rows = data.getRows();
    int cols = data.getCols();
    
    if (axis == 0) { // Column-wise
        std::vector<double> vars(cols, 0.0);
        for (int j = 0; j < cols; ++j) {
            for (int i = 0; i < rows; ++i) {
                double diff = data.at(i, j) - means[j];
                vars[j] += diff * diff;
            }
            vars[j] /= (rows > 1 ? rows - 1 : 1); // Sample variance
        }
        return vars;
    } else { // Row-wise
        std::vector<double> vars(rows, 0.0);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                double diff = data.at(i, j) - means[i];
                vars[i] += diff * diff;
            }
            vars[i] /= (cols > 1 ? cols - 1 : 1); // Sample variance
        }
        return vars;
    }
}

std::vector<double> Statistics::stdDev(const Matrix& data, int axis) {
    std::vector<double> vars = variance(data, axis);
    std::vector<double> stds(vars.size());
    for (size_t i = 0; i < vars.size(); ++i) {
        stds[i] = std::sqrt(vars[i]);
    }
    return stds;
}

Matrix Statistics::covarianceMatrix(const Matrix& data) {
    // Assumes rows are samples, columns are features
    int n = data.getRows();
    if (n < 2) throw std::invalid_argument("Need at least 2 samples for covariance");
    
    Matrix centered = data;
    std::vector<double> means = mean(data, 0);
    
    for (int i = 0; i < centered.getRows(); ++i) {
        for (int j = 0; j < centered.getCols(); ++j) {
            centered.at(i, j) -= means[j];
        }
    }
    
    // Cov = (X_centered^T * X_centered) / (n - 1)
    Matrix cov = centered.transpose() * centered;
    return cov * (1.0 / (n - 1));
}

Matrix Statistics::correlationMatrix(const Matrix& data) {
    Matrix cov = covarianceMatrix(data);
    int d = cov.getRows();
    Matrix corr(d, d);
    
    for (int i = 0; i < d; ++i) {
        for (int j = 0; j < d; ++j) {
            double std_i = std::sqrt(cov.at(i, i));
            double std_j = std::sqrt(cov.at(j, j));
            if (std_i > 0 && std_j > 0) {
                corr.at(i, j) = cov.at(i, j) / (std_i * std_j);
            } else {
                corr.at(i, j) = 0.0;
            }
        }
    }
    return corr;
}

std::pair<Matrix, std::vector<double>> Statistics::PCA(const Matrix& data, int numComponents) {
    // 1. Standardize data (optional but recommended, here we just center)
    Matrix centered = data;
    std::vector<double> means = mean(data, 0);
    for (int i = 0; i < centered.getRows(); ++i) {
        for (int j = 0; j < centered.getCols(); ++j) {
            centered.at(i, j) -= means[j];
        }
    }
    
    // 2. Compute Covariance Matrix
    Matrix cov = covarianceMatrix(data);
    
    // 3. Eigen Decomposition of Covariance Matrix
    // Note: Covariance matrix is symmetric, so eigenvalues are real
    auto [eigenValuesMat, eigenVectors] = Decomposer::Eigen(cov);
    
    // Extract eigenvalues from diagonal
    int d = cov.getRows();
    std::vector<std::pair<double, int>> eigenPairs;
    for (int i = 0; i < d; ++i) {
        eigenPairs.push_back({eigenValuesMat.at(i, i), i});
    }
    
    // Sort by eigenvalue descending
    std::sort(eigenPairs.begin(), eigenPairs.end(), 
              [](const auto& a, const auto& b) { return a.first > b.first; });
    
    // Select top numComponents
    if (numComponents > d) numComponents = d;
    
    Matrix components(d, numComponents);
    std::vector<double> explainedVariance;
    
    for (int k = 0; k < numComponents; ++k) {
        int idx = eigenPairs[k].second;
        explainedVariance.push_back(eigenPairs[k].first);
        
        // Copy eigenvector column
        for (int i = 0; i < d; ++i) {
            components.at(i, k) = eigenVectors.at(i, idx);
        }
    }
    
    return {components, explainedVariance};
}

Matrix Statistics::standardize(const Matrix& data) {
    Matrix result = data;
    std::vector<double> means = mean(data, 0);
    std::vector<double> stds = stdDev(data, 0);
    
    for (int j = 0; j < result.getCols(); ++j) {
        if (stds[j] == 0) continue; // Avoid division by zero
        for (int i = 0; i < result.getRows(); ++i) {
            result.at(i, j) = (result.at(i, j) - means[j]) / stds[j];
        }
    }
    return result;
}

} // namespace LinAlg
