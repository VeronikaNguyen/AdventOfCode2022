#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>


class File {
    public:
        std::string name;
        unsigned long size;

        File(std::string name, unsigned long size) {this->name = name; this->size = size;}
};


class Folder {
    public:
        std::string name;
        unsigned long size;
        bool computed_size;
        Folder* parent;
        std::vector<File*> files;
        std::vector<Folder*> children;

        Folder(std::string name, Folder* parent) {this->name = name; this->parent = parent; files = std::vector<File*>{}; children = std::vector<Folder*>{}; size = 0; computed_size = false;}
        void add_file(File* file) {files.push_back(file);}
        void add_child(Folder* child) {children.push_back(child);}
        void compute_size() {
            if (!computed_size) {
                size = 0;
                for (auto child : children) {
                    child->compute_size();
                    size += child->size;
                }
                for (auto file : files) {
                    size += file->size;
                }
                computed_size = true;
            }
        }
        unsigned long determine_sum_folders_smaller_than_number(unsigned long number) {
            unsigned long sum_folders = 0;
            for (auto child : children) {
                sum_folders += child->determine_sum_folders_smaller_than_number(number);
            }
            if (size < number) {
                sum_folders += size;
            }
            return sum_folders;
        }
        unsigned long find_smallest_folder_above_number(unsigned long number, unsigned long current_smallest_folder) {
            for (auto child : children) {
                current_smallest_folder = child->find_smallest_folder_above_number(number, current_smallest_folder);
            }
            if (size >= number and size < current_smallest_folder) {
                current_smallest_folder = size;
            }
            return current_smallest_folder;
        }
};


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


auto read_file_tree(std::string file_name) {
    std::ifstream infile(file_name);
    std::string line = "";
    bool is_ls = false;
    Folder* root;
    Folder* current_node;

    while (getline(infile, line)) {
        if (line == "$ cd /") {
            root = new Folder("/", 0);
            current_node = root;
        } else if (line == "$ ls") {
            is_ls = true;
        } else if (line.substr(0, 4) == "$ cd") {
            is_ls = false;
            auto splitted_line = split_string_by_delemeter(line, ' ');
            if (splitted_line[2] == "..") {
                current_node = current_node->parent;
            } else {
                for (auto folder : current_node->children) {
                    if (folder->name == splitted_line[2]) {
                        current_node = folder;
                        break;
                    }
                }
            }
        } else if (is_ls) {
            auto splitted_line = split_string_by_delemeter(line, ' ');
            if (splitted_line[0] == "dir") {
                current_node->add_child(new Folder(splitted_line[1], current_node));
            } else {
                current_node->add_file(new File(splitted_line[1], std::stoul (splitted_line[0], nullptr, 0)));
            }
        }
    }
    return root; 
}
