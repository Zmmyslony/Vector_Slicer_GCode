#include <iostream>
#include "source/engine/Hyrel.h"
#include <boost/filesystem.hpp>
#include <boost/dll.hpp>

namespace fs = boost::filesystem;


int main() {
    fs::path cwd = boost::dll::program_location().parent_path().parent_path();
    fs::path patternsDirectory = cwd / "patterns";

    std::vector<std::string> patternsToGenerate = {"radial, r = 1 cm", "radial, r = 0.5 cm", "diagonal, 1x0.5 cm",
                                                   "diagonal, 2x1 cm", "linear, 2x1 cm", "symmetricPositive, 2x0.6 cm"};

//    std::vector<std::string> patternsToGenerate = {"diagonal, 2x1 cm"};
    std::cout << "\nGenerating GCode for the files contained in" << std::endl << '\t' << patternsDirectory << std::endl;
    // All units are in mm
    double cleaningDistance = 20; // Also allows the material to start flowing until we are in the shear thinning regime
    int printingTemperature = 20;
    int moveSpeed = 1200;
    int printSpeed = 300;
    int toolNumber = 1;
    int uvPenToolNumber = 3;
    int uvDutyCycle = 10;

    double nozzleDiameter = 0.300;
    double layerHeight = 0.15;
    double extrusionMultiplier = 1.;

    double nozzleDiameterAssumed = 0.3; // Nozzle diameter which was assumed for generation of the director pattern
    double gridSpacingAssumed = 0.02; // Spacing which was used for slicing the pattern, can be scaled for different nozzle diameters
    double gridSpacing = gridSpacingAssumed * nozzleDiameter / nozzleDiameterAssumed;
    std::vector<double> toolOffset = {115, 0, 56};
    std::valarray<double> patternOffset = {0, 5};


    for (auto &pattern: patternsToGenerate) {
        generateGCodeHyrel(patternsDirectory, pattern, cleaningDistance, toolNumber, printingTemperature, moveSpeed,
                           printSpeed, nozzleDiameter, layerHeight, extrusionMultiplier, gridSpacing, patternOffset,
                           toolOffset, uvPenToolNumber, uvDutyCycle);
        hyrelOptimisation(patternsDirectory, pattern, cleaningDistance, toolNumber, printingTemperature, moveSpeed,
                           printSpeed, nozzleDiameter, layerHeight, extrusionMultiplier, gridSpacing, patternOffset,
                           toolOffset, uvPenToolNumber, uvDutyCycle);
    }

    std::cout << "Generation complete." << std::endl;
    return 0;
}
