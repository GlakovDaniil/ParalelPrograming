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

    // замер времени и вычисление
    auto start = chrono::high_resolution_clock::now();

    for (int i = 0; i < N; ++i) {
        for (int k = 0; k < N; ++k) {
            for (int j = 0; j < N; ++j) {
                C[i][j] += A[i][k] * B[k][j];
            }
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