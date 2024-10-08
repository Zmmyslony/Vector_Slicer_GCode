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
// Created by Michał Zmyślony on 04/01/2022.
//

#include <fstream>
#include <iostream>

#include "gcode_file.h"
#include "valarray_operations.h"
#include "importing.h"

const double vertical_move_slowdown = 4;
const std::valarray<double> zero_position = {1, 1};

void GCodeFile::generalCommand(int number, const std::string &suffix) {
    std::stringstream command_number;
    command_number << std::setw(2) << std::setfill('0') << number;
    body_stream << "G" << command_number.str() << " " << suffix + "\n";
}

void GCodeFile::command(const std::vector<char> &commands, const std::vector<bool> &is_int,
                        const std::vector<double> &values) {
    if (commands.size() == values.size() && commands.size() == is_int.size()) {
        for (int i = 0; i < commands.size(); i++) {
            if (is_int[i]) {
                body_stream << commands[i] << std::defaultfloat << int(values[i]) << " ";
            } else {
                body_stream << commands[i] << std::fixed << values[i] << " ";
            }
        }
        body_stream << "\n";
    } else {
        comment("\t\tSYNTAX ERROR");
    }
}

void GCodeFile::generalCommand(const std::vector<char> &commands, const std::vector<bool> &is_int,
                               const std::vector<double> &values, const std::string &comment) {
    if (commands.size() == values.size() && commands.size() == is_int.size()) {
        for (int i = 0; i < commands.size(); i++) {
            if (is_int[i]) {
                body_stream << commands[i] << int(values[i]) << " ";
            } else {
                body_stream << commands[i] << values[i] << " ";
            }
        }
        body_stream << "\t;" << comment << "\n";
    }
}

void GCodeFile::command(const char &command_letter, double value) {
    command({command_letter},
            {false},
            {value});
}

void GCodeFile::command(const char &command_letter, int value) {
    command({command_letter},
            {true},
            {(double) value});
}

void GCodeFile::setRelativePositioning() {
    command('G', 91);
}

void GCodeFile::setAbsolutePositioning() {
    command('G', 90);
}

void GCodeFile::autoHome() {
    comment("Auto homing");
    setRelativePositioning();
    moveVertical(10);
    setAbsolutePositioning();
    command({'G', 'X', 'Y', 'Z'},
            {true, false, false, false},
            {28, 0, 0, 0});
    positions = {0, 0, 0};
}

void GCodeFile::autoHome2D() {
    comment("Auto homing");
    setRelativePositioning();
    moveVertical(10);
    setAbsolutePositioning();
    command({'G', 'X', 'Y'},
            {true, false, false},
            {28, 0, 0});
    positions = {0, 0, positions[2]};
}

void GCodeFile::levelBed() {
    comment("Levelling the bed");
    command('G', 29);
}

void GCodeFile::setTemperatureHotend(int temperature) {
    comment("Setting hotend temperature");
    command({'M', 'S'},
            {true, true},
            {109, (double) temperature});
}

void GCodeFile::setTemperatureHotendGradual(int temperature) {
    for (int current_temperature = 20; current_temperature < temperature; current_temperature++) {
        setTemperatureHotend(current_temperature);
    }
}

void GCodeFile::setTemperatureBed(int temperature) {
    comment("Setting bed temperature");
    command({'M', 'S'},
            {true, true},
            {190, (double) temperature});
}

void GCodeFile::turnMotorsOff() {
    comment("Turning motors off");
    command('M', 84);
}

void GCodeFile::movePlanar(const std::valarray<double> &xy) {
    std::valarray<double> new_positions = {xy[0], xy[1], positions[2]};
    double moved_distance = norm(new_positions - positions);
    if (moved_distance > lift_off_distance) {
        moveVerticalRelative(1);
        command({'G', 'X', 'Y', 'F'},
                {true, false, false, true},
                {0, xy[0], xy[1], (double) move_speed});
        moveVerticalRelative(-1);
    } else {
        command({'G', 'X', 'Y', 'F'},
                {true, false, false, true},
                {0, xy[0], xy[1], (double) move_speed});
    }
    print_time += moved_distance / move_speed;
    positions = new_positions;
}

void GCodeFile::moveVertical(double z) {
    command({'G', 'Z', 'F'},
            {true, false, true},
            {0, z, (double) move_speed / vertical_move_slowdown});
    std::valarray<double> new_positions = {positions[0], positions[1], z};
    print_time += norm(new_positions - positions) / (move_speed / vertical_move_slowdown);
    positions = new_positions;
}

void GCodeFile::moveVerticalRelative(double delta_z) {
    moveVertical(positions[2] + delta_z);
}

void GCodeFile::move(double x, double y, double z, double speed) {
    command({'G', 'X', 'Y', 'Z', 'F'},
            {true, false, false, false, true},
            {0, x, y, z, (double) speed});

    std::valarray<double> new_positions = {x, y, z};
    print_time += norm(new_positions - positions) / speed;
    positions = new_positions;
}

void GCodeFile::move(double x, double y, double z) {
    move(x, y, z, move_speed);
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
    comment("Setting current coordinates as new zero");
    command({'G', 'X', 'Y', 'Z'},
            {true, false, false, false},
            {92, 0, 0, 0});
}

void GCodeFile::resetPositionOfFilament() {
    body_stream << "G92 E0" << "\n";
}

void GCodeFile::comment(const std::string &comment) {
    body_stream << "; " << comment << "\n";
}

GCodeFile::GCodeFile(int move_speed, int print_speed, double extrusion_coefficient, double lift_off_distance) :
        move_speed(move_speed),
        print_speed(print_speed),
        extrusion_coefficient(extrusion_coefficient),
        lift_off_distance(lift_off_distance) {
    body_stream.precision(3);
    body_stream << std::fixed;
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

void GCodeFile::printPath(const std::vector<std::valarray<double>> &path, const std::valarray<double> &position_offset,
                          double grid_distance) {

    comment("Moving up.");
    moveVerticalRelative(1);
    comment("Moving to new starting point.");

    movePlanar(path[0] * grid_distance + position_offset);
    comment("Moving down.");
    moveVerticalRelative(-1);
    comment("Starting new path.");
    for (auto &position: path) {
        extrude(position * grid_distance + position_offset);
    }
}

void
GCodeFile::printPattern(const std::vector<std::vector<std::valarray<double>>> &sorted_sequence_of_paths,
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
    std::vector<std::vector<std::vector<std::valarray<double>>>> sorted_paths = readPrintList(directory_path);
    GCodeFile g_code_file;
    g_code_file.init(temperature, 0, cleaning_distance);
    g_code_file.printPattern(sorted_paths[0], position_offset, grid_distance);
    g_code_file.shutDown();

    g_code_file.exportToFile(base_directory);
}
