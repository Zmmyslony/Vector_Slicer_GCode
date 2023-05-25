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

#include <iostream>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <math.h>

#include "hyrel.h"
#include "valarray_operations.h"
#include "pattern_boundaries.h"
#include "extrusion_configuration.h"
#include "printer_configuration.h"
#include "auxiliary.h"
#include "config.h"
#include "importing.h"

const std::string version = "0.2a";

int mCommandToolNumber(int tool_number) {
    return tool_number + 11;
}

void Hyrel::selectTool(unsigned int tool_number) {
    const unsigned int number_of_tools = 4;
    if (tool_number < number_of_tools) {
        addComment("Selecting tool");
        generalCommand('T', (int) tool_number);
    }
}

void Hyrel::defineHeightOffset(double height, unsigned int register_number) {
    const double max_height = 120;
    if (0 > height || height > max_height) {
        std::cout << "Gcode writing -> defineHeightOffset -> tool height: max value "
                  << max_height << ", used value " << height << "\n";
    } else {
        generalCommand({'M', 'H', 'Z'},
                       {true, true, false},
                       {660, (double) register_number, height});
    }
}

void Hyrel::invokeHeightOffset(double height, unsigned int register_number) {
    generalCommand({'G', 'Z', 'H'},
                   {true, false, true},
                   {0, height, (double) register_number});
}

void
Hyrel::defineToolOffset(int tool_number, const std::vector<double> &xyz) {
    const double x_max = 200;
    const double y_max = 200;
    const double z_max = 120;
    if (0 > xyz[0] || xyz[0] > x_max) {
        std::cout << "Gcode writing -> defineToolOffset -> tool x coordinate: max value "
                  << x_max << ", used value " << xyz[0] << "\n";
    } else if (0 > xyz[1] || xyz[1] > y_max) {
        std::cout << "Gcode writing -> defineToolOffset -> tool y coordinate: max value "
                  << y_max << ", used value " << xyz[1] << "\n";
    } else if (0 > xyz[2] || xyz[2] > z_max) {
        std::cout << "Gcode writing -> defineToolOffset -> tool z coordinate: max value "
                  << z_max << ", used value " << xyz[2] << "\n";
    } else {
        addComment("Defining tool offset");
        generalCommand(
                {'M', 'T', 'O', 'X', 'Y', 'Z'},
                {true, true, true, false, false, false},
                {6, (double) mCommandToolNumber(tool_number), (double) (tool_number + 1), xyz[0], xyz[1], xyz[2]});
    }
}

void Hyrel::configurePrime(int tool_number, double pulse_rate, double number_of_pulses, double dwell_time,
                           bool is_executed_immediately) {
    addComment("Configure priming");
    generalCommand({'M', 'T', 'S', 'E', 'P'},
                   {true, true, false, false, false},
                   {722, (double) mCommandToolNumber(tool_number), pulse_rate, number_of_pulses, dwell_time});
    if (is_executed_immediately) {
        generalCommand({'M', 'T', 'I'},
                       {true, true, true},
                       {722, (double) mCommandToolNumber(tool_number), (double) is_executed_immediately});
    }
}

void Hyrel::configureUnprime(int tool_number, double pulse_rate, double number_of_pulses, double dwell_time,
                             bool is_executed_immediately) {
    addComment("Configure unpriming");
    if (number_of_pulses > 0) {
        dwell_time = -number_of_pulses / pulse_rate * 1000;
        dwell_time = 0;
    } else {
        dwell_time = 0;
    }
    generalCommand({'M', 'T', 'S', 'E', 'P'},
                   {true, true, false, false, false},
                   {721, (double) mCommandToolNumber(tool_number), pulse_rate, number_of_pulses, dwell_time});
    if (is_executed_immediately) {
        generalCommand({'M', 'T', 'I'},
                       {true, true, true},
                       {721, (double) mCommandToolNumber(tool_number), (double) is_executed_immediately});
    }
}

void Hyrel::disablePriming(int tool_number) {
    configurePrime(tool_number, 0, 0, 0, false);
}

void Hyrel::disableUnpriming(int tool_number) {
    configureUnprime(tool_number, 0, 0, 0, false);
}


