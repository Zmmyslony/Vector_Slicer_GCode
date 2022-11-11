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

#include "printer_configuration.h"

PrinterConfiguration::PrinterConfiguration(int non_printing_speed, int bed_temperature, int print_head_tool_number,
                                           int cleaning_lines,
                                           int clean_distance)
        : non_printing_speed(non_printing_speed), bed_temperature(bed_temperature),
          print_head_tool_number(print_head_tool_number), cleaning_lines(cleaning_lines) {}

int PrinterConfiguration::getNonPrintingSpeed() const {
    return non_printing_speed;
}

int PrinterConfiguration::getBedTemperature() const {
    return bed_temperature;
}

int PrinterConfiguration::getPrintHeadToolNumber() const {
    return print_head_tool_number;
}

int PrinterConfiguration::getCleaningLines() const {
    return cleaning_lines;
}

int PrinterConfiguration::getCleanDistance() const {
    return clean_distance;
}
