#ifndef NETWORK_H
#define NETWORK_H

#include <iostream>
#include <vector>
#include <utility>
#include<bits/stdc++.h>



using namespace std;


struct Link {
    int cost;
    int p_active;
    bool active;
};

class Network {
public:
    Network(const vector<vector<Link>>& adj);
    void refresh();
    void route();
    void print() const;

    friend std::ostream& operator<<(std::ostream &os, const Network &network);

private:
    vector<vector<Link>> adj;
    vector<bool> activeNodes;
};

#endif //NETWORK_H
