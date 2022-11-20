#include "Network.hpp"

Network::Network() 
{
    std::string line;
    std::string number;
    int i = 0;
    getline(std::cin, line);
    for(auto x : line) {
        if (x == ' ') {
            if(i == 0) {
                nLocations = std::stoi(number);
                number = "";
            } else if (i == 1) {
                nHighways = std::stoi(number);
                number = "";
            }
            i++;
        } else {
            number = number + x;
        }
    }
    time = std::stoi(number);
    i = 0;
    number = "";
    while (getline(std::cin, line)) {
        int start = 0, destination = 0, length = 0, capacity = 0;
        for(auto x : line) {
            if (x == ' ') {
                if(i == 0) {
                    start = std::stoi(number);
                    number = "";
                } else if (i == 1) {
                    destination = std::stoi(number);
                    number = "";
                } else if (i == 2) {
                    length = std::stoi(number); 
                    number = ""; 
                } 
                i++;
            } else {
                number = number + x;
            }
        }
        capacity = std::stoi(number);
        number = "";
        i = 0;
        Highway edge(length, capacity, start, destination);
        edges.push_back(edge);
    }
    // std::ifstream myfile ("input.txt");

    // if(myfile.is_open()) {
    //     getline(myfile, line);
    //     for(auto x : line) {
    //         if (x == ' ') {
    //             if(i == 0) {
    //                 nLocations = std::stoi(number);
    //                 number = "";
    //             } else if (i == 1) {
    //                 nHighways = std::stoi(number);
    //                 number = "";
    //             }
    //             i++;
    //         } else {
    //             number = number + x;
    //         }
    //     }
    //     time = std::stoi(number);
    //     i = 0;
    //     number = "";
        
    //     while (getline(myfile, line)) {
    //         int start = 0, destination = 0, length = 0, capacity = 0;
    //         for(auto x : line) {
    //             if (x == ' ') {
    //                 if(i == 0) {
    //                     start = std::stoi(number);
    //                     number = "";
    //                 } else if (i == 1) {
    //                     destination = std::stoi(number);
    //                     number = "";
    //                 } else if (i == 2) {
    //                     length = std::stoi(number); 
    //                     number = ""; 
    //                 } 
    //                 i++;
    //             } else {
    //                 number = number + x;
    //             }
    //         }
    //         capacity = std::stoi(number);
    //         number = "";
    //         i = 0;
    //         Highway edge(length, capacity, start, destination);
    //         edges.push_back(edge);
    //     }
    //     myfile.close();
    // } else {
    //     std::cout << "Can't open file" << "\n";
    // }
}

Network::~Network() 
{    
}

void Network::printPath(std::vector<int> path) {
    std::cout << "Path: "; 
    for(int i = 0; i < path.size(); i++) {
        std::cout << path[i] << " ";
    }
    std::cout << "\n";
}

std::vector<int> Network::backtrace(std::vector<int>& parent, int s, int t) {
    std::vector<int> path;
    path.push_back(t);
    while(!(std::find(path.begin(), path.end(), s) != path.end())) {
        path.push_back(parent[path.back()]);
    }
    std::reverse(path.begin(), path.end());
    return path;
}

int Network::calcPathLength(std::vector<int>& path, std::vector<std::vector<std::pair<int, int>>> rGraph) {
    int length = 0;
    for(int i = 0; i < path.size() -1; i ++) {
        length += rGraph[path[i]][path[i+1]].first;
    }
    return length;
}

bool Network::bfs(std::vector<std::vector<std::pair<int, int>>> rGraph, int s, int t, std::vector<int>& parent) {
    std::vector<bool> visited(nLocations, 0);
    std::queue<int> q;
    std::vector<int> path;
    //path.push_back(s);

    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while(!q.empty()) {
        int u = q.front();
        q.pop();

        for(int v = 0; v < nLocations; v++) {
            if(visited[v] == false && rGraph[u][v].second > 0) {
                if(v == t) {
                    parent[v] = u;
                    std::vector<int> path = backtrace(parent, s, t);
                    //printPath(path);
                    //std::cout << "Path length: " << calcPathLength(path, rGraph) << "\n";
                    if(calcPathLength(path, rGraph) <= time) {
                        return true;
                    }   
                }

                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
    return false;
}

void Network::printGraphCapacity(std::vector<std::vector<std::pair<int, int>>> graph) {
    for(int i = 0; i < graph.size(); i++) {
        for(int j = 0; j < graph[0].size(); j++) {
            std::cout << graph[i][j].second << " ";
        }
        std::cout << "\n";
    }
}

int Network::fordFulkerson(std::vector<std::vector<std::pair<int, int>>> graph, int s, int t) {
    int u, v;
    std::vector<std::vector<std::pair<int, int>>> rGraph (nLocations, std::vector<std::pair<int, int>> (nLocations, {0,0}));
    for(u = 0; u < nLocations; u++) {
        for(v = 0; v < nLocations; v++) {
            rGraph[u][v] = graph[u][v];
        }
    }
    std::vector<int> parent(nLocations, 0);

    int maxFlow = 0;
    while(bfs(rGraph, s, t, parent)) {
        int pathFlow = INT_MAX;
        for(v = t; v != s; v = parent[v]) {
            u = parent[v];
            pathFlow = std::min(pathFlow, rGraph[u][v].second);         
        }

        for(v = t; v != s; v = parent[v]) {
            u = parent[v];
            rGraph[u][v].second -= pathFlow;
            rGraph[v][u].second += pathFlow;
        }
        maxFlow += pathFlow;
    }
    return maxFlow;
}

const std::vector<Highway>& Network::getEdges() {
    return edges;
}

int Network::getNoLocations() {
    return nLocations;
}

int Network::getNoHighways() {
    return nHighways;
}

int Network::getTime() {
    return time;
}

void Network::setTime(int aTime) {
    time = aTime;
}