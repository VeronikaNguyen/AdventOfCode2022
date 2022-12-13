#include <algorithm>
#include <fstream>
#include <iostream>
#include <utility>
#include <string>
#include <vector>


auto read_lists(std::string file_name) {
    std::ifstream infile(file_name);
    std::string line = "";
    int line_counter = 0;
    std::vector<std::pair<std::string, std::string>> lists;
    std::pair<std::string, std::string> list_pair;

    while (getline(infile, line)) {
        if (line_counter % 3 == 0) {
            list_pair.first = line;
        } else if (line_counter % 3 == 1) {
            list_pair.second = line;
            lists.push_back(list_pair);
        } 
        line_counter += 1;
    }
    return lists; 
}


int find_entry_length(std::string list, int idx, bool& is_list) {
    int end_idx = idx + 1;
    if (list.at(idx) == '[') {
        int num_open_brackets = 1;
        is_list = true;
        while (num_open_brackets > 0) {
            if (list.at(end_idx) == '[') {
                num_open_brackets += 1;
            } else if (list.at(end_idx) == ']') {
                num_open_brackets -= 1;
            }
            end_idx += 1;
        }
    } else if (list.at(idx) == ']') {
        return 0;
    } else {
        is_list = false;
        while (list.at(end_idx) != ',' and list.at(end_idx) != ']') {
            end_idx += 1;
        }
    }
    return end_idx - idx;
}


int compare_pair(std::pair<std::string, std::string> list_pair, std::pair<int, int> idx) {
    std::pair<bool, bool> is_list = {false, false};
    int first_entry_length = find_entry_length(list_pair.first, idx.first, is_list.first);
    int second_entry_length = find_entry_length(list_pair.second, idx.second, is_list.second);
    if (first_entry_length == 0 and second_entry_length == 0) {
        return 0;
    } else if (first_entry_length == 0) {
        return 1;
    } else if (second_entry_length == 0) {
        return -1;
    }

    if (idx.first < list_pair.first.size() - 1 and idx.second < list_pair.second.size()) {
        if (!is_list.first and !is_list.second) {
            int first = std::stoi(list_pair.first.substr(idx.first, first_entry_length));
            int second = std::stoi(list_pair.second.substr(idx.second, second_entry_length));
            if (first < second) {
                return 1;
            } else if (first > second) {
                return -1;
            }
        } else if (is_list.first and !is_list.second) {
            int res = compare_pair({list_pair.first.substr(idx.first, first_entry_length), "[" + list_pair.second.substr(idx.second, second_entry_length) + "]"}, {1, 1});
            if (res == -1 or res == 1) {
                return res;
            } 
        } else if (!is_list.first and is_list.second) { 
            int res = compare_pair({"[" + list_pair.first.substr(idx.first, first_entry_length) + "]", list_pair.second.substr(idx.second, second_entry_length)}, {1, 1});
            if (res == -1 or res == 1) {
                return res;
            } 
        } else {
            int res = compare_pair({list_pair.first.substr(idx.first, first_entry_length), list_pair.second.substr(idx.second, second_entry_length)}, {1, 1});
            if (res == -1 or res == 1) {
                return res;
            }
        }
        idx.first += first_entry_length;
        idx.second += second_entry_length;

        if (list_pair.first.at(idx.first) != ',' and list_pair.second.at(idx.second) == ',') {
            return 1;
        } else if (list_pair.first.at(idx.first) == ',' and list_pair.second.at(idx.second) != ',') {
            return -1;
        } else if (list_pair.first.at(idx.first) == ',' and list_pair.second.at(idx.second) == ','){
            idx.first += 1;
            idx.second += 1;
            return compare_pair(list_pair, idx);
        }
    }
    return 0;
}


int determine_sum_of_correct_pairs(std::vector<std::pair<std::string, std::string>> lists) {
    int sum_of_correct_pairs = 0;
    for (int idx = 1; idx <= lists.size(); idx++) {
        if (compare_pair(lists[idx - 1], {1, 1}) >= 0) {
            sum_of_correct_pairs += idx;
        } 
    }
    return sum_of_correct_pairs;
}


struct Packet {
    std::string value;

    Packet(const std::string& value) {
        this->value = value;
    }

    bool operator<(const Packet& other) {
        if (compare_pair({this->value, other.value}, {1,1}) >= 0) {
            return true;
        } else {
            return false;
        }
    }
};


std::vector<Packet> change_to_packets_and_add_decoder_packets(std::vector<std::pair<std::string, std::string>> lists) {
    std::vector<Packet> packets;
    for (auto list_pair : lists) {
        packets.push_back(Packet(list_pair.first));
        packets.push_back(Packet(list_pair.second));
    }
    packets.push_back(Packet("[[2]]"));
    packets.push_back(Packet("[[6]]"));
    return packets;
}


int determine_decoder_key(std::vector<std::pair<std::string, std::string>> lists) {
    std::vector<Packet> packets = change_to_packets_and_add_decoder_packets(lists);
    std::sort(packets.begin(), packets.end());
    std::pair<int, int> decoder_packets;
    for (int idx = 1; idx < packets.size(); idx++) {
        if (packets[idx - 1].value == "[[2]]") {
            decoder_packets.first = idx;
        } else if (packets[idx - 1].value == "[[6]]") {
            decoder_packets.second = idx;
            break;
        }
    }
    return decoder_packets.first * decoder_packets.second;
}