void Hyrel::extrude(const std::valarray<double> &xy, double speed) {
    std::valarray<double> new_positions = {xy[0], xy[1], positions[2]};
    double extrusion_length = norm(new_positions - positions);
    extrusion_value += extrusion_length;
    print_time += extrusion_length / speed;
    positions = new_positions;
    generalCommand({'G', 'X', 'Y', 'F', 'E'},
                   {true, false, false, true, true},
                   {1, xy[0], xy[1], (double) speed, 1});
}


void Hyrel::extrude(const std::valarray<double> &xy) {
    extrude(xy, print_speed);
}


void Hyrel::configureFlow(double nozzle_width, double layer_height, double flow_multiplier, int pulses, int tool) {
    addComment("Configuring flow");
    generalCommand({'M', 'T', 'W', 'Z', 'S', 'P'},
                   {true, true, false, false, false, true},
                   {221, (double) mCommandToolNumber(tool), nozzle_width, layer_height, flow_multiplier,
                    (double) pulses});
}

void Hyrel::setTemperatureHotend(int temperature, int tool_number) {
    addComment("Setting hotend temperature");
    generalCommand({'M', 'T', 'S'}, {true, true, true},
                   {109, (double) mCommandToolNumber(tool_number), (double) temperature});
}

void Hyrel::setUnitsToMillimetres() {
    addComment("Setting units to millimetres");
    generalCommand('G', 21);
}

void Hyrel::turnMotorsOff() {
    addComment("Turning motors off");
    generalCommand('M', 18);
}

void Hyrel::signalFinishedPrint() {
    addComment("Signaling finished print");
    generalCommand('M', 30);
}

void Hyrel::clearOffsets() {
    addComment("Clearing offsets");
    generalCommand('G', 53);
}

std::valarray<double> Hyrel::printZigZagPattern(double length, int number_of_lines, double line_separation,
                                                const std::valarray<double> &starting_position, double speed,
                                                int initial_index) {
//    extrude(starting_position, speed);
//    extrude(starting_position + std::valarray<double>{length, 0}, speed);
    std::valarray<double> last_coordinate;

    for (int i = initial_index; i < number_of_lines; i++) {
        if (i % 2 == 0) {
            extrude(starting_position + std::valarray<double>{0, i * line_separation}, speed);
            extrude(starting_position + std::valarray<double>{length, i * line_separation}, speed);
        } else {
            extrude(starting_position + std::valarray<double>{length, i * line_separation}, speed);
            extrude(starting_position + std::valarray<double>{0, i * line_separation}, speed);
        }
    }
    last_coordinate = starting_position + std::valarray<double>{0, (number_of_lines - 1) * line_separation};
    return last_coordinate;
}

std::valarray<double> Hyrel::printZigZagPattern(double length, int number_of_lines, double line_separation,
                                                const std::valarray<double> &starting_position, int initial_index) {
    return printZigZagPattern(length, number_of_lines, line_separation, starting_position, print_speed, initial_index);
}

int Hyrel::primeNow(double length, double prime_rate, double line_separation, double prime_pulses, int tool_number) {
    int priming_lines = ceil(prime_pulses / (USHRT_MAX - 1));
    double priming_pulses_per_line = prime_pulses / priming_lines;
    double priming_time = priming_pulses_per_line / prime_rate / 60;
    double priming_speed = std::min((double) print_speed, length / priming_time);
    addComment("Priming now");
    configurePrime(tool_number, prime_rate, priming_pulses_per_line, 0, false);

    for (int i = 0; i < priming_lines; i++) {
        if (i % 2 == 0) {
            movePlanar({0, i * line_separation});
            extrude(std::valarray<double>{length, i * line_separation}, priming_speed);
        } else {
            movePlanar({length, i * line_separation});
            extrude(std::valarray<double>{0, i * line_separation}, priming_speed);
        }
    }
    disablePriming(tool_number);
    addBreak();
    return priming_lines;
}

