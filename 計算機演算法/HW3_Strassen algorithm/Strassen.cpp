#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

const int maxSize = 64; //Use standard multiplication if matrix size smaller than maxSize

vector<vector<long long>> standardMultiply(const vector<vector<long long>> &A, const vector<vector<long long>> &B, int n) {
    vector<vector<long long>> C(n, vector<long long>(n, 0)); //Initialize matrix C with 0
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            long long sum = 0;
            for (int k = 0; k < n; k++) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }
    return C;
}

vector<vector<long long>> addMatrix(const vector<vector<long long>> &A, const vector<vector<long long>> &B, int n) {
    vector<vector<long long>> C(n, vector<long long>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
}

vector<vector<long long>> subtractMatrix(const vector<vector<long long>> &A, const vector<vector<long long>> &B, int n) {
    vector<vector<long long>> C(n, vector<long long>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    return C;
}

vector<vector<long long>> strassen(const vector<vector<long long>> &A, const vector<vector<long long>> &B, int n) {
    if (n <= maxSize) {
        return standardMultiply(A, B, n);
    }
    
    int newSize = n / 2;

    vector<vector<long long>> A11(newSize, vector<long long>(newSize)),
                             A12(newSize, vector<long long>(newSize)),
                             A21(newSize, vector<long long>(newSize)),
                             A22(newSize, vector<long long>(newSize));
    vector<vector<long long>> B11(newSize, vector<long long>(newSize)),
                             B12(newSize, vector<long long>(newSize)),
                             B21(newSize, vector<long long>(newSize)),
                             B22(newSize, vector<long long>(newSize));
    
    //Divide into 4 submatrix
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];
            
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }
    
    //Calculate 7 new matrix
    vector<vector<long long>> M1 = strassen(addMatrix(A11, A22, newSize), addMatrix(B11, B22, newSize), newSize);
    vector<vector<long long>> M2 = strassen(addMatrix(A21, A22, newSize), B11, newSize);
    vector<vector<long long>> M3 = strassen(A11, subtractMatrix(B12, B22, newSize), newSize);
    vector<vector<long long>> M4 = strassen(A22, subtractMatrix(B21, B11, newSize), newSize);
    vector<vector<long long>> M5 = strassen(addMatrix(A11, A12, newSize), B22, newSize);
    vector<vector<long long>> M6 = strassen(subtractMatrix(A21, A11, newSize), addMatrix(B11, B12, newSize), newSize);
    vector<vector<long long>> M7 = strassen(subtractMatrix(A12, A22, newSize), addMatrix(B21, B22, newSize), newSize);
    
    //Combine results 
    vector<vector<long long>> C11 = addMatrix(subtractMatrix(addMatrix(M1, M4, newSize), M5, newSize), M7, newSize);
    vector<vector<long long>> C12 = addMatrix(M3, M5, newSize);
    vector<vector<long long>> C21 = addMatrix(M2, M4, newSize);
    vector<vector<long long>> C22 = addMatrix(subtractMatrix(addMatrix(M1, M3, newSize), M2, newSize), M6, newSize);
    
    //Combine into complete matrix
    vector<vector<long long>> C(n, vector<long long>(n));
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i][j] = C11[i][j];
            C[i][j + newSize] = C12[i][j];
            C[i + newSize][j] = C21[i][j];
            C[i + newSize][j + newSize] = C22[i][j];
        }
    }
    return C;
}

int main() {
    int a, b, c, d; //Arow, Acol, Brow, Bcol
    cin >> a >> b >> c >> d;
    if (b != c) {
        cout << "Error: Incompatible matrices";
        return 1;
    }

    int size = max({a, b, c, d});
    size = pow(2, ceil(log2(size))); //Adjust matrix size to power of 2
    
    //Initialize matrix A and B with 0
    vector<vector<long long>> A(size, vector<long long>(size, 0));
    vector<vector<long long>> B(size, vector<long long>(size, 0));
    
    //Input matrix A and B
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < b; j++) {
            cin >> A[i][j];
        }
    }
    for (int i = 0; i < c; i++) {
        for (int j = 0; j < d; j++) {
            cin >> B[i][j];
        }
    }
    
    vector<vector<long long>> result = strassen(A, B, size); 
    
    //Output complete matrix
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < d; j++) {
            cout << result[i][j] << " ";
        }
    }
    cout << endl;
    return 0;
}
