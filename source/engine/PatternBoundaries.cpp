//
// Created by Michał Zmyślony on 18/08/2022.
//

#include <iostream>
#include "PatternBoundaries.h"

PatternBoundaries::PatternBoundaries(const std::vector<std::vector<std::valarray<int>>> &sequenceOfPaths) {
    for (auto &path: sequenceOfPaths) {
        for (auto &point: path) {
            if (xMax < point[0]) { xMax = point[0]; }
            if (xMin > point[0]) { xMin = point[0]; }
            if (yMax < point[1]) { yMax = point[1]; }
            if (yMin > point[1]) { yMin = point[1]; }
        }
    }
    xMax -= xMin;
    xMin -= xMin;
    yMax -= yMin;
    yMin -= yMin;
}

double PatternBoundaries::getXMin() const {
    return xMin;
}

double PatternBoundaries::getYMin() const {
    return yMin;
}

double PatternBoundaries::getXMax() const {
    return xMax;
}

double PatternBoundaries::getYMax() const {
    return yMax;
}

void PatternBoundaries::scale(double multiplier) {
    xMax *= multiplier;
    xMin *= multiplier;
    yMax *= multiplier;
    yMin *= multiplier;
}

void PatternBoundaries::move(const std::valarray<double> &offset) {
    xMin += offset[0];
    xMax += offset[0];
    yMin += offset[1];
    yMax += offset[1];
}

std::valarray<double> PatternBoundaries::getBottomLeft() {
    return std::valarray<double>({xMin, yMin});
}

std::valarray<double> PatternBoundaries::getBottomRight() {
    return std::valarray<double>({xMax, yMin});
}

std::valarray<double> PatternBoundaries::getTopLeft() {
    return std::valarray<double>({xMin, yMax});
}

std::valarray<double> PatternBoundaries::getTopRight() {
    return std::valarray<double>({xMax, yMax});
}

void PatternBoundaries::print() {
    std::cout << "xMin = " << xMin << ", xMax = " << xMax << ", yMin = " << yMin << ", yMax = " << yMax << std::endl;
}