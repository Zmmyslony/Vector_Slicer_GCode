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
// Created by Michał Zmyślony on 15/10/2021.
//

#ifndef GCODEGENERATOR_VALARRAY_OPERATIONS_H
#define GCODEGENERATOR_VALARRAY_OPERATIONS_H

#include <valarray>
#include <vector>

std::valarray<double> itodArray(const std::valarray<int> &int_array);

std::valarray<int> dtoiArray(const std::valarray<double> &double_array);

double generalNorm(const std::valarray<double> &array, const double &exponent);

double norm(const std::valarray<double> &array);

double norm(const std::valarray<int> &array);

std::valarray<double> generalNormalize(const std::valarray<double> &array, const double &exponent);

std::valarray<double> normalize(const std::valarray<double> &array);

std::valarray<double> normalize(const std::valarray<int> &array);

double dot(const std::valarray<double> &array_1, const std::valarray<double> &array_2);

double dot(const std::valarray<int> &array_1, const std::valarray<int> &array_2);

std::valarray<double> perpendicular(std::valarray<double> vector);

std::valarray<int> perpendicular(const std::valarray<int> &vector);

void printArray(const std::vector<std::valarray<int>> &array);

void printArray(const std::vector<std::valarray<double>> &array);

std::valarray<int> uinttointArray(const std::valarray<unsigned int> &uint_array);

bool isEqual(const std::valarray<bool> &bool_valarray);

#endif //GCODEGENERATOR_VALARRAY_OPERATIONS_H
