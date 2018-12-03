#include "Network.h"

/// @name Network
/// @brief Constructor for the Network class.
Network::Network(const vector<vector<Link>>& adj) : adj(adj) {}

/// @name refresh
/// @brief Determines which nodes and edges go down and changes the adjacency matrix to the new state.
void Network::refresh() {

}

/// @name route
/// @brief Implementation of Dijkstra's algorithm using the expected value of a certain route.
/// @details The expected value of a route is calculated as EX = cost * p(cost) + 10 * (100 - p(cost)).
/// @details The algorithm takes into account the cost of a link and the likelihood of the link succeeding.
void Network::route() {

}

/// @name print
/// @brief Prints out the adjacency matrix representing the network state, should only be used for debugging.
void Network::print() const {
    for (auto const& x : adj) {
        for (auto const& y : x) {
            string cost = "C: " + to_string(y.cost);
            string p_active = "P: " + to_string(y.p_active);
            string active = "A: " + string(y.active ? "true" : "false");
            string out = cost.append(" | ").append(p_active).append(" | ").append(active);
            cout << out << endl;
        }
        cout << endl;
    }
}

/// @name operator<<
/// @brief Outputs GraphViz notation for use in visualizing the network.
std::ostream& operator<<(std::ostream& os, const Network& network) {

}
