#include <iostream>
#include <vector>

#include "functions.cpp"


int main() {
    std::vector<std::vector<int>> assignments = read_assignments("day4");
    
    std::cout << "Solution part 1: " << count_fully_contained_assignments(assignments) << std::endl;   

    std::cout << "\nSolution part 2: " << count_overlapping_assignments(assignments) << std::endl;

    return 0;
}  

