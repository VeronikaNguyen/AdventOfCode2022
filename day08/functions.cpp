#include <fstream>
#include <iostream>
#include <string>
#include <vector>


auto read_trees(std::string file_name) {
    std::ifstream infile(file_name);
    std::string line = "";
    std::vector<std::vector<int>> trees;

    while (getline(infile, line)) {
        std::vector<int> entry;
        for (auto letter : line) {
            entry.push_back(int (letter));
        }
        trees.push_back(entry);
    }
    return trees; 
}


int count_visible_trees(std::vector<std::vector<int>> trees) {
    int visible[trees.size()][trees[0].size()] = {};

    for (int row_idx = 0; row_idx < trees.size(); row_idx++) {
        int min_tree = 0;
        for (int col_idx = 0; col_idx < trees[0].size(); col_idx++) {
            if (trees[row_idx][col_idx] > min_tree) {
                visible[row_idx][col_idx] = 1;
                min_tree = trees[row_idx][col_idx] ;
            }
        }
    }

    for (int row_idx = 0; row_idx < trees.size(); row_idx++) {
        int min_tree = 0;
        for (int col_idx = trees[0].size() - 1; col_idx >= 0; col_idx--) {
            if (trees[row_idx][col_idx] > min_tree) {
                visible[row_idx][col_idx] = 1;
                min_tree = trees[row_idx][col_idx] ;
            }
        }
    }

    for (int col_idx = 0; col_idx < trees[0].size(); col_idx++) {
        int min_tree = 0;
        for (int row_idx = 0; row_idx < trees.size(); row_idx++) {
            if (trees[row_idx][col_idx] > min_tree) {
                visible[row_idx][col_idx] = 1;
                min_tree = trees[row_idx][col_idx] ;
            }
        }
    }

    for (int col_idx = 0; col_idx < trees[0].size(); col_idx++) {
        int min_tree = 0;
        for (int row_idx = trees.size() - 1; row_idx >= 0; row_idx--) {
            if (trees[row_idx][col_idx] > min_tree) {
                visible[row_idx][col_idx] = 1;
                min_tree = trees[row_idx][col_idx] ;
            }
        }
    }

    int visible_trees = 0;
    for (int row_idx = 0; row_idx < trees.size(); row_idx++) {
        for (int col_idx = 0; col_idx < trees[0].size(); col_idx++) {
            if (visible[row_idx][col_idx] == 1) {
                visible_trees += 1;
            }
        }
    }
    return visible_trees;
}


int determine_viewing_score(std::vector<std::vector<int>> trees, int row, int col) {
    int viewing_score = 1;

    int view = 1;
    for (int col_idx = col + 1; col_idx < trees[0].size() - 1; col_idx++) {
        if (trees[row][col_idx] < trees[row][col]) {
            view += 1;
        } else {
            break;
        }
    }
    viewing_score *= view;
    view = 1;

    for (int col_idx = col - 1; col_idx > 0; col_idx--) {
        if (trees[row][col_idx] < trees[row][col]) {
            view += 1;
        } else {
            break;
        }
    }
    viewing_score *= view;
    view = 1;

    for (int row_idx = row + 1; row_idx < trees.size() - 1; row_idx++) {
        if (trees[row_idx][col] < trees[row][col]) {
            view += 1;
        } else {
            break;
        }
    }
    viewing_score *= view;
    view = 1;

    for (int row_idx = row - 1; row_idx > 0; row_idx--) {
        if (trees[row_idx][col] < trees[row][col]) {
            view += 1;
        } else {
            break;
        }
    }
    viewing_score *= view;

    return viewing_score; 
}

int determine_highest_viewing_score(std::vector<std::vector<int>> trees) {
    int max_viewing_score = 0;
    for (int row_idx = 1; row_idx < trees.size() - 1; row_idx++) {
        for (int col_idx = 1; col_idx < trees[0].size() - 1; col_idx++) {
            int viewing_score = determine_viewing_score(trees, row_idx, col_idx);
            if (max_viewing_score < viewing_score) {
                max_viewing_score = viewing_score;
            }
        }
    }
    return max_viewing_score;
}