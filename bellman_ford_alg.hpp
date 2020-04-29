#pragma once

#include "adjacency_list.hpp"
#include "adjacency_matrix.hpp"

static int infinity = 2147483647;				// maksymalna warto�� symbolizuj�ca niesko�czono��
static std::string ofilename = "output.txt";	// nazwa pliku, do kt�rego zapisany zostanie wynik dzia�ania algorytmu
												// znalezienia najkr�tszej drogi od podanego wierzcho�ka do pozosta�ych
double bellman_ford(std::shared_ptr<MatrixGraph> bf_graph, int bf_starting_vert, bool in_from_file);
double bellman_ford(std::shared_ptr<ListGraph> bf_graph, int bf_starting_vert, bool in_from_file);