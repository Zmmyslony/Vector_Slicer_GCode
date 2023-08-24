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
// Created by Michał Zmyślony on 04/08/2022.
//

#ifndef GCODEGENERATOR_HYREL_H
#define GCODEGENERATOR_HYREL_H

#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>
#include <valarray>

#include "gcode_file.h"
#include "pattern_boundaries.h"
#include "extrusion_configuration.h"
#include "printer_configuration.h"

namespace fs = boost::filesystem;

class Hyrel : public GCodeFile {

    void defineHeightOffset(double height, unsigned int register_number);

    void invokeHeightOffset(double height, unsigned int register_number);

    void defineToolOffset(int tool_number, const std::vector<double> &xyz);

    void extrude(const std::valarray<double> &xy, double speed);

    void extrude(const std::valarray<double> &xy);

    void selectTool(unsigned int tool_number);

    void setUnitsToMillimetres();

    void signalFinishedPrint();

    void clearOffsets();

    void turnMotorsOff();

    void
    configurePrime(int tool_number, double pulse_rate, double number_of_pulses, double dwell_time,
                   bool is_executed_immediately);

    void
    configureUnprime(int tool_number, double pulse_rate, double number_of_pulses, double dwell_time,
                     bool is_executed_immediately);

    void disablePriming(int tool_number);

    void setTemperatureHotend(int temperature, int tool_number);

public:

    void configureFlow(double nozzle_width, double layer_height, double flow_multiplier, int pulses, int tool);

    void
    init(int hotend_temperature, int bed_temperature, double clean_length, double nozzle_width,
         double first_layer_height, double layer_height, int tool_number, std::vector<double> &tool_offset,
         int cleaning_lines, double prime_pulses, double prime_rate);

    void shutDown(int tool_number, int prime_pulses, int unprime_rate);

    void shutDown(const PrinterConfiguration &printer_configuration);

    Hyrel(int move_speed, int print_speed, double extrusion_coefficient, double lift_off_distance);

    Hyrel(const ExtrusionConfiguration &extrusion_configuration, const PrinterConfiguration &printer_configuration);

    void
    printPath(const std::vector<std::valarray<double>> &path, const std::valarray<double> &position_offset,
              double grid_spacing);

    PatternBoundaries printPattern(const std::vector<std::vector<std::valarray<double>>> &sorted_sequence_of_paths,
                                   const std::valarray<double> &position_offset, double grid_spacing,
                                   bool is_flipped);

    void exportToFile(const boost::filesystem::path &results_path, const std::string &pattern_name,
                      const std::string &suffix, double extruded_amount, const std::string &comment);

    void exportToFile(const boost::filesystem::path &results_path, const std::string &pattern_name,
                      const std::string &suffix, double extruded_amount);

    void configureUvPen(int print_head_tool_number, int pen_tool_number, int duty_cycle);

    void addLocalOffset(std::vector<double> offset);

    void configureUvArray(int print_head_tool_number, int duty_cycle);

    void
    clean_and_prime(double clean_length, int number_of_lines, double nozzle_width, int height_offset_register,
                    double layer_height, double prime_rate, double prime_pulses, int tool_number);

    std::valarray<double>
    printZigZagPattern(double length, int number_of_lines, double line_separation,
                       const std::valarray<double> &starting_position, int initial_index);

    void init(const ExtrusionConfiguration &extrusion_configuration, const PrinterConfiguration &printer_configuration,
              double first_layer_height, std::vector<double> &tool_offset);

    void disableUnpriming(int tool_number);

    std::valarray<double> printZigZagPattern(double length, int number_of_lines, double line_separation,
                                             const std::valarray<double> &starting_position, double speed,
                                             int initial_index);

    int
    primeNow(double length, double prime_rate, double line_separation, double prime_pulses, int tool_number);

    void unprimeNow(double height, double prime_rate, double prime_pulses, int tool_number);
};


void
tuneLineSeparation(const boost::filesystem::path &export_directory, double printing_distance, int number_of_lines,
                   std::vector<double> &tool_offset, int curing_duty_cycle, double first_layer_height,
                   ExtrusionConfiguration extrusion_configuration, PrinterConfiguration printer_configuration,
                   double starting_line_separation, double finishing_line_separation, int line_separation_steps);

void
tuneLineSeparationAndHeight(const boost::filesystem::path &export_directory, double printing_distance,
                            int number_of_lines,
                            std::vector<double> &tool_offset, int curing_duty_cycle, double first_layer_height,
                            ExtrusionConfiguration extrusion_configuration, PrinterConfiguration printer_configuration,
                            double starting_line_separation, double finishing_line_separation,
                            int line_separation_steps,
                            double starting_height, double finishing_height, int height_steps);

void
tuneLineSeparationAndSpeed(const boost::filesystem::path &export_directory, double printing_distance,
                           int number_of_lines,
                           std::vector<double> &tool_offset, int curing_duty_cycle, double first_layer_height,
                           ExtrusionConfiguration extrusion_configuration,
                           PrinterConfiguration printer_configuration, double starting_line_separation,
                           double finishing_line_separation, int line_separation_steps, int starting_speed,
                           int finishing_speed,
                           int speed_steps);

void
multiPatternMultiLayer(const boost::filesystem::path &export_directory, std::vector<fs::path> pattern_paths,
                       const std::vector<std::valarray<double>> &pattern_offsets, std::vector<double> &tool_offset,
                       int curing_duty_cycle, double first_layer_height, std::vector<int> layers,
                       ExtrusionConfiguration extrusion_configuration, PrinterConfiguration printer_configuration,
                       bool is_flipping_enabled, double pattern_rotation) ;

Hyrel standardHyrelInitialisation(const ExtrusionConfiguration &extrusion_configuration,
                                  const PrinterConfiguration &printer_configuration, std::vector<double> &tool_offset,
                                  int curing_duty_cycle, double first_layer_height);

#endif //GCODEGENERATOR_HYREL_H
