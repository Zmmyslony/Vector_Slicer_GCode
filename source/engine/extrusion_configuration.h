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
// Created by Michał Zmyślony on 25/10/2022.
//

#ifndef GCODEGENERATOR_EXTRUSION_CONFIGURATION_H
#define GCODEGENERATOR_EXTRUSION_CONFIGURATION_H


class ExtrusionConfiguration {
    double diameter = 0.3;
    double layer_height = 0.2;
    double extrusion_multiplier = 1;
    int printing_speed = 100;
    int nozzle_temperature = 20;
    double lift_off_distance = 0;

public:
    [[nodiscard]] double getLiftOffDistance() const;

    [[nodiscard]] double getDiameter() const;

    [[nodiscard]] double getLayerHeight() const;

    [[nodiscard]] double getExtrusionMultiplier() const;

    [[nodiscard]] int getPrintingSpeed() const;

    [[nodiscard]] int getNozzleTemperature() const;

    ExtrusionConfiguration(int printing_speed, int nozzle_temperature, double diameter, double layer_height,
                           double extrusion_multiplier, double lift_off_distance);

};


#endif //GCODEGENERATOR_EXTRUSION_CONFIGURATION_H
