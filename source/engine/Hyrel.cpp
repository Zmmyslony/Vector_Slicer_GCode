//
// Created by Michał Zmyślony on 04/08/2022.
//

#include <iostream>
#include <fstream>
#include <ctime>

#include "Hyrel.h"
#include "ValarrayOperations.h"
#include "Exporting.h"
#include "PatternBoundaries.h"

int mCommandToolNumber(int toolNumber) {
    return toolNumber + 11;
}

void Hyrel::selectTool(unsigned int toolNumber) {
    const unsigned int numberOfTools = 4;
    if (toolNumber < numberOfTools) {
        addComment("Selecting tool");
        generalCommand('T', (int) toolNumber);
    }
}

void Hyrel::defineHeightOffset(unsigned int registerNumber, double height) {
// TODO Obtain max tool numbers from a new class of Printer -> Hyrel and automate retrieving maximal values
    const double maxHeight = 120;
    if (0 > height || height > maxHeight) {
        std::cout << "Gcode writing -> defineHeightOffset -> tool height: max value "
                  << maxHeight << ", used value " << height << "\n";
    } else {
        bodyStream << "M660 H" << registerNumber << " Z" << height << "\n";
    }
}

void
Hyrel::defineToolOffset(int toolNumber, const std::vector<double> &xyz, unsigned int heightRegisterOffset) {
    const double X_MAX = 200;
    const double Y_MAX = 200;
    const double Z_MAX = 120;
    if (0 > xyz[0] || xyz[0] > X_MAX) {
        std::cout << "Gcode writing -> defineToolOffset -> tool x coordinate: max value "
                  << X_MAX << ", used value " << xyz[0] << "\n";
    } else if (0 > xyz[1] || xyz[1] > Y_MAX) {
        std::cout << "Gcode writing -> defineToolOffset -> tool y coordinate: max value "
                  << Y_MAX << ", used value " << xyz[1] << "\n";
    } else if (0 > xyz[2] || xyz[2] > Z_MAX) {
        std::cout << "Gcode writing -> defineToolOffset -> tool z coordinate: max value "
                  << Z_MAX << ", used value " << xyz[2] << "\n";
    } else {
        addComment("Defining tool offset");
        generalCommand(
                {'M', 'T', 'O', 'X', 'Y', 'Z'},
                {true, true, true, false, false, false},
                {6, (double) mCommandToolNumber(toolNumber), (double) (toolNumber + 1), xyz[0], xyz[1], xyz[2]});
    }
}

void Hyrel::configurePrime(int toolNumber, double pulseRate, double numberOfPulses, double dwellTime,
                           bool isExecutedImmediately) {
    addComment("Configure priming");
    generalCommand({'M', 'T', 'S', 'E', 'P', 'I'},
                   {true, true, false, false, false, true},
                   {722, (double) mCommandToolNumber(toolNumber), pulseRate, numberOfPulses, dwellTime,
                    (double) isExecutedImmediately});
}


void Hyrel::configureUnprime(int toolNumber, double pulseRate, double numberOfPulses, double dwellTime,
                             bool isExecutedImmediately) {
    addComment("Configure priming");
    generalCommand({'M', 'T', 'S', 'E', 'P', 'I'},
                   {true, true, false, false, false, true},
                   {721, (double) mCommandToolNumber(toolNumber), pulseRate, numberOfPulses, dwellTime,
                    (double) isExecutedImmediately});
}

void Hyrel::disablePriming(int toolNumber) {
    configureUnprime(toolNumber, 0, 0, 0, false);
    configurePrime(toolNumber, 0, 0, 0, false);
}


void Hyrel::extrude(const std::valarray<double> &xy) {
    std::valarray<double> newPositions = {xy[0], xy[1], positions[2]};
    printTime += norm(newPositions - positions) / printSpeed;
    positions = newPositions;
    generalCommand({'G', 'X', 'Y', 'F', 'E'}, {true, false, false, true, true},
                   {1, xy[0], xy[1], (double) printSpeed, 1});
}

void Hyrel::configureFlow(double nozzleWidth, double layerHeight, double flowMultiplier, int pulses, int tool) {
    addComment("Configuring flow");
    generalCommand({'M', 'T', 'W', 'Z', 'S', 'P'}, {true, true, false, false, false, true},
                   {221, (double) mCommandToolNumber(tool), nozzleWidth, layerHeight, flowMultiplier, (double) pulses});
}

void Hyrel::setTemperatureHotend(int temperature, int toolNumber) {
    addComment("Setting hotend temperature");
    generalCommand({'M', 'T', 'S'}, {true, true, true},
                   {109, (double) mCommandToolNumber(toolNumber), (double) temperature});
}

void Hyrel::setUnitsToMillimetres() {
    addComment("Setting units to millimetres");
    generalCommand('G', 21);
}

void Hyrel::turnMotorsOff() {
    addComment("Turning motors off");
    generalCommand('M', 18);
}

void Hyrel::signalFinishedPrint() {
    addComment("Signaling finished print");
    generalCommand('M', 30);
}

