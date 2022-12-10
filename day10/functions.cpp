#include <fstream>
#include <iostream>
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


auto read_instructions(std::string file_name) {
    std::ifstream infile(file_name);
    std::string line = "";
    std::vector<std::vector<std::string>> instructions;

    while (getline(infile, line)) {
        instructions.push_back(split_string_by_delemeter(line, ' '));
    }
    return instructions; 
}


std::map<int, int> compute_register_values(std::vector<std::vector<std::string>> instructions) {
    int cycle = 1;
    int register_value = 1;
    std::map<int, int> register_values;
    for (auto instruction : instructions) {
        if (instruction[0] == "addx") {
            register_values[cycle] = register_value;
            register_values[cycle + 1] = register_value;
            register_value += std::stoi(instruction[1]);
            cycle += 2;
        } else {
            register_values[cycle] = register_value;
            cycle += 1;
        }
    }
    return register_values;
}


int compute_signal_strengths_sum_at_rounds(std::map<int, int> register_values, std::vector<int> rounds) {
    int round_idx = 0;
    int signal_strengths_sum = 0;
    for (std::map<int, int>::iterator iter = register_values.begin(); iter != register_values.end(); ++iter) {
        if (round_idx < rounds.size() and rounds[round_idx] == iter->first) {
            signal_strengths_sum += iter->second * rounds[round_idx];
            round_idx += 1;
        }
    }
    return signal_strengths_sum;
}


void print_sprite(std::map<int, int> register_values, std::vector<int> rounds, int modulus) {
    int round_idx = 0;
    int row = 0;
    std::vector<std::string> sprite;
    for (auto round : rounds) {
        sprite.push_back(std::string (modulus, '.'));
    }
    for (std::map<int, int>::iterator cycle = register_values.begin(); cycle != register_values.end(); ++cycle) {
        int position = (cycle->first - 1) % modulus;
        if (round_idx < rounds.size() and rounds[round_idx] == cycle->first) {
            round_idx += 1;
            row += 1;
        }
        if (row >= rounds.size()) {
            break;
        }
        if (abs(register_values[cycle->first] - position) <= 1) {
            sprite[row][position] = '#';
        } 
    }
    for (auto line : sprite) {
        std::cout << line << std::endl;
    }
    return;
}