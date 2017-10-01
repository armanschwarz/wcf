#include "lib/tools.hpp"

#include <boost/timer.hpp>

#include <algorithm>
#include <assert.h>
#include <fstream>
#include <iomanip>
#include <ostream>

int CountLines(
    std::istream& is,
    std::size_t fileSize,
    std::ostream& os,
    double freq,
    std::size_t chunkSize,
    bool live,
    bool simpleMode)
{
    std::string chunk;
    chunk.resize(chunkSize);
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

    while (remaining)
    {
        lines += ReadChunk(is, chunk, remaining);

        if (timer.elapsed() > freq && freq)
        {
            update();

            if (live)
                timer.restart();
            else
                break;
        }
        else if (!remaining)
        {
            update();
        }
    }

    os << std::endl;
    return 0;
}

std::size_t ReadChunk(
    std::istream& is,
    std::string& buf,
    std::size_t& remaining)
{
    const auto n = std::min(buf.size(), remaining);
    const auto p = &buf[0];
    is.read(p, n);
    remaining -= n;

    // FIXME this is the minime viable implementation. It's probably slow and
    // doesn't take into account OS specifics.
    return std::count_if(p, p + n, [](auto elem) { return elem == '\n'; });
}
