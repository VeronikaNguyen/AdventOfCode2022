#include <deque>
#include <fstream>
#include <iostream>
#include <utility>
#include <string>
#include <vector>


auto read_heightmap(std::string file_name) {
    std::ifstream infile(file_name);
    std::string line = "";
    std::vector<std::vector<int>> heightmap;
    std::pair<int, int> start_position;
    std::pair<int, int> end_position;

    int row = 0;
    while (getline(infile, line)) {
        int col = 0;
        heightmap.push_back(std::vector<int>{});
        for (auto letter : line) {
            if (letter == 'S') {
                start_position = {row, col};
                heightmap[row].push_back((int) 'a' - 97);
            } else if (letter == 'E') {
                end_position = {row, col};
                heightmap[row].push_back((int) 'z' - 97);
            } else {
                heightmap[row].push_back((int) letter - 97);
            }
            col += 1;
        }
        row += 1;
    }

    struct heightmap_input {
        std::vector<std::vector<int>> heightmap;
        std::pair<int, int> start_position;
        std::pair<int, int> end_position;
    };

    return heightmap_input{heightmap, start_position, end_position}; 
}


bool set_steps(const std::vector<std::vector<int>>& heightmap, std::vector<std::vector<int>>& steps_from_S, std::pair<int, int> position, std::pair<int, int> neighbour_position) {
    if (heightmap[neighbour_position.first][neighbour_position.second] - heightmap[position.first][position.second] <= 1) {
        if (
            steps_from_S[neighbour_position.first][neighbour_position.second] == -1 
            or steps_from_S[neighbour_position.first][neighbour_position.second] > steps_from_S[position.first][position.second] + 1
        ) 
        {
            steps_from_S[neighbour_position.first][neighbour_position.second] = steps_from_S[position.first][position.second] + 1;
            return true;
        }
    }
    return false;
}


void determine_steps_for_neighbours(const std::vector<std::vector<int>>& heightmap, std::vector<std::vector<int>>& steps_from_S, std::deque<std::pair<int, int>>& queue) {
    std::pair<int, int> position = queue[0];
    if (position.first > 0) {
        if (set_steps(heightmap, steps_from_S, position, {position.first - 1, position.second})) {
            queue.push_back({position.first - 1, position.second});
        }
    } 
    if (position.first < heightmap.size() - 1) {
        if (set_steps(heightmap, steps_from_S, position, {position.first + 1, position.second})) {
            queue.push_back({position.first + 1, position.second});
        }
    } 
    if (position.second > 0) {
        if (set_steps(heightmap, steps_from_S, position, {position.first, position.second - 1})) {
            queue.push_back({position.first, position.second - 1});
        }
    } 
    if (position.second < heightmap[0].size() - 1) {
        if (set_steps(heightmap, steps_from_S, position, {position.first, position.second + 1})) {
            queue.push_back({position.first, position.second + 1});
            
        }
    }
    queue.pop_front();
    if (queue.size() > 0) {
        determine_steps_for_neighbours(heightmap, steps_from_S, queue);
    }
    return;
}


int determine_shortest_path_from_start_position(const std::vector<std::vector<int>>& heightmap, std::pair<int, int> start_position, std::pair<int, int> end_position) {
    std::vector<std::vector<int>> steps_from_S = heightmap;
    for (auto& vector : steps_from_S) {
        std::fill(vector.begin(), vector.end(), -1);
    }
    steps_from_S[start_position.first][start_position.second] = 0;
    
    std::deque<std::pair<int, int>> queue = {start_position};
    determine_steps_for_neighbours(heightmap, steps_from_S, queue);
    return steps_from_S[end_position.first][end_position.second];
}


int determine_shortest_path_from_any_start_position(const std::vector<std::vector<int>>& heightmap, std::pair<int, int> end_position) {
    int shortest_path = heightmap.size() * heightmap[0].size();
    int row = 0;
    for (auto& vector : heightmap) {
        int col = 0;
        for (auto height : vector) {
            if (height == 0) {
                int temp_path = determine_shortest_path_from_start_position(heightmap, {row, col}, end_position);
                shortest_path = (temp_path < shortest_path and temp_path != -1) ? temp_path : shortest_path;
            }
            col += 1;
        }
        row += 1;
    }
    return shortest_path;
}
