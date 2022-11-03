//
// Created by Michał Zmyślony on 04/01/2022.
//

#include <fstream>
#include "GCodeFile.h"
#include "ValarrayOperations.h"
#include "Exporting.h"
#include <iostream>

const double vertical_move_slowdown = 1;
const std::valarray<double> zero_position = {1, 1};

void GCodeFile::generalCommand(int number, const std::string &suffix) {
    std::stringstream command_number;
    command_number << std::setw(2) << std::setfill('0') << number;
    body_stream << "G" << command_number.str() << " " << suffix + "\n";
}

void GCodeFile::generalCommand(const std::vector<char> &commands, const std::vector<bool> &is_int,
                               const std::vector<double> &values) {
    if (commands.size() == values.size() && commands.size() == is_int.size()) {
        for (int i = 0; i < commands.size(); i++) {
            if (is_int[i]) {
                body_stream << commands[i] << int(values[i]) << " ";
            } else {
                body_stream << commands[i] << std::fixed << values[i] << " ";
            }
        }
        body_stream << "\n";
    } else {
        addComment("\t\tSYNTAX ERROR");
    }
}

void GCodeFile::generalCommand(const std::vector<char> &commands, const std::vector<bool> &is_int,
                               const std::vector<double> &values, const std::string &comment) {
    if (commands.size() == values.size() && commands.size() == is_int.size()) {
        for (int i = 0; i < commands.size(); i++) {
            if (is_int[i]) {
                body_stream << commands[i] << int(values[i]) << " ";
            } else {
                body_stream << commands[i] << std::fixed << values[i] << " ";
            }
        }
        body_stream << "\t;" << comment << "\n";
    }
}

void GCodeFile::generalCommand(const char &command, double value) {
    generalCommand({command},
                   {false},
                   {value});
}

void GCodeFile::generalCommand(const char &command, int value) {
    generalCommand({command},
                   {true},
                   {(double) value});
}

void GCodeFile::setRelativePositioning() {
//    addComment("Setting relative positioning");
    generalCommand('G', 91);
}

void GCodeFile::setAbsolutePositioning() {
//    addComment("Setting absolute positioning");
    generalCommand('G', 90);
}

void GCodeFile::autoHome() {
    addComment("Auto homing");
    setRelativePositioning();
    moveVertical(10);
    setAbsolutePositioning();
    generalCommand({'G', 'X', 'Y', 'Z'},
                   {true, false, false, false},
                   {28, 0, 0, 0});
    positions = {0, 0, 0};
}

void GCodeFile::levelBed() {
    addComment("Levelling the bed");
    generalCommand('G', 29);
}

void GCodeFile::setTemperatureHotend(int temperature) {
    addComment("Setting hotend temperature");
    generalCommand({'M', 'S'},
                   {true, true},
                   {109, (double) temperature});
}

void GCodeFile::setTemperatureHotendGradual(int temperature) {
    for (int current_temperature = 20; current_temperature < temperature; current_temperature++) {
        setTemperatureHotend(current_temperature);
    }
}

void GCodeFile::setTemperatureBed(int temperature) {
    addComment("Setting bed temperature");
    generalCommand({'M', 'S'},
                   {true, true},
                   {190, (double) temperature});
}

void GCodeFile::turnMotorsOff() {
    addComment("Turning motors off");
    generalCommand('M', 84);
}

void GCodeFile::movePlanar(const std::valarray<double> &xy) {
    std::valarray<double> new_positions = {xy[0], xy[1], positions[2]};
    double moved_distance = norm(new_positions - positions);
    if (moved_distance > lift_off_distance) {
        moveVerticalRelative(1);
        generalCommand({'G', 'X', 'Y', 'F'},
                       {true, false, false, true},
                       {0, xy[0], xy[1], (double) move_speed});
        moveVerticalRelative(-1);
    } else {
        generalCommand({'G', 'X', 'Y', 'F'},
                       {true, false, false, true},
                       {0, xy[0], xy[1], (double) move_speed});
    }
    print_time += moved_distance / move_speed;
    positions = new_positions;
}

void GCodeFile::moveVertical(double z) {
    generalCommand({'G', 'Z', 'F'},
                   {true, false, true},
                   {0, z, (double) move_speed / vertical_move_slowdown});
    std::valarray<double> new_positions = {positions[0], positions[1], z};
    print_time += norm(new_positions - positions) / (move_speed / vertical_move_slowdown);
    positions = new_positions;
}

void GCodeFile::moveVerticalRelative(double delta_z) {
    positions[2] += delta_z;
    print_time += delta_z / (move_speed / vertical_move_slowdown);
    body_stream << "G0 Z" << positions[2] << " F" << move_speed / vertical_move_slowdown << "\n";
}

