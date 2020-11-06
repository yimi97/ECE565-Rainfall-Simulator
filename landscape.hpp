#pragma once

#include "datamap.hpp"
#include "vectormap.hpp"
class Landscape {
    public:
        // Constructor
        Landscape(double abr, int n, const vector<vector<int>> & landArray); 

        bool isComplete();

        void receive_new(int x, int y);
        void absorb(int x, int y);
        void cal_trickle(int x, int y); // Update nextTrickleMap ready for trickle
        void trickle(int row, int col);

        std::vector<std::vector<double>> printAbsorbed();
        void printRain(); 
        double checkRemain(int x, int y);

    private:
        Datamap rainMap;
        Datamap nextTrickleMap;
        Datamap absorbedMap;

        bool complete_flag; // Flag to indicate completion
        double absorption_rate;
        int dimension;

        VectorMap directions; /** need definition **/
};