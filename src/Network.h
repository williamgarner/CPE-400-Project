#ifndef NETWORK_H
#define NETWORK_H

#include <iostream>
#include <vector>
#include <utility>

using namespace std;

class Network {
public:
    Network(const vector<vector<pair<int, int>>>& adj);
    void route();
    void print() const;

    friend std::ostream& operator<<(std::ostream &os, const Network &network);

private:
    vector<vector<pair<int, int>>> adj;
};

#endif //NETWORK_H
