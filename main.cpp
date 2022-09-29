#include <iostream>
#include "source/engine/Hyrel.h"
#include <boost/filesystem.hpp>
#include <boost/dll.hpp>

namespace fs = boost::filesystem;


int main() {
    fs::path cwd = boost::dll::program_location().parent_path().parent_path();
    fs::path patternsDirectory = cwd / "patterns";

    std::vector<std::string> patternsToGenerate = {"radial, r = 1 cm", "radial, r = 0.5 cm", "diagonal, 1x0.5 cm",
                                                   "diagonal, 2x1 cm", "linear, 2x1 cm", "symmetricPositive, 2x0.6 cm",
                                                   "symmetric gauss curved rectangle", "linear, 1x0.5 cm",
                                                   "azimuthal, r = 1 cm"};
//    patternsToGenerate = {"radial, r = 1 cm"};
//    patternsToGenerate = {"linear, 2x1 cm"};
    std::cout << "\nGenerating GCode for the files contained in" << std::endl << '\t' << patternsDirectory << std::endl;
    // All units are in mm
    double cleaningDistance = 20; // Also allows the material to start flowing until we are in the shear thinning regime
    int printingTemperature = 20;
    int moveSpeed = 1000;
    int printSpeed = 100;
    int toolNumber = 1;
    int uvPenToolNumber = 3;
    int uvDutyCycle = 15;

    double nozzleDiameter = 0.223;
    double layerHeight = 0.200;
    double firstLayerHeight = 0.200;
    double extrusionMultiplier = 1.;

    double nozzleDiameterAssumed = 0.3; // Nozzle diameter which was assumed for generation of the director pattern
    double gridSpacingAssumed = 0.02; // Spacing which was used for slicing the pattern, can be scaled for different nozzle diameters
    double gridSpacing = gridSpacingAssumed * nozzleDiameter / nozzleDiameterAssumed;
    std::vector<double> toolOffset = {93, 3, 52.85};
    std::valarray<double> patternOffset = {0, 3};


    for (auto &pattern: patternsToGenerate) {
//        hyrelSingleLayer(patternsDirectory, pattern, cleaningDistance, toolNumber, printingTemperature, moveSpeed,
//                           printSpeed, nozzleDiameter, layerHeight, extrusionMultiplier, gridSpacing, patternOffset,
//                           toolOffset, uvPenToolNumber, uvDutyCycle);
        for (int layers = 1; layers <= 4; layers++) {
            hyrelMultiLayer(patternsDirectory, pattern, cleaningDistance, toolNumber, printingTemperature, moveSpeed,
                            printSpeed, nozzleDiameter, layerHeight, extrusionMultiplier, gridSpacing, patternOffset,
                            toolOffset, uvPenToolNumber, uvDutyCycle, layers, firstLayerHeight);
        }
    }

    std::cout << "Generation complete." << std::endl;
    return 0;
}
