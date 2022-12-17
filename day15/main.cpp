#include <iostream>

#include "functions.cpp"


int main() {
    auto sensors_and_beacons = read_sensors_and_beacons("day15");
    
    std::cout << "Solution part 1: " << count_non_beacon_positions_on_row_minus_beacon(sensors_and_beacons, 2000000, 1, 0) << std::endl;   
     
    std::cout << "\nSolution part 2: " << compute_tuning_frequency(sensors_and_beacons, 0, 4000000) << std::endl;

    return 0;
}  
