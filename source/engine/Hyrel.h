//
// Created by Michał Zmyślony on 04/08/2022.
//

#ifndef VECTOR_SLICER_HYREL_H
#define VECTOR_SLICER_HYREL_H

#include "GCodeFile.h"
#include "PatternBoundaries.h"
#include <boost/filesystem.hpp>

class Hyrel : public GCodeFile {
    void defineHeightOffset(unsigned int toolNumber, double height);

    void defineToolOffset(int toolNumber, const std::vector<double> &xyz, unsigned int heightRegisterOffset);

    void extrude(const std::valarray<double> &xy);

    void selectTool(unsigned int toolNumber);

    void setUnitsToMillimetres();

    void signalFinishedPrint();

    void clearOffsets();

    void turnMotorsOff();

    void
    clean(double cleanLength, int numberOfLines, double nozzleWidth, int HEIGHT_OFFSET_REGISTER, double layerHeight);

    void
    configurePrime(int toolNumber, double pulseRate, double numberOfPulses, double dwellTime,
                   bool isExecutedImmediately);

    void
    configureUnprime(int toolNumber, double pulseRate, double numberOfPulses, double dwellTime,
                     bool isExecutedImmediately);

    void disablePriming(int toolNumber);

    void setTemperatureHotend(int temperature, int toolNumber);

public:

    void configureFlow(double nozzleWidth, double layerHeight, double flowMultiplier, int pulses, int tool);

    void
    init(int hotendTemperature, int bedTemperature, double cleanLength, double nozzleWidth, double firstLayerHeight,
         double layerHeight, int toolNumber, std::vector<double> &toolOffset);

    void shutDown();

    Hyrel(int moveSpeed, int printSpeed, double extrusionCoefficient);

    void
    printPath(const std::vector<std::valarray<int>> &path, const std::valarray<double> &positionOffset,
              double gridDistance);

    PatternBoundaries printPattern(const std::vector<std::vector<std::valarray<int>>> &sortedSequenceOfPaths,
                                   const std::valarray<double> &positionOffset, double gridSpacing,
                                   double liftOffDistance);

    void exportToFile(const boost::filesystem::path &resultsPath, const std::string &patternName,
                      const std::string &suffix);

    void configureUVPen(int printHeadToolNumber, int penToolNumber, int dutyCycle);

    void addLocalOffset(std::vector<double> offset);
};

void testHeaderAndFooter();

void
hyrelSingleLayer(const boost::filesystem::path &directory, const std::string &patternName, double cleaningDistance,
                 int toolNumber, int temperature, int moveSpeed, int printSpeed, double nozzleDiameter,
                 double layerHeight, double extrusionMultiplier, double gridSpacing,
                 const std::valarray<double> &patternOffset, std::vector<double> &toolOffset, int uvPenToolNumber,
                 int curingDutyCycle);

void
hyrelMultiLayer(const boost::filesystem::path &directory, const std::string &patternName, double cleaningDistance,
                int toolNumber, int temperature, int moveSpeed, int printSpeed, double nozzleDiameter,
                double layerHeight, double extrusionMultiplier, double gridSpacing,
                const std::valarray<double> &patternOffset, std::vector<double> &toolOffset, int uvPenToolNumber,
                int curingDutyCycle, int layers, double firstLayerHeight);

#endif //VECTOR_SLICER_HYREL_H
