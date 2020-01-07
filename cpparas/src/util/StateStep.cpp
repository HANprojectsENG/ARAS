#include "util/StateStep.hpp"
#include <fstream>
#include <iostream>
#include <stdio.h>

namespace cpparas {

StateStep StateStep::fromFile(const std::string& filePath)
{
    std::ifstream inFile(filePath);
    StateStep result;

    if (!inFile.good())
        return result;

    inFile >> result.layer;
    inFile >> result.step;

    inFile.close();
    return result;
}

void StateStep::deleteFile(const std::string& filePath)
{
    std::remove(filePath.c_str());
}

void StateStep::saveToFile(const std::string& filePath)
{
    std::ofstream outFile(filePath);
    outFile << layer << " " << step << std::endl;
    outFile.close();
}

} // namespace cpparas
