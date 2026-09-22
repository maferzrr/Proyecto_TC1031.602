#include <iostream>

#include "crop.h"

using namespace std; 

// Implementación de Métodos

// Getters
string Crop::getName() const{
    return name;
}

string Crop::getSeason() const{
    return season;
}

int Crop::getGrowDays() const{
    return growDays;
}

int Crop::getRegrowDays() const{
    return regrowDays;
}

int Crop::getSellPrice() const{
    return sellPrice;
}

int Crop::getSeedCost() const{
    return seedCost;
}

// Métodos

bool Crop::canRegrow() const{
    if (regrowDays > 0){
        return true; 
    }
    else {
        return false;
    }
}

double Crop::dailyCropsProfit() const{
    if(!canRegrow()){
        double netProfit;
        double dailyCropsProfit;

        netProfit = (sellPrice - seedCost);
        
        dailyCropsProfit = (netProfit / growDays);

        return  dailyCropsProfit;
    }
    else {
       int totalHarvest;
       double totalRevenue;
       double netProfit;
       double dailyCropsProfit;

       totalHarvest = 1 + ((28 - growDays) / regrowDays);

       totalRevenue = (totalHarvest * sellPrice);

       netProfit = (totalRevenue - seedCost);

       dailyCropsProfit = (netProfit / 28.0);

       return dailyCropsProfit;
    }
}

bool Crop::operator<(const Crop& other) const{
    return dailyCropsProfit() < other.dailyCropsProfit();
}