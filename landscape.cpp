#include "landscape.hpp"
#include "datamap.hpp"
#include "vectormap.hpp"
#include <iostream>

Landscape::Landscape(double abr, int n, const vector<vector<int>> & landArray) : \
    rainMap(n), nextTrickleMap(n), absorbedMap(n),complete_flag(false), \
    absorption_rate(abr), dimension(n), directions(n) {
    this->directions.setData(landArray, n);
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


void Landscape::trickle(int row, int col) {
    double trickle_total= min(this->nextTrickleMap.getData(row, col), 1.0);
    std::vector<std::vector<int>> d = this->directions.getData(row, col);
    if (d.size()==0 || trickle_total==0){
        //continue;
        return;
    }
    int trickle_num = d.size();
    double trickle_amount = trickle_total/trickle_num;
    for(int i=0;i<trickle_num;i++){
        int r = row + d[i][0];
        int c = col + d[i][1];
        double currD = this->rainMap.getData(r, c);
        this->rainMap.setData(r, c, currD + trickle_amount);
    }
    double curr_rain = this->rainMap.getData(row, col);
    this->rainMap.setData(row, col, curr_rain-trickle_total); 
}

void Landscape::printRain(){
    for (int i=0;i<this->dimension;i++){
        for (int j=0;j<this->dimension;j++){
            cout << rainMap.getData(i,j)<<" ";
        }
        cout << endl;
    }
}

double Landscape::checkRemain(int x, int y){
    return this->rainMap.getData(x,y);
}