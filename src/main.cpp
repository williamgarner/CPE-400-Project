#include <iostream>
#include "Network.h"

const int MC = INT_MAX; // cost for no edge between vertices

int main() {
    vector<vector<pair<int, bool>>> adj = { // adjacency matrix
        {{0, false}, {2, true},   {4, true},   {5, true},   {3, true}},
        {{2, true},  {0, false},  {3, true},   {MC, false}, {MC, false}},
        {{4, true},  {3, true},   {0, false},  {1, true},   {MC, false}},
        {{5, true},  {MC, false}, {1, true},   {0, false},  {1, true}},
        {{3, true},  {MC, false}, {MC, false}, {1, true},   {0, false}}
    }; // first int is cost, second int is probability (in percentage) of the link staying up in the next refresh

    vector<vector<pair<int, bool>>> adj2 = { // adjacency matrix
        {{0, false}, {2, true},   {2, true},   {4, true}},
        {{2, true},  {0, false},  {MC, false}, {MC, false}},
        {{2, true},  {MC, false}, {0, false},  {1, true}},
        {{4, true},  {MC, false}, {1, true},   {0, false}},
    };
    
    Network network(adj);
    network.route();
    network.refresh();
    network.route();
    network.printSPMatrix();

    //cout << network;
    return 0;
}
