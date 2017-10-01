#include "lib/tools.hpp"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(Tests)

BOOST_AUTO_TEST_CASE(ReadChunkTest)
{
    std::vector<std::size_t> bufferSize = {7, 8, 9, 17, 100};
    std::vector<std::size_t> expectedResult = {0, 1, 1, 2, 3};

    const char* const contents = "abcdefg\nabcdefg\nabcdefg\n";

    for (std::size_t i = 0; i != bufferSize.size(); ++i)
    {
        std::stringstream ss(contents);
        std::string buf;
        buf.resize(bufferSize[i]);
        std::size_t remaining = strlen(contents);
        BOOST_CHECK_EQUAL(expectedResult[i], ReadChunk(ss, buf, remaining));

        const auto remainingExpected =
            buf.size() > strlen(contents) ? 0 : strlen(contents) - buf.size();

        BOOST_CHECK_EQUAL(remaining, remainingExpected);
    }
}

BOOST_AUTO_TEST_SUITE_END()
