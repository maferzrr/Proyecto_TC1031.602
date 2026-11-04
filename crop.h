#ifndef CROP_H
#define CROP_H

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
    // Constructores
    Crop();
    Crop(string name, string season, int growDays, int regrowDays, int sellPrice, int seedCost);

    // Getters
    string getName() const;
    string getSeason() const;
    int getGrowDays() const;
    int getRegrowDays() const;
    int getSellPrice() const;
    int getSeedCost() const;

    // Métodos
    bool canRegrow() const;
    float dailyCropsProfit() const;

    // Sobrecarga de operador
    bool operator<(const Crop& other) const;
};

// Constructor por defecto
Crop::Crop() : name(""), season(""), growDays(0), regrowDays(0), sellPrice(0), seedCost(0) {}

// Constructor por parámetros
Crop::Crop(string name, string season, int growDays, int regrowDays, int sellPrice, int seedCost)
    : name(name), season(season), growDays(growDays), regrowDays(regrowDays), 
      sellPrice(sellPrice), seedCost(seedCost) {}

// Getters
string Crop::getName() const { return name; }
string Crop::getSeason() const { return season; }
int Crop::getGrowDays() const { return growDays; }
int Crop::getRegrowDays() const { return regrowDays; }
int Crop::getSellPrice() const { return sellPrice; }
int Crop::getSeedCost() const { return seedCost; }

// Métodos
bool Crop::canRegrow() const {
    return regrowDays > 0;
}

float Crop::dailyCropsProfit() const {
    if (!canRegrow()) {
        if (growDays <= 0) return 0.0f;
        float netProfit = sellPrice - seedCost;
        return netProfit / growDays;
    } else {
        if (regrowDays <= 0) return 0.0f;
        int totalHarvest = 1 + ((28 - growDays) / regrowDays);
        float totalRevenue = totalHarvest * sellPrice;
        float netProfit = totalRevenue - seedCost;
        return netProfit / 28.0f;
    }
}

// Sobrecarga de operador
bool Crop::operator<(const Crop& other) const {
    return dailyCropsProfit() < other.dailyCropsProfit();
}

#endif