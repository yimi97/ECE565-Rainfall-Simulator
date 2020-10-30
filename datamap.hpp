#include <array>

class Datamap {
    public:
        
        // Constructor
        Datamap();

        double getData(int x, int y);
        void setData(int x, int y); 

        

    private: 
        std::array<std::array<double, N>, N>> dataMatrix;

};