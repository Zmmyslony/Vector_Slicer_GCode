/*
 * 2023, Michał Zmyślony, mlz22@cam.ac.uk.
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
// Created by Michał Zmyślony on 31/05/2023.
//

#ifndef GCODEGENERATOR_FULL_PRINTING_CONFIGURATION_H
#define GCODEGENERATOR_FULL_PRINTING_CONFIGURATION_H

#include <boost/filesystem.hpp>
#include <boost/dll.hpp>
#include <filesystem>
#include <valarray>
#include <vector>

#include "extrusion_configuration.h"
#include "printer_configuration.h"
#include "hyrel.h"

namespace fs = boost::filesystem;

class FullPrintingConfiguration {
    ExtrusionConfiguration extrusion_configuration;
    PrinterConfiguration printer_configuration;
    fs::path export_directory;
    std::vector<double> tool_offset;
    int uv_duty_cycle;
    double first_layer_height;

public:
    FullPrintingConfiguration(const ExtrusionConfiguration &extrusion_configuration,
                              const PrinterConfiguration &printer_configuration,
                              fs::path export_directory, std::vector<double> tool_offset,
                              int uv_duty_cycle, double first_layer_height);


    void multiPatternMultiLayer(const std::vector<fs::path> &pattern_paths, std::vector<int> layers,
                                double pattern_offsets, bool is_flipping_enabled,
                                double pattern_rotation);

    void multiLayer(const fs::path &pattern_path, double pattern_offset, int layers,
                    bool is_flipping_enabled, double pattern_rotation);

    void singleLayer(const fs::path &pattern_path, double pattern_offset,
                     bool is_flipping_enabled, double pattern_rotation);

    void tuneLineSeparation(double printing_distance, int number_of_lines,
                            double starting_line_separation, double finishing_line_separation,
                            int line_separation_steps);

    void tuneLineSeparationAndHeight(double printing_distance, int number_of_lines,
                                     double starting_line_separation, double finishing_line_separation,
                                     int line_separation_steps,
                                     double starting_height, double finishing_height, int height_steps);

    void tuneLineSeparationAndSpeed(double printing_distance, int number_of_lines,
                                    double starting_line_separation, double finishing_line_separation,
                                    int line_separation_steps,
                                    int starting_speed, int finishing_speed, int speed_steps);

    void
    printPatternGrid(const std::vector<std::vector<fs::path>> &path_grid,
                     const std::vector<std::vector<int>> &layers_grid,
                     double offsets, bool is_flipping_enabled, double pattern_rotation);
};

#endif //GCODEGENERATOR_FULL_PRINTING_CONFIGURATION_H
