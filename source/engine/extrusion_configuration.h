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

public:
    double getDiameter() const;

    double getLayerHeight() const;

    double getExtrusionMultiplier() const;

    int getPrintingSpeed() const;

    int getNozzleTemperature() const;

    ExtrusionConfiguration(int printing_speed, int nozzle_temperature, double diameter, double layer_height,
                           double extrusion_multiplier);

};


#endif //GCODEGENERATOR_EXTRUSION_CONFIGURATION_H
