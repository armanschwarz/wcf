#pragma once

#include <iosfwd>

// read from a file and dump the latest guess for file size into the output
// stream
int CountLines(
    std::istream& file,
    std::size_t fileSize,
    std::ostream& out,
    double freq,
    bool live,
    bool simpleMode);
