#pragma once

#include "graph.hpp"

class MatrixGraph : public Graph {

	std::unique_ptr<std::unique_ptr<int[]>[]> matrix;		// dynamiczna tablica dwuwymiarowa reprezentuj¹ca macierz

public:

	void fillG() const override;							// wype³nia graf losowymi krawedziami i wagami
	const int read_file(std::ifstream& file) override;		// tworzy graf na podstawie wczytanych danych
	void displayG() const override;

	const int& get_weight(int row, int col) const { return matrix[row][col]; }

	MatrixGraph(int verts, double den);
	MatrixGraph() :Graph() {};
};