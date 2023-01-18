/*
 * 2022, Michał Zmyślony, mlz22@cam.ac.uk.
 *
 * Please cite Michał Zmyślony and Dr John Biggins if you use any part of this code in work you publish or distribute.
 *
 * This file is part of gCodeGenerator.
 *
 * gCodeGenerator is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 *
 * gCodeGenerator is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with Foobar. If not, see <https://www.gnu.org/licenses/>.
 */

//
// Created by Michał Zmyślony on 13/10/2021.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <boost/filesystem/path.hpp>

#include "exporting.h"

std::vector<std::vector<int>> importTableInt(const fs::path &filename) {
    std::vector<std::vector<int>> table;
    std::string line;
    std::fstream file(filename.string());

    if (!file) {
        std::cout << filename << " does not exist" << std::endl;
        throw std::runtime_error("File " + filename.string() + " does not exists.");
    }

    while (std::getline(file, line)) {
        if (line[0] == '#') {
            continue;
        }
        std::string element;
        std::stringstream line_stream(line);
        std::vector<int> row;

        while (std::getline(line_stream, element, ',')) {
            row.push_back(stoi(element));
        }
        if (!row.empty()) {
            table.push_back(row);
        }
    }
    return table;
}

std::vector<std::vector<std::valarray<int>>> importTableValarrayInt(const fs::path &filename) {
    std::vector<std::vector<int>> table = importTableInt(filename);
    std::vector<std::vector<std::valarray<int>>> table_valarray;
    for (auto &row: table) {
        std::vector<std::valarray<int>> row_valarray;
        for (int i = 0; i < row.size(); i += 2) {
            row_valarray.push_back({row[i], row[i + 1]});
        }
        table_valarray.push_back(row_valarray);
    }
    return table_valarray;
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

std::vector<std::vector<std::valarray<int>>> read3DVectorFromFile(const fs::path &path) {
    return importTableValarrayInt(path);
}

