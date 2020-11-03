#pragma once

#include "datamap.hpp"

class Landscape {
    public:
        // Constructor
        Landscape(double abr, int n); 

        bool isComplete();

        void receive_new(int x, int y);
        void absorb(int x, int y);
        void cal_trickle(int x, int y); // Update nextTrickleMap ready for trickle
        void trickle();

        std::vector<std::vector<double>> printAbsorbed();

    private:
        Datamap rainMap;
        Datamap nextTrickleMap;
        Datamap absorbedMap;

        bool complete_flag; // Flag to indicate completion
        double absorption_rate;
        int dimension;

        VectorMap directions; /** need definition **/
};