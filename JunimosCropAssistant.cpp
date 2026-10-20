#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "crop.h"
#include "mergeSort.h"

using namespace std;

// Complejidad: O(n) - Recorre el vector para imprimir cada elemento
void printCrops(const vector<Crop>& cropList) {
    if (cropList.empty()) {
        cout << "No hay cultivos para mostrar.\n";
        return;
    }
    cout << "\n--------------------------------------------------------------\n";
    cout << "Nombre\t\tTemporada\tGanancia/dia\n";
    cout << "--------------------------------------------------------------\n";
    for (const Crop& c : cropList) {
        cout << c.getName() << "\t\t[" << c.getSeason() << "]\t\t"
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

        crops.push_back(Crop(name, season, stoi(strGrow), stoi(strRegrow), stoi(strSell), stoi(strSeed)));
    }

    file.close();

    Sorts<Crop> sorter;
    int opcion = 0;

    do {
        cout << "\n=== Junimo Crop Assistant ===\n";
        cout << "1. Ver todos los cultivos ordenados por rentabilidad\n";
        cout << "2. Filtrar cultivos por temporada\n";
        cout << "3. Salir\n";
        cout << "Selecciona una opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            // Complejidad: O(n log n) por el Merge Sort
            vector<Crop> sortedCrops = sorter.mergeSort(crops);
            cout << "\n--- Todos los Cultivos (Ordenados por Ganancia Diaria) ---";
            printCrops(sortedCrops);

        } else if (opcion == 2) {
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

            // Complejidad: O(n) para filtrar los elementos coincidentes
            vector<Crop> filteredCrops;
            for (const Crop& c : crops) {
                if (c.getSeason() == selectedSeason) {
                    filteredCrops.push_back(c);
                }
            }

            // Complejidad: O(k log k), donde k es el numero de cultivos de esa temporada
            vector<Crop> sortedSeasonCrops = sorter.mergeSort(filteredCrops);
            cout << "\n--- Cultivos de " << selectedSeason << " (Ordenados por Ganancia Diaria) ---";
            printCrops(sortedSeasonCrops);

        } else if (opcion == 3) {
            cout << "Saliendo del asistente. \n";
        } else {
            cout << "Opcion invalida. \n";
        }

    } while (opcion != 3);

    return 0;
}