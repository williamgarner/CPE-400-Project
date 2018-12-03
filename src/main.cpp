#include <iostream>
#include "Network.h"

const int MAX_COST = 10; // cost for no edge between vertices

int main() {
    vector<vector<pair<int, int>>> adj = { // adjacency matrix
        {{0, 0},        {2, 60},       {3, 50},       {MAX_COST, 0}},
        {{MAX_COST, 0}, {0, 0},        {MAX_COST, 0}, {MAX_COST, 0}},
        {{MAX_COST, 0}, {MAX_COST, 0}, {0, 0},        {4, 10}},
        {{1, 20},       {MAX_COST, 0}, {MAX_COST, 0}, {0, 0}}
    };

    Network network(adj);
    network.route();
    network.print();
    return 0;
}