void Hyrel::unprimeNow(double height, double prime_rate, double prime_pulses, int tool_number) {
    int priming_steps = ceil(prime_pulses / (USHRT_MAX - 1));
    double priming_pulses_per_line = prime_pulses / priming_steps;
    double priming_time = priming_pulses_per_line / prime_rate / 60;
    double priming_speed = std::min((double) print_speed, height / priming_time);
    addComment("Unpriming now");
    for (int i = 0; i < priming_steps; i++) {
        configureUnprime(tool_number, prime_rate, priming_pulses_per_line, 0, true);
        move(positions[0], positions[1], positions[2] + height, priming_speed);
    }
    disableUnpriming(tool_number);
}


void Hyrel::clean_and_prime(double clean_length, int number_of_lines, double nozzle_width, int height_offset_register,
                            double layer_height, double prime_rate, double prime_pulses, int tool_number) {
    addComment("Invoking offsets");
    movePlanar({0, 0});
    defineHeightOffset(layer_height, height_offset_register);
    invokeHeightOffset(0, height_offset_register);
    addBreak();

    int primed_lines = primeNow(clean_length, prime_rate, 2 * nozzle_width, prime_pulses, tool_number);

    addComment("Starting cleaning");
    if (clean_length > 0) {
        printZigZagPattern(clean_length, number_of_lines, 2 * nozzle_width, {0, 0}, primed_lines);
    }
}

void
Hyrel::init(int hotend_temperature, int bed_temperature, double clean_length, double nozzle_width,
            double first_layer_height, double layer_height, int tool_number, std::vector<double> &tool_offset,
            int cleaning_lines, double prime_pulses, double prime_rate) {
    const int height_offset_register = 2;
    const int kra_2_pulses_per_microlitre = 1297;

    addBreak();
    addComment(
            "Tool selected: T" + std::to_string(tool_number) + " / T" +
            std::to_string(mCommandToolNumber(tool_number)));
    addComment("Nozzle diameter: " + std::to_string(nozzle_width) + " mm");
    addComment("First layer height: " + std::to_string(first_layer_height) + " mm");
    addComment("Layer height: " + std::to_string(layer_height) + " mm");
    addBreak();

    setUnitsToMillimetres();
    clearOffsets();
    addBreak();

    autoHome2D();
    addBreak();
    defineToolOffset(tool_number, tool_offset);
    addBreak();

    setTemperatureHotend(hotend_temperature, tool_number);
    setTemperatureBed(bed_temperature);
    addBreak();

    disablePriming(tool_number);
    disableUnpriming(tool_number);
    configureFlow(nozzle_width, layer_height, extrusion_coefficient, kra_2_pulses_per_microlitre, tool_number);

    selectTool(tool_number);
    addBreak();
    clean_and_prime(clean_length, cleaning_lines, nozzle_width, height_offset_register, first_layer_height, prime_rate,
                    prime_pulses, tool_number);
    addBreak();

    addBreak();
    addComment("Starting printing");
}

void
Hyrel::init(const ExtrusionConfiguration &extrusion_configuration, const PrinterConfiguration &printer_configuration,
            double first_layer_height, std::vector<double> &tool_offset) {
    init(extrusion_configuration.getNozzleTemperature(), printer_configuration.getBedTemperature(),
         printer_configuration.getCleanDistance(),
         extrusion_configuration.getDiameter(), first_layer_height, extrusion_configuration.getLayerHeight(),
         printer_configuration.getPrintHeadToolNumber(), tool_offset, printer_configuration.getCleaningLines(),
         printer_configuration.getPrimePulses(), printer_configuration.getPrimeRate());
}

void Hyrel::configureUvPen(int print_head_tool_number, int pen_tool_number, int duty_cycle) {
    if (duty_cycle >= 0 && duty_cycle <= 100) {
        addComment("Linking pen to activate with the printing moves ");
        generalCommand({'M', 'T', 'S'},
                       {true, true, true},
                       {703, (double) mCommandToolNumber(pen_tool_number),
                        (double) mCommandToolNumber(print_head_tool_number)});
        generalCommand({'M', 'T', 'E'},
                       {true, true, true},
                       {620, (double) mCommandToolNumber(pen_tool_number), 1});
        generalCommand({'M', 'T', 'P'},
                       {true, true, true},
                       {621, (double) mCommandToolNumber(pen_tool_number), (double) duty_cycle});
    }
}

