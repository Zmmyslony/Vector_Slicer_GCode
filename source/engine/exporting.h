/*
 * Copyright (c) 2022, Michał Zmyślony, mlz22@cam.ac.uk. All rights reserved.
 *
 * Please cite Michał Zmyślony and Dr John Biggins if you use any part of this code in work you publish or distribute.
 *
 * This file is a part of gCode Generator.
 */

//
// Created by Michał Zmyślony on 13/10/2021.
//

#ifndef GCODEGENERATOR_EXPORTING_H
#define GCODEGENERATOR_EXPORTING_H

#include <string>
#include <valarray>
#include <vector>

void exportVectorTableToFile(const std::vector<std::vector<int>> &table, std::string &filename);

void exportVectorTableToFile(const std::vector<std::vector<double>> &table, std::string &filename);

void
export3DVectorToFile(const std::vector<std::vector<std::valarray<int>>> &grid_of_coordinates, const std::string &path,
                     const std::string &suffix);

std::vector<std::vector<std::valarray<int>>> read3DVectorFromFile(const std::string &path, const std::string &suffix);

#endif //GCODEGENERATOR_EXPORTING_H
