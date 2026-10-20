#ifndef CROP_H
#define CROP_H

#include <iostream>
#include <string>

using namespace std;

class Crop {
private:
    string name; 
    string season;
    int growDays;
    int regrowDays;
    int sellPrice;
    int seedCost;

public:
    // Complejidad: O(1) - Asignación directa de valores por defecto
    Crop() : name(""), season(""), growDays(0), regrowDays(0), sellPrice(0), seedCost(0) {}

    // Complejidad: O(1) - Inicialización directa de atributos
    Crop(string name, string season, int growDays, int regrowDays, int sellPrice, int seedCost)
        : name(name), season(season), growDays(growDays), regrowDays(regrowDays), 
          sellPrice(sellPrice), seedCost(seedCost) {}

    // Getters
    // Complejidad: O(1) - Retorno directo de atributo
    string getName() const { return name; }
    string getSeason() const { return season; }
    int getGrowDays() const { return growDays; }
    int getRegrowDays() const { return regrowDays; }
    int getSellPrice() const { return sellPrice; }
    int getSeedCost() const { return seedCost; }

    // Métodos
    // Complejidad: O(1) - Comparación condicional simple
    bool canRegrow() const {
        return regrowDays > 0;
    }

    // Complejidad: O(1) - Operaciones aritméticas elementales
    double dailyCropsProfit() const {
        if (!canRegrow()) {
            if (growDays <= 0) return 0.0;
            double netProfit = sellPrice - seedCost;
            return netProfit / growDays;
        } else {
            if (regrowDays <= 0) return 0.0;
            int totalHarvest = 1 + ((28 - growDays) / regrowDays);
            double totalRevenue = totalHarvest * sellPrice;
            double netProfit = totalRevenue - seedCost;
            return netProfit / 28.0;
        }
    }

    // Sobrecarga de operador
    // Complejidad: O(1) - Llama dos veces a dailyCropsProfit() que es O(1) y compara
    bool operator<(const Crop& other) const {
        return dailyCropsProfit() < other.dailyCropsProfit();
    }
};

#endif