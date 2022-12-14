#include <iostream>

#include "functions.cpp"


int main() {
    auto paths = read_paths("day14");
    
    std::cout << "Solution part 1: " << count_sand_particles(paths, true) << std::endl;   

    std::cout << "\nSolution part 2: " << count_sand_particles(paths, false) << std::endl;

    return 0;
}  
