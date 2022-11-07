/*
 * Copyright (c) 2022, Michał Zmyślony, mlz22@cam.ac.uk. All rights reserved.
 *
 * Please cite Michał Zmyślony and Dr John Biggins if you use any part of this code in work you publish or distribute.
 *
 * This file is a part of gCode Generator.
 */

//
// Created by Michał Zmyślony on 18/08/2022.
//

#ifndef GCODEGENERATOR_PATTERN_BOUNDARIES_H
#define GCODEGENERATOR_PATTERN_BOUNDARIES_H

#include <climits>
#include <vector>
#include <valarray>

class PatternBoundaries {
    double x_min = INT_MAX;
    double y_min = INT_MAX;
    double x_max = INT_MIN;
    double y_max = INT_MIN;

public:
    [[nodiscard]] double getXMin() const;

    [[nodiscard]] double getYMin() const;

    [[nodiscard]] double getXMax() const;

    [[nodiscard]] double getYMax() const;

    explicit PatternBoundaries(const std::vector<std::vector<std::valarray<int>>> &sequence_of_paths);

    void scale(double multiplier);

    void move(const std::valarray<double> &offset);

    std::valarray<double> getBottomLeftCorner();

    std::valarray<double> getBottomRightCorner();

    std::valarray<double> getTopLeftCorner();

    std::valarray<double> getTopRightCorner();

    void print() const;
};


#endif //GCODEGENERATOR_PATTERN_BOUNDARIES_H
