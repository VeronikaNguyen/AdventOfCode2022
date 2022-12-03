#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>


std::vector<std::vector<int>> read_calories_entries_of_every_inventory(std::string file_name) {
    std::ifstream infile(file_name);
    std::string line = "";
    std::vector<std::vector<int>> calories_entries_of_every_inventory;
    std::vector<int> calories_entries_of_one_inventory;
    while (getline(infile, line, '\n')) {
	    if (line.empty()) {
	        calories_entries_of_every_inventory.push_back(calories_entries_of_one_inventory);
	        calories_entries_of_one_inventory.clear();
	        continue;
	    }
	    int calories = std::stoi(line);
        calories_entries_of_one_inventory.push_back(calories);
    }
    calories_entries_of_every_inventory.push_back(calories_entries_of_one_inventory);
    return calories_entries_of_every_inventory;
}


std::vector<int> determine_calories_sum_per_inventory(std::vector<std::vector<int>> calories_entries_of_every_inventory) {
    std::vector<int> calories_sum_of_every_inventory;
    for (auto inventory : calories_entries_of_every_inventory) {
        int temp_calories_sum = 0;
        for (auto calories : inventory) {
            temp_calories_sum += calories;
        }
	    calories_sum_of_every_inventory.push_back(temp_calories_sum);
    }
    return calories_sum_of_every_inventory;
}	    


int determine_max_calories_of_inventories(std::vector<int> calories_sum_of_every_inventory) {
    int max_calories = 0;
    for (auto calories : calories_sum_of_every_inventory) {
	    if (calories > max_calories) {
	        max_calories = calories;
	    }
    }
   return max_calories;
}


int determine_sum_calories_of_top_three_inventories(std::vector<int> calories_sum_of_every_inventory) {
    std::sort(calories_sum_of_every_inventory.begin(), calories_sum_of_every_inventory.end(), std::greater<>());
    return calories_sum_of_every_inventory[0] + calories_sum_of_every_inventory[1] + calories_sum_of_every_inventory[2];
}
