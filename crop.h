#ifndef CROP_H
#define CROP_H

#include <iostream>
#include <string>
#include <vector>

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

    // Declarando constructor por defecto
    Crop(): name(""), season(""), growDays(0), regrowDays(0), sellPrice(0), seedCost(0) {}

    // Declarando constructor por parametros
    Crop(string name, string season, int growDays, int regrowDays, int sellPrice, int seedCost): 
    name(name), season(season), growDays(growDays), regrowDays(regrowDays), sellPrice(sellPrice), seedCost(seedCost) {}

    // Getters

    string getName() const;
    string getSeason() const;
    int getGrowDays () const;
    int getRegrowDays() const;
    int getSellPrice() const;
    int getSeedCost() const;

    // Métodos 
    bool canRegrow () const;
    double dailyCropsProfit() const;

    // Sobrecarga de operadores para comparacion
    bool operator<(const Crop& other) const;
};

#endif