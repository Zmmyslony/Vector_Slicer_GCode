//
// Created by Michał Zmyślony on 15/10/2021.
//

#include "valarray_operations.h"
#include <stdexcept>
#include <iostream>

std::valarray<double> itodArray(const std::valarray<int> &int_array) {
    std::valarray<double> double_array(int_array.size());
    for (int i = 0; i < int_array.size(); i++) {
        double_array[i] = (double) int_array[i];
    }
    return double_array;
}

std::valarray<int> dtoiArray(const std::valarray<double> &double_array) {
    std::valarray<int> int_array(double_array.size());
    for (int i = 0; i < double_array.size(); i++) {
        int_array[i] = lround(double_array[i]);
    }
    return int_array;
}

double generalNorm(const std::valarray<double> &array, const double &exponent) {
    double sum = 0;
    for (auto &element: array) {
        sum += pow(element, exponent);
    }
    return pow(sum, 1 / exponent);
}

double norm(const std::valarray<double> &array) {
    return generalNorm(array, 2);
}

double norm(const std::valarray<int> &array) {
    return norm(itodArray(array));
}

std::valarray<double> generalNormalize(const std::valarray<double> &array, const double &exponent) {
    return array / generalNorm(array, exponent);
}

std::valarray<double> normalize(const std::valarray<double> &array) {
    return generalNormalize(array, 2);
}

std::valarray<double> normalize(const std::valarray<int> &array) {
    return normalize(itodArray(array));
}

double dot(const std::valarray<double> &array_1, const std::valarray<double> &array_2) {
    double dot_product = 0;
    if (array_1.size() != array_2.size()) {
        throw std::invalid_argument("Dot: Dotted array are of different size.\n");
    }
    for (int i = 0; i < array_1.size(); i++) {
        dot_product += array_1[i] * array_2[i];
    }
    return dot_product;
}

double dot(const std::valarray<int> &array_1, const std::valarray<int> &array_2) {
    return dot(itodArray(array_1), itodArray(array_2));
}

std::valarray<double> perpendicular(std::valarray<double> vector) {
    if (vector.size() != 2) {
        throw std::invalid_argument("Perpendicular: Size of the valarray not equal to 2.\n");
    }
    return std::valarray<double>({-vector[1], vector[0]});
}


std::valarray<int> perpendicular(const std::valarray<int> &vector) {
    return dtoiArray(perpendicular(itodArray(vector)));
}


void printArray(const std::vector<std::valarray<int>> &array) {
    for (auto &row: array) {
        std::cout << "(";
        for (auto &element: row) {
            std::cout << element << ", ";
        }
        std::cout << "), ";
    }
    std::cout << std::endl;
}

void printArray(const std::vector<std::valarray<double>> &array) {
    for (auto &row: array) {
        std::cout << "(";
        for (auto &element: row) {
            std::cout << element << ", ";
        }
        std::cout << "), ";
    }
    std::cout << std::endl;
}

std::valarray<int> uinttointArray(const std::valarray<unsigned int> &uint_array) {
    std::valarray<int> int_array(uint_array.size());
    for (int i = 0; i < uint_array.size(); i++) {
        int_array[i] = lround(uint_array[i]);
    }
    return int_array;
}