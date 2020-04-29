#include "adjacency_list.hpp"

ListGraph::ListGraph(int verts, double den) {
	g_v = verts;
	g_e = static_cast<int>(den * verts * (verts - 1));				// ze wzoru na gêstoœæ grafu
	g_d = den;
	edge_arr = new Edge[static_cast<int>(den * verts * (verts - 1))];
}

void ListGraph::add_edge(int src, int dest, int weight, int position) const {
	edge_arr[position].source = src;
	edge_arr[position].destination = dest;
	edge_arr[position].weight = weight;
}

bool ListGraph::check_edge(int src, int dest) const {
	for (int i = 0; i < g_e; i++)
		if (dest == edge_arr[i].destination && src == edge_arr[i].source) return true;
	return false;
}

void ListGraph::fillG() const {
	if (g_d == 1) {										// przypadek grafu pe³nego
		int pos = 0;

		for (int i = 0; i < g_v; i++) {					// dla ka¿dego wierzcho³ka, który jest Ÿród³em krawêdzi
			for (int j = 0; j < g_v; j++) {				// dla ka¿dego wierzcho³ka, który jest koñcem krawêdzi
				if (i != j) {							// jeœli dane po³¹czenie nie jest pêtl¹
					int new_weight = rand() % 12 + 1;	// wylosuj now¹ wagê z przedzia³u od 1 do 12
					add_edge(i, j, new_weight, pos++);	// dodaj krawêdŸ do listy i zwiêksz wartoœæ 'pos'
				}
			}
		}
	}
	else {									// pozosta³e przypadki gêstoœci grafu
		int pos = 0;

		while (pos < g_e) {					// dopóki liczba tworzonych krawêdzi jest mniejsza od zadanej liczby krawêdzi
			int new_src = rand() % g_v;		// wylosuj wierzcho³ek pocz¹tkowy
			int new_dest = rand() % g_v;	// wylosuj wierzcho³ek koñcowy

			if (!check_edge(new_src, new_dest)) {				// jeœli krawêdŸ nie istnieje
				int new_weight = rand() % 12 + 1;				// wylosuj now¹ wagê z przeszia³u od 1 do 12
				add_edge(new_src, new_dest, new_weight, pos++);	// dodaj krawêdŸ do listy i zwiêksz wartoœæ 'pos'
			}
		}
	}
}

const int ListGraph::read_file(std::ifstream& file) {
	int starting_vert, src, dest, weight;

	file >> g_e >> g_v >> starting_vert;				// pobierz liczbe krawedzi, wierzcholkow i wierzcholek poczatkowy
	edge_arr = new Edge[g_e];

	for (int i = 0; i < g_e; i++) {
		file >> src >> dest >> weight;					// pobierz kolejne wiersze z pliku
		add_edge(src, dest, weight, i);					// dodaj krawêdŸ do listy
	}
	file.close();
	return starting_vert;
}

void ListGraph::displayG() const {
	for (int i = 0; i < g_v; i++) {
		for (int j = 0; j < g_e; j++) {
			if (edge_arr[j].source == i) {
				int w = edge_arr[j].weight;
				std::cout << i;
				if(w < 10) std::cout << "--[" << edge_arr[j].weight << "]-->" << edge_arr[j].destination << std::endl;
				else std::cout << "--[" << edge_arr[j].weight << "]->" << edge_arr[j].destination << std::endl;
			}
		}
		std::cout << std::endl;
	}
}