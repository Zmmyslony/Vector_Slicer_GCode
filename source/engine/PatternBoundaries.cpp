//
// Created by Michał Zmyślony on 18/08/2022.
//

#include <iostream>
#include "PatternBoundaries.h"

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