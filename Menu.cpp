//
// Created by User on 14.04.2025.
//
#include "Menu.h"
#include <iostream>
#include <string>
#include "ArrayList.hpp"
#include "TestGenerator.hpp"
#include "HeapPriorityQueue.hpp"
#include "ArrayPriorityQueue.hpp"

void showMenu() {
    std::cout << "====== MENU ======\n";
    std::cout << "1. Uruchom testy dla wszystkich struktur\n";
    std::cout << "2. Operacje na kolejkach priorytetowych\n";
    std::cout << "3. Operacje na Array Priority Queue\n";
    std::cout << "0. Wyjscie\n";
    std::cout << "Wybierz opcje: ";
}

void showOperationMenu() {
    std::cout << "\n==== OPERACJE ====\n";
    std::cout << "1. push_back - dodaj element na koniec\n";
    std::cout << "2. push_front - dodaj element na poczatek\n";
    std::cout << "3. insert - dodaj element na wybrana pozycje\n";
    std::cout << "4. remove_back - usun element z konca\n";
    std::cout << "5. remove_front - usun element z poczatku\n";
    std::cout << "6. remove - usun element z wybranej pozycji\n";
    std::cout << "7. get - pobierz element z wybranej pozycji\n";
    std::cout << "8. count - wyswietl liczbe elementow\n";
    std::cout << "9. wyswietl wszystkie elementy\n";
    std::cout << "10. search - wyszukaj element\n";
    std::cout << "0. Powrot do menu glownego\n";
    std::cout << "Wybierz operacje: ";
}

void showPriorityQueueMenu() {
    std::cout << "\n==== OPERACJE NA KOLEJCE PRIORYTETOWEJ ====\n";
    std::cout << "1. insert - dodaj element o podanym priorytecie\n";
    std::cout << "2. extract_max - usun i zwroc element o najwiekszym priorytecie\n";
    std::cout << "3. find_max - zwroc element o najwiekszym priorytecie\n";
    std::cout << "4. modify_key - zmien priorytet elementu\n";
    std::cout << "5. return_size - wyswietl liczbe elementow\n";
    std::cout << "0. Powrot do menu glownego\n";
    std::cout << "Wybierz operacje: ";
}

template<class T>
void performListOperations(BaseList<T>& list, const std::string& listName) {
    int choice;
    int value, index;

    do {
        showOperationMenu();
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Podaj wartosc: ";
                std::cin >> value;
                list.push_back(value);
                std::cout << "Dodano " << value << " na koniec listy.\n";
                break;

            case 2:
                std::cout << "Podaj wartosc: ";
                std::cin >> value;
                list.push_front(value);
                std::cout << "Dodano " << value << " na poczatek listy.\n";
                break;

            case 3:
                std::cout << "Podaj wartosc: ";
                std::cin >> value;
                std::cout << "Podaj indeks: ";
                std::cin >> index;
                list.insert(value, index);
                std::cout << "Dodano " << value << " na pozycji " << index << ".\n";
                break;

            case 4:
                if (list.count() > 0) {
                    value = list.remove_back();
                    std::cout << "Usunieto element " << value << " z konca listy.\n";
                } else {
                    std::cout << "Lista jest pusta!\n";
                }
                break;

            case 5:
                if (list.count() > 0) {
                    value = list.remove_front();
                    std::cout << "Usunieto element " << value << " z poczatku listy.\n";
                } else {
                    std::cout << "Lista jest pusta!\n";
                }
                break;

            case 6:
                if (list.count() > 0) {
                    std::cout << "Podaj indeks: ";
                    std::cin >> index;
                    if (index >= 0 && index < list.count()) {
                        value = list.remove(index);
                        std::cout << "Usunieto element " << value << " z pozycji " << index << ".\n";
                    } else {
                        std::cout << "Niepoprawny indeks!\n";
                    }
                } else {
                    std::cout << "Lista jest pusta!\n";
                }
                break;

            case 7:
                if (list.count() > 0) {
                    std::cout << "Podaj indeks: ";
                    std::cin >> index;
                    if (index >= 0 && index < list.count()) {
                        value = list.get(index);
                        std::cout << "Element na pozycji " << index << " to: " << value << ".\n";
                    } else {
                        std::cout << "Niepoprawny indeks!\n";
                    }
                } else {
                    std::cout << "Lista jest pusta!\n";
                }
                break;

            case 8:
                std::cout << "Liczba elementow: " << list.count() << ".\n";
                break;

            case 9:
                std::cout << "Elementy " << listName << ":\n";
                if (list.count() > 0) {
                    for (int i = 0; i < list.count(); i++) {
                        std::cout << list.get(i) << " ";
                    }
                    std::cout << "\n";
                } else {
                    std::cout << "Lista jest pusta!\n";
                }
                break;

            case 10:
                std::cout << "Podaj wartosc do wyszukania: ";
                std::cin >> value;
                index = list.search(value);
                if (index != -1) {
                    std::cout << "Element " << value << " znaleziono na pozycji " << index << ".\n";
                } else {
                    std::cout << "Element " << value << " nie zostal znaleziony.\n";
                }
                break;

            case 0:
                std::cout << "Powrot do menu glownego.\n";
                break;

            default:
                std::cout << "Niepoprawny wybor!\n";
        }

    } while (choice != 0);
}

