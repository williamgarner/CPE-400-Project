#include "Network.h"

/// @name Network
/// @brief Constructor for the Network class.
Network::Network(const vector<vector<Link>>& adj) : adj(adj) {}

/// @name refresh
/// @brief Determines which nodes and edges go down and changes the adjacency matrix to the new state.
void Network::refresh() {

    ofstream graphOutputFile;
    graphOutputFile.open("../src/graphOutput.dot");
    if(graphOutputFile.good())
        graphOutputFile << *this;
    else
        cout << "Could not open file" << endl;
    graphOutputFile.close();
    system("dot -Tpng ../src/graphOutput.dot -o ../src/graph.png");
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
    int src = 0;
    for (auto const& x : adj) {
        int dest = 0;
        for (auto const& y : x) {
            cout << src << " --> " << dest++ << endl;
            string cost = "C: " + to_string(y.cost);
            string p_active = "P: " + to_string(y.p_active);
            string active = "A: " + string(y.active ? "true" : "false");
            string out = cost.append(" | ").append(p_active).append(" | ").append(active);
            cout << out << endl;
        }
        src++;
        cout << endl;
    }
}

/// @name operator<<
/// @brief Outputs GraphViz notation for use in visualizing the network.
std::ostream& operator<<(std::ostream& os, const Network& network) {
    vector<pair<int, int>> connection;
    vector<string> cities = {"Reno", "SEOUL", "São Paulo","Houston ", "Bombay", "JAKARTA", "Karachi", "Washington D.C." "Moscow", "Shanghai", "Mexico City", "London", "Rio de Janeiro", "Chicago", "Los Angeles" , "Sydney", "St Petersburg", "Baghdad", "Madrid" };
    os << "graph G{" << endl;
    int src = 0;
    int city = 0;
    for (auto const& x : network.adj) {
        int dest = 0;
        for (auto const& y : x) {
            if(y.active)
            {
                if(find(connection.begin(), connection.end(), make_pair(src, dest)) == connection.end())
                {
                	os << src << "[label = \"" << cities[src] << "\"]" << endl;
                	os << dest << "[label = \"" << cities[dest] << "\"]" << endl;
                    os << src << " -- " << dest << "[label= \" " << y.cost << "\"];" << endl;
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
