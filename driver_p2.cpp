#include "test_function.hpp"

int main()
{
    srand(static_cast<unsigned int>(time(NULL)));
    std::cout << "DRIVER POKAZUJACY DZIALANIE METOD GRAFOW I ALGORYTMOW\n";
    std::cout << "PREZENTACJA ZOSTANIE WYKONANA NA GRAFIE PELNYM O 3 WIERZCHOLKACH\n";
    std::cout << "1. REPREZENTACJA ZA POMOCA MACIERZY SASIEDZTWA\n";

    std::unique_ptr<MatrixGraph> g1 = std::make_unique<MatrixGraph>(3, 1);

    std::cout << "Pobieranie liczby wierzcholkow i krawedzi (metody 'get_v' i 'get_e')\n";;
    std::cout << "W = " << g1->get_v() << ", K = " << g1->get_e() << std::endl <<std::endl;
    std::cout << "Wypelnienie grafu w sposob losowy metoda 'fillG'\n";

    g1->fillG();
    g1->displayG();

    std::cout << "Pobranie wagi krawedzi pomiedzy dwoma wierzcholkami (w tym przypadku pomiedzy wierzcholkami 1 i 2) metoda 'get_weight'\n";
    std::cout << "Waga: " << g1->get_weight(1, 2) << std::endl <<std::endl;
    std::cout << "Pobranie danych z pliku 'in.txt' i wygenerowanie na ich podstawie grafu metoda 'read_file'\n";
    std::cout << "Dane w pliku:\n";
    
    g1 = std::make_unique<MatrixGraph>();
    
    std::ifstream file;
    file.open("in.txt");
    g1->read_file(file);
    file.close();
    file.open("in.txt");

    std::cout << file.rdbuf() << std::endl << "Graf:\n";

    g1->displayG();
    file.close();

    std::cout << "2. REPREZENTACJA ZA POMOCA LISTY SASIEDZTWA\n";

    std::shared_ptr<ListGraph> g2 = std::make_shared<ListGraph>(3, 1);

    std::cout << "Wypelnienie grafu w sposob losowy metoda 'fillG'\n";

    g2->fillG();
    g2->displayG();

    std::cout << "Pobranie danych z pliku 'in.txt' i wygenerowanie na ich podstawie grafu metoda 'read_file'\n";
    std::cout << "Dane w pliku:\n";

    file.open("in.txt");
    g2->read_file(file);
    file.close();
    file.open("in.txt");

    std::cout << file.rdbuf() << std::endl << "Graf:\n";

    g2->displayG();
    file.close();

    std::cout << "Sprawdzenie czy istenieje polaczenie pomiedzy dwoma wierzcholkami (tutaj 0 i 1) metoda 'fillG'\n";
    std::cout << "Polaczenie pomiedzy wierzcholkami 0 i 1 istnieje: ";
    if (g2->check_edge(0, 1)) std::cout << "TAK\n\n";
    else std::cout << "NIE\n\n";

    std::cout << "3. ALGORYTM BELLMANA-FORDA\n";
    std::cout << "Uruchomienie algorytmu dla ostanio wyswietlonego grafu (przyjmujac, ze wierzcholkiem poczatkowym jest wierzcholek 0)\n";
    
    bellman_ford(std::move(g2), 0, true);
    file.open("output.txt");

    std::cout << "Wyniki zapisane w pliku 'output.txt':\n";
    std::cout << file.rdbuf();
    std::cout << "Koniec pracy drivera.\n";
    
    file.close();
}