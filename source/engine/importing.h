/*
 * 2023, Michał Zmyślony, mlz22@cam.ac.uk.
 *
 * Please cite Michał Zmyślony and Dr John Biggins if you use any part of this code in work you publish or distribute.
 *
 * This file is part of gCodeGenerator.
 *
 * gCodeGenerator is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 *
 * gCodeGenerator is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with Foobar. If not, see <https://www.gnu.org/licenses/>.
 */

//
// Created by Michał Zmyślony on 13/03/2023.
//

#ifndef GCODEGENERATOR_IMPORTING_H
#define GCODEGENERATOR_IMPORTING_H

#include <boost/filesystem/path.hpp>
#include <filesystem>
#include <string>
#include <valarray>
#include <vector>

namespace fs = boost::filesystem;

double readResolution(const fs::path &filepath);

std::vector<std::vector<std::valarray<double>>> read3DVectorFromFileDouble(const fs::path &path);

#endif //GCODEGENERATOR_IMPORTING_H
