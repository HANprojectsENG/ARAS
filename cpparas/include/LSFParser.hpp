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

    /**
     * A step. Represents one "place block" instruction.
     */
    struct LSFDataStruct {
        uint32_t layer = 0;
        uint32_t step = 0;
        uint32_t legosize = 0;
        Color color = Color::NONE;
        std::vector<Point<uint32_t>> coordinates = {};
    };

    /**
     * Collection of steps to be executed on one layer.
     */
    struct LSFStepBuffer {
        std::map<int, LSFDataStruct> Step;
    };

    /**
     * Collection of steps grouped by layer.
     */
    struct LSFData {
        std::map<int, LSFStepBuffer> Layer;
    };

    /**
     * @brief Parses a Lego Sequence File and returns the parsed data.
     */
    LSFData Load_LSF_file(std::string filepath);
    /**
     * @brief Parses one LSF instruction (line).
     */
    LSFDataStruct LSF_line_parse(std::string line);

    /**
     * @brief Returns the coordinate and brick shape of an LSF instruction.
     */
    std::pair<Point<uint32_t>, Brick> Data_to_brick(const LSFDataStruct& dataStruct);

}

} // namespace cpparas

#endif /* LSFPARSER_HPP */
