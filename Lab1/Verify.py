import numpy as np
import subprocess

with open("input.txt", "r") as f: # читаем матрицы
    data = f.read().split()

N = int(data[0])
idx = 1


A = [] # матрица В
for i in range(N):
    A.append([float(x) for x in data[idx : idx + N]])
    idx += N

B = [] # матрица А
for i in range(N):
    B.append([float(x) for x in data[idx : idx + N]])
    idx += N


subprocess.run(["./build/Debug/Multiplication.exe"]) # перемножение матриц с++

C_py = np.zeros((N, N))  # эталонная матрица

for i in range(N):
    for k in range(N):
        for j in range(N):
            C_py[i, j] += A[i][k] * B[k][j]

C_py = np.round(C_py, 2)

C_cpp = np.loadtxt("matrix_results.txt", skiprows=3) # результаты сравнения

if np.array_equal(C_cpp, C_py):
    status_text = "УСПЕХ"
else:
    status_text = "НЕУДАЧА"

with open("matrix_results.txt", "a", encoding="utf-8") as out:
    out.write("\n" + status_text + "\n")

print("отработала штатно")
