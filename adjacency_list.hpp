#pragma once

#include "graph.hpp"

struct Edge {							// struktura odpowiadaj¹ca krawêdzi pomiêdzy dwoma wierzcho³kami o konkretnej wadze
	int source, destination, weight;
};

class ListGraph : public Graph {

	Edge* edge_arr;

public:

	void fillG() const override;											// wype³nia graf losowymi krawedziami i wagami
	const int read_file(std::ifstream& file) override;						// tworzy graf na podstawie wczytanych danych
	void displayG() const override;

	void add_edge(int src, int dest, int weight, int position) const;		// dodaje krawêdŸ na pozycji "position"
	bool check_edge(int src, int dest) const;								// sprawdza, czy po³¹czenie miêdzy danymi wierzcho³kami istnieje

	const Edge* get_edges() const { return edge_arr; }

	ListGraph(int verts, double den);
	ListGraph() :Graph() {};
	~ListGraph() { delete[] edge_arr; }

};