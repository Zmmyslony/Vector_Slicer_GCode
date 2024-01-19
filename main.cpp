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

    // All units are in mm
    ExtrusionConfiguration extrusion_configuration(200, 80, 0.2,
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
    double first_layer_height = extrusion_configuration.getLayerHeight() + 0.025;

    std::vector<double> tool_offset = {101, 86, 0};
    double pattern_offset = 3;

    FullPrintingConfiguration printer(extrusion_configuration, printing_configuration,
                                      export_directory, tool_offset, uv_duty_cycle, first_layer_height);

    std::cout << "\nGenerating GCode for the files contained in" << std::endl << '\t' << paths_directory
              << std::endl;

    printer.printPatternGrid({{paths_directory / "longitudinal_20_10_mm"},
                              {paths_directory / "evertor_10_mm_0"}},
                             {{4, 6}},
                             pattern_offset, false, 0);

    printer.printPatternGrid({{paths_directory / "longitudinal_20_10_mm"},
                              {paths_directory / "iris_5_mm_0", paths_directory / "cylinder_5_mm_0"}},
                             {{4}},
                             pattern_offset, false, 0);

    for (int i = 1; i < 5; i++) {
        printer.printPatternGrid({{paths_directory / "longitudinal_20_10_mm"},
                                  {paths_directory / "radial_10_mm_SHWO", paths_directory / "radial_10_mm_MHMO",
                                          paths_directory / "radial_10_mm_WHSO"}},
                                 {{1, i}},
                                 pattern_offset, false, 0);
    }

    printer.printPatternGrid({{},
                              {paths_directory / "three_charge_blob"}},
                             {{1}},
                             pattern_offset, false, 0);

    double printing_distance = 10;
    int number_of_lines = 15;

//    printer.tuneLineSeparation(printing_distance, number_of_lines,
//                               1, 0.8, 5);

    printer.tuneLineSeparationAndSpeed(printing_distance, number_of_lines,
                                       0.8, 1.2, 3,
                                       200, 300, 5);

//
//    printer.tuneLineSeparationAndHeight(printing_distance, number_of_lines,
//                                        1.2, 0.6, 2,
//                                        0.09, 0.15, 5);
//

    std::cout << "Generation complete." << std::endl;
    return 0;
}
