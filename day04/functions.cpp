#include <fstream>
#include <iostream>
#include <vector>


std::vector<std::vector<int>> read_assignments(std::string file_name) {
    std::ifstream infile(file_name);
    std::string line = "";
    std::vector<std::vector<int>> assignments;
    while (getline(infile, line, '\n')) {
        std::vector<int> assignment;
        int start_idx = 0;
        for (std::string::size_type idx = 0; idx < line.size(); idx++) {
            if (line[idx] == '-' or line[idx] == ',') {
                assignment.push_back(std::stoi(line.substr(start_idx, idx - start_idx)));
                start_idx = idx + 1;
            } else if (idx == line.size() - 1) {
                assignment.push_back(std::stoi(line.substr(start_idx, idx - start_idx + 1)));
            }
        }
        assignments.push_back(assignment);
    }
    return assignments;
}


int count_fully_contained_assignments(std::vector<std::vector<int>> assignments) {
    int counter_fully_contained_assignments = 0;
    for (auto assignment : assignments) {
        if (assignment[0] <= assignment[2] and assignment[1] >= assignment[3]) {
            counter_fully_contained_assignments += 1;
        } else if (assignment[0] >= assignment[2] and assignment[1] <= assignment[3]) {
            counter_fully_contained_assignments += 1;
        }
    }
    return counter_fully_contained_assignments;
}


int count_overlapping_assignments(std::vector<std::vector<int>> assignments) {
    int counter_overlapping_assignments = 0;
    for (auto assignment : assignments) {
        if (assignment[0] <= assignment[2] and assignment[1] >= assignment[2]) {
            counter_overlapping_assignments += 1;
        } else if (assignment[0] <= assignment[3] and assignment[1] >= assignment[3]) {
            counter_overlapping_assignments += 1;
        } else if (assignment[2] <= assignment[0] and assignment[3] >= assignment[0]) {
            counter_overlapping_assignments += 1;
        } else if (assignment[2] <= assignment[1] and assignment[3] >= assignment[1]) {
            counter_overlapping_assignments += 1;
        }
    }
    return counter_overlapping_assignments;
}
