//
// Created by Michał Zmyślony on 04/08/2022.
//

#include <iostream>
#include <fstream>
#include <ctime>

#include "hyrel.h"
#include "valarray_operations.h"
#include "exporting.h"
#include "pattern_boundaries.h"
#include "extrusion_configuration.h"
#include "printer_configuration.h"

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
// TODO Obtain max tool numbers from a new class of Printer -> Hyrel and automate retrieving maximal values
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
    generalCommand({'G', 'X', 'Y', 'F', 'E'},
                   {true, false, false, true, true},
                   {1, xy[0], xy[1], (double) print_speed, 1});
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
                                                const std::valarray<double> &starting_position) {
    movePlanar(starting_position);
    extrude(starting_position + std::valarray<double>{length, 0});
    std::valarray<double> last_coordinate;

    for (int i = 1; i < number_of_lines; i++) {
        if (i % 2 == 0) {
            extrude(starting_position + std::valarray<double>{0, i * line_separation});
            extrude(starting_position + std::valarray<double>{length, i * line_separation});

            last_coordinate = starting_position + std::valarray<double>{0, i * line_separation};

        } else {
            extrude(starting_position + std::valarray<double>{length, i * line_separation});
            extrude(starting_position + std::valarray<double>{0, i * line_separation});

            last_coordinate = starting_position + std::valarray<double>{0, i * line_separation};
        }
    }
    return last_coordinate;
}

