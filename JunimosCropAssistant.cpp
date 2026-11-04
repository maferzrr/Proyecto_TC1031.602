#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>

#include "crop.h"
#include "mergeSort.h"
#include "BST.h"

using namespace std;

// Complejidad: O(n) - Recorre el vector para imprimir cada elemento en formato de tabla fija
void printCrops(const vector<Crop>& cropList) {
    if (cropList.empty()) {
        cout << "No hay cultivos para mostrar.\n";
        return;
    }
    cout << "\n--------------------------------------------------------------\n";
    cout << left << setw(15) << "Nombre" 
         << setw(12) << "Temporada" 
         << "Ganancia/dia\n";
    cout << "--------------------------------------------------------------\n";
    
    for (const Crop& c : cropList) {
        cout << left << setw(15) << c.getName() 
             << setw(12) << ("[" + c.getSeason() + "]") 
             << c.dailyCropsProfit() << " g/dia\n";
    }
    cout << "--------------------------------------------------------------\n";
}

int main() {
    ifstream file("crops.txt");

    if (!file.is_open()) {
        cout << "Hubo un error al abrir crops.txt, verifica que este en la misma carpeta.\n";
        return 1;
    }

    vector<Crop> crops;
    BST<string> cropTree; // Instancia de nuestra estructura no lineal (BST)
    string line;

    // Descartar la cabecera
    getline(file, line);

    // Complejidad: O(n) - Lectura lineal de las líneas del archivo
    while (getline(file, line)) {
        stringstream ss(line);
        string name, season, strGrow, strRegrow, strSell, strSeed;

        getline(ss, name, ',');
        getline(ss, season, ',');
        getline(ss, strGrow, ',');
        getline(ss, strRegrow, ',');
        getline(ss, strSell, ',');
        getline(ss, strSeed);

        Crop newCrop(name, season, stoi(strGrow), stoi(strRegrow), stoi(strSell), stoi(strSeed));
        crops.push_back(newCrop);

        // Insertar el nombre en el Árbol Binario de Búsqueda
        cropTree.add(name);
    }

    file.close();

    Sorts<Crop> sorter;
    int opcion = 0;

    do {
        cout << "\n=== Junimo Crop Assistant ===\n";
        cout << "1. Ver lista de cultivos sin ordenar\n";
        cout << "2. Ver todos los cultivos ordenados por rentabilidad\n";
        cout << "3. Filtrar cultivos por temporada\n";
        cout << "4. Buscar informacion de un cultivo por nombre \n";
        cout << "5. Ver nombres de cultivos en orden alfabetico \n";
        cout << "6. Ver cultivos que vuelven a crecer (Multi-cosecha)\n";
        cout << "7. Salir\n";
        cout << "Selecciona una opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            cout << "\n--- Lista de Cultivos (Sin Ordenar) ---";
            printCrops(crops);

        } else if (opcion == 2) {
            // Complejidad: O(n log n) por el Merge Sort
            vector<Crop> sortedCrops = sorter.mergeSort(crops);
            cout << "\n--- Todos los Cultivos (Ordenados por Ganancia Diaria) ---";
            printCrops(sortedCrops);

        } else if (opcion == 3) {
            int opcionTemp = 0;
            cout << "\nElige la temporada:\n";
            cout << "1. Spring\n";
            cout << "2. Summer\n";
            cout << "3. Fall\n";
            cout << "Opcion: ";
            cin >> opcionTemp;

            string selectedSeason = "";
            if (opcionTemp == 1) selectedSeason = "Spring";
            else if (opcionTemp == 2) selectedSeason = "Summer";
            else if (opcionTemp == 3) selectedSeason = "Fall";
            else {
                cout << "Opcion de temporada no valida.\n";
                continue;
            }

            vector<Crop> filteredCrops;
            for (const Crop& c : crops) {
                if (c.getSeason() == selectedSeason) {
                    filteredCrops.push_back(c);
                }
            }

            vector<Crop> sortedSeasonCrops = sorter.mergeSort(filteredCrops);
            cout << "\n--- Cultivos de " << selectedSeason << " (Ordenados por Ganancia Diaria) ---";
            printCrops(sortedSeasonCrops);

        } else if (opcion == 4) {
            // Búsqueda eficiente O(log n) en el BST
            string searchName;
            cout << "\nIngresa el nombre exacto del cultivo : ";
            cin >> searchName;

            if (cropTree.find(searchName)) {
                cout << "\n[!] Cultivo encontrado.\n";
                for (const Crop& c : crops) {
                    if (c.getName() == searchName) {
                        cout << "--------------------------------------------\n";
                        cout << "Nombre:              " << c.getName() << "\n";
                        cout << "Temporada:           " << c.getSeason() << "\n";
                        cout << "Dias de crecimiento: " << c.getGrowDays() << " dias\n";
                        cout << "Dias de regrow:      " << c.getRegrowDays() << " dias\n";
                        cout << "Precio de venta:     " << c.getSellPrice() << " g\n";
                        cout << "Costo de semilla:    " << c.getSeedCost() << " g\n";
                        cout << "Ganancia diaria:     " << c.dailyCropsProfit() << " g/dia\n";
                        cout << "--------------------------------------------\n";
                        break;
                    }
                }
            } else {
                cout << "\n[X] El cultivo '" << searchName << "' no existe en el sistema.\n";
            }

        } else if (opcion == 5) {
            // Recorrido Inorder para mostrar los datos ordenados alfabéticamente
            cout << "\n--- Cultivos en Orden Alfabetico (BST Inorder) ---\n";
            cropTree.printInorder();

        } else if (opcion == 6) {
            // Filtrar usando el método canRegrow()
            vector<Crop> regrowCrops;
            for (const Crop& c : crops) {
                if (c.canRegrow()) {
                    regrowCrops.push_back(c);
                }
            }

            vector<Crop> sortedRegrowCrops = sorter.mergeSort(regrowCrops);
            cout << "\n--- Cultivos con Multi-Cosecha (Ordenados por Ganancia) ---";
            printCrops(sortedRegrowCrops);

        } else if (opcion == 7) {
            cout << "Saliendo del asistente.\n";
        } else {
            cout << "Opcion invalida.\n";
        }

    } while (opcion != 7);

    return 0;
}