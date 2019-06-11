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

void create_matrix(vector<vector<int>> &partial_matrix, vector<vector<int>> &matrix, int i, int j, int z) {
	partial_matrix.resize(z);

	for(int aux = 0; aux < z; aux++) {
		partial_matrix[aux].resize(z);
	}

	for(int a = 0; a < z; a++) {
		for(int b = 0; b < z; b++) {
			partial_matrix[a][b] = matrix[a + i][b + j];
		}
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

void operation(vector<vector<int>> &matrix_r, vector<vector<int>> &matrix_1, vector<vector<int>> &matrix_2, int option, int z) {
	if(option == 0) { // faz a soma da matriz 1 com a matriz 2
		for(int i = 0; i < z; i++) {
			for(int j = 0; j < z; j++) {
				matrix_r[i][j] = matrix_1[i][j] + matrix_2[i][j]; 
			}
		}
	}
	else { // faz a subtração da matriz 1 com a matriz 2
		for(int i = 0; i < z; i++) {
			for(int j = 0; j < z; j++) {
				matrix_r[i][j] = matrix_1[i][j] - matrix_2[i][j]; 
			}
		}
	}
}

vector<vector<int>> strassen(vector<vector<int>> &A, vector<vector<int>> &B, int z) {
	if(z == 1) {
		vector<vector<int>> result;
		result.resize(1);
		result[0].resize(1);
		result[0][0] = A[0][0] * B[0][0];
		return result;
	}
	else {
		z /= 2;
		vector<vector<int>> A11, A12, A21, A22, B11, B12, B21, B22;
		create_matrix(A11, A, 0, 0, z);
		create_matrix(A12, A, 0, z, z);
		create_matrix(A21, A, z, 0, z);
		create_matrix(A22, A, z, z, z);
		create_matrix(B11, B, 0, 0, z);
		create_matrix(B12, B, 0, z, z);
		create_matrix(B21, B, z, 0, z);
		create_matrix(B22, B, z, z, z);

		vector<vector<int>> s1, s2, s3, s4, s5, s6, s7, s8, s9, s10;
		create_all_matrices(s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, z);
		operation(s1, B12, B22, 1, z);
		operation(s2, A11, A12, 0, z); 
		operation(s3, A21, A22, 0, z); 
		operation(s4, B21, B11, 1, z);
		operation(s5, A11, A22, 0, z);
		operation(s6, B11, B22, 0, z);
		operation(s7, A12, A22, 1, z);
		operation(s8, B21, B22, 0, z);
		operation(s9, A11, A21, 1, z);
		operation(s10, B11, B12, 0, z);

		vector<vector<int>> p1 = strassen(A11, s1, z);
		vector<vector<int>> p2 = strassen(s2, B22, z);
		vector<vector<int>> p3 = strassen(s3, B11, z);
		vector<vector<int>> p4 = strassen(A22, s4, z);
		vector<vector<int>> p5 = strassen(s5, s6, z);
		vector<vector<int>> p6 = strassen(s7, s8, z);
		vector<vector<int>> p7 = strassen(s9, s10, z);

		//cout << "entrou" << "\n";
		for(int i = 0; i < z; i++) {
			for(int j = 0; j < z; j++) {
				C[i][j] = p5[i][j] + p4[i][j] - p2[i][j] + p6[i][j];
				C[i][z + j] = p1[i][j] + p2[i][j];
				C[z + i][j] = p3[i][j] + p4[i][j];
				C[z + i][z + j] = p5[i][j] + p1[i][j] - p3[i][j] - p7[i][j];
			}
		}
		
		return C;
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
	C = strassen(A, B, z);

	for(int i = 0; i < N1; i++) {
		for(int j = 0; j < M2; j++) {
			cout << C[i][j] << " ";
		}
		cout << "\n";
	}

	return 0;
}
