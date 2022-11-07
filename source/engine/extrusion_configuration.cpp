/*
 * Copyright (c) 2022, Michał Zmyślony, mlz22@cam.ac.uk. All rights reserved.
 *
 * Please cite Michał Zmyślony and Dr John Biggins if you use any part of this code in work you publish or distribute.
 *
 * This file is a part of gCode Generator.
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
