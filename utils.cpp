// #include <chrono>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "landscape.hpp"
// using namespace std::chrono;

using namespace std;

void readFile(string& file, vector<vector<int>>& landArray, int N) {
    ifstream ifs;
    ifs.open(file, ifstream::in);

    landArray.assign(N, vector<int>(N, 0));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            ifs >> landArray[i][j];
        }
    }

    ifs.close();
}

int main(int argc, char** argv) {
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

    // auto start = high_resolution_clock::now();

    int rain = 0;
    while (true) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (rain < M) {
                    myLandscape.receive_new(i, j);
                }
                myLandscape.absorb(i, j);
                myLandscape.cal_trickle(i, j);
            }
        }
        rain++;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                myLandscape.trickle(i, j);
            }
        }

        if (rain >= M) {
            if (!myLandscape.checkRemain()) {
                break;  // No remain, break out
            }
        }
    }

    // auto stop = high_resolution_clock::now();
    // auto duration = duration_cast<milliseconds>(stop - start);

    vector<vector<double>> abs = myLandscape.printAbsorbed();
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << abs[i][j] << " ";
        }
        cout << endl;
    }

    myLandscape.printRain();

    // cout << duration.count() * 0.001 << endl;
    return EXIT_SUCCESS;
}