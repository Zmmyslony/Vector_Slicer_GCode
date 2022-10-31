//
// Created by Michał Zmyślony on 25/10/2022.
//

#include "printer_configuration.h"

PrinterConfiguration::PrinterConfiguration(int non_printing_speed, int bed_temperature, int print_head_tool_number)
        : non_printing_speed(non_printing_speed), bed_temperature(bed_temperature),
          print_head_tool_number(print_head_tool_number) {}

int PrinterConfiguration::getNonPrintingSpeed() const {
    return non_printing_speed;
}

int PrinterConfiguration::getBedTemperature() const {
    return bed_temperature;
}

int PrinterConfiguration::getPrintHeadToolNumber() const {
    return print_head_tool_number;
}