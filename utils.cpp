#include <map>
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "landscape.hpp"
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
    double A;
    stringstream ss(argv[3]);
    ss >> A;
    int N = atoi(argv[4]);
    string file = argv[5];
    vector<vector<int>> landArray;
    readFile(file, landArray, N);

    Landscape myLandscape(A, N, landArray);

    int rain = 0;
    while(true){
        bool finish = true;
        for (int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                if(rain<M)
                    myLandscape.receive_new(i, j);
                myLandscape.absorb(i, j);
                myLandscape.cal_trickle(i, j);
                
            }
        }
        rain++;
        for (int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                myLandscape.trickle(i, j);
                if (myLandscape.checkRemain(i,j) != 0.0){
                    finish = false;
                }
            }
        }
        if(finish)
            break;
    }
    vector<vector<double>> abs = myLandscape.printAbsorbed();
    for (int i=0;i<N;i++){
        for (int j=0;j<N;j++){
            cout << abs[i][j] << " ";
        }
        cout <<endl;
    }

    myLandscape.printRain();  
    return EXIT_SUCCESS;
}