#pragma once

#include <iostream>
#include <memory>
#include <fstream>
#include <chrono>

class Graph {			// podstawowa klasa "Graph", z której dziedziczyæ bêd¹ klasy grafów konkretnych typów
protected:

	int g_v, g_e;		// liczba wierzcho³ków i krawêdzi
	double g_d;			// gêstoœæ grafu

public:

	const int& get_v() const { return g_v; }
	const int& get_e() const { return g_e; }

	virtual void fillG() const = 0;							// wype³nia graf w sposób losowy
	virtual const int read_file(std::ifstream& file) = 0;	// wype³nia graf bazuj¹c na pliku wejœciowym
	virtual void displayG() const = 0;						// wyœwietlenie grafu na potrzeby drivera

	virtual ~Graph() {};
	Graph(int in_v, int in_e, double in_d) :g_v(in_v), g_e(in_e), g_d(in_d) {}
	Graph() {};
};