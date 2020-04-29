#pragma once

#include "adjacency_list.hpp"
#include "adjacency_matrix.hpp"

static int infinity = 2147483647;				// maksymalna wartoœæ symbolizuj¹ca nieskoñczonoœæ
static std::string ofilename = "output.txt";	// nazwa pliku, do którego zapisany zostanie wynik dzia³ania algorytmu
												// znalezienia najkrótszej drogi od podanego wierzcho³ka do pozosta³ych
double bellman_ford(std::shared_ptr<MatrixGraph> bf_graph, int bf_starting_vert, bool in_from_file);
double bellman_ford(std::shared_ptr<ListGraph> bf_graph, int bf_starting_vert, bool in_from_file);