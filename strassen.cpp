#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> A;
vector<vector<int>> B;
vector<vector<int>> C;

void print_matrix(int z) {
	for(int i = 0; i < z; i++) {
		for(int j = 0; j < z; j++) {
			cout << A[i][j] << ' ';
		}
		cout << "\n";
	}
	cout << "\n";

	for(int i = 0; i < z; i++) {
		for(int j = 0; j < z; j++) {
			cout << B[i][j] << ' ';
		}
		cout << "\n";
	}
}

int M7(int i_inicial, int j_inicial) {
	return (A[i_inicial][j_inicial + 1] - A[i_inicial + 1][j_inicial + 1]) * (B[i_inicial + 1][j_inicial] + B[i_inicial + 1][j_inicial + 1]);
}

int M6(int i_inicial, int j_inicial) {
	return (A[i_inicial + 1][j_inicial] - A[i_inicial][j_inicial]) * (B[i_inicial][j_inicial] + B[i_inicial][j_inicial + 1]);
}

int M5(int i_inicial, int j_inicial) {
	return (A[i_inicial][j_inicial] + A[i_inicial][j_inicial + 1]) * B[i_inicial + 1][j_inicial + 1];
}

int M4(int i_inicial, int j_inicial) {
	return A[i_inicial + 1][j_inicial + 1] * (B[i_inicial + 1][j_inicial] - B[i_inicial][j_inicial]);
}

int M3(int i_inicial, int j_inicial) {
	cout << A[i_inicial][j_inicial] << " " << B[i_inicial][j_inicial + 1] << " " << B[i_inicial + 1][j_inicial + 1] << "\n";
	return A[i_inicial][j_inicial] * (B[i_inicial][j_inicial + 1] - B[i_inicial + 1][j_inicial + 1]);
}

int M2(int i_inicial, int j_inicial) {
	return (A[i_inicial + 1][j_inicial] + A[i_inicial + 1][j_inicial + 1]) * B[i_inicial][j_inicial];
}

int M1(int i_inicial, int j_inicial) {
	//cout << A[i_inicial][j_inicial] << " " << A[i_inicial + 1][j_inicial + 1] << " " << B[i_inicial][j_inicial] << " " << B[i_inicial + 1][j_inicial + 1] << "\n";
	return (A[i_inicial][j_inicial] + A[i_inicial + 1][j_inicial + 1]) * (B[i_inicial][j_inicial] + B[i_inicial + 1][j_inicial + 1]);
}

void strassen(int i_inicial, int i_final, int j_inicial, int j_final) {
	if(i_final - i_inicial == 2 && j_final - j_inicial == 2) {
		cout << M3(i_inicial, j_inicial) << " " << M5(i_inicial, j_inicial) << "\n";
		C[i_inicial][j_inicial] = M1(i_inicial, j_inicial) + M4(i_inicial, j_inicial) - M5(i_inicial, j_inicial) + M7(i_inicial, j_inicial);
		C[i_inicial][j_inicial + 1] = M3(i_inicial, j_inicial) + M5(i_inicial, j_inicial);
		C[i_inicial + 1][j_inicial] = M2(i_inicial, j_inicial) + M4(i_inicial, j_inicial);
		//C[i_inicial + 1][j_inicial + 1] = M1(i_inicial, j_inicial) - M2(i_inicial, j_inicial) + M3(i_inicial, j_inicial) + M6(i_inicial, j_inicial);
		return;
	}
	else {
		strassen(i_inicial, i_final / 2, j_inicial, j_final / 2);
		strassen((i_final / 2), i_final, j_inicial, j_final / 2);
		strassen(i_inicial, i_final / 2, (j_final / 2), j_final);
		strassen((i_final / 2), i_final, (j_final / 2), j_final);
	}
}

int main() {
	int N1, N2, M1, M2; 
	cin >> N1 >> M1 >> N2 >> M2;
	if(M1 != N2) {
		cout << "Não é possível multiplicar as matrizes!" << "\n";
		return 0;
	}

	// parte do código que transforma os valores de N1, N2, M1 e M2 para a menor potência de 2 possível para que A, B e C sejam uma matriz quadrada de ordem 2^i
	vector<int> biggest; // verifica o maior valor entre N1, M1, N2 e M2
	biggest.push_back(N1);
	biggest.push_back(M1);
	biggest.push_back(N2);
	biggest.push_back(M2);

	sort(biggest.begin(), biggest.end());
	int aux = 1;
	while(1) {
		if(biggest[3] <= pow(2, aux)) {
			break;
		}
		aux++;
	}
	int z = pow(2, aux); // tamanho das matrizes será de z X z

	// aloca o tamanho das matrizes A, B e C para z X z
	A.resize(z);
	B.resize(z);
	C.resize(z);
	for(int i = 0; i < z; i++) {
		A[i].assign(z, 0);
		B[i].assign(z, 0);
		C[i].assign(z, 0);
	}

	// recebe e atribui os valores da matriz A

	for(int i = 0; i < N1; i++) {
		for(int j = 0; j < M1; j++) {
			cin >> A[i][j];
		}
	}

	// recebe e atribui os valores da matriz B

	for(int i = 0; i < N2; i++) {
		for(int j = 0; j < M2; j++) {
			cin >> B[i][j];
		}
	}
	strassen(0, z, 0, z);

	/*for(int i = 0; i < z; i++) {
		for(int j = 0; j < z; j++) {
			cout << C[i][j] << " ";
		}
		cout << "\n";
	}*/

	return 0;
}
