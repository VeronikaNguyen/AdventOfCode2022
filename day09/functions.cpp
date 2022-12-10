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


template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}


auto read_instructions(std::string file_name) {
    std::ifstream infile(file_name);
    std::string line = "";
    std::vector<std::vector<std::string>> instructions;

    while (getline(infile, line)) {
        instructions.push_back(split_string_by_delemeter(line, ' '));
    }
    return instructions; 
}


std::pair<int, int> move_head(std::vector<std::string> instruction, std::pair<int, int> head_position) {
    if (instruction[0] == "L") {
        head_position.first -= 1;
    } else if (instruction[0] == "R") {
        head_position.first += 1;
    } else if (instruction[0] == "U") {
        head_position.second += 1;
    } else if (instruction[0] == "D") {
        head_position.second -= 1;
    }
    return head_position;
}


std::pair<int, int> move_tail(std::pair<int, int> head_position, std::pair<int, int> tail_position) {
    if (head_position.first == tail_position.first and abs(head_position.second - tail_position.second) >= 2) {
        tail_position.second += sgn(head_position.second - tail_position.second);
    } else if (head_position.second == tail_position.second and abs(head_position.first - tail_position.first) >= 2) {
        tail_position.first += sgn(head_position.first - tail_position.first);
    } else if (abs(head_position.first - tail_position.first) == 1 and abs(head_position.second - tail_position.second) >= 2) {
        tail_position.first = head_position.first;
        tail_position.second += sgn(head_position.second - tail_position.second);
    } else if (abs(head_position.second - tail_position.second) == 1 and abs(head_position.first - tail_position.first) >= 2) {
        tail_position.second = head_position.second;
        tail_position.first += sgn(head_position.first - tail_position.first);
    } else if (abs(head_position.first - tail_position.first) == 2 and abs(head_position.second - tail_position.second) == 2) {
        tail_position.first += sgn(head_position.first - tail_position.first);
        tail_position.second += sgn(head_position.second - tail_position.second);
    }
    return tail_position;
}


int determine_visited_positions(std::vector<std::vector<std::string>> instructions, int knots) {
    std::vector<std::pair<int, int>> knot_positions;
    for (int knot = 0; knot < knots; knot++) {
        knot_positions.push_back(std::pair<int, int> (0, 0));
    }
    std::set<std::pair<int, int>> visited_positions;
    for (auto instruction : instructions) {
        for (int step = 0; step < std::stoi(instruction[1]); step++) {
            knot_positions[0] = move_head(instruction, knot_positions[0]);
            for (int knot = 1; knot < knots; knot++) {
                knot_positions[knot] = move_tail(knot_positions[knot - 1], knot_positions[knot]);
            }
            visited_positions.insert(knot_positions[knots - 1]);
        }
    }
    return visited_positions.size();
}
