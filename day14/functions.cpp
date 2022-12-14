#include <fstream>
#include <iostream>
#include <set>
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


auto read_paths(std::string file_name) {
    std::ifstream infile(file_name);
    std::string line = "";
    std::vector<std::vector<std::pair<int, int>>> paths;

    while (getline(infile, line)) {
        std::vector<std::pair<int, int>> path;
        std::vector<std::string> splitted_line = split_string_by_delemeter(line, ' ');
        for (int idx = 0; idx < splitted_line.size(); idx = idx + 2) {
            std::vector<std::string> pair = split_string_by_delemeter(splitted_line[idx], ',');
            path.push_back({std::stoi(pair[0]), std::stoi(pair[1])});
        }
        paths.push_back(path);
    }
    return paths; 
}


void insert_path_in_cave(std::set<std::pair<int, int>>& cave, std::pair<int, int> start_point, std::pair<int, int> end_point) {
    int start = 0;
    int end = 0;

    if (start_point.first == end_point.first) {
        if (start_point.second < end_point.second) {
            start = start_point.second;
            end = end_point.second;
        } else {
            start = end_point.second;
            end = start_point.second;
        }
        for (int second = start; second <= end; second++) {
            cave.insert({start_point.first, second});
        }
    } else if (start_point.second == end_point.second) {
        if (start_point.first < end_point.first) {
            start = start_point.first;
            end = end_point.first;
        } else {
            start = end_point.first;
            end = start_point.first;
        }
        for (int first = start; first <= end; first++) {
            cave.insert({first, start_point.second});
        }
    }
    return;
}


int determine_highest_coordinate(const std::vector<std::vector<std::pair<int, int>>>& paths) {
    int highest_coordinate = 0;
    for (auto path : paths) {
        for (auto coordinate : path) {
            if (highest_coordinate < coordinate.second) {
                highest_coordinate = coordinate.second;
            }
        }
    }
    return highest_coordinate;
}


std::set<std::pair<int, int>> construct_cave(std::vector<std::vector<std::pair<int, int>>>& paths) {
    std::set<std::pair<int, int>> cave;
    for (auto path : paths) {
        for (int idx = 1; idx < path.size(); idx++) {
            insert_path_in_cave(cave, path[idx - 1], path[idx]);
        }
    }   
    return cave;
}


enum Flow{below, left, right, stop};


Flow check_flow(std::pair<int, int>& sand, const std::set<std::pair<int, int>>& cave, const std::set<std::pair<int, int>>& sand_particles) {
    if (!cave.count({sand.first, sand.second + 1}) and !sand_particles.count({sand.first, sand.second + 1})) {
        sand = {sand.first, sand.second + 1};
        return Flow::below;
    } else if (!cave.count({sand.first - 1, sand.second + 1}) and !sand_particles.count({sand.first - 1, sand.second + 1})) {
        sand = {sand.first - 1, sand.second + 1};
        return Flow::left;
    } else if (!cave.count({sand.first + 1, sand.second + 1}) and !sand_particles.count({sand.first + 1, sand.second + 1})) {
        sand = {sand.first + 1, sand.second + 1};
        return Flow::right;
    } else {
        return Flow::stop;
    }
}


std::set<std::pair<int, int>> simulate_sand_particles(const std::set<std::pair<int, int>>& cave, int highest_coordinate, bool abyss) {
    std::set<std::pair<int, int>> sand_particles;
    if (abyss) {
        bool flows_in_abyss = false;
        while (!flows_in_abyss) {
            std::pair<int, int> sand = {500, 0};
            while (check_flow(sand, cave, sand_particles) != Flow::stop) {
                if (sand.second > highest_coordinate) {
                    flows_in_abyss = true;
                    break;
                }
            }
            if (!flows_in_abyss) {
                sand_particles.insert(sand);
            }
        }
    } else {
        std::pair<int, int> sand = {0, 0};
        while (sand != std::pair<int, int>{500, 0}) {
            sand = {500, 0};
            while (check_flow(sand, cave, sand_particles) != Flow::stop) {
                if (sand.second == highest_coordinate + 1) {
                    break;
                }
            }
            sand_particles.insert(sand);
        }
    }
    return sand_particles;
}


int count_sand_particles(std::vector<std::vector<std::pair<int, int>>>& paths, bool abyss) {
    std::set<std::pair<int, int>> cave = construct_cave(paths);
    int highest_coordinate = determine_highest_coordinate(paths);
    std::set<std::pair<int, int>> sand_particles = simulate_sand_particles(cave, highest_coordinate, abyss);
    return sand_particles.size();
}
