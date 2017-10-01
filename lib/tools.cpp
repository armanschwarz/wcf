#include "lib/tools.hpp"

#include <boost/timer.hpp>

#include <algorithm>
#include <assert.h>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <ostream>

int CountLines(
    std::istream& is,
    std::size_t fileSize,
    std::ostream& os,
    double freq,
    bool live,
    bool simpleMode)
{
    std::string buffer;
    buffer.reserve(1024);

    std::size_t remaining = fileSize;
    std::size_t lines = 0u;

    boost::timer timer;

    const auto update = [&os, &remaining, fileSize, &lines, simpleMode]()
    {
        const auto consumed = (fileSize - remaining);
        const auto lineCount = lines * fileSize / consumed;
        const auto accuracy = 100 * consumed / fileSize;

        // characters needed to represent the number of lines of this file if
        // it were made entirely of line breaks:
        const auto limit = static_cast<unsigned>(std::log10(fileSize)) + 1u;

        os << std::left;
        if (!simpleMode)
            os <<
                "\rline count: " << std::setw(limit) << lineCount <<
                " (accuracy: " << accuracy << "%)";
        else
            os << "\r" << std::setw(limit) << lineCount;
        os << std::flush;
    };

    do
    {
        assert(buffer.empty());
        std::getline(is, buffer);
        remaining -= buffer.size();
        buffer.clear();

        if (!is.eof())
            ++lines;

        if (timer.elapsed() > freq && freq)
        {
            update();

            if (live)
                timer.restart();
            else
                break;
        }
        else if (is.eof())
        {
            update();
        }
    }
    while (!is.eof());

    os << std::endl;

    return 0;
}
