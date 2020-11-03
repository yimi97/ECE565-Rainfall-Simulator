#include <array>
#include <vector>
#include <map>
using namespace std;

class VectorMap {
    public:
        
        // Constructor
        VectorMap(int N);

        // get the vector of trickle (x, y)s
        vector<vector<int>> getData(int x, int y);

        // set the vector map using land height matrix
        void setData(const vector<vector<int>> & landArray, int & N);

        ~VectorMap(){}

    private: 
        vector<vector<vector<char>>> dir;  // store the char of directions
        map<char,vector<int>> directions = {{'E',{0,1}},{'W',{0,-1}},{'N',{1,0}},{'S',{-1,0}}};

};