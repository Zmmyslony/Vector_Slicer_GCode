/*
 * Copyright (c) 2022, Michał Zmyślony, mlz22@cam.ac.uk. All rights reserved.
 *
 * Please cite Michał Zmyślony and Dr John Biggins if you use any part of this code in work you publish or distribute.
 *
 * This file is a part of gCode Generator.
 */

//
// Created by Michał Zmyślony on 04/01/2022.
//

#ifndef GCODEGENERATOR_GCODE_FILE_H
#define GCODEGENERATOR_GCODE_FILE_H

#include <sstream>
#include <iomanip>
#include <string>
#include <valarray>
#include <vector>

class GCodeFile {
    std::ostringstream body_stream;
    const int move_speed;
    int print_speed;
    const double extrusion_coefficient;
    double print_time = 0;
    double lift_off_distance = 0;

    std::valarray<double> positions = {0, 0, 0};
    double extrusion_value = 0;

private:

    void generalCommand(int number, const std::string &suffix);

    void setRelativePositioning();

    void setAbsolutePositioning();

    void autoHome();

    void levelBed();

    void setTemperatureHotend(int temperature);

    void setTemperatureHotendGradual(int temperature);

    void setTemperatureBed(int temperature);

    void turnMotorsOff();

    void resetPositionOfFilament();

    void generalCommand(const std::vector<char> &commands, const std::vector<bool> &is_int,
                        const std::vector<double> &values);

    void generalCommand(const char &command, double value);

    void generalCommand(const char &command, int value);

    void movePlanar(const std::valarray<double> &xy);

    void moveVerticalRelative(double delta_z);

    void move(double x, double y, double z);

    void extrude(const std::valarray<double> &xy);

    void
    generalCommand(const std::vector<char> &commands, const std::vector<bool> &is_int,
                   const std::vector<double> &values,
                   const std::string &comment);

public:
    [[nodiscard]] double getExtrusionValue() const;

    void setPrintSpeed(int print_speed);

    void moveVertical(double z);

    GCodeFile(int move_speed, int print_speed, double extrusion_coefficient, double lift_off_distance);

    explicit GCodeFile();

    void init(int hotend_temperature, int bed_temperature, double clean_length);

    void init(int hotend_temperature);

    void shutDown();

    void printPath(const std::vector<std::valarray<int>> &path, const std::valarray<double> &position_offset,
                   double grid_distance);

    std::string getText();

    void printPattern(const std::vector<std::vector<std::valarray<int>>> &sorted_sequence_of_paths,
                      const std::valarray<double> &position_offset,
                      double grid_distance);

    void exportToFile(const std::string &path);

    void addComment(const std::string &comment);

    void setCurrentCoordinatesToZero();

    void addBreak();

    friend class Hyrel;
};

void generateGCode(const std::string &base_directory, int temperature, double cleaning_distance,
                   const std::valarray<double> &position_offset, double grid_distance);

#endif //GCODEGENERATOR_GCODE_FILE_H