void Hyrel::clean(double clean_length, int number_of_lines, double nozzle_width, int height_offset_register,
                  double layer_height) {
    addComment("Invoking offsets");
    movePlanar({0, 0});
    defineHeightOffset(layer_height, height_offset_register);
    invokeHeightOffset(0, height_offset_register);
    addBreak();
    addComment("Starting cleaning");
    if (clean_length > 0) {
        printZigZagPattern(clean_length, number_of_lines, 2 * nozzle_width, {0, 0});
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
    defineToolOffset(tool_number, tool_offset);
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

void
Hyrel::init(const ExtrusionConfiguration &extrusion_configuration, const PrinterConfiguration &printer_configuration,
            double first_layer_height, int cleaning_lines, double clean_length, std::vector<double> &tool_offset) {
    init(extrusion_configuration.getNozzleTemperature(), printer_configuration.getBedTemperature(), clean_length,
         extrusion_configuration.getDiameter(), first_layer_height, extrusion_configuration.getLayerHeight(),
         printer_configuration.getPrintHeadToolNumber(), tool_offset, cleaning_lines);
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

Hyrel::Hyrel(int move_speed, int print_speed, double extrusion_coefficient, double lift_off_distance)
        : GCodeFile(move_speed, print_speed,
                    extrusion_coefficient, lift_off_distance) {

}

Hyrel::Hyrel(const ExtrusionConfiguration &extrusion_configuration, const PrinterConfiguration &printer_configuration)
        : Hyrel(printer_configuration.getNonPrintingSpeed(), extrusion_configuration.getPrintingSpeed(),
                extrusion_configuration.getExtrusionMultiplier(), extrusion_configuration.getLiftOffDistance()) {

}

bool isInDifferentDirection(const std::valarray<int> &last_position,
                            const std::valarray<int> &position,
                            const std::valarray<int> &previous_position,
                            const std::valarray<int> &previous_connecting_vector) {
    std::valarray<int> connecting_vector = position - previous_position;
    double dot_length = dot(previous_connecting_vector, connecting_vector) /
                        (norm(previous_connecting_vector) * norm(connecting_vector));
    return dot_length < 1 || isEqual(position == last_position);
}

void Hyrel::printPath(const std::vector<std::valarray<int>> &path, const std::valarray<double> &position_offset,
                      double grid_distance) {
    addComment("Starting new path.");
    std::valarray<int> previous_connecting_vector = {1, 0};
    std::valarray<int> previous_position = {0, 0};

    for (auto &position: path) {
        // Check if the printing direction differs, and if it doesn't merge the points into a single line to make gcode
        // clearer. Additionally, if it is a last point print it even if it is in the same direction.
        if (isInDifferentDirection(path.back(), position, previous_position, previous_connecting_vector)) {
            previous_connecting_vector = position - previous_position;
            extrude(itodArray(position) * grid_distance + position_offset);
        }
        previous_position = position;
    }
}

PatternBoundaries Hyrel::printPattern(const std::vector<std::vector<std::valarray<int>>> &sorted_sequence_of_paths,
                                      const std::valarray<double> &position_offset, double grid_spacing,
                                      double lift_off_distance) {

    for (auto &path: sorted_sequence_of_paths) {
        addComment("Moving to new starting point.");
        movePlanar(itodArray(path[0]) * grid_spacing + position_offset);

        printPath(path, position_offset, grid_spacing);

    }
    addComment("Pattern completed.");
    PatternBoundaries pattern_boundaries(sorted_sequence_of_paths);
    pattern_boundaries.scale(grid_spacing);
    pattern_boundaries.move(position_offset);
//    pattern_boundaries.print();
    return pattern_boundaries;
}


void Hyrel::exportToFile(const boost::filesystem::path &results_path, const std::string &pattern_name,
                         const std::string &suffix, double extruded_amount) {
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

    char *time = ctime(&ttime);
    file << std::fixed;
    file.precision(2);
    file << "; Generated using GCodeGenerator " << version << " on " << time;
    file << "; Michal Zmyslony, University of Cambridge, mlz22@cam.ac.uk" << std::endl << std::endl;;
    file << "; Estimated print time: " << print_time << " min" << std::endl;
    file << "; Estimated amount of extruded material: " << extruded_amount << " ul";
    file << getText();
    file.close();
}

void Hyrel::addLocalOffset(std::vector<double> offset) {
    generalCommand({'G', 'X', 'Y', 'Z'},
                   {true, false, false, false},
                   {54, offset[0], offset[1], offset[2]});
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
singleLayer(const boost::filesystem::path &directory, const std::string &pattern_name, double grid_spacing,
            const std::valarray<double> &pattern_offset, double cleaning_distance,
            std::vector<double> &tool_offset, int curing_duty_cycle, double first_layer_height,
            ExtrusionConfiguration extrusion_configuration, PrinterConfiguration printer_configuration) {
    multiLayer(directory, pattern_name, grid_spacing, pattern_offset, cleaning_distance, tool_offset, curing_duty_cycle,
               first_layer_height, 1, extrusion_configuration, printer_configuration);
}

void
multiLayer(const boost::filesystem::path &directory, const std::string &pattern_name, double grid_spacing,
           const std::valarray<double> &pattern_offset, double cleaning_distance,
           std::vector<double> &tool_offset, int curing_duty_cycle, double first_layer_height, int layers,
           ExtrusionConfiguration extrusion_configuration, PrinterConfiguration printer_configuration) {
    boost::filesystem::path pattern_path = directory / pattern_name;
    int number_of_cleaning_lines = 20;
    if (boost::filesystem::exists(pattern_path)) {
        std::vector<std::vector<std::valarray<int>>> sorted_paths = read3DVectorFromFile(pattern_path.string(),
                                                                                         "best_paths");
        Hyrel hyrel(extrusion_configuration, printer_configuration);
        hyrel.init(extrusion_configuration, printer_configuration, first_layer_height, number_of_cleaning_lines,
                   cleaning_distance, tool_offset);

        hyrel.configureUvArray(printer_configuration.getPrintHeadToolNumber(), curing_duty_cycle);
        hyrel.addBreak();

        std::valarray<double> cleaning_offset = {0,
                                                 2 * number_of_cleaning_lines * extrusion_configuration.getDiameter()};
        printMultiLayer(hyrel, pattern_offset + cleaning_offset, grid_spacing, sorted_paths, layers,
                        extrusion_configuration.getLayerHeight());
        hyrel.shutDown();

        std::ostringstream suffix_stream;
        suffix_stream << std::fixed << std::setprecision(3);
        suffix_stream << "_" << extrusion_configuration.getDiameter() << "_um_" << layers << "_layers";

        double extruded_amount = extrudedAmount(hyrel.getExtrusionValue(), extrusion_configuration.getDiameter(),
                                                extrusion_configuration.getLayerHeight(),
                                                extrusion_configuration.getExtrusionMultiplier());
        hyrel.exportToFile(directory / "gcode", pattern_name, suffix_stream.str(), extruded_amount);
    } else {
        std::cout << "ERROR: Directory \"" << pattern_path << "\" does not exist." << std::endl;
    }
}


void
tuneLineSeparation(const boost::filesystem::path &directory, double printing_distance, int number_of_lines,
                   std::vector<double> &tool_offset, int curing_duty_cycle, double first_layer_height,
                   ExtrusionConfiguration extrusion_configuration, PrinterConfiguration printer_configuration,
                   double max_line_separation, double min_line_separation, double line_separation_step) {
    int number_of_cleaning_lines = 16;
    Hyrel hyrel(extrusion_configuration, printer_configuration);
    hyrel.init(extrusion_configuration, printer_configuration, first_layer_height, number_of_cleaning_lines,
               printing_distance, tool_offset);

    hyrel.configureUvArray(printer_configuration.getPrintHeadToolNumber(), curing_duty_cycle);
    hyrel.addBreak();

    std::valarray<double> current_offset = {0, 2 * number_of_cleaning_lines * extrusion_configuration.getDiameter()};

    for (double relative_line_spacing = max_line_separation;
         relative_line_spacing >= min_line_separation; relative_line_spacing -= line_separation_step) {
        current_offset = hyrel.printZigZagPattern(printing_distance, number_of_lines,
                                                  relative_line_spacing * extrusion_configuration.getDiameter(),
                                                  current_offset + std::valarray<double>{0, 1});
    }
    hyrel.shutDown();

    std::ostringstream suffix_stream;
    suffix_stream << std::fixed << std::setprecision(3);
    suffix_stream << "_" << extrusion_configuration.getDiameter() << "_um";

    double extruded_amount = extrudedAmount(hyrel.getExtrusionValue(), extrusion_configuration.getDiameter(),
                                            extrusion_configuration.getLayerHeight(),
                                            extrusion_configuration.getExtrusionMultiplier());
    hyrel.exportToFile(directory / "gcode", "line_spacing", suffix_stream.str(), extruded_amount);
}

void
tuneLineSeparationAndHeight(const boost::filesystem::path &directory, double printing_distance, int number_of_lines,
                            std::vector<double> &tool_offset, int curing_duty_cycle, double first_layer_height,
                            ExtrusionConfiguration extrusion_configuration, PrinterConfiguration printer_configuration,
                            double max_line_separation, double min_line_separation, double line_separation_step,
                            double max_height, double min_height, double height_step) {
    int number_of_cleaning_lines = 16;
    Hyrel hyrel(extrusion_configuration, printer_configuration);
    hyrel.init(extrusion_configuration, printer_configuration, first_layer_height, number_of_cleaning_lines,
               printing_distance, tool_offset);

    hyrel.configureUvArray(printer_configuration.getPrintHeadToolNumber(), curing_duty_cycle);
    hyrel.addBreak();

    std::valarray<double> base_offset = {0, 2 * number_of_cleaning_lines * extrusion_configuration.getDiameter()};
    std::valarray<double> current_offset;

    for (double height = min_height; height <= max_height; height += height_step) {
        hyrel.moveVertical(height - first_layer_height);
        current_offset = base_offset;
        base_offset += {printing_distance + 1, 0};
        for (double relative_line_spacing = max_line_separation;
             relative_line_spacing >= min_line_separation; relative_line_spacing -= line_separation_step) {
            current_offset = hyrel.printZigZagPattern(printing_distance, number_of_lines,
                                                      relative_line_spacing * extrusion_configuration.getDiameter(),
                                                      current_offset + std::valarray<double>{0, 1});
        }
    }

    hyrel.shutDown();

    std::ostringstream suffix_stream;
    suffix_stream << std::fixed << std::setprecision(3);
    suffix_stream << "_" << extrusion_configuration.getDiameter() << "_um";

    double extruded_amount = extrudedAmount(hyrel.getExtrusionValue(), extrusion_configuration.getDiameter(),
                                            extrusion_configuration.getLayerHeight(),
                                            extrusion_configuration.getExtrusionMultiplier());
    hyrel.exportToFile(directory / "gcode", "height_and_line_spacing", suffix_stream.str(), extruded_amount);
}

void
tuneLineSeparationAndSpeed(const boost::filesystem::path &directory, double printing_distance, int number_of_lines,
                           std::vector<double> &tool_offset, int curing_duty_cycle, double first_layer_height,
                           ExtrusionConfiguration extrusion_configuration,
                           PrinterConfiguration printer_configuration, double max_line_separation,
                           double min_line_separation, double line_separation_step, int max_speed, int min_speed,
                           int speed_step) {
    int number_of_cleaning_lines = 16;
    Hyrel hyrel(extrusion_configuration, printer_configuration);
    hyrel.init(extrusion_configuration, printer_configuration, first_layer_height, number_of_cleaning_lines,
               printing_distance, tool_offset);

    hyrel.configureUvArray(printer_configuration.getPrintHeadToolNumber(), curing_duty_cycle);
    hyrel.addBreak();

    std::valarray<double> base_offset = {0, 2 * number_of_cleaning_lines * extrusion_configuration.getDiameter()};
    std::valarray<double> current_offset;

    for (int speed = max_speed; speed >= min_speed; speed -= speed_step) {
        hyrel.setPrintSpeed(speed);
        current_offset = base_offset;
        base_offset += {printing_distance + 1, 0};
        for (double relative_line_spacing = max_line_separation;
             relative_line_spacing >= min_line_separation; relative_line_spacing -= line_separation_step) {
            current_offset = hyrel.printZigZagPattern(printing_distance, number_of_lines,
                                                      relative_line_spacing * extrusion_configuration.getDiameter(),
                                                      current_offset + std::valarray<double>{0, 1});
        }
    }

    hyrel.shutDown();

    std::ostringstream suffix_stream;
    suffix_stream << std::fixed << std::setprecision(3);
    suffix_stream << "_" << extrusion_configuration.getDiameter() << "_um";

    double extruded_amount = extrudedAmount(hyrel.getExtrusionValue(), extrusion_configuration.getDiameter(),
                                            extrusion_configuration.getLayerHeight(),
                                            extrusion_configuration.getExtrusionMultiplier());
    hyrel.exportToFile(directory / "gcode", "speed_and_line_spacing", suffix_stream.str(), extruded_amount);
}
