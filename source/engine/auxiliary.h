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

#ifndef GCODEGENERATOR_AUXILIARY_H
#define GCODEGENERATOR_AUXILIARY_H

#include <iostream>

#include "extrusion_configuration.h"
#include "hyrel.h"

std::string getDiameterString(const ExtrusionConfiguration &extrusion_configuration);

double extrudedAmount(double length, double width, double height, double extrusion_multiplier);

double extrudedAmount(const Hyrel &hyrel, const ExtrusionConfiguration &extrusion_configuration);

std::string getParameterListString(const std::string &parameter_name, double minimum, double maximum, int steps);

std::string getParameterListStringTwoDimensional(const std::string &parameter_name_first, double minimum_first,
                                                 double maximum_first, int steps_first,
                                                 const std::string &parameter_name_second, double minimum_second,
                                                 double maximum_second, int steps_second);

#endif //GCODEGENERATOR_AUXILIARY_H