void Hyrel::configureUvArray(int print_head_tool_number, int duty_cycle) {
    if (duty_cycle >= 0 && duty_cycle <= 100) {
        addComment("Setting UV array duty cycle ");
        generalCommand({'M', 'T', 'P'},
                       {true, true, true},
                       {106, (double) mCommandToolNumber(print_head_tool_number),
                        (double) duty_cycle});
    }
    addBreak();
}

void Hyrel::shutDown(int tool_number, int prime_pulses, int unprime_rate) {
    addBreak();
    unprimeNow(5, unprime_rate, prime_pulses, tool_number);
    addBreak();

    setTemperatureBed(0);
    GCodeFile::setTemperatureHotend(0);
    addBreak();

    autoHome2D();
//    move(0, 0, 40); // Hyrel 30M has zero height at the print-bed
//    addBreak();

    turnMotorsOff();
    signalFinishedPrint();
}

void Hyrel::shutDown(const PrinterConfiguration &printer_configuration) {
    shutDown(printer_configuration.getPrintHeadToolNumber(), printer_configuration.getPrimePulses(),
             printer_configuration.getUnprimeRate());
}

Hyrel::Hyrel(int move_speed, int print_speed, double extrusion_coefficient, double lift_off_distance)
        : GCodeFile(move_speed, print_speed,
                    extrusion_coefficient, lift_off_distance) {

}

Hyrel::Hyrel(const ExtrusionConfiguration &extrusion_configuration, const PrinterConfiguration &printer_configuration)
        : Hyrel(printer_configuration.getNonPrintingSpeed(), extrusion_configuration.getPrintingSpeed(),
                extrusion_configuration.getExtrusionMultiplier(), extrusion_configuration.getLiftOffDistance()) {

}

bool isInDifferentDirection(const std::valarray<double> &last_position,
                            const std::valarray<double> &position,
                            const std::valarray<double> &previous_position,
                            const std::valarray<double> &previous_connecting_vector) {
    std::valarray<double> connecting_vector = position - previous_position;
    double dot_length = dot(previous_connecting_vector, connecting_vector) /
                        (norm(previous_connecting_vector) * norm(connecting_vector));
    return dot_length < 1 || isEqual(position == last_position);
}

void Hyrel::printPath(const std::vector<std::valarray<double>> &path, const std::valarray<double> &position_offset,
                      double grid_distance) {
    addComment("Starting new path.");
    std::valarray<double> previous_connecting_vector = {1, 0};
    std::valarray<double> previous_position = {0, 0};

    for (auto &position: path) {
        // Check if the printing direction differs, and if it doesn't merge the points into a single line to make gcode
        // clearer. Additionally, if it is a last point print it even if it is in the same direction.
        if (isInDifferentDirection(path.back(), position, previous_position, previous_connecting_vector)) {
            previous_connecting_vector = position - previous_position;
            extrude(position * grid_distance + position_offset);
        }
        previous_position = position;
    }
}

PatternBoundaries Hyrel::printPattern(const std::vector<std::vector<std::valarray<double>>> &sorted_sequence_of_paths,
                                      const std::valarray<double> &position_offset, double grid_spacing,
                                      bool is_flipped) {
    PatternBoundaries pattern_boundaries(sorted_sequence_of_paths);
    pattern_boundaries.scale(grid_spacing);
    pattern_boundaries.move(position_offset);
    for (auto &path: sorted_sequence_of_paths) {
        addComment("Moving to new path.");
        movePlanar(path[0] * grid_spacing + position_offset);

        printPath(path, position_offset, grid_spacing);
    }
    addComment("Pattern completed.");
//    pattern_boundaries.print();
    return pattern_boundaries;
}

