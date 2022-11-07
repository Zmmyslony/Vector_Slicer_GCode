/*
 * Copyright (c) 2022, Michał Zmyślony, mlz22@cam.ac.uk. All rights reserved.
 *
 * Please cite Michał Zmyślony and Dr John Biggins if you use any part of this code in work you publish or distribute.
 *
 * This file is a part of gCode Generator.
 */

//
// Created by Michał Zmyślony on 07/11/2022.
//

#include <sstream>
#include <iomanip>

#include "auxiliary.h"

std::string getDiameterString(const ExtrusionConfiguration &extrusion_configuration) {
    std::ostringstream suffix_stream;
    suffix_stream << std::fixed << std::setprecision(3);
    suffix_stream << "_" << extrusion_configuration.getDiameter() << "_um";
    return suffix_stream.str();
}

double extrudedAmount(double length, double width, double height, double extrusion_multiplier) {
    return length * width * height * extrusion_multiplier;
}

double extrudedAmount(const Hyrel &hyrel, const ExtrusionConfiguration &extrusion_configuration) {
    return extrudedAmount(hyrel.getExtrusionValue(), extrusion_configuration.getDiameter(),
                          extrusion_configuration.getLayerHeight(),
                          extrusion_configuration.getExtrusionMultiplier());
}
