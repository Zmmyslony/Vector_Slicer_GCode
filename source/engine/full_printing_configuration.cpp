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

#include "full_printing_configuration.h"

#include <utility>
#include <iostream>

FullPrintingConfiguration::FullPrintingConfiguration(const ExtrusionConfiguration &extrusion_configuration,
                                                     const PrinterConfiguration &printer_configuration,
                                                     fs::path export_directory, std::vector<double> tool_offset,
                                                     int uv_duty_cycle, double first_layer_height)
        : extrusion_configuration(extrusion_configuration), printer_configuration(printer_configuration),
          export_directory(std::move(export_directory)),
          tool_offset(std::move(tool_offset)), uv_duty_cycle(uv_duty_cycle), first_layer_height(first_layer_height) {}


void FullPrintingConfiguration::printPatternColumn(const std::vector<fs::path> &pattern_paths,
                                                   const std::vector<int> &layers,
                                                   double offsets, bool is_flipping_enabled,
                                                   double pattern_rotation)
/***
 * Prints patterns in a column-like manner (y-axis)
 * @param pattern_paths
 * @param layers if not all patterns have specified layer count, it uses the last specified value for further patterns.
 * @param offsets distance between patterns in y-direction.
 * @param is_flipping_enabled are patterns mirrored between the layers.
 * @param pattern_rotation are patterns rotated.
 */
{
    std::vector<std::vector<fs::path>> path_grid = {{}};
    std::vector<std::vector<int>> layers_grid = {{}};
    for (const auto &pattern_path: pattern_paths) {
        path_grid.emplace_back(std::vector<fs::path>{pattern_path});
    }
    for (const int &layer: layers) {
        layers_grid.emplace_back(std::vector<int>{layer});
    }

    printPatternGrid(path_grid, layers_grid, offsets, is_flipping_enabled, pattern_rotation);
}

void FullPrintingConfiguration::printPatternColumn(const fs::path &pattern_paths,
                                                   const int &layers,
                                                   double offsets, bool is_flipping_enabled,
                                                   double pattern_rotation)
/***
 * Prints patterns in a column-like manner (y-axis)
 * @param pattern_paths
 * @param layers if not all patterns have specified layer count, it uses the last specified value for further patterns.
 * @param offsets distance between patterns in y-direction.
 * @param is_flipping_enabled are patterns mirrored between the layers.
 * @param pattern_rotation are patterns rotated.
 */
{
    printPatternColumn(std::vector<fs::path>{pattern_paths}, std::vector<int>{layers}, offsets, is_flipping_enabled, pattern_rotation);
}

void FullPrintingConfiguration::printPatternRow(const std::vector<fs::path> &pattern_paths,
                                                const std::vector<int> &layers,
                                                double offsets, bool is_flipping_enabled,
                                                double pattern_rotation)
/***
 * Prints patterns in a row-like manner (x-axis)
 * @param pattern_paths
 * @param layers if not all patterns have specified layer count, it uses the last specified value for further patterns.
 * @param offsets distance between patterns in x-direction.
 * @param is_flipping_enabled are patterns mirrored between the layers.
 * @param pattern_rotation are patterns rotated.
 */
{
    printPatternGrid({pattern_paths}, {layers}, offsets, is_flipping_enabled, pattern_rotation);
}

void FullPrintingConfiguration::printPatternRow(const fs::path &pattern_paths,
                                                const int &layers,
                                                double offsets, bool is_flipping_enabled,
                                                double pattern_rotation)
/***
 * Prints patterns in a row-like manner (x-axis)
 * @param pattern_paths
 * @param layers if not all patterns have specified layer count, it uses the last specified value for further patterns.
 * @param offsets distance between patterns in x-direction.
 * @param is_flipping_enabled are patterns mirrored between the layers.
 * @param pattern_rotation are patterns rotated.
 */
{
    printPatternRow(std::vector<fs::path>{pattern_paths}, std::vector<int>{layers}, offsets, is_flipping_enabled, pattern_rotation);
}

void FullPrintingConfiguration::printPatternGrid(const std::vector<std::vector<fs::path>> &path_grid,
                                                 const std::vector<std::vector<int>> &layers_grid,
                                                 double offsets, bool is_flipping_enabled, double pattern_rotation)
/***
* Prints provided patterns in a grid, where the first dimension goes in the x-direction and the 2nd in the y-direction.
*
* @param path_grid grid of patterns to print - note [0, 0] pattern is automatically the cleaning pattern.
* @param layers_grid layers corresponding to each pattern. If the there are too few rows (1st dim), the following rows
* will have the same number of layers as the last pattern in the last existing row. If there are too few entries in the
* row, it repeats the last value.
* @param offsets mm distance between patterns in each row, and between the rows.
* @param is_flipping_enabled - are patterns flipped between the layers.
* @param pattern_rotation - are all patterns rotated.
*/
{
    try {
        ::printPatternGrid(export_directory, path_grid, layers_grid, offsets, tool_offset, uv_duty_cycle,
                           first_layer_height, extrusion_configuration, printer_configuration,
                           is_flipping_enabled, pattern_rotation);
    }
    catch (std::runtime_error &err) {
        std::cout << err.what() << std::endl;
    }
}


void FullPrintingConfiguration::tuneLineSeparation(double printing_distance, int number_of_lines,
                                                   double starting_line_separation, double finishing_line_separation,
                                                   int line_separation_steps) {
    ::tuneLineSeparation(export_directory, printing_distance, number_of_lines, tool_offset, uv_duty_cycle,
                         first_layer_height, extrusion_configuration, printer_configuration, starting_line_separation,
                         finishing_line_separation, line_separation_steps);
}


void FullPrintingConfiguration::tuneLineSeparationAndHeight(double printing_distance, int number_of_lines,
                                                            double starting_line_separation,
                                                            double finishing_line_separation, int line_separation_steps,
                                                            double starting_height, double finishing_height,
                                                            int height_steps) {

    ::tuneLineSeparationAndHeight(export_directory, printing_distance, number_of_lines, tool_offset, uv_duty_cycle,
                                  first_layer_height, extrusion_configuration, printer_configuration,
                                  starting_line_separation, finishing_line_separation, line_separation_steps,
                                  starting_height, finishing_height, height_steps);
}


void FullPrintingConfiguration::tuneLineSeparationAndSpeed(double printing_distance, int number_of_lines,
                                                           double starting_line_separation,
                                                           double finishing_line_separation, int line_separation_steps,
                                                           int starting_speed, int finishing_speed, int speed_steps) {

    ::tuneLineSeparationAndSpeed(export_directory, printing_distance, number_of_lines, tool_offset, uv_duty_cycle,
                                 first_layer_height, extrusion_configuration, printer_configuration,
                                 starting_line_separation, finishing_line_separation, line_separation_steps,
                                 starting_speed, finishing_speed, speed_steps);

}

const ExtrusionConfiguration &FullPrintingConfiguration::getExtrusionConfiguration() const {
    return extrusion_configuration;
}

const PrinterConfiguration &FullPrintingConfiguration::getPrinterConfiguration() const {
    return printer_configuration;
}







