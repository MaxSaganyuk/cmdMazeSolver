#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include <Windows.h>

using namespace std;

bool canExit(int** matrix, int*& path, int N, int M) {

	enum Ways {
		RIGHT,
		DOWN,
		LEFT,
		UP
	};

	int n = 0;
	int k = 0;

	int count = 0;
	bool** bool_matrix;
	bool_matrix = new bool* [N];
	for (int i = 0; i < M; i++) bool_matrix[i] = new bool[N];


	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			bool_matrix[i][j] = false;
		}
	}

	bool search = true;
	bool found = false;

	bool path_found = false;

	while (search) {
		bool_matrix[n][k] = true;
		path_found = false;
		
		if (n == N - 1 && k == M - 1) {
			search = false;
			found = true;
		}
		else if (k + 1 < M && !matrix[n][k + 1] && !bool_matrix[n][k + 1]) {
			k++;
			path[count++] = RIGHT;
		}
		else if (n + 1 < N && !matrix[n + 1][k] && !bool_matrix[n + 1][k]) {
			n++;
			path[count++] = DOWN;
		}
		else if (k - 1 > 0 && !matrix[n][k - 1] && !bool_matrix[n][k - 1]) {
			k--;
			path[count++] = LEFT;
		}
		else if (n - 1 > 0 && !matrix[n - 1][k] && !bool_matrix[n - 1][k]) {
			n--;
			path[count++] = UP;
		}
		else {
			if (n == 0 && k == 0) search = false;
			else {
				if (path[count - 1] == RIGHT) k--;
				else if (path[count - 1] == LEFT) k++;
				else if (path[count - 1] == DOWN) n--;
				else if (path[count - 1] == UP) n++;
				path[count--] = -1;
			}
		}	
	}

	return found;
}

int** set_start_and_end(int** matrix, int N, int M) {
	matrix[0][0] = 0;
	matrix[N - 1][M - 1] = 0;

	return matrix;
}

int** randMatrix(int N, int M) {
	int** matrix;
	matrix = new int* [N];
	for (int i = 0; i < M; i++) matrix[i] = new int[N];

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			matrix[i][j] = rand() % 2;
		}
	}

	return matrix;
}

int** getMatrixFromFile(int& Nres, int& Mres) {
	ifstream file("matrix.txt");
	char thechar;

	bool correctFile = true;

	int N = 0;
	int M = 0;

	int** matrix;

	while (!file.eof()) {
		file.get(thechar);
		if (thechar == '0' || thechar == '1') ++N;
		else if (thechar == ' ') continue;
		else if (thechar == '\n') ++M;
		else {
			correctFile = false;
			break;
		}
	}
	file.close();

	++M;
	N /= M;

	if (!correctFile) {
		cout << "Incorrent File" << endl;
		exit(1);
	}

	matrix = new int*[N];
	for (int i = 0; i < M; i++) matrix[i] = new int[N];

	int i = 0;
	int j = 0;

	file.open("matrix.txt");
	while (!file.eof()) {
		file.get(thechar);
		if (thechar == '0' || thechar == '1') {
			matrix[i][j] = thechar - '0';
			++j;
		}
		else if (thechar == ' ') continue;
		else if (thechar == '\n') {
			++i;
			j = 0;
		}
	}

	Nres = N;
	Mres = M;
	return matrix;
}

void printMatrix(int** matrix, int* path, int N, int M) {

	int direction[4][2] = {
		{ 0,  1},
		{ 1,  0},
		{ 0, -1},
		{-1,  0}
	};

	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	
	bool** realPath;
	realPath = new bool* [N];
	for (int i = 0; i < M; i++) realPath[i] = new bool[N];
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			realPath[i][j] = false;
		}
	}

	int currentPath[] = { 0, 0 };

	for (int i = 0; path[i] != -1; i++) {
		realPath[currentPath[0]][currentPath[1]] = true;

		for (int j = 0; j < 4; j++) {
			if (j == path[i]) {
				currentPath[0] += direction[j][0];
				currentPath[1] += direction[j][1];
				break;
			}
		}
	}
	realPath[0][0] = true;
	realPath[N - 1][M - 1] = true;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (realPath[i][j]) {
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
			}
			else SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
			cout << matrix[i][j] << ' ';
		}
		cout << endl;
	}
	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}

int main(int argc, char* argv[]) {
	srand(time(NULL));

	int N;
	int M;
	int give_true = 0;
	bool filed = false;

	int** matrix = nullptr;

	N = atoi(argv[1]);
	if (N == -1) {
		matrix = getMatrixFromFile(N, M);
		filed = true;
	}
	else {
		M = atoi(argv[2]);
		give_true = atoi(argv[3]);
	}

	int* path = new int[N * M];
	for (int i = 0; i < N * M; i++) path[i] = -1;

	bool res = false;

	do {
		if (!filed) {
			matrix = randMatrix(N, M);
			matrix = set_start_and_end(matrix, N, M);
		}
		res = canExit(matrix, path, N, M);
	} while (!res && give_true);

	printMatrix(matrix, path, N, M);
	cout << res << endl;
}