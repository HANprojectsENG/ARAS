#include "LSFParser.hpp"
#include "types/Color.hpp"
#include "types/Point.hpp"
#include <gtest/gtest.h>

using namespace cpparas;

TEST(LSFParserSuite, LineParse)
{
    const std::string lineInput = "1, 4, 4, 24, 26, 17, 26, 18, 27, 17, 27, 18";

    const cpparas::LSFParser::LSFDataStruct expectedResult = {
        1,
        4,
        4,
        cpparas::Color::YELLOW,
        std::vector<cpparas::Point<uint32_t>> {
            { 26, 17 },
            { 26, 18 },
            { 27, 17 },
            { 27, 18 } }
    };

    const cpparas::LSFParser::LSFDataStruct result = cpparas::LSFParser::LSF_line_parse(lineInput);
    EXPECT_EQ(result, expectedResult);
}
