#include <iostream>
#include <vector>
#include <limits>
#include <stdexcept>
#include <iomanip>
using namespace std;

// Matrix type using long long
using Matrix = vector<vector<long long>>;

// Function declarations
void inputMatrix(Matrix& matrix, long long rows, long long cols);
void displayMatrix(const Matrix& matrix);
long long getSize(const string& prompt);
void addMatrices(const Matrix& a, const Matrix& b, Matrix& result);
void subtractMatrices(const Matrix& a, const Matrix& b, Matrix& result);
void multiplyMatrices(const Matrix& a, const Matrix& b, Matrix& result);
void transposeMatrix(const Matrix& matrix, Matrix& result);
long long calculateDeterminant(const Matrix& matrix);
Matrix getMinor(const Matrix& matrix, long long row, long long col);

int main() {
    while (true) {
        cout << "\nMATRIX CALCULATOR:\n";
        cout << "1. Addition (A + B)\n";
        cout << "2. Subtraction (A - B)\n";
        cout << "3. Multiplication (A . B)\n";
        cout << "4. Transpose (A^T)\n";
        cout << "5. Determinant (|A|)\n";
        cout << "6. Exit\n";
        cout << "Your choice: ";

        long long choice;
        cin >> choice;

        if (choice == 6) {
            cout << "Exiting program...\n";
            break;
        }

        try {
            Matrix matrix1, matrix2, result;
            long long rows, cols;

            switch (choice) {
                case 1: 
                case 2: {
                    rows = getSize("Enter number of rows: ");
                    cols = getSize("Enter number of columns: ");
                    
                    cout << "\nMatrix A:\n";
                    inputMatrix(matrix1, rows, cols);
                    cout << "\nMatrix B:\n";
                    inputMatrix(matrix2, rows, cols);

                    if (matrix1.size() != matrix2.size() || matrix1[0].size() != matrix2[0].size()) {
                        cout << "Error: Matrices must be same size for addition/subtraction!\n";
                        break;
                    }

                    if (choice == 1) {
                        addMatrices(matrix1, matrix2, result);
                        cout << "\nAddition Result:\n";
                    } else {
                        subtractMatrices(matrix1, matrix2, result);
                        cout << "\nSubtraction Result:\n";
                    }
                    displayMatrix(result);
                    break;
                }

                case 3: { // Multiplication
                    rows = getSize("Enter rows for Matrix A: ");
                    cols = getSize("Enter columns for Matrix A: ");
                    long long colsB = getSize("Enter columns for Matrix B: ");
                    
                    cout << "\nMatrix A:\n";
                    inputMatrix(matrix1, rows, cols);
                    cout << "\nMatrix B:\n";
                    inputMatrix(matrix2, cols, colsB);

                    if (matrix1[0].size() != matrix2.size()) {
                        cout << "Error: Columns of A must match rows of B!\n";
                        break;
                    }

                    multiplyMatrices(matrix1, matrix2, result);
                    cout << "\nMultiplication Result:\n";
                    displayMatrix(result);
                    break;
                }

                case 4: { // Transpose
                    rows = getSize("Enter number of rows: ");
                    cols = getSize("Enter number of columns: ");
                    
                    cout << "\nMatrix to transpose:\n";
                    inputMatrix(matrix1, rows, cols);
                    transposeMatrix(matrix1, result);
                    cout << "\nTransposed Matrix:\n";
                    displayMatrix(result);
                    break;
                }

                case 5: { // Determinant
                    rows = getSize("Enter size of square matrix (n x n): ");
                    
                    cout << "\nMatrix for determinant:\n";
                    inputMatrix(matrix1, rows, rows);

                    if (matrix1.size() != matrix1[0].size()) {
                        cout << "Error: Matrix must be square for determinant!\n";
                        break;
                    }

                    long long det = calculateDeterminant(matrix1);
                    cout << "\nDeterminant: " << det << endl;
                    break;
                }

                default:
                    cout << "Invalid choice! Try again.\n";
            }
        } catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    return 0;
}

// Function implementations
long long getSize(const string& prompt) {
    long long size;
    while (true) {
        cout << prompt;
        cin >> size;
        if (cin.fail() || size <= 0) {
            cout << "Invalid input. Enter positive integer: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            return size;
        }
    }
}

void inputMatrix(Matrix& matrix, long long rows, long long cols) {
    matrix.clear();
    for (long long i = 0; i < rows; ++i) {
        vector<long long> row;
        for (long long j = 0; j < cols; ++j) {
            cout << "Element [" << i+1 << "][" << j+1 << "]: ";
            long long element;
            cin >> element;
            row.push_back(element);
        }
        matrix.push_back(row);
    }
}

void displayMatrix(const Matrix& matrix) {
    for (const auto& row : matrix) {
        for (long long element : row) {
            cout << element << "\t";
        }
        cout << endl;
    }
}

void addMatrices(const Matrix& a, const Matrix& b, Matrix& result) {
    result.clear();
    for (long long i = 0; i < a.size(); ++i) {
        vector<long long> row;
        for (long long j = 0; j < a[0].size(); ++j) {
            row.push_back(a[i][j] + b[i][j]);
        }
        result.push_back(row);
    }
}

void subtractMatrices(const Matrix& a, const Matrix& b, Matrix& result) {
    result.clear();
    for (long long i = 0; i < a.size(); ++i) {
        vector<long long> row;
        for (long long j = 0; j < a[0].size(); ++j) {
            row.push_back(a[i][j] - b[i][j]);
        }
        result.push_back(row);
    }
}

void multiplyMatrices(const Matrix& a, const Matrix& b, Matrix& result) {
    result.clear();
    for (long long i = 0; i < a.size(); ++i) {
        vector<long long> row;
        for (long long j = 0; j < b[0].size(); ++j) {
            long long sum = 0;
            for (long long k = 0; k < a[0].size(); ++k) {
                sum += a[i][k] * b[k][j];
            }
            row.push_back(sum);
        }
        result.push_back(row);
    }
}

void transposeMatrix(const Matrix& matrix, Matrix& result) {
    result.clear();
    for (long long j = 0; j < matrix[0].size(); ++j) {
        vector<long long> row;
        for (long long i = 0; i < matrix.size(); ++i) {
            row.push_back(matrix[i][j]);
        }
        result.push_back(row);
    }
}

long long calculateDeterminant(const Matrix& matrix) {
    long long n = matrix.size();
    if (n == 1) {
        return matrix[0][0];
    }
    if (n == 2) {
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    }

    long long det = 0;
    for (long long col = 0; col < n; ++col) {
        Matrix minor = getMinor(matrix, 0, col);
        det += (col % 2 == 0 ? 1 : -1) * matrix[0][col] * calculateDeterminant(minor);
    }
    return det;
}

Matrix getMinor(const Matrix& matrix, long long row, long long col) {
    Matrix minor;
    for (long long i = 0; i < matrix.size(); ++i) {
        if (i == row) continue;
        vector<long long> minorRow;
        for (long long j = 0; j < matrix.size(); ++j) {
            if (j == col) continue;
            minorRow.push_back(matrix[i][j]);
        }
        minor.push_back(minorRow);
    }
    return minor;
}
