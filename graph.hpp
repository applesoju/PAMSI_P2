#pragma once

#include <iostream>
#include <memory>
#include <fstream>
#include <chrono>

class Graph {			// podstawowa klasa "Graph", z kt�rej dziedziczy� b�d� klasy graf�w konkretnych typ�w
protected:

	int g_v, g_e;		// liczba wierzcho�k�w i kraw�dzi
	double g_d;			// g�sto�� grafu

public:

	const int& get_v() const { return g_v; }
	const int& get_e() const { return g_e; }

	virtual void fillG() const = 0;							// wype�nia graf w spos�b losowy
	virtual const int read_file(std::ifstream& file) = 0;	// wype�nia graf bazuj�c na pliku wej�ciowym
	virtual void displayG() const = 0;						// wy�wietlenie grafu na potrzeby drivera

	virtual ~Graph() {};
	Graph(int in_v, int in_e, double in_d) :g_v(in_v), g_e(in_e), g_d(in_d) {}
	Graph() {};
};