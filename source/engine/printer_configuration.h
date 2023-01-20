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

#ifndef GCODEGENERATOR_PRINTER_CONFIGURATION_H
#define GCODEGENERATOR_PRINTER_CONFIGURATION_H

class PrinterConfiguration {
    int non_printing_speed = 1000;
    int bed_temperature = 0;
    int print_head_tool_number = 1;
    int cleaning_lines = 10;
    int clean_distance = 10;
    int prime_pulses = 0;
    int prime_rate = 0;

public:
    PrinterConfiguration(int non_printing_speed, int bed_temperature, int print_head_tool_number, int cleaning_lines,
                         int cleaning_distance, int priming_pulses, int priming_rate);

    [[nodiscard]] int getNonPrintingSpeed() const;

    [[nodiscard]] int getBedTemperature() const;

    [[nodiscard]] int getPrintHeadToolNumber() const;

    [[nodiscard]] int getCleaningLines() const;

    [[nodiscard]] int getCleanDistance() const;

    [[nodiscard]] int getPrimePulses() const;

    [[nodiscard]] int getPrimeRate() const;
};

#endif //GCODEGENERATOR_PRINTER_CONFIGURATION_H
