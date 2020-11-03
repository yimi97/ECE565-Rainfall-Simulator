#include "landscape.hpp"

#include <iostream>

#include "datamap.hpp"

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

void Landscape::receive_new(int x, int y) {
    double currD = this->rainMap.getData(x, y);
    // std::cout<< currD << " ";
    this->rainMap.setData(x, y, currD + 1);
}

void Landscape::absorb(int x, int y) {
    double currR = this->rainMap.getData(x, y);
    double currA = this->absorbedMap.getData(x, y);
    double realAbsorbed;

    if (currR < this->absorption_rate) {
        realAbsorbed = currR;
    } else {
        realAbsorbed = this->absorption_rate;
    }

    this->rainMap.setData(x, y, currR - realAbsorbed);
    this->absorbedMap.setData(x, y, currA + realAbsorbed);
}

void Landscape::cal_trickle(int x, int y) {
    double curr = this->rainMap.getData(x, y);
    this->nextTrickleMap.setData(x, y, curr);
}

std::vector<std::vector<double>> Landscape::printAbsorbed() {
    std::vector<std::vector<double>> out;

    for (int row = 0; row < this->dimension; row++) {
        std::vector<double> currRow;
        for (int col = 0; col < this->dimension; col++) {
            currRow.push_back(this->absorbedMap.getData(row, col));
        }
        out.push_back(currRow);
    }

    return out;
}

void Landscape::trickle() {}