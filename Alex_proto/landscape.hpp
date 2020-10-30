#include "Datamap.hpp"

class Landscape {
    public:
        bool complete_flag; // Flag to indicate completion
         
        // Constructor
        Landscape(); 

        bool isComplete();

        void receive_new();
        void absorb();
        void cal_trickle(); // Update nextTrickleMap ready for trickle
        void trickle();

    private:
        Datamap rainMap;
        Datamap heightMap;
        Datamap nextTrickleMap;
        Datamap absorbedMap;
};