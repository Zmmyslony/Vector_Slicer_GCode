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
