#ifndef NETWORK_H
#define NETWORK_H

#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <bits/stdc++.h>



using namespace std;

class Network {
public:
    Network(const vector<vector<pair<int, bool>>>& adj);
    void refresh();
    void route();
    void printAdjMatrix() const;
    void printSPMatrix() const;

    friend std::ostream& operator<<(std::ostream &os, const Network &network);

private:
    void update(int x, int y, int cost);
    void update(int x, int y, bool active);
    int getMinIndex(const set<int>& sptSet, const vector<int>& distVec) const;

    vector<vector<pair<int, bool>>> adjMatrix;
    vector<vector<pair<int, bool>>> spMatrix;
    vector<bool> activeNodes;
    const int MAX_COST = INT_MAX;
};

#endif //NETWORK_H
