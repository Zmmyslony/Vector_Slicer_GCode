#include <iostream>
#include "source/engine/Hyrel.h"
#include "source/engine/extrusion_configuration.h"
#include "source/engine/printer_configuration.h"
#include <boost/filesystem.hpp>
#include <boost/dll.hpp>

namespace fs = boost::filesystem;


int main() {
    fs::path cwd = boost::dll::program_location().parent_path().parent_path();
    fs::path patterns_directory = cwd / "patterns";

    std::vector<std::string> patterns_to_generate = {"radial, r = 1 cm", "radial, r = 0.5 cm", "diagonal, 1x0.5 cm",
                                                     "diagonal, 2x1 cm", "linear, 2x1 cm",
                                                     "symmetricPositive, 2x0.6 cm",
                                                     "symmetric gauss curved rectangle", "linear, 1x0.5 cm",
                                                     "azimuthal, r = 1 cm"};
    patterns_to_generate = {"azimuthal, r = 1 cm"};
//    patterns_to_generate = {"linear, 2x1 cm"};
    std::cout << "\nGenerating GCode for the files contained in" << std::endl << '\t' << patterns_directory
              << std::endl;
    // All units are in mm
    double cleaning_distance = 20; // Also allows the material to start flowing until we are in the shear thinning regime

    ExtrusionConfiguration extrusion_configuration(50, 20, 0.2, 0.08, 1);
    PrinterConfiguration printing_configuration(1000, 0, 2);

    int uv_duty_cycle = 30;
    double first_layer_height = extrusion_configuration.getLayerHeight();

    double nozzle_diameter_assumed = 0.3; // Nozzle diameter which was assumed for generation of the director pattern
    double grid_spacing_assumed = 0.02; // Spacing which was used for slicing the pattern, can be scaled for different nozzle diameters
    double grid_spacing = grid_spacing_assumed * extrusion_configuration.getDiameter() / nozzle_diameter_assumed;
    std::vector<double> tool_offset = {50, 150, 0};
    std::valarray<double> pattern_offset = {0, 2};


    for (auto &pattern: patterns_to_generate) {
        multiLayer(patterns_directory, pattern, grid_spacing, pattern_offset, cleaning_distance,
                   tool_offset, uv_duty_cycle, first_layer_height, 1, extrusion_configuration,
                   printing_configuration);
        multiLayer(patterns_directory, pattern, grid_spacing, pattern_offset, cleaning_distance,
                   tool_offset, uv_duty_cycle, first_layer_height, 4, extrusion_configuration,
                   printing_configuration);
        tuneLineSeparation(patterns_directory, 10, tool_offset, uv_duty_cycle, first_layer_height,
                           extrusion_configuration, printing_configuration, 2, 0.75, 0.25);
    }

    std::cout << "Generation complete." << std::endl;
    return 0;
}
