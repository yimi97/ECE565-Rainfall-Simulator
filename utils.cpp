#include <map>
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "landscape.hpp"
using namespace std;

double calc_time(struct timespec start, struct timespec end) {
	double start_sec = (double)start.tv_sec*1000000000.0 + (double)start.tv_nsec;
	double end_sec = (double)end.tv_sec*1000000000.0 + (double)end.tv_nsec;
	if (end_sec < start_sec) {
		return 0;
	} else {
		return end_sec - start_sec;
	}
}

void readFile(string & file, vector<vector<int>> & landArray, int N){
    ifstream ifs;
    ifs.open(file, ifstream::in);
    
    landArray.assign(N, vector<int>(N, 0));
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            ifs >> landArray[i][j];
		}
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
    struct timespec start_time, end_time;

    Landscape * myLandscape = new Landscape(A, N, landArray);

    clock_gettime(CLOCK_MONOTONIC, &start_time);
    int rain = 0;
    while(true){
        bool finish = true;
        for (int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                if(rain<M)
                    myLandscape->receive_new(i, j);
                myLandscape->absorb(i, j);
                myLandscape->cal_trickle(i, j);
                
            }
        }
        rain++;
        for (int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                myLandscape->trickle(i, j);
                if (myLandscape->checkRemain(i,j)!=0.0){
                    finish = false;
                }
            }
        }
        if(finish && rain>M)
            break;
    }
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    double elapsed_s = calc_time(start_time, end_time) / 1000000000.0;
    
    cout <<"STEP: "<<rain<< "  TIME: "<<elapsed_s<<endl;
    vector<vector<double>> abs = myLandscape->printAbsorbed();
    ofstream myfile;
    myfile.open ("output.txt");
    myfile << "Rainfall simulation took "<< rain <<" time steps to complete.\n";
    myfile << "Runtime = "<<elapsed_s<<" seconds\n";
    myfile << "\n";
    for (int i=0;i<N;i++){
        for (int j=0;j<N;j++){
            myfile << abs[i][j] << " ";
        }
        myfile << "\n";
    }
    myfile.close(); 
    return EXIT_SUCCESS;
}