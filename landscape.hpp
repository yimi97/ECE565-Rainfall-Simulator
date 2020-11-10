#pragma once

#include "datamap.hpp"
#include "vectormap.hpp"
class Landscape {
    public:
        // Constructor
        Landscape(double abr, int n, const vector<vector<int>> & landArray); 

        void receive_new(int x, int y);
        void absorb(int x, int y);
        void cal_trickle(int x, int y); // Update nextTrickleMap ready for trickle
        void trickle(int row, int col);

        std::vector<std::vector<double>> printAbsorbed();
        void printRain(); 
        bool checkRemain();

    private:
        Datamap rainMap;
        Datamap nextTrickleMap;
        Datamap absorbedMap;

        double absorption_rate;
        int dimension;

        VectorMap directions; /** need definition **/
};