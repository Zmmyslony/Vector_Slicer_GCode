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

#include <stdexcept>
#include <iostream>
#include <algorithm>

#include "pattern_boundaries.h"
#include "valarray_operations.h"

vald itodArray(const vali &int_array) {
    vald double_array(int_array.size());
    for (int i = 0; i < int_array.size(); i++) {
        double_array[i] = (double) int_array[i];
    }
    return double_array;
}

vali dtoiArray(const vald &double_array) {
    vali int_array(double_array.size());
    for (int i = 0; i < double_array.size(); i++) {
        int_array[i] = lround(double_array[i]);
    }
    return int_array;
}

double generalNorm(const vald &array, const double &exponent) {
    double sum = 0;
    for (auto &element: array) {
        sum += pow(element, exponent);
    }
    return pow(sum, 1 / exponent);
}

double norm(const vald &array) {
    return generalNorm(array, 2);
}

double norm(const vali &array) {
    return norm(itodArray(array));
}

vald generalNormalize(const vald &array, const double &exponent) {
    return array / generalNorm(array, exponent);
}

vald normalize(const vald &array) {
    return generalNormalize(array, 2);
}

vald normalize(const vali &array) {
    return normalize(itodArray(array));
}

double dot(const vald &array_1, const vald &array_2) {
    double dot_product = 0;
    if (array_1.size() != array_2.size()) {
        throw std::invalid_argument("Dot: Dotted array are of different size.\n");
    }
    for (int i = 0; i < array_1.size(); i++) {
        dot_product += array_1[i] * array_2[i];
    }
    return dot_product;
}

double dot(const vali &array_1, const vali &array_2) {
    return dot(itodArray(array_1), itodArray(array_2));
}

vald perpendicular(vald vector) {
    if (vector.size() != 2) {
        throw std::invalid_argument("Perpendicular: Size of the valarray not equal to 2.\n");
    }
    return vald({-vector[1], vector[0]});
}


vali perpendicular(const vali &vector) {
    return dtoiArray(perpendicular(itodArray(vector)));
}


void printArray(const std::vector<vali> &array) {
    for (auto &row: array) {
        std::cout << "(";
        for (auto &element: row) {
            std::cout << element << ", ";
        }
        std::cout << "), ";
    }
    std::cout << std::endl;
}

void printArray(const std::vector<vald> &array) {
    for (auto &row: array) {
        std::cout << "(";
        for (auto &element: row) {
            std::cout << element << ", ";
        }
        std::cout << "), ";
    }
    std::cout << std::endl;
}

vali uinttointArray(const std::valarray<unsigned int> &uint_array) {
    vali int_array(uint_array.size());
    for (int i = 0; i < uint_array.size(); i++) {
        int_array[i] = lround(uint_array[i]);
    }
    return int_array;
}

bool isEqual(const std::valarray<bool> &bool_valarray) {
    bool equals = true;
    for (auto item: bool_valarray) {
        equals &= item;
    }
    return equals;
}

vald rotate(vald array, double angle) {
    return {array[0] * cos(angle) - array[1] * sin(angle),
            array[1] * cos(angle) + array[0] * sin(angle)};
}

vald rotateWithOffset(const vald &array, double angle, const vald &offset) {
    auto offset_rotation = rotate(array - offset, angle);
    return offset_rotation + offset;
}

std::vector<std::vector<vald>>
rotatePattern(std::vector<std::vector<vald>> pattern, double angle, const vald &centre_of_rotation) {
    std::vector<std::vector<vald>> rotated_pattern;
    for (auto &path: pattern) {
        for (auto &element: path) {
            element = rotateWithOffset(element, angle, centre_of_rotation);
        }
    }
    return pattern;
}

std::vector<std::vector<vald>> rotatePattern(const std::vector<std::vector<vald>> &pattern, double angle) {
    PatternBoundaries boundaries(pattern, 0);
    vald pattern_centre = boundaries.getCentre();
    return rotatePattern(pattern, angle, pattern_centre);
}

std::vector<std::vector<std::vector<vald>>> rotatePattern(const std::vector<std::vector<std::vector<vald>>> &pattern_stack, double angle) {
    std::vector<std::vector<std::vector<vald>>> rotated_stack;
    rotated_stack.reserve(pattern_stack.size());
for (auto &pattern: pattern_stack) {
        rotated_stack.emplace_back(rotatePattern(pattern, angle));
    }
    return rotated_stack;
}

std::vector<std::vector<vald>> flipPattern(const std::vector<std::vector<vald>> &pattern) {
    auto flipped_pattern = pattern;
    std::reverse_copy(pattern.begin(), pattern.end(), flipped_pattern.begin());
    for (auto &path: flipped_pattern) {
        std::reverse(path.begin(), path.end());
    }
    return flipped_pattern;
}