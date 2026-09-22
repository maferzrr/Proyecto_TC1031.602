#include <iostream>

#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "crop.h"
#include "mergeSort.h"

using namespace std;

int main() {
    ifstream file("crops.txt");

    if (!file.is_open()) {
        cout << "Hubo un error al abrir crops.txt, verifica que este en la misma carpeta." << endl;
        return 1;
    }

    vector<Crop> crops;
    string line;

    getline(file, line);

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
    vector<Crop> sortedCrops = sorter.mergeSort(crops);

   
    cout << "Total crops sorted: " << sortedCrops.size() << endl;
    cout << "------------------------------------------" << endl;
    for (const Crop& c : sortedCrops) {
        cout << c.getName() << " [" << c.getSeason() << "] -> Profit/day: " 
             << c.dailyCropsProfit() << " g/day" << endl;
    }

    return 0;
}