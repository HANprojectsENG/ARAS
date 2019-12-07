#ifndef LSFPARSER_HPP
#define LSFPARSER_HPP

#include <string>

#define STEPS_PER_LAYER 10
#define TOTAL_LAYERS 10

namespace LSFParser {

    struct LSFDataStruct {
        uint32_t layer = 0;
        uint32_t step = 0;
        uint32_t legosize = 0;
        uint32_t color = 0;
        uint32_t coordinates[24] = {};
    };

    struct LSFStepBuffer {
        LSFDataStruct Step[STEPS_PER_LAYER];
    };

    struct LSFData {
        LSFStepBuffer Layer[TOTAL_LAYERS];
    };

    LSFData Load_LSF_file(std::string filepath);
    LSFDataStruct LSF_line_parse(std::string line);


}

#endif /* LSFPARSER_HPP */
