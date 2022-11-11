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

std::string getParameterListString(const std::string &parameter_name, double minimum, double maximum, int steps) {
    std::ostringstream parameter_list_string;
    parameter_list_string << std::fixed << std::setprecision(3);
    parameter_list_string << "; Varied parameter: " << parameter_name << "; values: ";
    double value_step = (maximum - minimum) / (steps - 1);
    for (int i = 0; i < steps; i++) {
        parameter_list_string << minimum + i * value_step << ", ";
    }
    parameter_list_string << std::endl;
    return parameter_list_string.str();
}

std::string getParameterListStringTwoDimensional(const std::string &parameter_name_first, double minimum_first,
                                                 double maximum_first, int steps_first,
                                                 const std::string &parameter_name_second, double minimum_second,
                                                 double maximum_second, int steps_second) {
    return getParameterListString(parameter_name_first, minimum_first, maximum_first, steps_first) +
           getParameterListString(parameter_name_second, minimum_second, maximum_second, steps_second);
}