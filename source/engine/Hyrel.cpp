//
// Created by Michał Zmyślony on 04/08/2022.
//

#include <iostream>
#include <fstream>
#include <ctime>

#include "Hyrel.h"
#include "ValarrayOperations.h"
#include "Exporting.h"
#include "PatternBoundaries.h"

const std::string version = "0.1a";

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

void Hyrel::defineHeightOffset(unsigned int register_number, double height) {
// TODO Obtain max tool numbers from a new class of Printer -> Hyrel and automate retrieving maximal values
    const double max_height = 120;
    if (0 > height || height > max_height) {
        std::cout << "Gcode writing -> defineHeightOffset -> tool height: max value "
                  << max_height << ", used value " << height << "\n";
    } else {
        body_stream << "M660 H" << register_number << " Z" << height << "\n";
    }
}

void
Hyrel::defineToolOffset(int tool_number, const std::vector<double> &xyz, unsigned int height_register_offset) {
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
    generalCommand({'M', 'T', 'S', 'E', 'P', 'I'},
                   {true, true, false, false, false, true},
                   {722, (double) mCommandToolNumber(tool_number), pulse_rate, number_of_pulses, dwell_time,
                    (double) is_executed_immediately});
}


void Hyrel::configureUnprime(int tool_number, double pulse_rate, double number_of_pulses, double dwell_time,
                             bool is_executed_immediately) {
    addComment("Configure priming");
    generalCommand({'M', 'T', 'S', 'E', 'P', 'I'},
                   {true, true, false, false, false, true},
                   {721, (double) mCommandToolNumber(tool_number), pulse_rate, number_of_pulses, dwell_time,
                    (double) is_executed_immediately});
}

void Hyrel::disablePriming(int tool_number) {
    configureUnprime(tool_number, 0, 0, 0, false);
    configurePrime(tool_number, 0, 0, 0, false);
}


void Hyrel::extrude(const std::valarray<double> &xy) {
    std::valarray<double> new_positions = {xy[0], xy[1], positions[2]};
    double extrusion_length = norm(new_positions - positions);
    extrusion_value += extrusion_length;
    print_time += extrusion_length / print_speed;
    positions = new_positions;
    generalCommand({'G', 'X', 'Y', 'F', 'E'}, {true, false, false, true, true},
                   {1, xy[0], xy[1], (double) print_speed, 1});
}

