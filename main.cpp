#include "test_function.hpp"

int main()
{
	srand(static_cast<unsigned int>(time(NULL)));

	static std::string matofile = "output_times_mat.txt";	// nazwy plików, w których zapisane będą średnie czasy działania algorytmu
	static std::string listofile = "output_times_list.txt";
	static bool testy = true;								// stała wskazująca, czy przeprowadzane są testy efektywności
	static bool plik = true;								// stała wskazująca, czy mają zostać wczytane dane z pliku

	std::string ifilename;
	std::ofstream ofile;
	std::ifstream ifile;

	int choice;
	int n_loops = 100;										// liczba losowych instancji dla tej samej gęstości i ilości wierzchołków
	int vertices_arr[5] = { 20, 50, 100, 250, 500 };		// ilości wierzchołków
	double density_arr[4] = { 0.25 , 0.5, 0.75, 1 };		// gęstości grafów
	if(!testy) {											// jeśli nie są przeprowadzane testy
		n_loops = 1;										// zmień liczbę losowych instancji
		for (int i = 0; i < 5; i++)
			vertices_arr[i] = 4 + 4 * i;					// i ilości wierzchołków, aby przyspieszyć obliczenia
	}
	
	ofile.open(matofile, std::ofstream::out);

	if (!ofile.is_open()) {
		std::cerr << "BLAD PRZY OTWIERANIU PLIKU" << std::endl;
		return 1;
	}
	
	std::cout << "TEST MACIERZY SASIEDZTWA" << std::endl;
	test<MatrixGraph>(vertices_arr, density_arr, ofile, n_loops);
	ofile.close();

	ofile.open(listofile, std::ofstream::out);

	if (!ofile.is_open()) {
		std::cerr << "BLAD PRZY OTWIERANIU PLIKU" << std::endl;
		return 1;
	}

	std::cout << "TEST LISTY SASIEDZTWA" << std::endl;
	test<ListGraph>(vertices_arr, density_arr, ofile, n_loops);
	ofile.close();
	
	if (plik) {
		std::cout << "TEST WCZYTYWANIA DANYCH Z PLIKU" << std::endl;
		std::cout << "Podaj nazwe pliku, w ktorym znajduja sie dane" << std::endl;
		std::cin >> ifilename;

		ifile.open(ifilename);
		if (!ifile.is_open()) {
			std::cerr << "WYSTAPIL BLAD PODCZAS PROBY OTWARCIA PLIKU\n";
			return 1;
		}

		std::cout << "Podaj sposob reprezentacji grafu:\n";
		std::cout << "1. Macierz sasiedztwa\n";
		std::cout << "2. Lista sasiedztwa\n";
		std::cout << "Wybor: ";
		std::cin >> choice;
		std::cout << std::endl;

		switch (choice)
		{
		case 1:
			std::cout << "TEST GRAFU W FORMIE MACIERZY SASIEDZTWA\n";
			file_graph<MatrixGraph>(ifile);
			break;

		case 2:
			std::cout << "TEST GRAFU W FORMIE LISTY SASIEDZTWA\n";
			file_graph<ListGraph>(ifile);
			break;

		default:
			std::cerr << "PODANO NIEPOPRAWNA OPCJE\n";
			return 1;
		}
		std::cout << "KONIEC TESTU, WYNIKI ZNAJDUJA SIE W PLIKU \"" << ofilename << "\"\n";

		ifile.close();
	}
	return 0;
}