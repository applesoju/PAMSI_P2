#include "bellman_ford_alg.hpp"

void display_arr(int* arr, int n) {			// funkcja pomocnicza do sprawdzania poprawnoœci dzia³ania algorytmu
	for (int i = 0; i < n; i++) {
		std::cout << i << " >>>> " << arr[i] << std::endl;
	}
}

double bellman_ford(std::shared_ptr<MatrixGraph> bf_graph, int bf_starting_vert, bool in_from_file) {
	auto clock_start = std::chrono::high_resolution_clock::now();		// pobierz czas przez rozpoczêciem dzia³ania algorytmu

	int beg, end, wgt;
	int verts = bf_graph->get_v();
	int* distance_arr = new int[verts];				// tablica, w której przechowywane bêd¹ dystanse
	int* predecessor_arr = new int[verts];			// tablica, w której przechowywane bêd¹ wierzcho³ki miêdzy wierzcho³kiem startowym, a koñcowym

	for (int i = 0; i < verts; i++) {				// zainicjuj tablicê dystanów najwiêksz¹ mozliw¹
		distance_arr[i] = infinity;					// wartoœci¹ ("infinity") i tablicê poprzedników 
		predecessor_arr[i] = 0;						// zerami
	}

	distance_arr[bf_starting_vert] = 0;				// ustaw odleg³oœæ startowego wierzcho³ka od samego siebie jako 0

	for (int i = 1; i < verts; i++) {				// rozluŸnienie krawêdzi od 1 do verts-1
		for (int j = 0; j < verts; j++) {			// dla ka¿dego wiersza macierzy
			for (int k = 0; k < verts; k++) {		// dla ka¿dej kolumny macierzy
				beg = j;							// pobierz pocz¹tkowy wierzcho³ek
				end = k;							// pobierz koñcowy wierzcho³ek
				wgt = bf_graph->get_weight(j, k);	// pobierz wagê krawêdzi

				if (distance_arr[beg] != infinity && distance_arr[end] > distance_arr[beg] + wgt && wgt != infinity) {		// jeœli znaleziona œcie¿ka jest krótsza i waga nie jest równa 'infinity'
					distance_arr[end] = distance_arr[beg] + wgt;		// zapisz now¹ œcie¿kê
					if(in_from_file)									// jeœli graf zosta³ zadany z pliku, czyli jeœli chcemy rozwi¹zanie zapisaæ w pliku		
						predecessor_arr[end] = beg;						// wstaw poprzednika do przechowania w tablicy
				}
			}
		}
	}

	auto clock_stop = std::chrono::high_resolution_clock::now();		// pobierz czas po zakoñczeniu algorytmu
	
	if (in_from_file) {					// jeœli dane zosta³y pobrane z pliku
		std::ofstream file;
		int tmp, j;

		file.open(ofilename);			// otwórz plik o danej nazwie

		if (!file.is_open()) {
			std::cerr << "WYSTAPIL BLAD PRZY PROBIE OTWARCIA PLIKU";
			return -1;
		}

		file << "Najkrotsza droga z wierzcholka nr " << bf_starting_vert << " |\n" << std::string(36, '-') << "|" << std::endl;

		for (int i = 0; i < verts; i++) {			// sprawdŸ drogê do ka¿dego wierzcho³ka
			if (i == bf_starting_vert) continue;	// poza wierzcho³kiem startowym

			int* store = new int[verts - 1];		// tymczasowa tablica do zapisu drogi
			j = 0;

			file << "Do wierzcholka nr " << i << " -> ";

			if (distance_arr[i] == infinity) file << "nieskonczonosc" << std::endl << "Wierzcholki nie sa polaczone\n";
			else {
				file << distance_arr[i] << std::endl;
				store[j++] = i;
				tmp = i;

				file << "Droga: " << bf_starting_vert;

				while (predecessor_arr[tmp] != bf_starting_vert) {
					tmp = predecessor_arr[tmp];		// sprawdzaj kolejnych poprzedników a¿ do wierzcho³ka pocz¹tkowego
					store[j++] = tmp;				// zapisuj kolejnych poprzedników
				}

				for (int k = j - 1; k >= 0; k--)	// wypisz poprzedników w odwrotnej kolejnoœci
					file << " ----> " << store[k];	// aby odtworzyæ drogê do konkretnego wierzcho³ka
				file << std::endl << std::endl;
			}
			delete[] store;
		}

		file.close();
	}

	delete[] distance_arr;
	delete[] predecessor_arr;

	return std::chrono::duration<double, std::milli>(clock_stop - clock_start).count();		// zwróæ czas w jakim algorytm zakoñczy³ dzia³anie, w milisekundach
}

