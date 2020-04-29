#pragma once

#include "bellman_ford_alg.hpp"

template <typename T>
void test(int(&v_arr)[5], double(&d_arr)[4], std::ofstream& output_times, int loops) {
	int starting_v;
	double sum_of_results, avg_time;
	
	for (double dens : d_arr) {					// dla ka¿dej danej gêstoœci grafu
		sum_of_results = 0;
		for (int verts : v_arr) {				// dla ka¿dej danej iloœci wierzcho³ków
			for (int i = 0; i < loops; i++) {	// dla ka¿dej iteracji danej kombinacji gêstoœci i iloœci wierzcho³ków
				std::shared_ptr<T> graph = std::make_shared<T>(verts, dens);
				
				starting_v = rand() % verts;	// wylosuj wierzcho³ek pocz¹tkowy
				graph->fillG();					// wype³nij graf w sposób losowy
				sum_of_results += bellman_ford(std::move(graph), starting_v, false);	// zliczaj czasy zakoñczenia pracy algorytmu
			}
			std::cout << "WIERZCHOLKI: " << verts << " KONIEC!" << std::endl;			// wyœwietl komunikat oznajmiaj¹cy zakoñczenie testu
		}																				// dla danej liczby wierzcho³ków
		avg_time = sum_of_results / loops;		// policz œredni¹

		output_times << "GESTOSC = " << dens << std::endl;
		output_times << "SREDNI CZAS: " << avg_time << " milisekund\n\n";				// zapisz wyniki w pliku

		std::cout << std::endl << "GESTOSC: " << dens << " KONIEC!" << std::endl;		// wyœwietl komunikat oznajmiaj¹cy zakoñczenie testu dla danej gêstoœci
	}
}

template <typename T>
void file_graph(std::ifstream& input_file) {
	std::shared_ptr<T> graph = std::make_shared<T>();
	bellman_ford(std::move(graph), graph->read_file(input_file), true);
}