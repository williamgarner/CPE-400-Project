#ifndef NETWORK_H
#define NETWORK_H

#include <iostream>
#include <vector>
#include <utility>

using namespace std;

struct link {
    int cost;
    int p_active;
    bool active;
};

class Network {
public:
    Network(const vector<vector<link>>& adj);
    void refresh();
    void route();
    void print() const;

    friend std::ostream& operator<<(std::ostream &os, const Network &network);

private:
    vector<vector<link>> adj;
    vector<bool> activeNodes;
};

#endif //NETWORK_H
