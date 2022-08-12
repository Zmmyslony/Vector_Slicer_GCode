#include <iostream>
#include "source/engine/Hyrel.h"
#include <boost/filesystem.hpp>
#include <boost/dll.hpp>

namespace fs = boost::filesystem;


std::string getSourceDirectory() {
    std::string file_path = __FILE__;
    std::string dir_path = file_path.substr(0, file_path.rfind("\\"));
    return dir_path;
}

int main() {
    fs::path cwd = boost::dll::program_location().parent_path().parent_path();
    fs::path patternsDirectory = cwd / "patterns";

    std::vector<std::string> patternsToGenerate = {"radial, r = 1 cm", "radial, r = 0.5 cm", "diagonal, 1x0.5 cm"};
    std::cout << "\nGenerating GCode for the files contained in" << std::endl << '\t' << patternsDirectory << std::endl;
    // All units are in mm
    double cleaningDistance = 20; // Also allows the material to start flowing until we are in the shear thinning regime
    int toolNumber = 1;
    int printingTemperature = 20;
    int moveSpeed = 1800;
    int printSpeed = 600;
    double nozzleDiameter = 0.490;
    double nozzleDiameterAssumed = 0.3; // Nozzle diameter which was assumed for generation of the director pattern
    double layerHeight = 0.2;

    double extrusionMultiplier = 1;
    double gridSpacingAssumed = 0.02; // Spacing which was used for slicing the pattern, can be scaled for different nozzle diameters
    double gridSpacing = gridSpacingAssumed * nozzleDiameter / nozzleDiameterAssumed;
    std::vector<double> toolOffset = {120, 30, 56};
    std::valarray<double> patternOffset = {0, 5};


    for (auto &pattern : patternsToGenerate) {
        generateGCodeHyrel(patternsDirectory, pattern, cleaningDistance, toolNumber, printingTemperature, moveSpeed,
                           printSpeed, nozzleDiameter, layerHeight, extrusionMultiplier, gridSpacing, patternOffset, toolOffset);
    }

    std::cout << "Generation complete." << std::endl;
    return 0;
}
