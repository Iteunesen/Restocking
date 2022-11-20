#ifndef NETWORK_HPP_
#define NETWORK_HPP_

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <queue>
#include <climits>
#include <algorithm>

#include "Highway.hpp"

class Network {
    public:
        Network();
        virtual ~Network();

        int getNoLocations();
        int getNoHighways();
        int getTime();
        void setTime(int aTime);

        const std::vector<Highway>& getEdges();

        void printGraphCapacity(std::vector<std::vector<std::pair<int, int>>> graph);
        void printPath(std::vector<int> path);

        int calcPathLength(std::vector<int>& path, std::vector<std::vector<std::pair<int, int>>> rGraph);
        bool bfs(std::vector<std::vector<std::pair<int, int>>> rGraph, int s, int t, std::vector<int>& parent);
        std::vector<int> backtrace(std::vector<int>& parent, int s, int t);
        int fordFulkerson(std::vector<std::vector<std::pair<int, int>>> graph, int s, int t);

    private:
        int nLocations;
        int nHighways;
        int time;
        //Node source;
        //Node sink;
        std::vector<Highway> edges;
};

#endif 