#include "adjacency_matrix.hpp"

static int infinity = 2147483647;			// maksymalna warto�� zmiennej typu int

MatrixGraph::MatrixGraph(int verts, double den) {
	g_v = verts;
	g_e = static_cast<int>(den * verts * (verts - 1));				// ze wzoru na g�sto�� grafu
	g_d = den;
	matrix = std::make_unique<std::unique_ptr<int[]>[]>(verts);

	for (int i = 0; i < verts; i++) {
		matrix[i] = std::make_unique<int[]>(verts);

		for (int j = 0; j < verts; j++) {
			if (i != j) matrix[i][j] = infinity;	// zainicjalizuj wszystko warto�ci� "infinity"
			else matrix[i][j] = 0;					// poza kom�rkami na przek�tnej macierzy
		}
	}
}

void MatrixGraph::fillG() const {
	if (g_d == 1) {									// przypadek grafu pe�nego
		for(int i = 0; i < g_v; i++) {				// dla ka�dego wiersza macierzy
			for (int j = 0; j < g_v; j++) {			// dla ka�dej kolumny macierzy
				int new_weight = rand() % 12 + 1;	// wylosuj wag� z przedzia�u od 1 do 12
				matrix[i][j] = new_weight;			// przypisz now� wag� aktualnej kom�rce
			}
		}
	}
	else {									// pozosta�e przypadki g�sto�ci grafu
		int row_vert, col_vert;
		int num_of_edges = g_e;

		while (num_of_edges) {
			row_vert = rand() % g_v;		// losowy wyb�r wierzcho�k�w pomi�dzy kt�rymi
			col_vert = rand() % g_v;		// stworzona zostanie kraw�d�

			if (matrix[row_vert][col_vert] == infinity || matrix[row_vert][col_vert] == 0) {	// je�li w danej kom�rce znajduje si� 0 lub "infinity"
				int new_weight = rand() % 12 + 1;			// wylosuj now� wag� z przedzia�u od 1 do 12
				matrix[row_vert][col_vert] = new_weight;	// i przypisz j� danej kom�rce
				num_of_edges--;								// odlicz stworzon� kraw�d� od zadanej liczby kraw�dzi
			}
		}
	}
}

const int MatrixGraph::read_file(std::ifstream& file) {
	int starting_vert, src, dest, weight;

	file >> g_e >> g_v >> starting_vert;			// pobierz liczbe krawedzi, wierzcholkow i wierzcholek poczatkowy
	matrix = std::make_unique<std::unique_ptr<int[]>[]>(g_v);

	for (int i = 0; i < g_v; i++) {
		matrix[i] = std::move(std::make_unique<int[]>(g_v));

		for (int j = 0; j < g_v; j++) {
			if (i != j) matrix[i][j] = infinity;	// zainicjalizuj wszystko warto�ci� "infinity"
			else matrix[i][j] = 0;					// poza kom�rkami na przek�tnej macierzy
		}
	}

	for (int i = 0; i < g_e; i++) {
		file >> src >> dest >> weight;				// pobierz kolejne wiersze z pliku
		matrix[src][dest] = weight;					// zapisz dane polaczenie w macierzy
	}

	file.close();
	return starting_vert;							
}

void MatrixGraph::displayG() const {
	for (int i = 0; i < g_v; i++) {
		for (int j = 0; j < g_v; j++) {
			int w = get_weight(i, j);
			if (w != infinity && w != 0) {
				std::cout << i;
				if(w < 10) std::cout << "--[" << w << "]-->" << j << std::endl;
				else std::cout << "--[" << w << "]->" << j << std::endl;
			}
		}
		std::cout << std::endl;
	}
}