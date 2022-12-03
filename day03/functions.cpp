#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>


std::vector<std::string> read_rucksack(std::string file_name) {
    std::ifstream infile(file_name);
    std::string line = "";
    std::vector<std::string> rucksack;
    while (getline(infile, line, '\n')) {
        rucksack.push_back(line);
    }
    return rucksack;
}


char find_same_item_in_compartments(std::string items) {
    for (int item1_idx = 0; item1_idx < items.size() / 2; item1_idx++) {
        for (int item2_idx = items.size() / 2; item2_idx < items.size(); item2_idx++) {
            if (items[item1_idx] == items[item2_idx]) {
                return items[item1_idx];        
            }
        }
    }
    return '\0';
}


char find_same_item_in_groups(std::string items1, std::string items2, std::string items3) {
    for (auto item1 : items1) {
        for (auto item2 : items2) {
            for (auto item3 : items3) {
                if (item1 == item2 and item2 == item3) {
                    return item1;
                }
            }
        }
    }
    return '\0';
}


int compute_priority(char item) {
    int priority = 0;
    if (item > 96) {
        priority = (int) item - 96;
    } else {
        priority += (int) item - 64 + 26;
    }
    return priority;
}


int compute_sum_of_priorities_for_same_item_in_comparments(std::vector<std::string> rucksack) {
    int sum_of_priorities = 0;
    for (auto items : rucksack) {
        char same_item = find_same_item_in_compartments(items);
        sum_of_priorities += compute_priority(same_item);
    }
    return sum_of_priorities;
}


int compute_sum_of_priorities_for_same_item_in_groups(std::vector<std::string> rucksack) {
    int sum_of_priorities = 0;
    for(std::vector<std::string>::size_type items_idx = 0; items_idx < rucksack.size(); items_idx = items_idx + 3) {
        char same_item = find_same_item_in_groups(rucksack[items_idx], rucksack[items_idx + 1], rucksack[items_idx + 2]);
        sum_of_priorities += compute_priority(same_item);
    }
    return sum_of_priorities;
}
