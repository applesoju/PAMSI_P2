#include "bellman_ford_alg.hpp"

void display_arr(int* arr, int n) {			// funkcja pomocnicza do sprawdzania poprawno�ci dzia�ania algorytmu
	for (int i = 0; i < n; i++) {
		std::cout << i << " >>>> " << arr[i] << std::endl;
	}
}

double bellman_ford(std::shared_ptr<MatrixGraph> bf_graph, int bf_starting_vert, bool in_from_file) {
	auto clock_start = std::chrono::high_resolution_clock::now();		// pobierz czas przez rozpocz�ciem dzia�ania algorytmu

	int beg, end, wgt;
	int verts = bf_graph->get_v();
	int* distance_arr = new int[verts];				// tablica, w kt�rej przechowywane b�d� dystanse
	int* predecessor_arr = new int[verts];			// tablica, w kt�rej przechowywane b�d� wierzcho�ki mi�dzy wierzcho�kiem startowym, a ko�cowym

	for (int i = 0; i < verts; i++) {				// zainicjuj tablic� dystan�w najwi�ksz� mozliw�
		distance_arr[i] = infinity;					// warto�ci� ("infinity") i tablic� poprzednik�w 
		predecessor_arr[i] = 0;						// zerami
	}

	distance_arr[bf_starting_vert] = 0;				// ustaw odleg�o�� startowego wierzcho�ka od samego siebie jako 0

	for (int i = 1; i < verts; i++) {				// rozlu�nienie kraw�dzi od 1 do verts-1
		for (int j = 0; j < verts; j++) {			// dla ka�dego wiersza macierzy
			for (int k = 0; k < verts; k++) {		// dla ka�dej kolumny macierzy
				beg = j;							// pobierz pocz�tkowy wierzcho�ek
				end = k;							// pobierz ko�cowy wierzcho�ek
				wgt = bf_graph->get_weight(j, k);	// pobierz wag� kraw�dzi

				if (distance_arr[beg] != infinity && distance_arr[end] > distance_arr[beg] + wgt && wgt != infinity) {		// je�li znaleziona �cie�ka jest kr�tsza i waga nie jest r�wna 'infinity'
					distance_arr[end] = distance_arr[beg] + wgt;		// zapisz now� �cie�k�
					if(in_from_file)									// je�li graf zosta� zadany z pliku, czyli je�li chcemy rozwi�zanie zapisa� w pliku		
						predecessor_arr[end] = beg;						// wstaw poprzednika do przechowania w tablicy
				}
			}
		}
	}

	auto clock_stop = std::chrono::high_resolution_clock::now();		// pobierz czas po zako�czeniu algorytmu
	
	if (in_from_file) {					// je�li dane zosta�y pobrane z pliku
		std::ofstream file;
		int tmp, j;

		file.open(ofilename);			// otw�rz plik o danej nazwie

		if (!file.is_open()) {
			std::cerr << "WYSTAPIL BLAD PRZY PROBIE OTWARCIA PLIKU";
			return -1;
		}

		file << "Najkrotsza droga z wierzcholka nr " << bf_starting_vert << " |\n" << std::string(36, '-') << "|" << std::endl;

		for (int i = 0; i < verts; i++) {			// sprawd� drog� do ka�dego wierzcho�ka
			if (i == bf_starting_vert) continue;	// poza wierzcho�kiem startowym

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
					tmp = predecessor_arr[tmp];		// sprawdzaj kolejnych poprzednik�w a� do wierzcho�ka pocz�tkowego
					store[j++] = tmp;				// zapisuj kolejnych poprzednik�w
				}

				for (int k = j - 1; k >= 0; k--)	// wypisz poprzednik�w w odwrotnej kolejno�ci
					file << " ----> " << store[k];	// aby odtworzy� drog� do konkretnego wierzcho�ka
				file << std::endl << std::endl;
			}
			delete[] store;
		}

		file.close();
	}

	delete[] distance_arr;
	delete[] predecessor_arr;

	return std::chrono::duration<double, std::milli>(clock_stop - clock_start).count();		// zwr�� czas w jakim algorytm zako�czy� dzia�anie, w milisekundach
}