void Hyrel::configureFlow(double nozzle_width, double layer_height, double flow_multiplier, int pulses, int tool) {
    addComment("Configuring flow");
    generalCommand({'M', 'T', 'W', 'Z', 'S', 'P'}, {true, true, false, false, false, true},
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

void Hyrel::clean(double clean_length, int number_of_lines, double nozzle_width, int height_offset_register,
                  double layer_height) {
    addComment("Invoking offsets");
    generalCommand({'M', 'H', 'Z'},
                   {true, true, false},
                   {660, (double) height_offset_register, layer_height});
    generalCommand({'G', 'X', 'Y'},
                   {true, false, false},
                   {0, 0, 0});
    generalCommand({'G', 'Z', 'H'},
                   {true, false, true},
                   {0, 0, (double) height_offset_register});

    addBreak();
    addComment("Starting cleaning");
    if (clean_length > 0) {
        for (int i = 0; i < number_of_lines; i++) {
            if (i % 2 == 0) {
                movePlanar({0, i * nozzle_width});
                extrude({clean_length, i * nozzle_width});

            } else {
                movePlanar({clean_length, i * nozzle_width});
                extrude({0, i * nozzle_width});
            }
        }
    }
}

void
Hyrel::init(int hotend_temperature, int bed_temperature, double clean_length, double nozzle_width,
            double first_layer_height, double layer_height, int tool_number, std::vector<double> &tool_offset,
            int cleaning_lines) {
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

    autoHome();
    addBreak();
    defineToolOffset(tool_number, tool_offset, height_offset_register);
    addBreak();

    setTemperatureHotend(hotend_temperature, tool_number);
    setTemperatureBed(bed_temperature);
    addBreak();

    configureFlow(nozzle_width, layer_height, extrusion_coefficient, kra_2_pulses_per_microlitre, tool_number);
    disablePriming(tool_number);

    selectTool(tool_number);
    addBreak();
    clean(clean_length, cleaning_lines, nozzle_width, height_offset_register, first_layer_height);
    addBreak();
    addComment("Starting printing");
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

void Hyrel::configureUvarray(int print_head_tool_number, int duty_cycle) {
    if (duty_cycle >= 0 && duty_cycle <= 100) {
        addComment("Linking pen to activate with the printing moves ");
        generalCommand({'M', 'T', 'S'},
                       {true, true, true},
                       {106, (double) mCommandToolNumber(print_head_tool_number),
                        (double) mCommandToolNumber(duty_cycle)});
    }
}


void Hyrel::shutDown() {
    setTemperatureBed(0);
    GCodeFile::setTemperatureHotend(0);
    addBreak();

    autoHome();
    move(0, 0, 40); // Hyrel 30M has zero height at the print-bed
    addBreak();

    turnMotorsOff();
    signalFinishedPrint();
}

Hyrel::Hyrel(int move_speed, int print_speed, double extrusion_coefficient) : GCodeFile(move_speed, print_speed,
                                                                                        extrusion_coefficient) {

}

void Hyrel::printPath(const std::vector<std::valarray<int>> &path, const std::valarray<double> &position_offset,
                      double grid_distance) {
    addComment("Starting new path.");
    std::valarray<int> previous_connecting_vector = {1, 0};
    std::valarray<int> previous_position = {0, 0};

    for (auto &position: path) {
        std::valarray<int> connecting_vector = position - previous_position;
        previous_position = position;
        double dot_length = dot(previous_connecting_vector, connecting_vector) /
                            (norm(previous_connecting_vector) * norm(connecting_vector));
        if (dot_length < 1 || position[0] == path.back()[0] && position[1] == path.back()[1]) {
            previous_connecting_vector = connecting_vector;
            extrude(itodArray(position) * grid_distance + position_offset);
        }
    }
}

PatternBoundaries Hyrel::printPattern(const std::vector<std::vector<std::valarray<int>>> &sorted_sequence_of_paths,
                                      const std::valarray<double> &position_offset, double grid_spacing,
                                      double lift_off_distance) {
    std::valarray<int> current_coordinates;
    std::valarray<int> previous_coordinates = {(int) (positions[0] / grid_spacing),
                                               (int) (positions[1] / grid_spacing)};

    for (auto &path: sorted_sequence_of_paths) {
        current_coordinates = path.front();
        double current_distance = norm(previous_coordinates - current_coordinates) * grid_spacing;
        if (current_distance > lift_off_distance) {
            addComment("Moving up.");
            moveVerticalRelative(1);
            addComment("Moving to new starting point.");
            movePlanar(itodArray(path[0]) * grid_spacing + position_offset);
            addComment("Moving down.");
            moveVerticalRelative(-1);
        } else {
            addComment("Moving to new starting point.");
            movePlanar(itodArray(path[0]) * grid_spacing + position_offset);
        }
        printPath(path, position_offset, grid_spacing);
        previous_coordinates = path.back();
    }
    addComment("Pattern completed.");
    PatternBoundaries pattern_boundaries(sorted_sequence_of_paths);
    pattern_boundaries.scale(grid_spacing);
    pattern_boundaries.move(position_offset);
//    pattern_boundaries.print();
    return pattern_boundaries;
}


void testHeaderAndFooter() {
    Hyrel hyrel(600, 100, 1);
    std::vector<double> tool_offset = {50, 30, 30};
    hyrel.init(20, 0, 30, 0.335, 0, 0.16, 1, tool_offset, 0);
    hyrel.shutDown();
    std::cout << hyrel.getText();
}


void Hyrel::exportToFile(const boost::filesystem::path &results_path, const std::string &pattern_name,
                         const std::string &suffix, double extruded_amount) {
    boost::filesystem::path filename = results_path / (pattern_name + suffix + ".gcode");
    std::ofstream file(filename.string());

    time_t ttime = time(nullptr);

    char *time = ctime(&ttime);
    file << std::fixed;
    file.precision(2);
    file << "; Generated using GCodeGenerator " << version << " on " << time;
    file << "; Michał Zmyślony, University of Cambridge, mlz22@cam.ac.uk" << std::endl << std::endl;;
    file << "; Estimated print time: " << print_time << " min" << std::endl;
    file << "; Estimated amount of extruded material: " << extruded_amount << " μl";
    file << getText();
    file.close();
}

void Hyrel::addLocalOffset(std::vector<double> offset) {
    generalCommand({'G', 'X', 'Y', 'Z'},
                   {true, false, false, false},
                   {54, offset[0], offset[1], offset[2]});
}

void
hyrelSingleLayer(const boost::filesystem::path &directory, const std::string &pattern_name, double cleaning_distance,
                 int tool_number, int temperature, int move_speed, int print_speed, double nozzle_diameter,
                 double layer_height, double extrusion_multiplier, double grid_spacing,
                 const std::valarray<double> &pattern_offset, std::vector<double> &tool_offset, int uv_pen_tool_number,
                 int curing_duty_cycle) {
    hyrelMultiLayer(directory, pattern_name, cleaning_distance, tool_number, temperature, move_speed, print_speed,
                    nozzle_diameter, layer_height, extrusion_multiplier, grid_spacing, pattern_offset, tool_offset,
                    uv_pen_tool_number, curing_duty_cycle, 1, layer_height);
}

void printMultiLayer(Hyrel &hyrel, const std::valarray<double> &initial_pattern_offset, double grid_spacing,
                     const std::vector<std::vector<std::valarray<int>>> &sorted_paths, int layers,
                     double layer_height) {

    for (int i = 0; i < layers; i++) {
        double current_layer_height = i * layer_height;
        hyrel.moveVertical(current_layer_height);
        hyrel.printPattern(sorted_paths, initial_pattern_offset, grid_spacing, 2);
    }
}


double extrudedAmount(double length, double width, double height, double extrusion_multiplier) {
    return length * width * height * extrusion_multiplier;
}

void
hyrelMultiLayer(const boost::filesystem::path &directory, const std::string &pattern_name, double cleaning_distance,
                int tool_number, int temperature, int move_speed, int print_speed, double nozzle_diameter,
                double layer_height, double extrusion_multiplier, double grid_spacing,
                const std::valarray<double> &pattern_offset, std::vector<double> &tool_offset, int uv_pen_tool_number,
                int curing_duty_cycle, int layers, double first_layer_height) {
    boost::filesystem::path pattern_path = directory / pattern_name;
    int number_of_cleaning_lines = 12;
    if (boost::filesystem::exists(pattern_path)) {
        std::vector<std::vector<std::valarray<int>>> sorted_paths = read3DVectorFromFile(pattern_path.string(),
                                                                                         "best_paths");
        Hyrel hyrel(move_speed, print_speed, extrusion_multiplier);
        hyrel.init(temperature, 0, cleaning_distance, nozzle_diameter, first_layer_height,
                   layer_height, tool_number, tool_offset, number_of_cleaning_lines);
//        hyrel.configureUvPen(tool_number, uv_pen_tool_number, curing_duty_cycle);
        hyrel.configureUvarray(tool_number, curing_duty_cycle);
        hyrel.addBreak();

        std::valarray<double> cleaning_offset = {0, number_of_cleaning_lines * nozzle_diameter};
        printMultiLayer(hyrel, pattern_offset + cleaning_offset, grid_spacing, sorted_paths, layers, layer_height);
        hyrel.shutDown();

        std::ostringstream suffix_stream;
        suffix_stream << std::fixed << std::setprecision(3);
        suffix_stream << "_" << nozzle_diameter << "_um_" << layers << "_layers";

        double extruded_amount = extrudedAmount(hyrel.getExtrusionValue(), nozzle_diameter, layer_height,
                                                extrusion_multiplier);
        hyrel.exportToFile(directory / "gcode", pattern_name, suffix_stream.str(), extruded_amount);
    } else {
        std::cout << "ERROR: Directory \"" << pattern_path << "\" does not exist." << std::endl;
    }
}