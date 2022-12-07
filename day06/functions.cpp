#include <map>
#include <fstream>
#include <iostream>
#include <string>


auto read_buffer(std::string file_name) {
    std::ifstream infile(file_name);
    std::string line = "";
    getline(infile, line);
    return line;
}


bool check_if_value_is_zero_or_undefined_in_dictionary(std::map<char,int> &dictionary, char &key) {
    if (dictionary.find(key) == dictionary.end()) {
        return true;
    } else if (dictionary[key] == 0) {
        return true;
    } else {
        return false;
    }
}


void increase_value_by_one(std::map<char,int> &dictionary, char &key, int &distinct_keys) {
    if (check_if_value_is_zero_or_undefined_in_dictionary(dictionary, key)) {
        distinct_keys += 1;
        dictionary[key] = 1;
    } else {
        dictionary[key] += 1;
    }
    return;
}


int determine_start_of_package(std::string buffer, int distinct_characters) {
    std::map<char, int> last_letters = {};
    int distinct_letters = 0;
    
    for(std::string::size_type idx = 0; idx < buffer.size(); idx++) {
        char letter = buffer[idx];
        if (idx < distinct_characters) {
            increase_value_by_one(last_letters, letter, distinct_letters);
        } else if (distinct_letters == distinct_characters) {
            return idx;
        } else {
            last_letters[buffer[idx - distinct_characters]] -= 1;
            if (last_letters[buffer[idx - distinct_characters]] == 0) {
                distinct_letters -= 1;
            }
            increase_value_by_one(last_letters, letter, distinct_letters);
        }
    }
    return 0;
}
