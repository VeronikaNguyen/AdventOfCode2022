#include <iostream>
#include <vector>

#include "functions.cpp"


int main() {
    std::vector<std::string> rucksack = read_rucksack("day3");
    
    std::cout << "Solution part 1: " << compute_sum_of_priorities_for_same_item_in_comparments(rucksack) << std::endl;   

    std::cout << "\nSolution part 2: " << compute_sum_of_priorities_for_same_item_in_groups(rucksack) << std::endl;

    return 0;
}  