void Hyrel::clearOffsets() {
    addComment("Clearing offsets");
    generalCommand('G', 53);
}

void Hyrel::clean(double cleanLength, int numberOfLines, double nozzleWidth, int HEIGHT_OFFSET_REGISTER,
                  double layerHeight) {
    addComment("Invoking offsets");
    generalCommand({'M', 'H', 'Z'},
                   {true, true, false},
                   {660, (double) HEIGHT_OFFSET_REGISTER, layerHeight});
    generalCommand({'G', 'X', 'Y'},
                   {true, false, false},
                   {0, 0, 0});
    generalCommand({'G', 'Z', 'H'},
                   {true, false, true},
                   {0, 0, (double) HEIGHT_OFFSET_REGISTER});

    addBreak();
    addComment("Starting cleaning");
    if (cleanLength > 0) {
        for (int i = 0; i < numberOfLines; i++) {
            if (i % 2 == 0) {
                movePlanar({0, i * nozzleWidth});
                extrude({cleanLength, i * nozzleWidth});

            } else {
                movePlanar({cleanLength, i * nozzleWidth});
                extrude({0, i * nozzleWidth});
            }
        }
    }
}

void
Hyrel::init(int hotendTemperature, int bedTemperature, double cleanLength, double nozzleWidth, double firstLayerHeight,
            double layerHeight, int toolNumber, std::vector<double> &toolOffset) {
    const int HEIGHT_OFFSET_REGISTER = 2;
    const int KRA2_PULSES_PER_MICROLITRE = 1297;
    const int CLEANING_LINES = 6;

    addBreak();
    addComment("Tool selected: T" + std::to_string(toolNumber) + " / T" + std::to_string(mCommandToolNumber(toolNumber)));
    addComment("Nozzle diameter: " + std::to_string(nozzleWidth) + " mm");
    addComment("First layer height: " + std::to_string(firstLayerHeight) + " mm");
    addComment("Layer height: " + std::to_string(layerHeight) + " mm");
    addBreak();

    setUnitsToMillimetres();
    clearOffsets();
    addBreak();

    autoHome();
    addBreak();
    defineToolOffset(toolNumber, toolOffset, HEIGHT_OFFSET_REGISTER);
    addBreak();

    setTemperatureHotend(hotendTemperature, toolNumber);
    setTemperatureBed(bedTemperature);
    addBreak();

    configureFlow(nozzleWidth, layerHeight, extrusionCoefficient, KRA2_PULSES_PER_MICROLITRE, toolNumber);
    disablePriming(toolNumber);

    selectTool(toolNumber);
    addBreak();
    clean(cleanLength, CLEANING_LINES, nozzleWidth, HEIGHT_OFFSET_REGISTER, firstLayerHeight);
    addBreak();
    addComment("Starting printing");
}

void Hyrel::configureUVPen(int printHeadToolNumber, int penToolNumber, int dutyCycle) {
    if (dutyCycle >= 0 && dutyCycle <= 100) {
        addComment("Linking pen to activate with the printing moves ");
        generalCommand({'M', 'T', 'S'},
                       {true, true, true},
                       {703, (double) mCommandToolNumber(penToolNumber),
                        (double) mCommandToolNumber(printHeadToolNumber)});
        generalCommand({'M', 'T', 'E'},
                       {true, true, true},
                       {620, (double) mCommandToolNumber(penToolNumber), 1});
        generalCommand({'M', 'T', 'P'},
                       {true, true, true},
                       {621, (double) mCommandToolNumber(penToolNumber), (double) dutyCycle});
    }
}

void Hyrel::shutDown() {
    setTemperatureBed(0);
    GCodeFile::setTemperatureHotend(0);
    addBreak();

    autoHome();
    addBreak();

    turnMotorsOff();
    signalFinishedPrint();
}

Hyrel::Hyrel(int moveSpeed, int printSpeed, double extrusionCoefficient) : GCodeFile(moveSpeed, printSpeed,
                                                                                     extrusionCoefficient) {

}

void Hyrel::printPath(const std::vector<std::valarray<int>> &path, const std::valarray<double> &positionOffset,
                      double gridDistance) {
    addComment("Starting new path.");
    std::valarray<int> previousConnectingVector = {1, 0};
    std::valarray<int> previousPosition = {0, 0};

    for (auto &position: path) {
        std::valarray<int> connectingVector = position - previousPosition;
        previousPosition = position;
        double dotLength = dot(previousConnectingVector, connectingVector) /
                           (norm(previousConnectingVector) * norm(connectingVector));
        if (dotLength < 1 || position[0] == path.back()[0] && position[1] == path.back()[1]) {
            previousConnectingVector = connectingVector;
            extrude(itodArray(position) * gridDistance + positionOffset);
        }
    }
}

