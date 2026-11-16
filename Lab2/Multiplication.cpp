#include <omp.h>
import std;

using namespace std;

int main() {
    int N;
    ifstream in("input.txt");
    in >> N; //размерность матриц

    // чтение матрицы А
    vector<vector<double>> A(N, vector<double>(N));
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            in >> A[i][j];

    // чтение матрицы В
    vector<vector<double>> B(N, vector<double>(N));
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            in >> B[i][j];

    vector<vector<double>> C(N, vector<double>(N, 0.0));

    // задаем количество потоков для эксперимента
    int num_threads = 8;
    omp_set_num_threads(num_threads);

    #pragma omp parallel
    {
        if (omp_get_thread_num() == 0)
            cout << "РЕАЛНО ПОТОКОВ: " << omp_get_num_threads() << "\n";
    }

    // замер времени и вычисление
    auto start = chrono::high_resolution_clock::now();

    #pragma omp parallel for
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            double sum = 0.0;
            for (int k = 0; k < N; ++k) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start;

    // запись результатов
    ofstream out("matrix_results.txt");
    out << "Объем задачи (N): " << N << "x" << N << "\n";

    out << fixed << setprecision(4);
    out << "Время выполнения: " << duration.count() << " мс\n";
    out << "--- Результирующая матрица ---\n";

    // запись матрицы с округлением до 2 знаков после запятой
    out << fixed << setprecision(2);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            out << C[i][j] << " ";
        }
        out << "\n";
    }
    out.close();
    return 0;
}