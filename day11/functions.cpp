#include <algorithm>
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


struct Monkey {
    std::vector<int> items;
    std::string operation;
    int test_number;
    int if_true_to_monkey;
    int if_false_to_monkey;
};


auto read_monkeys(std::string file_name) {
    std::ifstream infile(file_name);
    std::string line = "";
    std::vector<Monkey> monkeys;
    int line_counter = 0;

    while (getline(infile, line)) {
        if (line_counter % 7 == 0) {
            std::vector<std::string> splitted_line = split_string_by_delemeter(line, ' ');
            monkeys.push_back(Monkey());
        } else if (line_counter % 7 == 1) {
            std::vector<std::string> splitted_line = split_string_by_delemeter(line, ':');
            splitted_line = split_string_by_delemeter(splitted_line[1], ',');
            for (auto item : splitted_line) {
                monkeys.back().items.push_back(std::stoi(item));
            }
        } else if (line_counter % 7 == 2) {
            std::vector<std::string> splitted_line = split_string_by_delemeter(line, '=');
            monkeys.back().operation = splitted_line[1];
        } else if (line_counter % 7 == 3) {
            std::vector<std::string> splitted_line = split_string_by_delemeter(line, ' ');
            monkeys.back().test_number = std::stoi(splitted_line.back());
        } else if (line_counter % 7 == 4) {
            std::vector<std::string> splitted_line = split_string_by_delemeter(line, ' ');
            monkeys.back().if_true_to_monkey = std::stoi(splitted_line.back());
        } else if (line_counter % 7 == 5) {
            std::vector<std::string> splitted_line = split_string_by_delemeter(line, ' ');
            monkeys.back().if_false_to_monkey = std::stoi(splitted_line.back());
        }
        line_counter += 1;
    }
    return monkeys; 
}


unsigned long long compute_mod(unsigned long long number, int modulus) {
    number %= modulus;
    if (number < 0) {
        number += modulus;
    }
    return number;
}


unsigned long long compute_operation(unsigned long long item, std::string operation, bool divide_by_three, int modulus) {
    std::vector<std::string> splitted_operation = split_string_by_delemeter(operation, ' ');
    if (!divide_by_three) {
        item = compute_mod(item, modulus);
    }
    
    if ("old" == splitted_operation[1] and "old" == splitted_operation[3]) {
        if (splitted_operation[2] == "*") {
            item = item * item;
        } else if (splitted_operation[2] == "+") {
            item = item + item;
        }
    } else if ("old" == splitted_operation[1]) {
        if (splitted_operation[2] == "*") {
            item = item * std::stoi(splitted_operation[3]);
        } else if (splitted_operation[2] == "+") {
            item = item + std::stoi(splitted_operation[3]);
        }
    }
    if (divide_by_three) {
        item /= 3;
    } else {
        item = compute_mod(item, modulus);
    }
    return item;
}


void pass_item_to_next_monkey(std::vector<Monkey>& monkeys, int monkey, unsigned long long item) {
    if (item % monkeys[monkey].test_number == 0) {
        monkeys[monkeys[monkey].if_true_to_monkey].items.push_back(item);
    } else {
        monkeys[monkeys[monkey].if_false_to_monkey].items.push_back(item);
    }
    return;
}


unsigned long long compute_monkey_business_from_inspected_items(std::vector<unsigned long long>& inspected_items) {
    std::sort(inspected_items.begin(), inspected_items.end());
    return inspected_items[inspected_items.size() - 1] * inspected_items[inspected_items.size() - 2];
}


unsigned long long compute_monkey_business(std::vector<Monkey>& monkeys, int rounds, bool divide_by_three) {
    int modulus = 1;
    std::vector<unsigned long long> inspected_items;
    for (auto monkey : monkeys) {
        inspected_items.push_back(0);
        modulus *= monkey.test_number;
    }
    for (int round = 0; round < rounds; round++) {
        for (int monkey = 0; monkey < monkeys.size(); monkey++) {
            inspected_items[monkey] += monkeys[monkey].items.size();
            for (int item_idx = 0; item_idx < monkeys[monkey].items.size(); item_idx++) {
                int item = monkeys[monkey].items[item_idx];
                item = compute_operation(item, monkeys[monkey].operation, divide_by_three, modulus);
                pass_item_to_next_monkey(monkeys, monkey, item);
            }
            monkeys[monkey].items.clear();
        }
    }
    return compute_monkey_business_from_inspected_items(inspected_items);
}