void Hyrel::exportToFile(const boost::filesystem::path &results_path, const std::string &pattern_name,
                         const std::string &suffix, double extruded_amount, const std::string &comment) {
    if (!is_directory(results_path)) {
        std::cout << "GCode directory \"" << results_path.string() << "\" does not exist. Attempting to create it."
                  << std::endl;
        boost::filesystem::create_directory(results_path);
        if (!is_directory(results_path)) {
            std::cout << "GCode directory could not be created. Please create it manually." << std::endl;
            std::cout << "Aborting generation of " << pattern_name << std::endl;
            return;
        } else {
            std::cout << "Creation successful." << std::endl;
        }
    }
    boost::filesystem::path filename = results_path / (pattern_name + suffix + ".gcode");
    std::ofstream file(filename.string());

    time_t ttime = time(nullptr);

    char time[26];
    ctime_s(time, sizeof time, &ttime);
    file << std::fixed << std::setprecision(3);
    file << "; Generated using GCodeGenerator " << PROJECT_VER << " on " << time;
    file << "; Michal Zmyslony, University of Cambridge, mlz22@cam.ac.uk" << std::endl << std::endl;
    file << "; Estimated print time: " << print_time << " min" << std::endl;
    file << "; Estimated amount of extruded material: " << extruded_amount << " ul" << std::endl;
    file << comment;
    file << getText();
    file.close();
    std::cout << "Exported \"" << filename.stem().string() << "\" successfully." << std::endl;
}

void Hyrel::exportToFile(const boost::filesystem::path &results_path, const std::string &pattern_name,
                         const std::string &suffix, double extruded_amount) {
    exportToFile(results_path, pattern_name, suffix, extruded_amount, "");
}

void Hyrel::addLocalOffset(std::vector<double> offset) {
    generalCommand({'G', 'X', 'Y', 'Z'},
                   {true, false, false, false},
                   {54, offset[0], offset[1], offset[2]});
}

void printMultiLayer(Hyrel &hyrel, const std::valarray<double> &initial_pattern_offset, double grid_spacing,
                     const std::vector<std::vector<std::vector<std::valarray<double>>>> &stacked_patterns, int layers,
                     double layer_height,
                     bool is_flipping_enabled) {

    for (int i = 0; i < layers; i++) {
        const auto &current_pattern = stacked_patterns[i % stacked_patterns.size()];

        double current_layer_height = i * layer_height;
        hyrel.moveVertical(current_layer_height);
        if (is_flipping_enabled && i % 2 == 1) {
            auto flipped_pattern = flipPattern(current_pattern);
            hyrel.printPattern(flipped_pattern, initial_pattern_offset, grid_spacing, true);
        } else {
            hyrel.printPattern(current_pattern, initial_pattern_offset, grid_spacing, false);
        }
    }
}

void
singleLayer(const boost::filesystem::path &export_directory, const fs::path &pattern_path, double grid_spacing,
            const std::valarray<double> &pattern_offset, std::vector<double> &tool_offset, int curing_duty_cycle,
            double first_layer_height, ExtrusionConfiguration extrusion_configuration,
            PrinterConfiguration printer_configuration) {
    multiLayer(export_directory, pattern_path, pattern_offset, tool_offset, curing_duty_cycle,
               first_layer_height, 1, extrusion_configuration, printer_configuration, false, 0);
}

Hyrel standardHyrelInitialisation(const ExtrusionConfiguration &extrusion_configuration,
                                  const PrinterConfiguration &printer_configuration, std::vector<double> &tool_offset,
                                  int curing_duty_cycle, double first_layer_height) {
    Hyrel hyrel(extrusion_configuration, printer_configuration);
    hyrel.init(extrusion_configuration, printer_configuration, first_layer_height, tool_offset);

    hyrel.configureUvArray(printer_configuration.getPrintHeadToolNumber(), curing_duty_cycle);
    return hyrel;
}

