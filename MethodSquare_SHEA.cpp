/Метод квадратного корня для СЛАУ/
#include <iostream>
#include <fstream>
using namespace std;
void OutMatrix(double* arr[], int n){
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout.width(10);
            cout << arr[i][j] << "  ";
        }
        cout << endl;
    }
}
void OutMatrixOneD(double arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout <<"x["<<i+1<<"]= "<< arr[i] << endl;
    }
    cout << endl;
}
double* Cholesky(double* array[], int m, double b[]) {
    double** triangleArr = new double* [m];
    for (int i = 0; i < m; i++) {
        triangleArr[i] = new double[m];
        for (int j = 0; j < m; j++) {
            triangleArr[i][j] = 0;
        }
    }
    triangleArr[0][0] = sqrt(array[0][0]);
    for (int j = 1; j < m; j++) {
        triangleArr[0][j] = (array[0][j]) / triangleArr[0][0];
    }
    
    for (int j = 1; j < m; j++) {
        for (int i = 1; i < m; i++) {
            double sum = 0.0;
            double secSum = 0.0;
            for (int k = 0; k < i; k++) {
                sum = sum + triangleArr[k][i] * triangleArr[k][i];
                if (i<j) secSum = secSum + triangleArr[k][i] * triangleArr[k][j];
            }
            triangleArr[i][i] = sqrt(array[i][i] - sum);
            if (i < j) triangleArr[i][j] = (array[i][j] - secSum) / triangleArr[i][i];
        }
    }

    double* result = new double[m];
    double* matrixY = new double[m];
    //ищем столбец У
    matrixY[0] = b[0] / triangleArr[0][0];
    for (int i = 1; i < m; i++) {
        double sum = 0.0;
        for (int k = 0; k < i; k++) {
            sum = sum + triangleArr[k][i] * matrixY[k];
        }
        matrixY[i] = (b[i] - sum) / triangleArr[i][i];
    }
    // Наконец то находим столбец иксов
    result[m-1] = (matrixY[m-1]) / triangleArr[m-1][m-1];
    for (int i = m-2;i>=0;i--) {
        double sum = 0.0;
        for (int k = i+1; k <= m-1; k++) {
            sum = sum + triangleArr[i][k] * result[k];
        }
        result[i] = (matrixY[i] - sum) / triangleArr[i][i];
    }
    return result;
}
double** ReverseMatrix(double* array[], int m) {
    double** result = new double* [m];
    for (int i = 0; i < m; i++) {
        double* tempB = new double[m];
        for (int k = 0; k < m; k++) {
            if (k == i) tempB[k] = 1;
            else tempB[k] = 0;
        }
        result[i] = Cholesky(array, m, tempB);
    }
    return result;
}
int main()
{
    string path = "Matrix.txt";
    ifstream fin;
    fin.open(path);
    int rows, cols;

        fin >> rows;
        cols = rows;

        double** arr = new double* [rows];
        double* vectorX = new double [rows];
        double* vector = new double[rows];
        double** reversedArr = new double* [rows];
        for (int i = 0; i < rows; i++) {
            arr[i] = new double[cols];
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
        vector = Cholesky(arr, rows, vectorX);
        cout << "Found roots of the systems of equation: " << endl;
        OutMatrixOneD(vector, rows);
        cout << "Reversed matrix A: " << endl;
        reversedArr = ReverseMatrix(arr, rows);
        OutMatrix(reversedArr, rows);

    delete[] vectorX;
    delete[] vector;
    for (int i = 0; i < rows; i++) {
        delete[] arr[i];
        delete[] reversedArr[i];
    }
    delete[] arr;
    delete[] reversedArr;
}