template<class T>
void performPriorityQueueOperations(PriorityQueueBase<T>& queue, const std::string& queueName) {
    int choice;
    int value, priority;

    do {
        showPriorityQueueMenu();
        std::cin >> choice;

        try {
            switch (choice) {
                case 1: // insert
                    std::cout << "Podaj wartosc elementu: ";
                    std::cin >> value;
                    std::cout << "Podaj priorytet elementu: ";
                    std::cin >> priority;
                    queue.insert(value, priority);
                    std::cout << "Dodano element " << value << " o priorytecie " << priority << ".\n";
                    break;

                case 2: // extract_max
                    if (queue.return_size() > 0) {
                        value = queue.extract_max();
                        std::cout << "Usunieto element " << value << " o najwyzszym priorytecie.\n";
                    } else {
                        std::cout << "Kolejka jest pusta!\n";
                    }
                    break;

                case 3: // find_max
                    if (queue.return_size() > 0) {
                        value = queue.find_max();
                        std::cout << "Element o najwyzszym priorytecie: " << value << ".\n";
                    } else {
                        std::cout << "Kolejka jest pusta!\n";
                    }
                    break;

                case 4: // modify_key
                    std::cout << "Podaj wartosc elementu do modyfikacji: ";
                    std::cin >> value;
                    std::cout << "Podaj nowy priorytet: ";
                    std::cin >> priority;
                    queue.modify_key(value, priority);
                    std::cout << "Zmieniono priorytet elementu " << value << " na " << priority << ".\n";
                    break;

                case 5: // return_size
                    std::cout << "Liczba elementow w kolejce " << queueName << ": " << queue.return_size() << ".\n";
                    break;

                case 0:
                    std::cout << "Powrot do menu glownego.\n";
                    break;

                default:
                    std::cout << "Niepoprawny wybor!\n";
            }
        } catch (const std::out_of_range& e) {
            std::cout << "Blad: " << e.what() << "\n";
        } catch (...) {
            std::cout << "Wystapil nieznany blad!\n";
        }

    } while (choice != 0);
}

void runMenu() {
    int choice;

    do {
        showMenu();
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Uruchamianie testow dla wszystkich struktur...\n";
                generateTests();
                break;

            case 2: {
                int queueChoice;
                std::cout << "Wybierz typ kolejki priorytetowej:\n";
                std::cout << "1. HeapPriorityQueue (Kolejka oparta na kopcu)\n";
                std::cout << "2. ArrayPriorityQueue (Kolejka oparta na tablicy)\n";
                std::cout << "Wybor: ";
                std::cin >> queueChoice;

                if (queueChoice == 1) {
                    HeapPriorityQueue<int> heapQueue;
                    std::cout << "Wybrano HeapPriorityQueue\n";
                    performPriorityQueueOperations(heapQueue, "HeapPriorityQueue");
                } else if (queueChoice == 2) {
                    ArrayPriorityQueue<int> arrayQueue;
                    std::cout << "Wybrano ArrayPriorityQueue\n";
                    performPriorityQueueOperations(arrayQueue, "ArrayPriorityQueue");
                } else {
                    std::cout << "Niepoprawny wybor!\n";
                }
                break;
            }

            case 0:
                std::cout << "Koniec programu.\n";
                break;

            default:
                std::cout << "Niepoprawny wybor!\n";
        }

    } while (choice != 0);
}

template void performListOperations<int>(BaseList<int>& list, const std::string& listName);
template void performPriorityQueueOperations<int>(PriorityQueueBase<int>& queue, const std::string& queueName);