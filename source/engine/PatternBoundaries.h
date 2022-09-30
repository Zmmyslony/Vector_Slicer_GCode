//
// Created by Michał Zmyślony on 18/08/2022.
//

#ifndef GCODEGENERATOR_PATTERNBOUNDARIES_H
#define GCODEGENERATOR_PATTERNBOUNDARIES_H

#include <climits>
#include <vector>
#include <valarray>

class PatternBoundaries {
    double x_min = INT_MAX;
    double y_min = INT_MAX;
    double x_max = INT_MIN;
    double y_max = INT_MIN;

public:
    double getXMin() const;

    double getYMin() const;

    double getXMax() const;

    double getYMax() const;

    PatternBoundaries(const std::vector<std::vector<std::valarray<int>>> &sequence_of_paths);

    void scale(double multiplier);

    void move(const std::valarray<double> &offset);

    std::valarray<double> getBottomLeftCorner();

    std::valarray<double> getBottomRightCorner();

    std::valarray<double> getTopLeftCorner();

    std::valarray<double> getTopRightCorner();

    void print() const;
};


#endif //GCODEGENERATOR_PATTERNBOUNDARIES_H
