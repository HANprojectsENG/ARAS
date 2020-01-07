#ifndef LSFPARSER_HPP
#define LSFPARSER_HPP

#include <map>
#include <string>

#define STEPS_PER_LAYER 10
#define TOTAL_LAYERS 10

namespace cpparas {

namespace LSFParser {

    struct LSFDataStruct {
        uint32_t layer = 0;
        uint32_t step = 0;
        uint32_t legosize = 0;
        uint32_t color = 0;
        uint32_t coordinates[24] = {};
    };

    struct LSFStepBuffer {
        std::map<int, LSFDataStruct> Step;
    };

    struct LSFData {
        std::map<int, LSFStepBuffer> Layer;
    };

    LSFData Load_LSF_file(std::string filepath);
    LSFDataStruct LSF_line_parse(std::string line);

}

} // namespace cpparas

#endif /* LSFPARSER_HPP */
