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

    vector<vector<int>> probMatrix;
    for (int i = 0; i < adj.size(); i++) {
        vector<int> probs;
        for (int j = 0; j < adj.size(); j++) {
            cout << "Enter percentage of failure for route from node " << i << " to node " << j << ": ";
            int prob;
            cin >> prob;
            probs.emplace_back(prob);
        }
        probMatrix.emplace_back(probs);
    }
    
    Network network(adj);

    network.input(probMatrix);
    network.printProbMatrix();
    network.route();
    network.printAdjMatrix();
    cout << endl;
    network.printSPMatrix();
    cout << endl;

    network.refresh();

    network.route();
    network.printAdjMatrix();
    cout << endl;
    network.printSPMatrix();
    cout << endl;
    return 0;
}
