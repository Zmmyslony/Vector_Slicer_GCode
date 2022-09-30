//
// Created by Michał Zmyślony on 13/10/2021.
//

#include "Exporting.h"
#include <iostream>
#include <fstream>
#include <sstream>

std::string readRowToString(const std::vector<int> &row) {
    std::string row_string;
    for (auto &element: row) {
        row_string += std::to_string(element);
        row_string += ",";
    }
    row_string.pop_back();
    row_string += "\n";
    return row_string;
}


std::string readRowToString(const std::vector<double> &row) {
    std::string row_string;
    for (auto &element: row) {
        row_string += std::to_string(element);
        row_string += ",";
    }
    row_string.pop_back();
    row_string += "\n";
    return row_string;
}


void exportVectorTableToFile(const std::vector<std::vector<int>> &table, std::string &filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (auto &row: table) {
            file << readRowToString(row);
        }
        file.close();
    }
}


void exportVectorTableToFile(const std::vector<std::vector<double>> &table, std::string &filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (auto &row: table) {
            file << readRowToString(row);
        }
    }
    file.close();
}


std::vector<std::vector<int>> indexTable(const std::vector<std::vector<std::valarray<int>>> &grid_of_coordinates,
                                         int index) {
    std::vector<std::vector<int>> table;
    table.reserve(grid_of_coordinates.size());
    for (auto &row: grid_of_coordinates) {
        std::vector<int> new_row;
        new_row.reserve(row.size());
        for (auto &element: row) {
            new_row.push_back(element[index]);
        }
        table.push_back(new_row);
    }
    return table;
}


void
export3DVectorToFile(const std::vector<std::vector<std::valarray<int>>> &grid_of_coordinates, const std::string &path,
                     const std::string &suffix) {
    std::vector<std::vector<int>> x_table = indexTable(grid_of_coordinates, 0);
    std::vector<std::vector<int>> y_table = indexTable(grid_of_coordinates, 1);

    std::string x_filename = path + "\\x_" + suffix + ".csv";
    std::string y_filename = path + "\\y_" + suffix + ".csv";

    exportVectorTableToFile(x_table, x_filename);
    exportVectorTableToFile(y_table, y_filename);
}


std::vector<std::vector<int>> importTableInt(const std::string &filename) {
    std::vector<std::vector<int>> table;
    std::string line;
    std::fstream file(filename);

    if (!file) {
        std::cout << filename << " does not exist" << std::endl;
    }

    while (std::getline(file, line)) {
        std::string element;
        std::stringstream line_stream(line);
        std::vector<int> row;

        while (std::getline(line_stream, element, ',')) {
            row.push_back(stoi(element));
        }
        table.push_back(row);
    }
    return table;
}

std::vector<std::vector<std::valarray<int>>> mergeTwoTables(const std::vector<std::vector<int>> &x_table,
                                                            const std::vector<std::vector<int>> &y_table) {
    std::vector<std::vector<std::valarray<int>>> merged_table;
    for (int i = 0; i < x_table.size(); i++) {
        std::vector<std::valarray<int>> merged_row;
        for (int j = 0; j < x_table[i].size(); j++) {
            std::valarray<int> merged_element = {x_table[i][j], y_table[i][j]};
            merged_row.push_back(merged_element);
        }
        merged_table.push_back(merged_row);
    }
    return merged_table;
}


std::vector<std::vector<std::valarray<int>>> read3DVectorFromFile(const std::string &path, const std::string &suffix) {
    std::string x_filename = path + "\\x_" + suffix + ".csv";
    std::string y_filename = path + "\\y_" + suffix + ".csv";

    std::vector<std::vector<int>> x_table = importTableInt(x_filename);
    std::vector<std::vector<int>> y_table = importTableInt(y_filename);

    std::vector<std::vector<std::valarray<int>>> merged_tables = mergeTwoTables(x_table, y_table);
    return merged_tables;
}

