//
// Created by Michał Zmyślony on 04/08/2022.
//

#ifndef GCODEGENERATOR_HYREL_H
#define GCODEGENERATOR_HYREL_H

#include "GCodeFile.h"
#include "PatternBoundaries.h"
#include <boost/filesystem.hpp>

class Hyrel : public GCodeFile {
    void defineHeightOffset(unsigned int register_number, double height);

    void defineToolOffset(int tool_number, const std::vector<double> &xyz, unsigned int height_register_offset);

    void extrude(const std::valarray<double> &xy);

    void selectTool(unsigned int tool_number);

    void setUnitsToMillimetres();

    void signalFinishedPrint();

    void clearOffsets();

    void turnMotorsOff();

    void
    clean(double clean_length, int number_of_lines, double nozzle_width, int height_offset_register,
          double layer_height);

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
         int cleaning_lines);

    void shutDown();

    Hyrel(int move_speed, int print_speed, double extrusion_coefficient);

    void
    printPath(const std::vector<std::valarray<int>> &path, const std::valarray<double> &position_offset,
              double grid_distance);

    PatternBoundaries printPattern(const std::vector<std::vector<std::valarray<int>>> &sorted_sequence_of_paths,
                                   const std::valarray<double> &position_offset, double grid_spacing,
                                   double lift_off_distance);

    void exportToFile(const boost::filesystem::path &results_path, const std::string &pattern_name,
                      const std::string &suffix, double extruded_amount);

    void configureUvPen(int print_head_tool_number, int pen_tool_number, int duty_cycle);

    void addLocalOffset(std::vector<double> offset);

    void configureUvarray(int print_head_tool_number, int duty_cycle);
};

void testHeaderAndFooter();

void
hyrelSingleLayer(const boost::filesystem::path &directory, const std::string &pattern_name, double cleaning_distance,
                 int tool_number, int temperature, int move_speed, int print_speed, double nozzle_diameter,
                 double layer_height, double extrusion_multiplier, double grid_spacing,
                 const std::valarray<double> &pattern_offset, std::vector<double> &tool_offset, int uv_pen_tool_number,
                 int curing_duty_cycle);

void
hyrelMultiLayer(const boost::filesystem::path &directory, const std::string &pattern_name, double cleaning_distance,
                int tool_number, int temperature, int move_speed, int print_speed, double nozzle_diameter,
                double layer_height, double extrusion_multiplier, double grid_spacing,
                const std::valarray<double> &pattern_offset, std::vector<double> &tool_offset, int uv_pen_tool_number,
                int curing_duty_cycle, int layers, double first_layer_height);

#endif //GCODEGENERATOR_HYREL_H
