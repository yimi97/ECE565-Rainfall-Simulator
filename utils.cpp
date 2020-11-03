#include <map>
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "vectormap.hpp"
using namespace std;

void readFile(string & file, vector<vector<int>> & landArray, int N){
    ifstream ifs;
    ifs.open(file, ifstream::in);
    string line;

    while(getline(ifs, line)){
        vector<int> lineParsed;
        istringstream ss(line);
        string num;	
        while (getline(ss, num,' ')){
            lineParsed.push_back(atoi(num.c_str()));
        }
        landArray.push_back(lineParsed);
    }

    ifs.close();
}

int main(int argc, char ** argv){
    int P = atoi(argv[1]);
    int M = atoi(argv[2]);
    int A = atoi(argv[3]);
    int N = atoi(argv[4]);
    string file = argv[5];
    vector<vector<int>> landArray;
    readFile(file, landArray, N);

    // test VectorMap
    VectorMap * vm = new VectorMap(N);
    vm->setData(landArray, N);
    vector<vector<int>> res = vm->getData(0,2);
    for (size_t i=0;i<res.size();i++){
        cout << "x: "<< res[i][0] << ", y: " << res[i][1]<<endl;
    }
    delete vm;

    return EXIT_SUCCESS;
}