void
multiPatternMultiLayer(const boost::filesystem::path &export_directory, std::vector<fs::path> pattern_paths,
                       const std::vector<vald> &pattern_offsets, std::vector<double> &tool_offset,
                       int curing_duty_cycle, double first_layer_height, int layers,
                       ExtrusionConfiguration extrusion_configuration, PrinterConfiguration printer_configuration,
                       bool is_flipping_enabled, double pattern_rotation) {
    for (auto &pattern_path : pattern_paths) {
        pattern_path.replace_extension("csv");
    }

    if (std::all_of(pattern_paths.begin(), pattern_paths.end(),
                    [](const fs::path &pattern_path) { return fs::exists(pattern_path); })) {
        Hyrel hyrel = standardHyrelInitialisation(extrusion_configuration, printer_configuration,
                                                  tool_offset, curing_duty_cycle, first_layer_height);

        std::valarray<double> cleaning_offset = {0, 2 * printer_configuration.getCleaningLines() *
                                                    extrusion_configuration.getDiameter()};

        std::string pattern_name;
        assert(pattern_paths.size() == pattern_offsets.size());

        for (int i = 0; i < pattern_paths.size(); i++) {
            double slicing_resolution = readResolution(pattern_paths[i]);
            double grid_spacing = extrusion_configuration.getDiameter() / slicing_resolution;

            std::vector<std::vector<std::vector<vald>>> stacked_patterns = readPrintList(pattern_paths[i]);
            stacked_patterns = rotatePattern(stacked_patterns, pattern_rotation);
            printMultiLayer(hyrel, pattern_offsets[i] + cleaning_offset, grid_spacing, stacked_patterns, layers,
                            extrusion_configuration.getLayerHeight(), is_flipping_enabled);
            pattern_name += pattern_paths[i].stem().string() + "_";
        }
        pattern_name.pop_back();

        hyrel.shutDown(printer_configuration);

        std::string diameter_suffix = getDiameterString(extrusion_configuration);
        std::string suffix = diameter_suffix + "_" + std::to_string(layers) + "_layers";
        double extruded_amount = extrudedAmount(hyrel, extrusion_configuration);
        hyrel.exportToFile(export_directory, pattern_name, suffix, extruded_amount);
    } else {
        std::cout << "ERROR: One of the input directories \"" << pattern_paths[0] << "\" does not exist." << std::endl;
    }
}

void
multiLayer(const boost::filesystem::path &export_directory, fs::path pattern_path,
           const std::valarray<double> &pattern_offset, std::vector<double> &tool_offset, int curing_duty_cycle,
           double first_layer_height, int layers, ExtrusionConfiguration extrusion_configuration,
           PrinterConfiguration printer_configuration, bool is_flipping_enabled, double pattern_rotation) {

    multiPatternMultiLayer(export_directory, {pattern_path}, {pattern_offset}, tool_offset,
                           curing_duty_cycle, first_layer_height, layers, extrusion_configuration,
                           printer_configuration, is_flipping_enabled, pattern_rotation);
}


void tuneLineSeparationBody(Hyrel &hyrel, std::valarray<double> &current_offset,
                            const std::valarray<double> &pattern_spacing,
                            double finishing_line_separation, double starting_line_separation,
                            int line_separation_steps, double printing_distance, int number_of_lines, double diameter) {
    double line_separation_step = (finishing_line_separation - starting_line_separation) / (line_separation_steps - 1);
    for (int j = 0; j < line_separation_steps; j++) {
        hyrel.movePlanar(current_offset + pattern_spacing);
        current_offset = hyrel.printZigZagPattern(printing_distance, number_of_lines,
                                                  (starting_line_separation + j * line_separation_step) *
                                                  diameter, current_offset + pattern_spacing, 0);
    }
}

void
tuneLineSeparation(const boost::filesystem::path &export_directory, double printing_distance, int number_of_lines,
                   std::vector<double> &tool_offset, int curing_duty_cycle, double first_layer_height,
                   ExtrusionConfiguration extrusion_configuration, PrinterConfiguration printer_configuration,
                   double starting_line_separation, double finishing_line_separation,
                   int line_separation_steps) {
    Hyrel hyrel = standardHyrelInitialisation(extrusion_configuration, printer_configuration,
                                              tool_offset, curing_duty_cycle, first_layer_height);
    std::valarray<double> current_offset = {0, 2 * printer_configuration.getCleaningLines() *
                                               extrusion_configuration.getDiameter()};

    tuneLineSeparationBody(hyrel, current_offset, std::valarray<double>{0, 1}, finishing_line_separation,
                           starting_line_separation, line_separation_steps, printing_distance, number_of_lines,
                           extrusion_configuration.getDiameter());
    hyrel.shutDown(printer_configuration);

    std::string diameter_suffix = getDiameterString(extrusion_configuration);
    double extruded_amount = extrudedAmount(hyrel, extrusion_configuration);
    std::string tuning_description = getParameterListString("relative_line_spacing", starting_line_separation,
                                                            finishing_line_separation, line_separation_steps);
    hyrel.exportToFile(export_directory, "line_spacing", diameter_suffix, extruded_amount,
                       tuning_description);
}

