#ifndef LSFPARSER_HPP
#define LSFPARSER_HPP

#include "types/Brick.hpp"
#include "types/Color.hpp"
#include "types/Point.hpp"
#include <map>
#include <string>
#include <vector>

namespace cpparas {

namespace LSFParser {

    struct LSFDataStruct {
        uint32_t layer = 0;
        uint32_t step = 0;
        uint32_t legosize = 0;
        Color color = Color::NONE;
        std::vector<Point<uint32_t>> coordinates = {};
    };

    struct LSFStepBuffer {
        std::map<int, LSFDataStruct> Step;
    };

    struct LSFData {
        std::map<int, LSFStepBuffer> Layer;
    };

    LSFData Load_LSF_file(std::string filepath);
    LSFDataStruct LSF_line_parse(std::string line);

    std::pair<Point<uint32_t>, Brick> Data_to_brick(const LSFDataStruct& dataStruct);

}

} // namespace cpparas

#endif /* LSFPARSER_HPP */
