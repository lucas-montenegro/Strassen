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

void create_all_matrices(vector<vector<int>> &s1, vector<vector<int>> &s2, vector<vector<int>> &s3, vector<vector<int>> &s4, vector<vector<int>> &s5, vector<vector<int>> &s6, vector<vector<int>> &s7, vector<vector<int>> &s8, vector<vector<int>> &s9, vector<vector<int>> &s10, int z) {
	s1.resize(z);
	s2.resize(z);
	s3.resize(z);
	s4.resize(z);
	s5.resize(z);
	s6.resize(z);
	s7.resize(z);
	s8.resize(z);
	s9.resize(z);
	s10.resize(z);

	for(int i = 0; i < z; i++) {
		s1[i].assign(z, 0);
		s2[i].assign(z, 0);
		s3[i].assign(z, 0);
		s4[i].assign(z, 0);
		s5[i].assign(z, 0);
		s6[i].assign(z, 0);
		s7[i].assign(z, 0);
		s8[i].assign(z, 0);
		s9[i].assign(z, 0);
		s10[i].assign(z, 0);
	}
}

void operation(vector<vector<int>> &matrix_r, vector<vector<int>> &matrix_1, vector<vector<int>> &matrix_2, int i1_inicial, int j1_inicial, int i2_inicial, int j2_inicial, int option, int z) {
	if(option == 0) { // faz a soma da matriz 1 com a matriz 2
		for(int i = 0; i < z; i++) {
			for(int j = 0; j < z; j++) {
				matrix_r[i][j] = matrix_1[i1_inicial + i][j1_inicial + j] + matrix_2[i2_inicial + i][j2_inicial + j]; 
			}
		}
	}
	else { // faz a subtração da matriz 1 com a matriz 2
		for(int i = 0; i < z; i++) {
			for(int j = 0; j < z; j++) {
				matrix_r[i][j] = matrix_1[i1_inicial + i][j1_inicial + j] - matrix_2[i2_inicial + i][j2_inicial + j]; 
			}
		}
	}
}

int strassen(vector<vector<int>> &A, vector<vector<int>> &B, int i_inicial, int j_inicial, int z) {
	if(z == 1) {
		return A[i_inicial][j_inicial] * B[i_inicial][j_inicial];
	}
	else {
		z /= 2;
		vector<vector<int>> s1, s2, s3, s4, s5, s6, s7, s8, s9, s10;
		create_all_matrices(s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, z);
		operation(s1, B, B, i_inicial, z / 2, z / 2, z / 2, 1, z);
		operation(s2, A, A, i_inicial, j_inicial, i_inicial, z / 2, 0, z); 
		operation(s3, A, A, z / 2, j_inicial, z / 2, z / 2, 0, z); 
		operation(s4, B, B, z / 2, j_inicial, i_inicial, j_inicial, 1, z);
		operation(s5, A, A, i_inicial, j_inicial, z / 2, z / 2, 0, z);
		operation(s6, B, B, i_inicial, j_inicial, z / 2, z / 2, 0, z);
		operation(s7, A, A, i_inicial, z / 2, z / 2, z / 2, 1, z);
		operation(s8, B, B, z / 2, j_inicial, z / 2, z / 2, 0, z);
		operation(s9, A, A, i_inicial, j_inicial, z / 2, j_inicial, 1, z);
		operation(s10, B, B, i_inicial, j_inicial, i_inicial, z / 2, 0, z);

		int p1 = strassen(A, s1, i_inicial, j_inicial, z);
		int p2 = strassen(s2, B, z / 2, z / 2, z);
		int p3 = strassen(s3, B, i_inicial, j_inicial, z);
		int p4 = strassen(A, s4, z / 2, z / 2, z);
		int p5 = strassen(s5, s6, i_inicial, j_inicial, z);
		int p6 = strassen(s7, s8, i_inicial, j_inicial, z);
		int p7 = strassen(s9, s10, i_inicial, j_inicial, z);

		C[i_inicial][j_inicial] = p5 + p4 - p2 + p6;
		C[i_inicial][z / 2] = p1 + p2;
		C[z / 2][j_inicial] = p3 + p4;
		C[z / 2][z / 2] = p5 + p1 - p3 - p7;
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
	strassen(A, B, 0, 0, z);

	for(int i = 0; i < z; i++) {
		for(int j = 0; j < z; j++) {
			cout << C[i][j] << " ";
		}
		cout << "\n";
	}

	return 0;
}
