#include <array>
#include <deque>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <sstream>
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


auto read_stacks_and_moves(std::string file_name) {
    std::vector<std::deque<char>> stacks;
    std::vector<std::array<int, 3>> moves;

    std::ifstream infile(file_name);
    std::string line = "";
    bool read_stacks = true, initialize = true;
    while (getline(infile, line)) {
        bool first_empty_space = true;
        if (initialize) {
            for (int stack_len = 0; stack_len < 9; stack_len++) {
                stacks.push_back(std::deque<char>{});
            }
            initialize = false;
        }
        if (not line.empty() and read_stacks) {
            int stack_number = -1, empty_space = 0;
            bool read_stack = false;
            for (auto letter : line) {
                if (letter == ' ') {
                    empty_space += 1;
                    if (first_empty_space and empty_space % 3 == 0) {
                        stack_number += 1;
                        first_empty_space = false;
                        empty_space = 0;
                    } else if (empty_space % 5 == 0) {
                        stack_number += 1;
                        empty_space = 0;
                    }
                } else if (letter == '[') {
                    first_empty_space = false;
                    stack_number += 1;
                    read_stack = true;
                } else if (letter == ']') {
                    read_stack = false;
                    empty_space = 0;
                } else if (read_stack) {
                    stacks[stack_number].push_front(letter);
                }
            }
        } else if (line.empty()) {
            read_stacks = false;
        } else {
            auto splitted_line = split_string_by_delemeter(line, ' ');
            std::array<int, 3> move = {std::stoi(splitted_line[1]), std::stoi(splitted_line[3]) - 1, std::stoi(splitted_line[5]) - 1};
            moves.push_back(move);
        }
    }

    struct stacks_and_moves{
        std::vector<std::deque<char>> stacks;
        std::vector<std::array<int, 3>> moves;
    };

    return stacks_and_moves{stacks, moves}; 
}


std::string read_top_of_stacks(std::vector<std::deque<char>> stacks) {
    std::string top_of_stacks = "";
    for (auto stack : stacks) {
        if (!stack.empty()) {
            top_of_stacks += stack.back();
        }
    } 
    return top_of_stacks;
}


std::string read_top_of_stacks_after_move(std::vector<std::deque<char>> stacks, std::vector<std::array<int, 3>> moves) {
    for (auto move : moves) {
        for (int num_pop = 0; num_pop < move[0]; num_pop++) {
            if (!stacks[move[1]].empty()) {
                char element = stacks[move[1]].back();
                stacks[move[2]].push_back(element);    
                stacks[move[1]].pop_back();
            }
        }
    }
    return read_top_of_stacks(stacks);
}


std::string read_top_of_stacks_after_whole_stack_move(std::vector<std::deque<char>> stacks, std::vector<std::array<int, 3>> moves) {
    for (auto move : moves) {
        for (int num_pop = -move[0]; num_pop < 0; num_pop++) {
            if (num_pop + stacks[move[1]].size() >= 0) {
                char element = stacks[move[1]].at(stacks[move[1]].size() + num_pop);
                stacks[move[2]].push_back(element);    
            }
        }
        for (int num_pop = -move[0]; num_pop < 0; num_pop++) {
            stacks[move[1]].pop_back();
        }
    }
    return read_top_of_stacks(stacks);
}
