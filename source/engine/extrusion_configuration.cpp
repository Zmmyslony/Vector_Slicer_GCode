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

#include "extrusion_configuration.h"

ExtrusionConfiguration::ExtrusionConfiguration(int printing_speed, int nozzle_temperature, double diameter,
                                               double layer_height,
                                               double extrusion_multiplier, double lift_off_distance) : diameter(
        diameter),
                                                                                                        layer_height(
                                                                                                                layer_height),
                                                                                                        extrusion_multiplier(
                                                                                                                extrusion_multiplier),
                                                                                                        printing_speed(
                                                                                                                printing_speed),
                                                                                                        nozzle_temperature(
                                                                                                                nozzle_temperature),
                                                                                                        lift_off_distance(
                                                                                                                lift_off_distance) {}

double ExtrusionConfiguration::getDiameter() const {
    return diameter;
}

double ExtrusionConfiguration::getLayerHeight() const {
    return layer_height;
}

double ExtrusionConfiguration::getExtrusionMultiplier() const {
    return extrusion_multiplier;
}

int ExtrusionConfiguration::getPrintingSpeed() const {
    return printing_speed;
}

int ExtrusionConfiguration::getNozzleTemperature() const {
    return nozzle_temperature;
}

double ExtrusionConfiguration::getLiftOffDistance() const {
    return lift_off_distance;
}