PatternBoundaries Hyrel::printPattern(const std::vector<std::vector<std::valarray<int>>> &sortedSequenceOfPaths,
                                      const std::valarray<double> &positionOffset, double gridSpacing,
                                      double liftOffDistance) {
    std::valarray<int> currentCoordinates;
    std::valarray<int> previousCoordinates = {(int) (positions[0] / gridSpacing), (int) (positions[1] / gridSpacing)};

    for (auto &path: sortedSequenceOfPaths) {
        currentCoordinates = path.front();
        double currentDistance = norm(previousCoordinates - currentCoordinates) * gridSpacing;
        if (currentDistance > liftOffDistance) {
            addComment("Moving up.");
            moveVerticalRelative(1);
            addComment("Moving to new starting point.");
            movePlanar(itodArray(path[0]) * gridSpacing + positionOffset);
            addComment("Moving down.");
            moveVerticalRelative(-1);
        } else {
            addComment("Moving to new starting point.");
            movePlanar(itodArray(path[0]) * gridSpacing + positionOffset);
        }
        printPath(path, positionOffset, gridSpacing);
        previousCoordinates = path.back();
    }
    addComment("Pattern completed.");
    PatternBoundaries patternBoundaries(sortedSequenceOfPaths);
    patternBoundaries.scale(gridSpacing);
    patternBoundaries.move(positionOffset);
//    patternBoundaries.print();
    return patternBoundaries;
}


void testHeaderAndFooter() {
    Hyrel hyrel(600, 100, 1);
    std::vector<double> toolOffset = {50, 30, 30};
    hyrel.init(20, 0, 30, 0.335, 0, 0.16, 1, toolOffset);
    hyrel.shutDown();
    std::cout << hyrel.getText();
}


void Hyrel::exportToFile(const boost::filesystem::path &resultsPath, const std::string &patternName,
                         const std::string &suffix) {
    boost::filesystem::path filename = resultsPath / (patternName + suffix + ".gcode");
    std::ofstream file(filename.string());

    time_t ttime = time(0);

    char* time = ctime(&ttime);

    file << "; " << time;
    file << "; Estimated print time: " << printTime << " min" << std::endl;
    file << getText();
    file.close();
}

void Hyrel::addLocalOffset(std::vector<double> offset) {
    generalCommand({'G', 'X', 'Y', 'Z'},
                   {true, false, false, false},
                   {54, offset[0], offset[1], offset[2]});
}

void
hyrelSingleLayer(const boost::filesystem::path &directory, const std::string &patternName, double cleaningDistance,
                 int toolNumber, int temperature, int moveSpeed, int printSpeed, double nozzleDiameter,
                 double layerHeight, double extrusionMultiplier, double gridSpacing,
                 const std::valarray<double> &patternOffset, std::vector<double> &toolOffset, int uvPenToolNumber,
                 int curingDutyCycle) {
    hyrelMultiLayer(directory, patternName, cleaningDistance, toolNumber, temperature, moveSpeed, printSpeed,
                    nozzleDiameter, layerHeight, extrusionMultiplier, gridSpacing, patternOffset, toolOffset,
                    uvPenToolNumber, curingDutyCycle, 1, layerHeight);
}

void printMultiLayer(Hyrel &hyrel, const std::valarray<double> &initialPatternOffset, double gridSpacing,
                     const std::vector<std::vector<std::valarray<int>>> &sortedPaths, int layers, double layerHeight) {

    for (int i = 0; i < layers; i++) {
        double currentLayerHeight = i * layerHeight;
        hyrel.moveVertical(currentLayerHeight);
        hyrel.printPattern(sortedPaths, initialPatternOffset, gridSpacing, 2);
    }
}


void
hyrelMultiLayer(const boost::filesystem::path &directory, const std::string &patternName, double cleaningDistance,
                int toolNumber, int temperature, int moveSpeed, int printSpeed, double nozzleDiameter,
                double layerHeight, double extrusionMultiplier, double gridSpacing,
                const std::valarray<double> &patternOffset, std::vector<double> &toolOffset, int uvPenToolNumber,
                int curingDutyCycle, int layers, double firstLayerHeight) {
    boost::filesystem::path patternPath = directory / patternName;
    if (boost::filesystem::exists(patternPath)) {
        std::vector<std::vector<std::valarray<int>>> sortedPaths = read3DVectorFromFile(patternPath.string(),
                                                                                        "best_paths");
        Hyrel hyrel(moveSpeed, printSpeed, extrusionMultiplier);
        hyrel.init(temperature, 0, cleaningDistance, nozzleDiameter, firstLayerHeight,
                   layerHeight, toolNumber, toolOffset);
        hyrel.configureUVPen(toolNumber, uvPenToolNumber, curingDutyCycle);
        hyrel.addBreak();

        printMultiLayer(hyrel, patternOffset, gridSpacing, sortedPaths, layers, layerHeight);
        hyrel.shutDown();
        std::ostringstream suffixStream;

        suffixStream << std::fixed << std::setprecision(3);
        suffixStream << "_" << nozzleDiameter << "_um_" << layers << "_layers";
        hyrel.exportToFile(directory / "gcode", patternName, suffixStream.str());
    } else {
        std::cout << "ERROR: Directory \"" << patternPath << "\" does not exist." << std::endl;
    }
}