#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <sstream>
#include <string>
#include <vector>


template <typename Out>
void split_string_by_delemeter(const std::string &s, char delimeter, Out result) {
    std::istringstream iss(s);
    std::string item;
    while (std::getline(iss, item, delimeter)) {
        *result++ = item;
    }
}


std::vector<std::string> split_string_by_delemeter(const std::string &s, char delimeter) {
    std::vector<std::string> elements;
    split_string_by_delemeter(s, delimeter, std::back_inserter(elements));
    return elements;
}


auto read_valves_and_tunnels(std::string file_name) {
    std::ifstream infile(file_name);
    std::string line = "";
    std::map<std::string, int> valves;
    std::map<std::string, std::vector<std::string>> tunnels;

    while (getline(infile, line)) {
        std::vector<std::string> splitted_line = split_string_by_delemeter(line, ' ');
        valves[splitted_line[1]] = std::stoi(splitted_line[4].substr(5, splitted_line[4].size() - 1));
        for (int idx = 9; idx < splitted_line.size(); idx++) {
            tunnels[splitted_line[1]].push_back(splitted_line[idx].substr(0, 2));
        }
    }

    struct valves_and_tunnels {
        std::map<std::string, int> valves;
        std::map<std::string, std::vector<std::string>> tunnels;
    };

    return valves_and_tunnels {valves, tunnels}; 
}


void floyd_warshall(std::vector<std::vector<int>> &adjacency_matrix, int matrix_size) {
    for (int k = 0; k < matrix_size; k++) {
        for (int i = 0; i < matrix_size; i++) {
            for (int j = 0; j < matrix_size; j++) {
                if (adjacency_matrix[i][k] + adjacency_matrix[k][j] < adjacency_matrix[i][j] and adjacency_matrix[i][k] + adjacency_matrix[k][j] >= 0)
                    adjacency_matrix[i][j] = adjacency_matrix[i][k] + adjacency_matrix[k][j];
                    adjacency_matrix[j][i] = adjacency_matrix[i][j];
            }
        }
    }
    return;
}


std::map<std::string, std::vector<std::pair<std::string, int>>> determine_direct_tunnels(std::map<std::string, int> valves, std::map<std::string, std::vector<std::string>> tunnels) {
    std::vector<std::string> valves_with_flow;
    std::map<int, std::string> map_idx_to_valves;
    std::map<std::string, int> map_valves_to_idx;

    int idx = 0;
    for (auto valve : valves) {
        if (valve.second != 0) {
            valves_with_flow.push_back(valve.first);
        }
        map_idx_to_valves[idx] = valve.first;
        map_valves_to_idx[valve.first] = idx;
        idx += 1;
    }

    int num_valves = valves.size();
    std::vector<std::vector<int>> adjacency_matrix; 
    for (int row = 0; row < num_valves; row++) {
        adjacency_matrix.push_back(std::vector<int>{});
        for (int col = 0; col < num_valves; col++) {
            if (row == col) {
                adjacency_matrix[row].push_back(0);
            } else {
                adjacency_matrix[row].push_back(std::numeric_limits<int>::max());
            }
        }
    }

    for (auto tunnel : tunnels) {
        for (auto neighbour : tunnel.second) {
            adjacency_matrix[map_valves_to_idx[tunnel.first]][map_valves_to_idx[neighbour]] = 1;
            adjacency_matrix[map_valves_to_idx[neighbour]][map_valves_to_idx[tunnel.first]] = 1;
        }
    }
    
    floyd_warshall(adjacency_matrix, num_valves);

    std::map<std::string, std::vector<std::pair<std::string, int>>> direct_tunnels;
    for (auto valve : valves_with_flow) {
        direct_tunnels["AA"].push_back(std::pair<std::string, int> {valve, adjacency_matrix[map_valves_to_idx["AA"]][map_valves_to_idx[valve]]});
    }
    for (auto valve1 : valves_with_flow) {
        direct_tunnels[valve1] = std::vector<std::pair<std::string, int>>{};
        for (auto valve2 : valves_with_flow) {
            direct_tunnels[valve1].push_back(std::pair<std::string, int> {valve2, adjacency_matrix[map_valves_to_idx[valve1]][map_valves_to_idx[valve2]]});
        }
    }
    return direct_tunnels;
}


int compute_highest_pressure(std::map<std::string, int> valves, std::map<std::string, std::vector<std::string>> tunnels, int minutes) {
    std::map<std::string, std::vector<std::pair<std::string, int>>> direct_tunnels = determine_direct_tunnels(valves, tunnels);
    return 0;
}