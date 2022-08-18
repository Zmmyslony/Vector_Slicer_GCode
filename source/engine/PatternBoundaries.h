//
// Created by Michał Zmyślony on 18/08/2022.
//

#ifndef GCODEGENERATOR_PATTERNBOUNDARIES_H
#define GCODEGENERATOR_PATTERNBOUNDARIES_H

#include <climits>
#include <vector>
#include <valarray>

class PatternBoundaries {
    double xMin = INT_MAX;
    double yMin = INT_MAX;
    double xMax = INT_MIN;
    double yMax = INT_MIN;

public:
    double getXMin() const;

    double getYMin() const;

    double getXMax() const;

    double getYMax() const;

    PatternBoundaries(const std::vector<std::vector<std::valarray<int>>> &sequenceOfPaths);

    void scale(double multiplier);

    void move(const std::valarray<double> &offset);

    std::valarray<double> getBottomLeft();

    std::valarray<double> getBottomRight();

    std::valarray<double> getTopLeft();

    std::valarray<double> getTopRight();

    void print();
};


#endif //GCODEGENERATOR_PATTERNBOUNDARIES_H
