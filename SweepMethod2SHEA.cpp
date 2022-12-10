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
void sweep1(double* matrix[], double freeMembers[], int size) {
    double temp;
    double* a = new double[size];
    double* b = new double[size];
    double* x = new double[size];
    temp = matrix[0][0];
    a[0] = -matrix[0][1] / temp;
    b[0] = freeMembers[0] / temp;
    for (int i = 1; i < size - 1; i++) {
        temp = matrix[i][i] + matrix[i][i - 1] * a[i - 1];
        a[i] = -matrix[i][i + 1] / temp;
        b[i] = (freeMembers[i] - matrix[i][i - 1] * b[i - 1]) / temp;
    }
    x[size - 1] = (freeMembers[size - 1] - matrix[size - 1][size - 2] * b[size - 2]) / (matrix[size - 1][size - 1] + matrix[size - 1][size - 2] * a[size - 2]);
    for (int i = size - 2; i >= 0; i--) {
        x[i] = a[i] * x[i + 1] + b[i];
    }

    for (int i = 0; i < size; i++)
    {
        cout.width(10);
        cout << x[i] << "\t";
    }
    delete[] a, b, x;
}

long double* Sweep(long double* arr[], int rows, long double B[]) {
    long double* r = new long double[rows];
    long double* t = new long double[rows];
    long double* x = new long double[rows];
    long double a0 = 0.0, cn = 0.0;
    r[rows - 1] = (arr[rows-1 ][rows - 2] / arr[rows - 1][rows - 1]);
    t[rows - 1] = (B[rows-1] / arr[rows - 1][rows-1]);
    for (int i = rows - 2; i >=0; i--) {
        if (i == 0) r[i] =( a0 / (arr[i][i] - arr[i][i+1] * r[i + 1]));
        else r[i] = ((arr[i][i - 1]) / (arr[i][i] - arr[i][i+1] * r[i + 1]));
        t[i] = ((B[i] + arr[i][i + 1] * t[i + 1]) / (arr[i][i] - arr[i][i+1] * r[i + 1]));
    }
    
    x[0] = (B[0] + arr[0][1] * t[0]) / (arr[0][0] - arr[0][1] * r[0]);
    for (int i = 1; i < rows; i++) {
        x[i] = r[i] * x[i - 1] + t[i];
    }
    OutMatrixOneD(r, rows);
    OutMatrixOneD(t, rows);
    return x;
}

int main()
{
    string path = "Matrix.txt";
    ifstream fin;
    fin.open(path);
    int rows, cols;

    fin >> rows;
    cols = rows;

    long double** arr = new long double* [rows];
    long double* vectorX = new long double[rows];
    double* vector = new double[rows];
    double** reversedArr = new double* [rows];
    for (int i = 0; i < rows; i++) {
        arr[i] = new long double[cols];
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
        {
            fin >> arr[i][j];
        }
    }
    for (int i = 0; i < rows; i++) {
        fin >> vectorX[i];
    }
    cout << "Found roots of the systems of equation: " << endl;
    OutMatrixOneD(Sweep(arr,rows,vectorX), rows);
    delete[] arr;
    delete[] vectorX;

}


