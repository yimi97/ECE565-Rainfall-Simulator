#pragma once

#include "datamap.hpp"

class Landscape {
    public:
        // Constructor
        Landscape(double abr, int n); 

        bool isComplete();

        void receive_new();
        void absorb();
        void cal_trickle(); // Update nextTrickleMap ready for trickle
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