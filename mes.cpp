// mes.cpp

// PRL 2024/2025 - Projekt c. 1
// MES - Minimum Extraction Sort
// Autor: Sofiia Kucherenko, xkucer0v

#include <iostream>
#include <fstream>
#include <vector>
#include <mpi.h>

using namespace std;

int main(int argc, char *argv[]) {
    int numprocs; // Celkovy pocet procesoru (2n - 1)
    int rank;     // ID tohoto konkretniho procesu (0 az 2n-2)

    // Inicializace MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Vypocet poctu listu (n) z celkoveho poctu procesoru
    int n = (numprocs + 1) / 2;

    // Urceni role tohoto procesu pomoci ranku
    bool is_root = (rank == 0);
    bool is_leaf = (rank >= n - 1);
    
    // Urceni indexu rodice a potomku (pro vnitrni uzly)
    int parent = (rank - 1) / 2;
    int left_child = 2 * rank + 1;
    int right_child = 2 * rank + 2;

    // Hodnota reprezentujici "prazdny uzel" (vstupni cisla jsou 0-255)
    const int EMPTY = 256; 
    int my_value = -1;

    // 1: Nacteni a distribuce dat
    if (is_root) {
        vector<int> numbers;
        fstream file("numbers", ios::in | ios::binary);
        if (file.is_open()) {
            unsigned char c;
            // Cteni po bajtech a pretypovani na int
            while (file.read((char*)&c, sizeof(c))) {
                numbers.push_back((int)c);
            }
            file.close();
        }

        // Vypis puvodni neserazene posloupnosti (oddeleno mezerou)
        for (size_t i = 0; i < numbers.size(); i++) {
            cout << numbers[i] << (i == numbers.size() - 1 ? "" : " ");
        }
        cout << endl;

        // Rozeslani cisel listum
        for (int i = 0; i < n; i++) {
            int target_rank = n - 1 + i;
            if (target_rank == 0) {
                // Specialni pripad pro n=1 (koren je zaroven jedinym listem)
                my_value = numbers[i];
            } else {
                MPI_Send(&numbers[i], 1, MPI_INT, target_rank, 0, MPI_COMM_WORLD);
            }
        }
    }

    // Pokud je proces list (a neni to koren pri n=1), prijme svou hodnotu od korene
    if (is_leaf && rank != 0) {
        MPI_Recv(&my_value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    // 2: Samotny algoritmus Minimum Extraction Sort   
    if (is_leaf) {
        // Logika listu
        if (n == 1) {
            // Kdyz je na vstupu jen jedno cislo, rovnou ho vypiseme a koncime
            cout << my_value << endl;
        } else {
            // List posila svou platnou hodnotu rodici
            MPI_Send(&my_value, 1, MPI_INT, parent, 0, MPI_COMM_WORLD);
            // List uz zadnou dalsi platnou hodnotu nema, posle tedy znacku EMPTY
            int empty_val = EMPTY;
            MPI_Send(&empty_val, 1, MPI_INT, parent, 0, MPI_COMM_WORLD);
        }
    } else {
        // Logika nelistoveho uzlu (vnitrni uzly a koren)
        int left_val, right_val;

        // Prvotni nacteni hodnot od obou potomku
        MPI_Recv(&left_val, 1, MPI_INT, left_child, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&right_val, 1, MPI_INT, right_child, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        while (true) {
            // Pokud uz nemame zadna platna cisla z obou vetvi, koncime s praci
            if (left_val == EMPTY && right_val == EMPTY) {
                if (!is_root) {
                    int send_val = EMPTY;
                    MPI_Send(&send_val, 1, MPI_INT, parent, 0, MPI_COMM_WORLD);
                }
                break; 
            }

            int min_val;
            int source_child;

            // Porovnani - vybirame mensi hodnotu
            if (left_val < right_val) {
                min_val = left_val;
                source_child = left_child;
            } else {
                min_val = right_val;
                source_child = right_child;
            }

            // Odeslani nebo vypis vitezne hodnoty
            if (is_root) {
                cout << min_val << endl;
            } else {
                MPI_Send(&min_val, 1, MPI_INT, parent, 0, MPI_COMM_WORLD);
            }

            // Zadost o novou hodnotu (nahradu) od toho potomka, jehoz hodnotu jsme prave spotrebovali
            if (source_child == left_child) {
                MPI_Recv(&left_val, 1, MPI_INT, left_child, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            } else {
                MPI_Recv(&right_val, 1, MPI_INT, right_child, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            }
        }
    }

    // Ukonceni MPI
    MPI_Finalize();
    return 0;
}