double bellman_ford(std::shared_ptr<ListGraph> bf_graph, int bf_starting_vert, bool in_from_file) {
	auto clock_start = std::chrono::high_resolution_clock::now();		// pobierz czas przez rozpocz�ciem dzia�ania algorytmu

	int beg, end, wgt;
	int verts = bf_graph->get_v();
	int edges = bf_graph->get_e();
	int* distance_arr = new int[verts];				// tablica, w kt�rej przechowywane b�d� dystanse
	int* predecessor_arr = new int[verts];			// tablica, w kt�rej przechowywane b�d� wierzcho�ki mi�dzy wierzcho�kiem startowym, a ko�cowym

	for (int i = 0; i < verts; i++) {				// zainicjuj tablic� dystan�w najwi�ksz� mozliw�
		distance_arr[i] = infinity;					// warto�ci� ("infinity") i tablic� poprzednik�w 
		predecessor_arr[i] = 0;						// zerami
	}

	distance_arr[bf_starting_vert] = 0;					// ustaw odleg�o�� startowego wierzcho�ka od samego siebie jako 0

	for (int i = 1; i < verts; i++) {					// rozlu�nienie kraw�dzi od 1 do verts-1
		for (int j = 0; j < edges; j++) {				// dla wszystkich kraw�dzi
			beg = bf_graph->get_edges()[j].source;		// pobierz pocz�tkowy wierzcho�ek
			end = bf_graph->get_edges()[j].destination;	// pobierz koncowy wierzcho�ek
			wgt = bf_graph->get_edges()[j].weight;		// pobierz wag� kraw�dzi

			if (distance_arr[beg] != infinity && distance_arr[end] > distance_arr[beg] + wgt) {		// je�li znaleziona �cie�ka jest kr�tsza
				distance_arr[end] = distance_arr[beg] + wgt;

				if (in_from_file)									// je�li graf zosta� zadany z pliku, czyli je�li chcemy rozwi�zanie zapisa� w pliku		
					predecessor_arr[end] = beg;						// wstaw poprzednika do przechowania w tablicy
			}
		}
	}

	auto clock_stop = std::chrono::high_resolution_clock::now();	// pobierz czas po zako�czeniu algorytmu

	if (in_from_file) {					// je�li dane zosta�y pobrane z pliku
		std::ofstream file;
		int tmp, j;

		file.open(ofilename);			// otw�rz plik o danej nazwie

		if (!file.is_open()) {
			std::cerr << "WYSTAPIL BLAD PRZY PROBIE OTWARCIA PLIKU";
			return -1;
		}

		file << "Najkrotsza droga z wierzcholka nr " << bf_starting_vert << " |\n" << std::string(36, '-') << "|" << std::endl;

		for (int i = 0; i < verts; i++) {			// sprawd� drog� do ka�dego wierzcho�ka
			if (i == bf_starting_vert) continue;	// poza wierzcho�kiem startowym

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
					tmp = predecessor_arr[tmp];		// sprawdzaj kolejnych poprzednik�w a� do wierzcho�ka pocz�tkowego
					store[j++] = tmp;				// zapisuj kolejnych poprzednik�w
				}

				for (int k = j - 1; k >= 0; k--)	// wypisz poprzednik�w w odwrotnej kolejno�ci
					file << " ----> " << store[k];	// aby odtworzy� drog� do konkretnego wierzcho�ka
				file << std::endl << std::endl;
			}
			delete[] store;
		}

		file.close();
	}

	delete[] distance_arr;
	delete[] predecessor_arr;

	return std::chrono::duration<double, std::milli>(clock_stop - clock_start).count();		// zwr�� czas w jakim algorytm zako�czy� dzia�anie, w milisekundach
}