#include "LSFParser.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

namespace cpparas {

namespace LSFParser {

    LSFData Load_LSF_file(std::string filepath)
    {
        LSFData data;
        LSFDataStruct lineData;

        std::ifstream file { filepath };
        std::string line;
        uint32_t current_line = 0;

        while (std::getline(file, line)) {
            lineData = LSF_line_parse(line);
            if (lineData.legosize % 2 == 0 && lineData.legosize >= 2 && lineData.legosize <= 12) {
                data.Layer[lineData.layer].Step[lineData.step] = lineData;
            } else {
                std::cout << "LSF Insertion fail on line: " << std::to_string(current_line) << std::endl;
            }
            current_line++;
        }
        return data;
    }

    LSFDataStruct LSF_line_parse(std::string line)
    {
        std::replace(line.begin(), line.end(), ',', ' ');
        std::stringstream splitted_string { line };
        LSFDataStruct lineData;
        splitted_string >> lineData.layer;
        splitted_string >> lineData.step;
        splitted_string >> lineData.legosize;
        uint32_t icolor;
        splitted_string >> icolor;
        lineData.color = (Color)icolor;
        for (uint32_t i = 0; i < lineData.legosize; i++) {
            Point<uint32_t> coordinate;
            splitted_string >> coordinate.col;
            splitted_string >> coordinate.row;
            lineData.coordinates.push_back(coordinate);
        }
        return lineData;
    }

} // namespace LSFParser

} // namespace cpparas
