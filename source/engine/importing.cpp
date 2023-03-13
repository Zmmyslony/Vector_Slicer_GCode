/*
 * 2023, Michał Zmyślony, mlz22@cam.ac.uk.
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
// Created by Michał Zmyślony on 13/03/2023.
//

#include <boost/filesystem/path.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

#include "importing.h"


double readResolution(const fs::path &filepath) {
    std::vector<std::vector<double>> table;
    std::string line;
    std::fstream file(filepath.string());

    if (!file) {
        std::cout << filepath << " does not exist" << std::endl;
        throw std::runtime_error("File " + filepath.string() + " does not exists.");
    }

    while (std::getline(file, line)) {
        if ((line.find("# Print diameter:") != std::string::npos)) {
            std::string element;
            std::stringstream line_stream(line);
            std::vector<std::string> row;

            while (std::getline(line_stream, element, ' ')) {
                row.push_back(element);
            }
            std::cout << "Imported resolution: " << row.back() << std::endl;
            return std::stod(row.back());
        }
    }
    return 1;
}

std::vector<std::vector<double>> importTableDouble(const fs::path &filename) {
    std::vector<std::vector<double>> table;
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
        std::vector<double> row;

        while (std::getline(line_stream, element, ',')) {
            row.push_back(stoi(element));
        }
        if (!row.empty()) {
            table.push_back(row);
        }
    }
    return table;
}


std::vector<std::vector<std::valarray<double>>> importTableValarrayDouble(const fs::path &filename) {
    std::vector<std::vector<double>> table = importTableDouble(filename);
    std::vector<std::vector<std::valarray<double>>> table_valarray;
    for (auto &row: table) {
        std::vector<std::valarray<double>> row_valarray;
        for (int i = 0; i < row.size(); i += 2) {
            row_valarray.push_back({row[i], row[i + 1]});
        }
        table_valarray.push_back(row_valarray);
    }
    return table_valarray;
}

std::vector<std::vector<std::valarray<double>>> read3DVectorFromFileDouble(const fs::path &path) {
    return importTableValarrayDouble(path);
}