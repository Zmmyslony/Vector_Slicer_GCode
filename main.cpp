#include <iostream>
#include "source/engine/Hyrel.h"
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
//    patterns_to_generate = {"radial, r = 1 cm"};
//    patterns_to_generate = {"linear, 2x1 cm"};
    std::cout << "\nGenerating GCode for the files contained in" << std::endl << '\t' << patterns_directory
              << std::endl;
    // All units are in mm
    double cleaning_distance = 20; // Also allows the material to start flowing until we are in the shear thinning regime
    int printing_temperature = 20;
    int move_speed = 1000;
    int print_speed = 100;
    int tool_number = 1;
    int uv_pen_tool_number = 1;
    int uv_duty_cycle = 15;

    double nozzle_diameter = 0.260;
    double layer_height = 0.200;
    double first_layer_height = 0.200;
    double extrusion_multiplier = 1.;

    double nozzle_diameter_assumed = 0.3; // Nozzle diameter which was assumed for generation of the director pattern
    double grid_spacing_assumed = 0.02; // Spacing which was used for slicing the pattern, can be scaled for different nozzle diameters
    double grid_spacing = grid_spacing_assumed * nozzle_diameter / nozzle_diameter_assumed;
    std::vector<double> tool_offset = {15, 15, 0};
    std::valarray<double> pattern_offset = {0, 3};


    for (auto &pattern: patterns_to_generate) {
//        hyrelSingleLayer(patterns_directory, pattern, cleaning_distance, tool_number, printing_temperature, move_speed,
//                           print_speed, nozzle_diameter, layer_height, extrusion_multiplier, grid_spacing, pattern_offset,
//                           tool_offset, uv_pen_tool_number, uv_duty_cycle);
//        for (int layers = 1; layers <= 4; layers++) {
//            hyrelMultiLayer(patterns_directory, pattern, cleaning_distance, tool_number, printing_temperature, move_speed,
//                            print_speed, nozzle_diameter, layer_height, extrusion_multiplier, grid_spacing, pattern_offset,
//                            tool_offset, uv_pen_tool_number, uv_duty_cycle, layers, first_layer_height);
//        }
        hyrelMultiLayer(patterns_directory, pattern, cleaning_distance, tool_number, printing_temperature, move_speed,
                        print_speed, nozzle_diameter, layer_height, extrusion_multiplier, grid_spacing, pattern_offset,
                        tool_offset, uv_pen_tool_number, uv_duty_cycle, 1, first_layer_height);
        hyrelMultiLayer(patterns_directory, pattern, cleaning_distance, tool_number, printing_temperature, move_speed,
                        print_speed, nozzle_diameter, layer_height, extrusion_multiplier, grid_spacing, pattern_offset,
                        tool_offset, uv_pen_tool_number, uv_duty_cycle, 6, first_layer_height);
    }

    std::cout << "Generation complete." << std::endl;
    return 0;
}
