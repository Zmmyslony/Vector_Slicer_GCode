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
// Created by Michał Zmyślony on 18/08/2022.
//

#include <iostream>

#include "pattern_boundaries.h"

PatternBoundaries::PatternBoundaries(const std::vector<std::vector<std::valarray<int>>> &sequence_of_paths) {
    for (auto &path: sequence_of_paths) {
        for (auto &point: path) {
            if (x_max < point[0]) { x_max = point[0]; }
            if (x_min > point[0]) { x_min = point[0]; }
            if (y_max < point[1]) { y_max = point[1]; }
            if (y_min > point[1]) { y_min = point[1]; }
        }
    }
    x_max -= x_min;
    x_min -= x_min;
    y_max -= y_min;
    y_min -= y_min;
}

double PatternBoundaries::getXMin() const {
    return x_min;
}

double PatternBoundaries::getYMin() const {
    return y_min;
}

double PatternBoundaries::getXMax() const {
    return x_max;
}

double PatternBoundaries::getYMax() const {
    return y_max;
}

void PatternBoundaries::scale(double multiplier) {
    x_max *= multiplier;
    x_min *= multiplier;
    y_max *= multiplier;
    y_min *= multiplier;
}

void PatternBoundaries::move(const std::valarray<double> &offset) {
    x_min += offset[0];
    x_max += offset[0];
    y_min += offset[1];
    y_max += offset[1];
}

std::valarray<double> PatternBoundaries::getBottomLeftCorner() {
    return std::valarray<double>({x_min, y_min});
}

std::valarray<double> PatternBoundaries::getBottomRightCorner() {
    return std::valarray<double>({x_max, y_min});
}

std::valarray<double> PatternBoundaries::getTopLeftCorner() {
    return std::valarray<double>({x_min, y_max});
}

std::valarray<double> PatternBoundaries::getTopRightCorner() {
    return std::valarray<double>({x_max, y_max});
}

void PatternBoundaries::print() const {
    std::cout << "x_min = " << x_min << ", x_max = " << x_max << ", y_min = " << y_min << ", y_max = " << y_max
              << std::endl;
}