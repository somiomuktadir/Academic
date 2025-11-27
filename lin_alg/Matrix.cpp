#include "Matrix.h"
#include "Decomposer.h"

Matrix::Matrix(int r, int c, double initialValue) : rows(r), cols(c) {
    data.reserve(r);
    data.resize(r, std::vector<double>(c, initialValue));
}

Matrix::Matrix(const std::vector<std::vector<double>>& d) {
    if (d.empty()) {
        rows = 0;
        cols = 0;
    } else {
        rows = d.size();
        cols = d[0].size();
        data = d;
    }
}

int Matrix::getRows() const {
    return rows;
}

int Matrix::getCols() const {
    return cols;
}

double& Matrix::at(int r, int c) {
    if (r < 0 || r >= rows || c < 0 || c >= cols) {
        throw std::out_of_range("Matrix index out of bounds");
    }
    return data[r][c];
}

const double& Matrix::at(int r, int c) const {
    if (r < 0 || r >= rows || c < 0 || c >= cols) {
        throw std::out_of_range("Matrix index out of bounds");
    }
    return data[r][c];
}

Matrix Matrix::operator+(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("Matrix dimensions must match for addition");
    }
    Matrix result(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result.data[i][j] = data[i][j] + other.data[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator-(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("Matrix dimensions must match for subtraction");
    }
    Matrix result(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result.data[i][j] = data[i][j] - other.data[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator*(const Matrix& other) const {
    if (cols != other.rows) {
        throw std::invalid_argument("Matrix dimensions incompatible for multiplication");
    }
    Matrix result(rows, other.cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < other.cols; ++j) {
            for (int k = 0; k < cols; ++k) {
                result.data[i][j] += data[i][k] * other.data[k][j];
            }
        }
    }
    return result;
}

Matrix Matrix::operator*(double scalar) const {
    Matrix result(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result.data[i][j] = data[i][j] * scalar;
        }
    }
    return result;
}

Matrix Matrix::transpose() const {
    Matrix result(cols, rows);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result.data[j][i] = data[i][j];
        }
    }
    return result;
}

Matrix Matrix::identity(int n) {
    Matrix result(n, n);
    for (int i = 0; i < n; ++i) {
        result.data[i][i] = 1.0;
    }
    return result;
}

void Matrix::print() const {
    std::cout << std::fixed << std::setprecision(4);
    for (const auto& row : data) {
        std::cout << "[ ";
        for (double val : row) {
            std::cout << val << " ";
        }
        std::cout << "]" << std::endl;
    }
}

Matrix operator*(double scalar, const Matrix& mat) {
    return mat * scalar;
}

double Matrix::trace() const {
    if (rows != cols) throw std::invalid_argument("Matrix must be square for trace");
    double sum = 0;
    for (int i = 0; i < rows; ++i) sum += data[i][i];
    return sum;
}

int Matrix::rank() const {
    // Gaussian elimination to row echelon form
    Matrix M = *this;
    int pivotRow = 0;
    for (int col = 0; col < cols && pivotRow < rows; ++col) {
        int sel = pivotRow;
        for (int i = pivotRow + 1; i < rows; ++i) {
            if (std::abs(M.data[i][col]) > std::abs(M.data[sel][col])) {
                sel = i;
            }
        }
        
        if (std::abs(M.data[sel][col]) < 1e-10) continue;
        
        std::swap(M.data[sel], M.data[pivotRow]);
        
        for (int i = pivotRow + 1; i < rows; ++i) {
            double factor = M.data[i][col] / M.data[pivotRow][col];
            for (int j = col; j < cols; ++j) {
                M.data[i][j] -= factor * M.data[pivotRow][j];
            }
        }
        pivotRow++;
    }
    return pivotRow;
}

Matrix Matrix::rref() const {
    Matrix M = *this;
    int lead = 0;
    int rowCount = rows;
    int colCount = cols;

    for (int r = 0; r < rowCount; ++r) {
        if (colCount <= lead) break;
        int i = r;
        while (M.at(i, lead) == 0) {
            i++;
            if (rowCount == i) {
                i = r;
                lead++;
                if (colCount == lead) return M;
            }
        }

        for (int k = 0; k < colCount; ++k) {
            std::swap(M.at(i, k), M.at(r, k));
        }

        double val = M.at(r, lead);
        for (int k = 0; k < colCount; ++k) {
            M.at(r, k) /= val;
        }

        for (int i = 0; i < rowCount; ++i) {
            if (i != r) {
                double val = M.at(i, lead);
                for (int k = 0; k < colCount; ++k) {
                    M.at(i, k) -= val * M.at(r, k);
                }
            }
        }
        lead++;
    }
    return M;
}

double Matrix::conditionNumber() const {
    // Condition number is ratio of max singular value to min singular value
    // We can use SVD for this.
    try {
        auto [U, S, V] = Decomposer::SVD(*this);
        double maxSv = 0;
        double minSv = 1e300; // Large number
        
        int minDim = std::min(rows, cols);
        for(int i=0; i<minDim; ++i) {
            double s = S.at(i,i);
            if(s > maxSv) maxSv = s;
            if(s < minSv && s > 1e-10) minSv = s; // Avoid zero singular values for singular matrices
        }
        
        if (minSv > 1e299) return 1.0/0.0; // Infinity (singular)
        if (minSv < 1e-10) return 1.0/0.0;
        
        return maxSv / minSv;
    } catch (...) {
        return -1.0; // Error
    }
}
