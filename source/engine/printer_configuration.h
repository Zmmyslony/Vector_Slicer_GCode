//
// Created by Michał Zmyślony on 25/10/2022.
//

#ifndef GCODEGENERATOR_PRINTER_CONFIGURATION_H
#define GCODEGENERATOR_PRINTER_CONFIGURATION_H


class PrinterConfiguration {
    int non_printing_speed = 1000;
    int bed_temperature = 0;
    int print_head_tool_number = 1;

public:
    PrinterConfiguration(int non_printing_speed, int bed_temperature, int print_head_tool_number);

    int getNonPrintingSpeed() const;

    int getBedTemperature() const;

    int getPrintHeadToolNumber() const;
};


#endif //GCODEGENERATOR_PRINTER_CONFIGURATION_H
