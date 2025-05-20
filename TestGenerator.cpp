#include "TestGenerator.hpp"

#include "AVLTree.hpp"
#include "AVLTreeHashTable.hpp"
#include "CuckooHashTable.hpp"

void generateTests() {
    std::ofstream file;
    file.open("./data.txt", std::ios::out | std::ios::trunc);

    if (!file.is_open()) {
        std::cout << "Plik nie moze zostac otworzony" << std::endl;
        return;
    }

    std::cout << "Generowanie testow\n";

    int sizes[8] = {5000, 8000, 10000, 16000, 20000, 40000, 60000, 100000};
    std::vector<std::string> operacje = {"insert", "remove"};

    file << "rozmiar,operacja,avl_tree_avg,cuckoo_avg\n";

    for (int i = 0; i < 8; i++) {
        int size = sizes[i];
        for (const auto& operacja : operacje) {
            long long totalAvlTreeTime = 0;
            long long totalCuckooTime = 0;

            // ilosc testow na jedna operacje
            for (int j = 0; j < 100; j++) {
                // Ustawiamy inny seed dla każdego przypadku
                srand(time(nullptr) + j);

                AVLTreeHashTable<int> avl_tree(16);
                CuckooHashTable<int> cuckoo(16);

                // Inicjalizacja list
                int *keyArray = new int[size];
                int *valueArray = new int[size];

                fillArray(keyArray, valueArray, size);

                arrayToList(size, keyArray, valueArray, [&](int k, int v) { avl_tree.insert(k, v); });
                arrayToList(size, keyArray, valueArray, [&](int k, int v) { cuckoo.insert(k, v); });

                int rKey = rand() % 1001;
                int rValue = rand() % 10001;

                // AVL Tree
                long long durationAvl;
                if (operacja == "insert") {
                    durationAvl = measureTime([&]() { avl_tree.insert(rKey, rValue); });
                } else if (operacja == "remove") {
                    durationAvl = measureTime([&]() { avl_tree.remove(rKey); });
                } else {
                    durationAvl = 0;
                }
                totalAvlTreeTime += durationAvl;

                // Cuckoo
                long long durationCuckoo;
                if (operacja == "insert") {
                    durationCuckoo = measureTime([&]() { cuckoo.insert(rKey, rValue); });
                } else if (operacja == "remove") {
                    durationCuckoo = measureTime([&]() { cuckoo.remove(rKey); });
                } else {
                    durationCuckoo = 0;
                }
                totalCuckooTime += durationCuckoo;

                delete [] keyArray;
                delete [] valueArray;
            }
            long long avgAvlTime = totalAvlTreeTime / 100;
            long long avgCuckooTime = totalCuckooTime / 100;

            file << size << "," << operacja << "," << avgAvlTime << "," << avgCuckooTime << "\n";
            std::cout << "Zakonczono testy dla operacji " << operacja << " na rozmiarze " << size << std::endl;
            std::cout << "  Sredni czas dla avl tree: " << avgAvlTime << " ns" << std::endl;
            std::cout << "  Sredni czas dla cuckoo hash table: " << avgCuckooTime << " ns" << std::endl;
        }
    }

    file.close();
    std::cout << "Wyniki zapisano do pliku data.txt" << std::endl;
}
