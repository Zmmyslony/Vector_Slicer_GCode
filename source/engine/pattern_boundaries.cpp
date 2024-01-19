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

PatternBoundaries::PatternBoundaries(
        const std::vector<std::vector<std::valarray<double>>> &sequence_of_paths, double grid_spacing) {
    for (auto &path: sequence_of_paths) {
        for (auto &point: path) {
            if (x_max < point[0]) { x_max = point[0]; }
            if (x_min > point[0]) { x_min = point[0]; }
            if (y_max < point[1]) { y_max = point[1]; }
            if (y_min > point[1]) { y_min = point[1]; }
        }
    }
//    x_max -= x_min;
//    x_min -= x_min;
//    y_max -= y_min;
//    y_min -= y_min;

    x_max *= grid_spacing;
    x_min *= grid_spacing;
    y_max *= grid_spacing;
    y_min *= grid_spacing;
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

std::valarray<double> PatternBoundaries::getCentre() const {
    return {(x_max + x_min) / 2, (y_max + y_min) / 2};
}

void PatternBoundaries::print() const {
    std::cout << "x_min = " << x_min << ", x_max = " << x_max << ", y_min = " << y_min << ", y_max = " << y_max
              << std::endl;
}

PatternBoundaries::PatternBoundaries(const PatternBoundaries &one, const PatternBoundaries &two) :
        x_min(fmin(one.x_min, two.x_min)),
        y_min(fmin(one.y_min, two.y_min)),
        x_max(fmax(one.x_max, two.x_max)),
        y_max(fmax(one.y_max, two.y_max)) {}

void PatternBoundaries::join(const PatternBoundaries &other) {
    *this = PatternBoundaries(*this, other);
}

PatternBoundaries
PatternBoundaries::joinRelativeX(const PatternBoundaries &one, const PatternBoundaries &two, double x_offset) {
    return {fmin(one.x_min, two.x_min), fmin(one.y_min, two.y_min), one.x_max + two.x_max + x_offset, fmax(one.y_max, two.y_max)};
};

PatternBoundaries
PatternBoundaries::joinRelativeY(const PatternBoundaries &one, const PatternBoundaries &two, double y_offset) {
    return {fmin(one.x_min, two.x_min), fmin(one.y_min, two.y_min), fmax(one.x_max, two.x_max), one.y_max + two.y_max + y_offset};
}

void PatternBoundaries::joinRelativeX(const PatternBoundaries &other, double x_offset) {
    *this = joinRelativeX(*this, other, x_offset);
}

void PatternBoundaries::joinRelativeY(const PatternBoundaries &other, double y_offset) {
    *this = joinRelativeY(*this, other, y_offset);
}

PatternBoundaries::PatternBoundaries(double x_min, double y_min, double x_max, double y_max) :
        x_min(x_min),
        y_min(y_min),
        x_max(x_max),
        y_max(y_max) {}

