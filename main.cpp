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

#include "source/engine/hyrel.h"
#include "source/engine/extrusion_configuration.h"
#include "source/engine/printer_configuration.h"

namespace fs = boost::filesystem;

int main() {
    fs::path cwd = boost::dll::program_location().parent_path().parent_path();
    fs::path paths_directory = cwd / "paths";
    fs::path export_directory = cwd / "gcode";

    std::vector<std::string> patterns_to_generate = {"radial, r = 1 cm",
                                                     "radial, r = 0.5 cm",
                                                     "diagonal, 1x0.5 cm",
                                                     "diagonal, 2x1 cm",
                                                     "linear, 2x1 cm",
                                                     "symmetricPositive, 2x0.6 cm",
                                                     "symmetric gauss curved rectangle",
                                                     "linear, 1x0.5 cm",
                                                     "azimuthal, r = 1 cm"};
    patterns_to_generate = {"radial, r = 1 cm", "azimuthal, r = 1 cm"};
    patterns_to_generate = {"linear, 2x1 cm",
                            "symmetricPositive, 2x0.6 cm",
                            "symmetric gauss curved rectangle",};
    patterns_to_generate = {"linear_2x1_cm", "azimuthal_1_cm", "linear_1x05_cm", "symmetric_gauss_curved_4x3_cm"};

    // All units are in mm
    ExtrusionConfiguration extrusion_configuration(150, 80, 0.20, 0.1, 1.0, 2);
    PrinterConfiguration printing_configuration(500, 0, 2,
                                                10, 15,
                                                15000, 2000);
    // For priming 1297 pulses is a single microlitre, tune this value in order to obtain desirable flow.
    // Single microlitre is 14 mm of "filament" for a nozzle diameter of 300 um.
    // 100 pulses = 1 mm of filament
    // 320k pulses is a single lead screw revolution
    // 10k priming rate corresponds to around 6000 printing speed

    int uv_duty_cycle = 100;
    double first_layer_height = extrusion_configuration.getLayerHeight() + 0.025;

    double nozzle_diameter_assumed = 0.3; // Nozzle diameter which was assumed for generation of the director pattern
    double grid_spacing_assumed = 0.02; // Spacing which was used for slicing the pattern, can be scaled for different nozzle diameters
    double grid_spacing = grid_spacing_assumed * extrusion_configuration.getDiameter() / nozzle_diameter_assumed;
    std::vector<double> tool_offset = {150, 90, 0};
    std::valarray<double> pattern_offset = {0, 2};

    std::cout << "\nGenerating GCode for the files contained in" << std::endl << '\t' << paths_directory
              << std::endl;

    for (auto &pattern: patterns_to_generate) {
        singleLayer(export_directory, paths_directory / (pattern + ".csv"), grid_spacing, pattern_offset,
                    tool_offset, uv_duty_cycle, first_layer_height, extrusion_configuration,
                    printing_configuration);

        multiLayer(export_directory, paths_directory / (pattern + ".csv"), grid_spacing, pattern_offset,
                   tool_offset, uv_duty_cycle, first_layer_height, 4, extrusion_configuration,
                   printing_configuration);
    }

    double printing_distance = 10;
    int number_of_lines = 9;

    tuneLineSeparation(export_directory, printing_distance, number_of_lines, tool_offset, uv_duty_cycle,
                       first_layer_height,
                       extrusion_configuration, printing_configuration,
                       1, 0.8, 5);

    tuneLineSeparationAndHeight(export_directory, printing_distance, number_of_lines, tool_offset, uv_duty_cycle,
                                first_layer_height,
                                extrusion_configuration, printing_configuration,
                                1.2, 0.6, 2,
                                0.09, 0.15, 5);

    tuneLineSeparationAndSpeed(export_directory, printing_distance, number_of_lines, tool_offset, uv_duty_cycle,
                               first_layer_height,
                               extrusion_configuration, printing_configuration,
                               1.2, 0.8, 3,
                               200, 300, 3);

    std::cout << "Generation complete." << std::endl;
    return 0;
}
