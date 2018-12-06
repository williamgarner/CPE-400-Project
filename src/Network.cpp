#include "Network.h"
#include <stdlib.h>

unsigned int Network::pngNum = 0;

/// @name Network
/// @brief Constructor for the Network class.
Network::Network(const vector<vector<pair<int, bool>>>& adjMatrix) : adjMatrix(adjMatrix) {}

/// @name refresh
/// @brief Determines which nodes and edges go down and changes the adjacency matrix to the new state.
void Network::refresh() {
    srand(time(NULL));
    for (int i = 0; i < adjMatrix.size(); i++) {
        for (int j = 0; j < adjMatrix.size(); j++) {
            if (i != j) {
                int gen = rand() % 100;
                if (gen < probMatrix[i][j]) {
                    update(i, j, MAX_COST);
                    update(i, j, false);
                }
            }
        }
    }

    ofstream graphOutputFile;
    graphOutputFile.open("../src/graphOutput.dot");
    if(graphOutputFile.good())
        graphOutputFile << *this;
    else
        cout << "Could not open file" << endl;
    graphOutputFile.close();
    string sysCall = {"dot -Tpng ../src/graphOutput.dot -o ../src/graph" + to_string(pngNum++) + ".png"};
    system(sysCall.c_str());
}

/// @name route
/// @brief Implementation of Dijkstra's algorithm using the expected value of a certain route.
/// @details The expected value of a route is calculated as EX = cost * p(cost) + 10 * (100 - p(cost)).
/// @details The algorithm takes into account the cost of a link and the likelihood of the link succeeding.
void Network::route() {
    spMatrix.clear();
    for (int i = 0; i < adjMatrix.size(); i++) {
        set<int> sptSet;
        vector<int> distVec;

        for (auto const& x : adjMatrix) {
            distVec.emplace_back(MAX_COST);
        }

        distVec[i] = 0;
        for (int j = 0; j < adjMatrix.size(); j++) {
            int minIndex = getMinIndex(sptSet, distVec);
            sptSet.insert(minIndex);
            auto const& destNode = adjMatrix[minIndex];
            for (int k = 0; k < destNode.size(); k++) {

                int distToDest = destNode[k].first;
                if (distToDest != MAX_COST && distVec[minIndex] != MAX_COST) {
                    int alt = distVec[minIndex] + destNode[k].first;
                    if (alt < distVec[k]) {
                        distVec[k] = alt;
                    }
                }
            }
        }

        vector<pair<int, bool>> sp;
        for (auto x : distVec) {
            bool canReach = x != MAX_COST;
            sp.emplace_back(make_pair(x, canReach));
        }
        spMatrix.emplace_back(sp);

        sptSet.clear();
        distVec.clear();
    }
}

void Network::input(vector<vector<int>> probs) {
    for (auto const& x : probs) {
        vector<int> prob;
        for (auto y : x) {
            prob.emplace_back(y);
        }
        probMatrix.emplace_back(prob);
    }
}

int Network::getMinIndex(const set<int>& sptSet, const vector<int>& distVec) const {
    int minIndex = 0, minDist = MAX_COST;
    for (int i = 0; i < distVec.size(); i++) {
        if (sptSet.find(i) == sptSet.end() && distVec[i] < minDist) {
            minIndex = i;
            minDist = distVec[i];
        }
    }
    return minIndex;
}

void Network::update(int x, int y, int cost) {
    adjMatrix[x][y].first = cost;
    adjMatrix[y][x].first = cost;
}

void Network::update(int x, int y, bool active) {
    adjMatrix[x][y].second = active;
    adjMatrix[y][x].second = active;
}

/// @name printAdjMatrix
/// @brief Prints out the adjacency matrix representing the network state, should only be used for debugging.
void Network::printAdjMatrix() const {
//    int src = 0;
//    for (auto const& x : adjMatrix) {
//        int dest = 0;
//        for (auto const& y : x) {
//            cout << src << " -> " << dest++ << endl;
//            string cost = "C: " + to_string(y.first);
//            string active = "A: " + string(y.second ? "true" : "false");
//            string out = cost.append(" | ").append(active);
//            cout << out << endl;
//        }
//        src++;
//        cout << endl;
//    }
    cout << "Adjacency Matrix" << endl;
    for (int i = 0; i < adjMatrix.size(); i++) {
        cout << i << ": ";
        for (int j = 0; j < adjMatrix.size(); j++) {
            int dist = adjMatrix[i][j].first;
            if (dist != MAX_COST) {
                cout << dist << " ";
            } else {
                cout << "INF" << " ";
            }
        }
        cout << endl;
    }
}

/// @name printSPMatrix
/// @brief Prints out the shortest path matrix representing the network state, should only be used for debugging.

void Network::printSPMatrix() const {
    cout << "Shortest Path Matrix" << endl;
    for (int i = 0; i < spMatrix.size(); i++) {
        cout << i << ": ";
        for (int j = 0; j < spMatrix.size(); j++) {
            int dist = spMatrix[i][j].first;
            if (dist != MAX_COST) {
                cout << dist << " ";
            } else {
                cout << "INF" << " ";
            }
        }
        cout << endl;
    }
}

void Network::printProbMatrix() const {
    cout << "Probability Matrix" << endl;
    for (int i = 0; i < probMatrix.size(); i++) {
        cout << i << ": ";
        for (int j = 0; j < probMatrix.size(); j++) {
            int dist = probMatrix[i][j];
            cout << dist << " ";
        }
        cout << endl;
    }
}

/// @name operator<<
/// @brief Outputs GraphViz notation for use in visualizing the network.
std::ostream& operator<<(std::ostream& os, const Network& network) {
    vector<pair<int, int>> connection;
    vector<string> cities = {"Reno", "Seoul", "São Paulo","Houston", "Bombay", "JAKARTA", "Karachi", "Washington D.C.",
                             "Moscow", "Shanghai", "Mexico City", "London", "Rio de Janeiro", "Chicago", "Los Angeles" ,
                             "Sydney", "St Petersburg", "Baghdad", "Madrid" };
    os << "graph G{" << endl;
    int src = 0;
    for (auto const& x : network.adjMatrix) {
        int dest = 0;
        for (auto const& y : x) {
            if(y.second)
            {
                if(find(connection.begin(), connection.end(), make_pair(src, dest)) == connection.end())
                {
                    os << src << "[label = \"" << cities[src] << "\"]" << endl;
                	os << dest << "[label = \"" << cities[dest] << "\"]" << endl;
                    os << src << " -- " << dest << "[label= \" " << y.first << "\"];" << endl;
                    connection.emplace_back(dest, src);
                }
            }
            dest++;
        }
        src++;
    }
    os << "labelloc=\"t\"" << endl;
    os << "label=\"The End of the World\"" << endl;
    os << '}';
}
