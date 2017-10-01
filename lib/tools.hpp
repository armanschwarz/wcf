#pragma once

#include <iosfwd>

// read from a file and dump the latest guess for file size into the output
// stream
int CountLines(
    std::istream& file,
    std::size_t fileSize,
    std::ostream& out,
    double freq,
    std::size_t chunkSize,
    bool live,
    bool simpleMode);

// read a chunk of characters into the buffer and count the number of line
// breaks
std::size_t ReadChunk(
    std::istream& file,
    std::string& buf,
    std::size_t& remaining);
