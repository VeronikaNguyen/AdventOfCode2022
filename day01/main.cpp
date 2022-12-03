#include <iostream>
#include <vector>

#include "functions.cpp"


int main() {
    std::vector<std::vector<int>> calories_entries_of_every_inventory = read_calories_entries_of_every_inventory("day1");
    std::vector<int> calories_sum_of_every_inventory = determine_calories_sum_per_inventory(calories_entries_of_every_inventory);
    
    std::cout << "Solution part 1: " << determine_max_calories_of_inventories(calories_sum_of_every_inventory) << std::endl;   

    std::cout << "\nSolution part 2: " << determine_sum_calories_of_top_three_inventories(calories_sum_of_every_inventory) << std::endl;

    return 0;
}  

