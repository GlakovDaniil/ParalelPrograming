#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <iomanip>

using namespace std;

int main() {
    int N=2;

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dis(1.0, 50.0);

    // cоздаем одну большую матрицу на 2*N строк
    vector<vector<double>> big_matrix(2 * N, vector<double>(N));

    for (int i = 0; i < 2 * N; ++i) {
        for (int j = 0; j < N; ++j) {
            big_matrix[i][j] = dis(gen);
        }
    }

    ofstream out("input.txt");

    out << fixed << setprecision(1);
    out << N << "\n";

    for (int i = 0; i < 2 * N; ++i) {
        for (int j = 0; j < N; ++j) {
            out << big_matrix[i][j] << (j == N - 1 ? "" : " ");
        }
        out << "\n";
    }

    out.close();

    return 0;
}
