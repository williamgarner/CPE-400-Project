#include "Network.h"

/// @name Network
/// @brief Constructor for the Network class.
Network::Network(const vector<vector<pair<int, int>>>& adj) : adj(adj) {}

/// @name route
/// @brief Implementation of Dijkstra's algorithm using the expected value of a certain route.
/// @details The expected value of a route is calculated as EX = cost * p(cost) + 10 * (1 - p(cost)).
/// @details The algorithm takes into account the cost of a link and the likelihood of the link succeeding.
void Network::route() {

}

/// @name print
/// @brief Prints out the adjacency matrix representing the network state, should only be used for debugging.
void Network::print() const {
    for (auto const& x : adj) {
        for (auto const& y : x) {
            string cost = "C: " + to_string(y.first);
            string prob = "P: " + to_string(y.second);
            string out = cost.append(" | ").append(prob);
            cout << out << endl;
        }
        cout << endl;
    }
}

/// @name operator<<
/// @brief Outputs GraphViz notation for use in visualizing the network.
std::ostream& operator<<(std::ostream& os, const Network& network) {

}
