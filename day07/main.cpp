#include <iostream>

#include "functions.cpp"


int main() {
    auto root = read_file_tree("day7");
    root->compute_size();
    
    std::cout << "Solution part 1: " << root->determine_sum_folders_smaller_than_number(100000) << std::endl;   

    std::cout << "\nSolution part 2: " << root->find_smallest_folder_above_number(30000000 - (70000000 - root->size), root->size) << std::endl;

    return 0;
}  
