#include <iostream>
#include "source/engine/Hyrel.h"


std::string getSourceDirectory() {
    std::string file_path = __FILE__;
    std::string dir_path = file_path.substr(0, file_path.rfind("\\"));
    return dir_path;
}

int main() {
    std::string sourceDirectory = getSourceDirectory();
    std::string printDirectory = sourceDirectory + R"(\patterns\radial, r = 1 cm)";
    std::cout << "\nGenerating GCode for the files contained in" << std::endl << '\t' << printDirectory << std::endl;
    // All units are in mm
    double cleaningDistance = 20; // Also allows the material to start flowing so that we are in the shear thinning regime
    int toolNumber = 1;
    int printingTemperature = 20;
    int moveSpeed = 600;
    int printSpeed = 200;
    double nozzleDiameter = 0.335;
    double nozzleDiameterAssumed = 0.3; // Nozzle diameter which was assumed for generation of the director pattern
    double layerHeight = 0.16;

    double extrusionMultiplier = 1;
    double gridSpacingAssumed = 0.02; // Spacing which was used for slicing the pattern, can be scaled for different nozzle diameters
    double gridSpacing = gridSpacingAssumed * nozzleDiameter / nozzleDiameterAssumed;
    std::vector<double> toolOffset = {30, 120, 40};
    std::valarray<double> patternOffset = {0, 5};


    generateGCodeHyrel(printDirectory, cleaningDistance, toolNumber, printingTemperature, moveSpeed, printSpeed,
                       nozzleDiameter, layerHeight, extrusionMultiplier, gridSpacing, patternOffset, toolOffset);
    std::cout << "Generation complete." << std::endl;
    return 0;
}
