#include "landscape.hpp"
#include "datamap.hpp"
#include <iostream>

Landscape::Landscape(double abr, int n) : rainMap(n), nextTrickleMap(n), absorbedMap(n) {
    this->complete_flag = false;
    this->absorption_rate = abr;
    this->dimension = n;
}

bool Landscape::isComplete() {
    for (int row = 0; row < this->dimension; row++) {
        for (int col = 0; col < this->dimension; col++) {
            if (this->rainMap.getData(row, col) != 0) {
                return false;
            }
        }
    }

    return true;
}

void Landscape::receive_new() {
    for (int row = 0; row < this->dimension; row++) {
        for (int col = 0; col < this->dimension; col++) {
            double currD = this->rainMap.getData(row, col);
            this->rainMap.setData(row, col, currD + 1);
        }
    }
}

void Landscape::absorb() {
    for (int row = 0; row < this->dimension; row++) {
        for (int col = 0; col < this->dimension; col++) {
            double currR = this->rainMap.getData(row, col);
            double currA = this->absorbedMap.getData(row, col);
            double realAbsorbed;

            if(currR < this->absorption_rate) {
                realAbsorbed = currR;
            }
            else {
                realAbsorbed = this->absorption_rate;
            }

            this->rainMap.setData(row, col, currR - realAbsorbed);
            this->absorbedMap.setData(row, col, currA + realAbsorbed);
        }
    }
}

void Landscape::cal_trickle() {
    for (int row = 0; row < this->dimension; row++) {
        for (int col = 0; col < this->dimension; col++) {
            double curr = this->rainMap.getData(row, col);
            this->nextTrickleMap.setData(row, col, curr);
        }
    }
}

std::vector<std::vector<double>> Landscape::printAbsorbed() {
    std::vector<std::vector<double>> out;
    
    for (int row = 0; row < this->dimension; row++) {
        std::vector<double> currRow;
        for (int col = 0; col < this->dimension; col++) {
            currRow.push_back(this->absorbedMap.getData(row,col));
        }
        out.push_back(currRow);
    }

    return out;
}

void Landscape::trickle() {}