void
tuneLineSeparationAndHeight(const boost::filesystem::path &export_directory, double printing_distance,
                            int number_of_lines,
                            std::vector<double> &tool_offset, int curing_duty_cycle, double first_layer_height,
                            ExtrusionConfiguration extrusion_configuration, PrinterConfiguration printer_configuration,
                            double starting_line_separation, double finishing_line_separation,
                            int line_separation_steps,
                            double starting_height, double finishing_height, int height_steps) {
    Hyrel hyrel = standardHyrelInitialisation(extrusion_configuration, printer_configuration,
                                              tool_offset, curing_duty_cycle, first_layer_height);

    std::valarray<double> base_offset = {0, 2 * printer_configuration.getCleaningLines() *
                                            extrusion_configuration.getDiameter()};
    std::valarray<double> current_offset;

    double height_step = (finishing_height - starting_height) / (height_steps - 1);
    for (int i = 0; i < height_steps; i++) {
        hyrel.moveVertical(starting_height + i * height_step - first_layer_height);
        current_offset = base_offset;
        base_offset += {printing_distance + 1, 0};
        tuneLineSeparationBody(hyrel, current_offset, std::valarray<double>{0, 1}, finishing_line_separation,
                               starting_line_separation, line_separation_steps, printing_distance, number_of_lines,
                               extrusion_configuration.getDiameter());
    }

    hyrel.shutDown(printer_configuration);

    std::string diameter_suffix = getDiameterString(extrusion_configuration);
    double extruded_amount = extrudedAmount(hyrel, extrusion_configuration);
    std::string tuning_description = getParameterListStringTwoDimensional("height", starting_height, finishing_height,
                                                                          height_steps, "relative_line_spacing",
                                                                          starting_line_separation,
                                                                          finishing_line_separation,
                                                                          line_separation_steps);
    hyrel.exportToFile(export_directory, "height_and_line_spacing", diameter_suffix,
                       extruded_amount, tuning_description);
}

void
tuneLineSeparationAndSpeed(const boost::filesystem::path &export_directory, double printing_distance,
                           int number_of_lines,
                           std::vector<double> &tool_offset, int curing_duty_cycle, double first_layer_height,
                           ExtrusionConfiguration extrusion_configuration,
                           PrinterConfiguration printer_configuration, double starting_line_separation,
                           double finishing_line_separation, int line_separation_steps, int starting_speed,
                           int finishing_speed,
                           int speed_steps) {
    Hyrel hyrel = standardHyrelInitialisation(extrusion_configuration, printer_configuration,
                                              tool_offset, curing_duty_cycle, first_layer_height);

    std::valarray<double> base_offset = {0, 2 * printer_configuration.getCleaningLines() *
                                            extrusion_configuration.getDiameter()};
    std::valarray<double> current_offset;

    int speed_step = (finishing_speed - starting_speed) / (speed_steps - 1);
    for (int i = 0; i < speed_steps; i++) {
        hyrel.setPrintSpeed(starting_speed + speed_step * i);
        current_offset = base_offset;
        base_offset += {printing_distance + 1, 0};
        tuneLineSeparationBody(hyrel, current_offset, std::valarray<double>{0, 1}, finishing_line_separation,
                               starting_line_separation, line_separation_steps, printing_distance, number_of_lines,
                               extrusion_configuration.getDiameter());
    }
    hyrel.shutDown(printer_configuration);

    std::string diameter_suffix = getDiameterString(extrusion_configuration);
    double extruded_amount = extrudedAmount(hyrel, extrusion_configuration);
    std::string tuning_description = getParameterListStringTwoDimensional("speed", starting_speed, finishing_speed,
                                                                          speed_steps, "relative_line_spacing",
                                                                          starting_line_separation,
                                                                          finishing_line_separation,
                                                                          line_separation_steps);
    hyrel.exportToFile(export_directory, "speed_and_line_spacing", diameter_suffix,
                       extruded_amount, tuning_description);
}
