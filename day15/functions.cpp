#include <fstream>
#include <iostream>
#include <set>
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


auto read_sensors_and_beacons(std::string file_name) {
    std::ifstream infile(file_name);
    std::string line = "";
    std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> sensors_and_beacons;

    while (getline(infile, line)) {
        std::vector<std::string> splitted_line = split_string_by_delemeter(line, ' ');
        std::pair<int, int> sensor;
        std::pair<int, int> beacon;
        
        sensor.first = std::stoi(splitted_line[2].substr(2, splitted_line[2].size() - 3));
        sensor.second = std::stoi(splitted_line[3].substr(2, splitted_line[3].size() - 3));
    
        beacon.first = std::stoi(splitted_line[8].substr(2, splitted_line[8].size() - 3));
        beacon.second = std::stoi(splitted_line[9].substr(2, splitted_line[9].size() - 2));
        
        sensors_and_beacons.push_back({sensor, beacon});
    }
    return sensors_and_beacons; 
}


int compute_hamilton_distance(const std::pair<std::pair<int, int>, std::pair<int, int>>& sensor_and_beacon) {
    int sensor_x = sensor_and_beacon.first.first;
    int sensor_y = sensor_and_beacon.first.second;

    int beacon_x = sensor_and_beacon.second.first;
    int beacon_y = sensor_and_beacon.second.second;

    return abs(sensor_x - beacon_x) + abs(sensor_y - beacon_y);
}


std::set<int> determine_beacon_positions(const std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>& sensors_and_beacons, int row, int min_coordinate, int max_coordinate) {
    std::set<int> beacon_positions;
    for (auto sensor_and_beacon : sensors_and_beacons) {
        if (row == sensor_and_beacon.second.second and min_coordinate <= sensor_and_beacon.second.first and sensor_and_beacon.second.second <= max_coordinate) {
            beacon_positions.insert(sensor_and_beacon.second.first);
        }
    }
    return beacon_positions;
}


std::vector<std::pair<int, int>> determine_non_beacon_intervals_on_row(const std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>& sensors_and_beacons, int row) {
    std::vector<std::pair<int, int>> non_beacon_intervals;
    int new_min_coordinate = sensors_and_beacons[0].second.first;
    int new_max_coordinate = sensors_and_beacons[0].second.second;
    for (auto sensor_and_beacon : sensors_and_beacons) {
        std::pair<int, int> non_beacon_interval;
        int hamilton_distance = compute_hamilton_distance(sensor_and_beacon);
        if (abs(row - sensor_and_beacon.first.second) <= hamilton_distance) {
            non_beacon_interval.first = sensor_and_beacon.first.first - (hamilton_distance - abs(row - sensor_and_beacon.first.second));
            non_beacon_interval.second = sensor_and_beacon.first.first + (hamilton_distance - abs(row - sensor_and_beacon.first.second));
            non_beacon_intervals.push_back(non_beacon_interval);
        }
    }
    return non_beacon_intervals;
}


std::vector<std::pair<int, int>> cut_intervals(std::vector<std::pair<int, int>> non_beacon_intervals, std::vector<std::pair<int, int>> beacon_intervals) {
    for (auto non_beacon_interval : non_beacon_intervals) {
        std::vector<std::pair<int, int>> new_beacon_intervals;
        for (auto beacon_interval : beacon_intervals) {
            if (
                beacon_interval.first > beacon_interval.second 
                or (non_beacon_interval.first <= beacon_interval.first and non_beacon_interval.second >= beacon_interval.second)
            ) {
                continue;
            } else if (
                non_beacon_interval.first >= beacon_interval.first and non_beacon_interval.first <= beacon_interval.second
                and non_beacon_interval.second >= beacon_interval.first and non_beacon_interval.second <= beacon_interval.second
            ) { 
                new_beacon_intervals.push_back({beacon_interval.first, non_beacon_interval.first - 1});
                new_beacon_intervals.push_back({non_beacon_interval.second + 1, beacon_interval.second});
            } else if (
                non_beacon_interval.first >= beacon_interval.first and non_beacon_interval.first <= beacon_interval.second
            ) {
                new_beacon_intervals.push_back({beacon_interval.first, non_beacon_interval.first - 1});
            } else if (
                non_beacon_interval.second >= beacon_interval.first and non_beacon_interval.second <= beacon_interval.second
            ) {
                new_beacon_intervals.push_back({non_beacon_interval.second + 1, beacon_interval.second});
            } else {
                new_beacon_intervals.push_back(beacon_interval);
            }
        }
        beacon_intervals = new_beacon_intervals;
    }
    std::vector<std::pair<int, int>> new_beacon_intervals;
    for (auto beacon_interval : beacon_intervals) {
        if (beacon_interval.first > beacon_interval.second) {
            continue;
        }
        else {
            new_beacon_intervals.push_back(beacon_interval);
        }
    }
    return new_beacon_intervals;
}


std::vector<std::pair<int, int>> determine_beacon_intervals(
    const std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>& sensors_and_beacons, 
    int row, int& min_coordinate, int& max_coordinate
) {
    std::vector<std::pair<int, int>> non_beacon_intervals = determine_non_beacon_intervals_on_row(sensors_and_beacons, row);
    if (min_coordinate > max_coordinate) {
        for (auto interval : non_beacon_intervals) {
            min_coordinate = (min_coordinate > interval.first) ? interval.first : min_coordinate;
            max_coordinate = (max_coordinate < interval.second) ? interval.second : max_coordinate;
        }
    }
    return cut_intervals(non_beacon_intervals, {{min_coordinate, max_coordinate}});
}


int count_non_beacon_positions_on_row(
    std::vector<std::pair<int, int>> beacon_intervals,
    int row, int min_coordinate, int max_coordinate
) {
    int count_non_beacon_postions = max_coordinate - min_coordinate + 1;
    for (auto interval : beacon_intervals) {
        count_non_beacon_postions -= interval.second - interval.first + 1;
    }
    return count_non_beacon_postions;
}


int count_non_beacon_positions_on_row_minus_beacon(
    const std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>& sensors_and_beacons, int row, int min_coordinate, int max_coordinate
) {
    std::vector<std::pair<int, int>> beacon_intervals = determine_beacon_intervals(sensors_and_beacons, row, min_coordinate, max_coordinate);
    std::set<int> beacon_positions = determine_beacon_positions(sensors_and_beacons, row, min_coordinate, max_coordinate);
    int count_non_beacon_postions = count_non_beacon_positions_on_row(beacon_intervals, row, min_coordinate, max_coordinate) - beacon_positions.size();
    return count_non_beacon_postions;
}


unsigned long long int compute_tuning_frequency(
    const std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>& sensors_and_beacons, 
    int min_coordinate,
    int max_coordinate
) {
    for (int row = 0; row <= max_coordinate; row++) {
        std::vector<std::pair<int, int>> beacon_intervals = determine_beacon_intervals(sensors_and_beacons, row, min_coordinate, max_coordinate);      
        if (count_non_beacon_positions_on_row(beacon_intervals, row, min_coordinate, max_coordinate) != max_coordinate - min_coordinate + 1) {    
            return (unsigned long long int) beacon_intervals[0].first * 4000000 + row;
        }
    }
    return 0;
}