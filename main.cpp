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

#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/dll.hpp>
#include <filesystem>

#include "source/engine/hyrel.h"
#include "source/engine/extrusion_configuration.h"
#include "source/engine/printer_configuration.h"
#include "source/engine/full_printing_configuration.h"

namespace fs = boost::filesystem;

int main() {
    fs::path cwd = boost::dll::program_location().parent_path().parent_path();
    fs::path paths_directory = cwd / "paths";
    fs::path export_directory = cwd / "gcode";

    std::vector<std::string> patterns_to_generate;
//    patterns_to_generate = {"fan_asymmetric_negative_3x2_cm", "fan_symmetric_negative_3x2_cm",
//                            "fan_asymmetric_positive_3x2_cm", "fan_symmetric_positive_3x2_cm"};

//    patterns_to_generate = {"fan_asymmetric_negative_15x1_cm", "fan_symmetric_negative_15x1_cm",
//                            "fan_asymmetric_positive_15x1_cm", "fan_symmetric_positive_15x1_cm"};

//    patterns_to_generate = {"iris_r_inner_5_mm", "cylinder_r_inner_5_mm", "evertor_r_inner_5_mm", "radial_2_cm"};
    patterns_to_generate = {"evertor_r_inner_10_mm_40", "evertor_r_inner_10_mm_45", "evertor_r_inner_10_mm_50"};
    patterns_to_generate = {"fan_gripper_12x48mm_TN_first", "fan_gripper_12x48mm_TN_second"};

    // All units are in mm
    ExtrusionConfiguration extrusion_configuration(260, 80, 0.2,
                                                   0.1, 1.0, 20);

    PrinterConfiguration printing_configuration(3000, 0, 1,
                                                13, 15,
                                                40000, 10000, 20000);
    // For priming 1297 pulses is a single microlitre, tune this value in order to obtain desirable flow.
    // Single microlitre is 14 mm of "filament" for a nozzle diameter of 300 um.
    // 100 pulses = 1 mm of filament
    // 320k pulses is a single lead screw revolution
    // 10k priming rate corresponds to around 6000 printing speed

    int uv_duty_cycle = 50;
    double first_layer_height = extrusion_configuration.getLayerHeight() + 0.02;

    std::vector<double> tool_offset = {128, 87, 0};
    std::valarray<double> pattern_offset = {0, 2};

    FullPrintingConfiguration printer(extrusion_configuration, printing_configuration,
                                      export_directory, tool_offset, uv_duty_cycle, first_layer_height);

    std::cout << "\nGenerating GCode for the files contained in" << std::endl << '\t' << paths_directory
              << std::endl;

    for (auto &pattern: patterns_to_generate) {
        try {
            printer.singleLayer(paths_directory / pattern, pattern_offset, false, 0);
            printer.multiLayer(paths_directory / pattern, pattern_offset, 2, false, 0);

            double x_clean_offset = (double) printing_configuration.getCleanDistance() + 3;
            double y_clean_offset =
                    -(double) printing_configuration.getCleaningLines() * extrusion_configuration.getDiameter() * 2;

            printer.multiPatternMultiLayer({paths_directory / "linear_2x1_cm", paths_directory / pattern},
                                           {{x_clean_offset, y_clean_offset}, pattern_offset},
                                           {4, 4}, false, 0);
        }
        catch (...) {}

    }

    double printing_distance = 10;
    int number_of_lines = 9;

//    printer.tuneLineSeparation(printing_distance, number_of_lines,
//                               1, 0.8, 5);
//
//    printer.tuneLineSeparationAndHeight(printing_distance, number_of_lines,
//                                        1.2, 0.6, 2,
//                                        0.09, 0.15, 5);
//
//    printer.tuneLineSeparationAndSpeed(printing_distance, number_of_lines,
//                                       1.4, 1, 3,
//                                       400, 2000, 5);

    std::cout << "Generation complete." << std::endl;
    return 0;
}
