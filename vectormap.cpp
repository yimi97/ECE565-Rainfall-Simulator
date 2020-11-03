#include "vectormap.hpp"

VectorMap::VectorMap(int N) {
    dir.assign(N, vector<vector<char>>(N,vector<char>(0)));
}

vector<vector<int>> VectorMap::getData(int x, int y){
    vector<char> trickle = dir[x][y];
    vector<vector<int>> res;
    for (size_t i=0;i<trickle.size();i++){
        res.push_back(directions[trickle[i]]);
    }
    return res;
}

void VectorMap::setData(const vector<vector<int>> & landArray, int & N){
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            int minHeight = landArray[i][j]-1;
            for(map<char,vector<int>>::iterator it=directions.begin(); it!= directions.end(); ++it){
                int r = i+(it->second)[0];
                int c = j+(it->second)[1];
                if(r>=0 && r<N && c>=0 && c<N){
                    if (landArray[r][c]<minHeight){
                        minHeight = landArray[r][c];
                        if(!dir[i][j].empty())
                            dir[i][j].clear();
                        dir[i][j].push_back(it->first);
                    } 
                    else if(landArray[r][c]==minHeight){
                        dir[i][j].push_back(it->first);
                    }
                }
            }
        }
    }
}