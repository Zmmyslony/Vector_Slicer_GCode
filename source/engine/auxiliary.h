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
// Created by Michał Zmyślony on 07/11/2022.
//

#ifndef GCODEGENERATOR_AUXILIARY_H
#define GCODEGENERATOR_AUXILIARY_H

#include <iostream>

#include "extrusion_configuration.h"
#include "full_printing_configuration.h"
#include "hyrel.h"

std::string getDiameterString(const ExtrusionConfiguration &extrusion_configuration);

double extrudedVolume(double length, double width, double height, double extrusion_multiplier);

double extrudedVolume(const Hyrel &hyrel, const ExtrusionConfiguration &extrusion_configuration);

int extrudedPulses(const Hyrel &hyrel, const ExtrusionConfiguration &extrusion_configuration);

std::string getParameterListString(const std::string &parameter_name, double minimum, double maximum, int steps);

std::string getParameterListStringTwoDimensional(const std::string &parameter_name_first, double minimum_first,
                                                 double maximum_first, int steps_first,
                                                 const std::string &parameter_name_second, double minimum_second,
                                                 double maximum_second, int steps_second);

#endif //GCODEGENERATOR_AUXILIARY_H
