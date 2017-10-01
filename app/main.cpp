#include "lib/tools.hpp"
#include "lib/buildVariablesMap.hpp"

#include <boost/filesystem.hpp>

#include <iostream>
#include <fstream>

int main(int argc, char** argv)
{
    boost::program_options::variables_map vm;

    try
    {
        vm = BuildVariablesMap(argc, argv);
    }
    catch (const std::logic_error& e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }

    const auto filename = vm["file"].as<std::string>();
    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cerr << "failed to open " << filename << std::endl;
        return 1;
    }

    return CountLines(
        file,
        boost::filesystem::file_size(filename),
        std::cout,
        vm["time-interval"].as<double>(),
        1024u,
        vm["live"].as<bool>(),
        vm["simple-output"].as<bool>());
}
