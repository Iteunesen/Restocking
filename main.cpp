#include <iostream>

#include "Network.hpp"
#include <utility>
#include <queue>

int main() {
    Network network;

    std::vector<std::vector<std::pair<int, int>>> graph(network.getNoLocations(), std::vector<std::pair<int, int>> (network.getNoLocations(), {0,0}));
    std::vector<Highway> edges = network.getEdges();

    for(Highway& edge : edges) {
        graph[edge.getStart()][edge.getDestination()] = {edge.getLength(), edge.getCapacity()}; 
    }

    int totalMaxFlow = 0;
    int timesToRun = network.getTime();

    for(int i = 0; i < timesToRun; i++) {
        int maxFlow = network.fordFulkerson(graph, 0, network.getNoLocations() - 1);
        //std::cout << "Max flow at " << network.getTime() << " is " << maxFlow << "\n"; 
        totalMaxFlow += maxFlow;
        network.setTime(network.getTime()-1);
    }
    
    std::cout << totalMaxFlow;
    //std::cout << "Total flow possible through network is: " << totalMaxFlow << "\n";
}