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

#ifndef GCODEGENERATOR_PATTERN_BOUNDARIES_H
#define GCODEGENERATOR_PATTERN_BOUNDARIES_H

#include <climits>
#include <vector>
#include <valarray>

class PatternBoundaries {
    double x_min = DBL_MAX;
    double y_min = DBL_MAX;
    double x_max = DBL_MIN;
    double y_max = DBL_MIN;

public:
    [[nodiscard]] double getXMin() const;

    [[nodiscard]] double getYMin() const;

    [[nodiscard]] double getXMax() const;

    [[nodiscard]] double getYMax() const;

    explicit PatternBoundaries(
            const std::vector<std::vector<std::valarray<double>>> &sequence_of_paths, double grid_spacing);

    PatternBoundaries(const PatternBoundaries &one, const PatternBoundaries &two);

    PatternBoundaries(double x_min, double y_min, double x_max, double y_max);

    void join(const PatternBoundaries &other);

    static PatternBoundaries joinRelativeX(const PatternBoundaries &one, const PatternBoundaries &two, double x_offset);

    static PatternBoundaries joinRelativeY(const PatternBoundaries &one, const PatternBoundaries &two, double y_offset);

    void joinRelativeX(const PatternBoundaries &other, double x_offset);

    void joinRelativeY(const PatternBoundaries &other, double y_offset);

    void scale(double multiplier);

    void move(const std::valarray<double> &offset);

    std::valarray<double> getBottomLeftCorner();

    std::valarray<double> getBottomRightCorner();

    std::valarray<double> getTopLeftCorner();

    std::valarray<double> getTopRightCorner();

    [[nodiscard]] std::valarray<double> getCentre() const;

    void print() const;
};

#endif //GCODEGENERATOR_PATTERN_BOUNDARIES_H
