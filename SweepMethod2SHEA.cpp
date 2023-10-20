
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
void OutMatrix(long double* arr[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout.width(10);

            cout << setprecision(3) << arr[i][j] << "  ";
        }
        cout << endl;
    }
}
void OutMatrixOneD(long double arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << "x[" << i + 1 << "]= " << setprecision(3) << arr[i] << endl;
    }
    cout << endl;
}
int ProveStable(long double A[], long double B[], long double C[], int n) {
    int flag = 1;
    for (int i = 0; i < n; i++) {
        if (abs(B[i]) < abs(A[i]) + abs(C[i])) {
            cout << "The method is not stable" << endl;
            return 0;
        }
        else  if (abs(B[i]) > abs(A[i]) + abs(C[i])) flag = 0;//нашли одно строгое неравенство

    }
    if (flag==1) cout << "The method is not stable" << endl;
    else cout << "The method is stable" << endl;
}
long double* Sweep(long double A[], long double B[], long double C[], long double F[], int n) {
    long double* R = new long double[n + 1];
    long double* T = new long double[n + 1];
    long double* x = new long double[n + 1];
    long double an = -A[n-1], a = -A[1], b = B[1], bn = B[n-1], c0 = -C[0], c = -C[1], f0 = F[0], fn = F[n-1], f = F[1], b0 = B[0];    
    R[n] = an / bn;
    T[n] = fn / bn;
    for (int i = n - 1; i > 0; i--) {
        R[i] = a / (b - c * R[i + 1]);
        T[i] = (f + c * T[i + 1]) / (b - c * R[i + 1]);
    }
    x[0] = (f0 + c0 * T[1]) / (b0 - c0 * R[1]); 
    for (int i = 1; i <= n; i++) {
        x[i] = R[i] * x[i - 1] + T[i];
    }
    return x;
}

int main()
{
    string path = "Matrix.txt";
    ifstream fin;
    fin.open(path);
    int rows;
    fin >> rows;
    long double* vectorA = new long double[rows];
    long double* vectorB = new long double[rows];
    long double* vectorC = new long double[rows];
    long double* vectorX = new long double[rows];
    for (int i = 0; i < rows; i++) {
        fin >> vectorA[i];
    }
    for (int i = 0; i < rows; i++) {
        fin >> vectorB[i];
    }
    for (int i = 0; i < rows; i++) {
        fin >> vectorC[i];
    }
    for (int i = 0; i < rows; i++) {
        fin >> vectorX[i];
    }
    ProveStable(vectorA, vectorB, vectorC, rows);

    cout << "Found roots of the systems of equation: " << endl;
    OutMatrixOneD(Sweep(vectorA, vectorB, vectorC, vectorX, rows), rows);
    delete[] vectorX;

}


