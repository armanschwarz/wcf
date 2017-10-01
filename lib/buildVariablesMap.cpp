#include "lib/buildVariablesMap.hpp"

#include <boost/lexical_cast.hpp>

using namespace boost::program_options;

variables_map BuildVariablesMap(int argc, char** argv)
{
    variables_map vm;

    options_description desc{"Print newline counts for the provided file"};

    desc.add_options()
        ("help,h", "Display this help screen")
        ("file,f", value<std::string>()->required(),
            "Input file to count lines from")
        ("live,l", bool_switch()->default_value(false),
            "Update the best guess after each interval, and return when the actual line count is known. This overrides default behavior, where wcf simply returns after the first interval with the line count guess")
        ("simple-output,s", bool_switch()->default_value(false),
            "Output only the guess value without accuracy estimation. If live mode is disabled this will cause wcf to only output the guess value once")
        ("time-interval,t", value<double>()->default_value(0.25),
            "Time in seconds between line count updates. Set to 0 to only display the line count once the whole file has been read.");

    store(parse_command_line(argc, argv, desc), vm);

    if (vm.count("help"))
        // invalid_argument might make more sense, but logic_error is what
        // boost's program_options errors inherit from so it makes sense for
        // consistency.
        throw std::logic_error(boost::lexical_cast<std::string>(desc));

    try
    {
        notify(vm);
    }
    catch (const error_with_option_name& e)
    {
        throw;
    }

    return vm;
}