double bellman_ford(std::shared_ptr<ListGraph> bf_graph, int bf_starting_vert, bool in_from_file) {
	auto clock_start = std::chrono::high_resolution_clock::now();		// pobierz czas przez rozpoczêciem dzia³ania algorytmu

	int beg, end, wgt;
	int verts = bf_graph->get_v();
	int edges = bf_graph->get_e();
	int* distance_arr = new int[verts];				// tablica, w której przechowywane bêd¹ dystanse
	int* predecessor_arr = new int[verts];			// tablica, w której przechowywane bêd¹ wierzcho³ki miêdzy wierzcho³kiem startowym, a koñcowym

	for (int i = 0; i < verts; i++) {				// zainicjuj tablicê dystanów najwiêksz¹ mozliw¹
		distance_arr[i] = infinity;					// wartoœci¹ ("infinity") i tablicê poprzedników 
		predecessor_arr[i] = 0;						// zerami
	}

	distance_arr[bf_starting_vert] = 0;					// ustaw odleg³oœæ startowego wierzcho³ka od samego siebie jako 0

	for (int i = 1; i < verts; i++) {					// rozluŸnienie krawêdzi od 1 do verts-1
		for (int j = 0; j < edges; j++) {				// dla wszystkich krawêdzi
			beg = bf_graph->get_edges()[j].source;		// pobierz pocz¹tkowy wierzcho³ek
			end = bf_graph->get_edges()[j].destination;	// pobierz koncowy wierzcho³ek
			wgt = bf_graph->get_edges()[j].weight;		// pobierz wagê krawêdzi

			if (distance_arr[beg] != infinity && distance_arr[end] > distance_arr[beg] + wgt) {		// jeœli znaleziona œcie¿ka jest krótsza
				distance_arr[end] = distance_arr[beg] + wgt;

				if (in_from_file)									// jeœli graf zosta³ zadany z pliku, czyli jeœli chcemy rozwi¹zanie zapisaæ w pliku		
					predecessor_arr[end] = beg;						// wstaw poprzednika do przechowania w tablicy
			}
		}
	}

	auto clock_stop = std::chrono::high_resolution_clock::now();	// pobierz czas po zakoñczeniu algorytmu

	if (in_from_file) {					// jeœli dane zosta³y pobrane z pliku
		std::ofstream file;
		int tmp, j;

		file.open(ofilename);			// otwórz plik o danej nazwie

		if (!file.is_open()) {
			std::cerr << "WYSTAPIL BLAD PRZY PROBIE OTWARCIA PLIKU";
			return -1;
		}

		file << "Najkrotsza droga z wierzcholka nr " << bf_starting_vert << " |\n" << std::string(36, '-') << "|" << std::endl;

		for (int i = 0; i < verts; i++) {			// sprawdŸ drogê do ka¿dego wierzcho³ka
			if (i == bf_starting_vert) continue;	// poza wierzcho³kiem startowym

			int* store = new int[verts - 1];		// tymczasowa tablica do zapisu drogi
			j = 0;

			file << "Do wierzcholka nr " << i << " -> ";

			if (distance_arr[i] == infinity) file << "nieskonczonosc" << std::endl << "Wierzcholki nie sa polaczone\n";
			else {
				file << distance_arr[i] << std::endl;
				store[j++] = i;
				tmp = i;

				file << "Droga: " << bf_starting_vert;

				while (predecessor_arr[tmp] != bf_starting_vert) {
					tmp = predecessor_arr[tmp];		// sprawdzaj kolejnych poprzedników a¿ do wierzcho³ka pocz¹tkowego
					store[j++] = tmp;				// zapisuj kolejnych poprzedników
				}

				for (int k = j - 1; k >= 0; k--)	// wypisz poprzedników w odwrotnej kolejnoœci
					file << " ----> " << store[k];	// aby odtworzyæ drogê do konkretnego wierzcho³ka
				file << std::endl << std::endl;
			}
			delete[] store;
		}

		file.close();
	}

	delete[] distance_arr;
	delete[] predecessor_arr;

	return std::chrono::duration<double, std::milli>(clock_stop - clock_start).count();		// zwróæ czas w jakim algorytm zakoñczy³ dzia³anie, w milisekundach
}