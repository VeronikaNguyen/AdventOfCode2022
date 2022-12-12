#include <iostream>

#include "functions.cpp"


int main() {
    auto heightmap_input = read_heightmap("day12");
    
    std::cout << "Solution part 1: " << determine_shortest_path_from_start_position(heightmap_input.heightmap, heightmap_input.start_position, heightmap_input.end_position) << std::endl;   

    std::cout << "\nSolution part 2: " << determine_shortest_path_from_any_start_position(heightmap_input.heightmap, heightmap_input.end_position)  << std::endl;

    return 0;
}  
