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

using vali = std::valarray<int>;
using vald = std::valarray<double>;

vald itodArray(const vali &int_array);

vali dtoiArray(const vald &double_array);

double generalNorm(const vald &array, const double &exponent);

double norm(const vald &array);

double norm(const vali &array);

vald generalNormalize(const vald &array, const double &exponent);

vald normalize(const vald &array);

vald normalize(const vali &array);

double dot(const vald &array_1, const vald &array_2);

double dot(const vali &array_1, const vali &array_2);

vald perpendicular(vald vector);

vali perpendicular(const vali &vector);

void printArray(const std::vector<vali> &array);

void printArray(const std::vector<vald> &array);

vali uinttointArray(const std::valarray<unsigned int> &uint_array);

bool isEqual(const std::valarray<bool> &bool_valarray);

std::vector<std::vector<vald>>
rotatePattern(std::vector<std::vector<vald>> pattern, double angle, const vald &centre_of_rotation);

std::vector<std::vector<vald>> rotatePattern(const std::vector<std::vector<vald>> &pattern, double angle);

std::vector<std::vector<vald>> flipPattern(const std::vector<std::vector<vald>> &pattern);

#endif //GCODEGENERATOR_VALARRAY_OPERATIONS_H
