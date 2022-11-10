/*
 * Copyright (c) 2022, Michał Zmyślony, mlz22@cam.ac.uk. All rights reserved.
 *
 * Please cite Michał Zmyślony and Dr John Biggins if you use any part of this code in work you publish or distribute.
 *
 * This file is a part of gCode Generator.
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
    fs::path patterns_directory = cwd / "patterns";

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

    // All units are in mm
    ExtrusionConfiguration extrusion_configuration(500, 65, 0.20, 0.12, 1, 2);
    PrinterConfiguration printing_configuration(400, 0, 2, 10, 15);

    int uv_duty_cycle = 25;
    double first_layer_height = extrusion_configuration.getLayerHeight() + 0.00;

    double nozzle_diameter_assumed = 0.3; // Nozzle diameter which was assumed for generation of the director pattern
    double grid_spacing_assumed = 0.02; // Spacing which was used for slicing the pattern, can be scaled for different nozzle diameters
    double grid_spacing = grid_spacing_assumed * extrusion_configuration.getDiameter() / nozzle_diameter_assumed;
    std::vector<double> tool_offset = {145, 115, 0};
    std::valarray<double> pattern_offset = {0, 2};

    std::cout << "\nGenerating GCode for the files contained in" << std::endl << '\t' << patterns_directory
              << std::endl;

    for (auto &pattern: patterns_to_generate) {
        singleLayer(patterns_directory, pattern, grid_spacing, pattern_offset,
                    tool_offset, uv_duty_cycle, first_layer_height, extrusion_configuration,
                    printing_configuration);

        multiLayer(patterns_directory, pattern, grid_spacing, pattern_offset,
                   tool_offset, uv_duty_cycle, first_layer_height, 4, extrusion_configuration,
                   printing_configuration);
    }

    double printing_distance = 10;
    int number_of_lines = 9;

    tuneLineSeparation(patterns_directory, printing_distance, number_of_lines, tool_offset, uv_duty_cycle,
                       first_layer_height,
                       extrusion_configuration, printing_configuration,
                       1.8, 0.8, 6);

    tuneLineSeparationAndHeight(patterns_directory, printing_distance, number_of_lines, tool_offset, uv_duty_cycle,
                                first_layer_height,
                                extrusion_configuration, printing_configuration,
                                1.2, 0.6, 2,
                                0.09, 0.15, 5);

    tuneLineSeparationAndSpeed(patterns_directory, printing_distance, number_of_lines, tool_offset, uv_duty_cycle,
                               first_layer_height,
                               extrusion_configuration, printing_configuration,
                               1.4, 0.8, 4,
                               400, 500, 4);

    std::cout << "Generation complete." << std::endl;
    return 0;
}