void GCodeFile::move(double x, double y, double z) {
    generalCommand({'G', 'X', 'Y', 'Z', 'F'},
                   {true, false, false, false, true},
                   {0, x, y, z, (double) move_speed});

    std::valarray<double> new_positions = {x, y, z};
    print_time += norm(new_positions - positions) / move_speed;
    positions = new_positions;
}

void GCodeFile::extrude(const std::valarray<double> &xy) {
    std::valarray<double> new_positions = {xy[0], xy[1], positions[2]};
//    double extrusion = extrusion_coefficient * norm(new_positions - positions);
    double extrusion = norm(new_positions - positions);
    extrusion_value += extrusion;
    print_time += norm(new_positions - positions) / print_speed;
    positions = new_positions;
    body_stream << "G1 X" << xy[0] << " Y" << xy[1] << " F" << print_speed << " E" << extrusion_value << "\n";
}


void GCodeFile::setCurrentCoordinatesToZero() {
    addComment("Setting current coordinates as new zero");
    generalCommand({'G', 'X', 'Y', 'Z'},
                   {true, false, false, false},
                   {92, 0, 0, 0});
}

void GCodeFile::resetPositionOfFilament() {
    body_stream << "G92 E0" << "\n";
}

void GCodeFile::addComment(const std::string &comment) {
    body_stream << "; " << comment << "\n";
}


GCodeFile::GCodeFile(int move_speed, int print_speed, double extrusion_coefficient, double lift_off_distance) :
        move_speed(move_speed),
        print_speed(print_speed),
        extrusion_coefficient(extrusion_coefficient),
        lift_off_distance(lift_off_distance) {
    body_stream.precision(3);
}

GCodeFile::GCodeFile() :
        GCodeFile(600, 100, 1, 2) {
}


void GCodeFile::init(int hotend_temperature, int bed_temperature, double clean_length) {
    autoHome();
    levelBed();

    setAbsolutePositioning();
    resetPositionOfFilament();
    setTemperatureBed(bed_temperature);
    setTemperatureHotendGradual(hotend_temperature);

    move(1, 1, 0);
    extrude(zero_position + std::valarray<double>({clean_length, 0}));
}

void GCodeFile::init(int hotend_temperature) {
    init(hotend_temperature, 0, 20);
}

void GCodeFile::shutDown() {
    setTemperatureBed(0);
    setTemperatureHotend(0);

    moveVertical(10);
    movePlanar(zero_position);
    turnMotorsOff();
}

std::string GCodeFile::getText() {
    return body_stream.str();
}

void GCodeFile::printPath(const std::vector<std::valarray<int>> &path, const std::valarray<double> &position_offset,
                          double grid_distance) {

    addComment("Moving up.");
    moveVerticalRelative(1);
    addComment("Moving to new starting point.");

    movePlanar(itodArray(path[0]) * grid_distance + position_offset);
    addComment("Moving down.");
    moveVerticalRelative(-1);
    addComment("Starting new path.");
    for (auto &position: path) {
        extrude(itodArray(position) * grid_distance + position_offset);
    }
}

void
GCodeFile::printPattern(const std::vector<std::vector<std::valarray<int>>> &sorted_sequence_of_paths,
                        const std::valarray<double> &position_offset,
                        double grid_distance) {
    for (auto &path: sorted_sequence_of_paths) {
        printPath(path, position_offset, grid_distance);
    }
}

void GCodeFile::exportToFile(const std::string &path) {
    std::string filename = path + R"(\results\pattern.gcode)";
    std::ofstream file(filename);

    file << "; Estimated print time: " << print_time << " min" << std::endl;
    file << getText();
    file.close();
}

void GCodeFile::addBreak() {
    body_stream << "\n";
}

void GCodeFile::setPrintSpeed(int print_speed) {
    GCodeFile::print_speed = print_speed;
}

double GCodeFile::getExtrusionValue() const {
    return extrusion_value;
}


void generateGCode(const std::string &base_directory, int temperature, double cleaning_distance,
                   const std::valarray<double> &position_offset, double grid_distance) {
    std::cout << std::endl;
    std::string directory_path = base_directory + R"(\results)";
    std::vector<std::vector<std::valarray<int>>> sorted_paths = read3DVectorFromFile(directory_path, "best_paths");
    GCodeFile g_code_file;
    g_code_file.init(temperature, 0, cleaning_distance);
    g_code_file.printPattern(sorted_paths, position_offset, grid_distance);
    g_code_file.shutDown();

    g_code_file.exportToFile(base_directory);
}
