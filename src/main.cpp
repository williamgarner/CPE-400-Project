#include <iostream>
#include "Network.h"

const int MAX_COST = 10; // cost for no edge between vertices

int main() {
    vector<vector<link>> adj = { // adjacency matrix
        {{0, 0, true},  {2, 60, true},        {3, 50, true},       {1, 20, true}},
        {{2, 60, true}, {0, 0, true},         {MAX_COST, 0, true}, {MAX_COST, 0, true}},
        {{3, 50, true}, {MAX_COST, 0, true},  {0, 0, true},        {4, 10, true}},
        {{1, 20, true}, {MAX_COST, 0, true},  {4, 10, true},       {0, 0, true}}
    }; // first int is cost, second int is probability (in percentage) of the link staying up in the next refresh

    Network network(adj);
    network.route();
    network.refresh();
    network.route();
    network.print();

    return 0;
}