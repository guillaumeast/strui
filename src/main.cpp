#include <algorithm>
#include <string>
#include <iostream>
#include <cstdlib>      // std::atoi
#include "strui.hpp"

using string = std::string;
template<typename T> using vector = std::vector<T>;
template<typename T> using opt = std::optional<T>;

static string red = "\033[31m";
static string reset = "\033[0m";

static int handle_count(int argc, char* argv[]);
static int handle_join(int argc, char* argv[]);
static int handle_split(int argc, char* argv[]);
static int handle_repeat(int argc, char* argv[]);

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        std::cerr << red << "Usage: " << argv[0] << "<command> <...args...>" << reset << "\n";
        return 1;
    }

    string command = argv[1];

    if      (command == "count")         return handle_count(argc, argv);
    else if (command == "join")          return handle_join(argc, argv);
    else if (command == "split")         return handle_split(argc, argv);
    else if (command == "repeat")        return handle_repeat(argc, argv);

    else if (command == "clean")         std::cout << strui::clean(argv[2]) << "\n";
    else if (command == "flat_width")    std::cout << strui::flat_width(argv[2]) << "\n";
    else if (command == "width")         std::cout << strui::width(argv[2]) << "\n";
    else if (command == "height")        std::cout << strui::height(argv[2]) << "\n";

    return 0;
}

static int handle_count(int argc, char* argv[])
{
    if (argc != 4)
    {
        std::cerr << red << "Usage: " << argv[0] << " " << argv[1] << " <value> <string>" << reset << "\n";
        return 1;
    }

    std::cout << strui::count(argv[2], argv[3]) << "\n";
    return 0;
}

static int handle_join(int argc, char* argv[])
{
    if (argc < 4)
    {
        std::cerr << red << "Usage: " << argv[0] << " " << argv[1] << " ?--separator ?<separator> <...strings...>" << reset << "\n";
        return 1;
    }

    vector<string> input;
    string separator = "";
    for (int i = 2; i < argc; i++)
    {
        if (string(argv[i]) == "--separator")
        {
            separator = argv[++i];
            continue;
        }

        input.push_back(argv[i]);
    }

    std::cout << strui::join(input, separator) << "\n";
    return 0;
}

static int handle_split(int argc, char* argv[])
{
    if (argc != 4)
    {
        std::cerr << red << "Usage: " << argv[0] << " " << argv[1] << " <string> <separator>" << reset << "\n";
        return 1;
    }

    vector<string> result = strui::split(argv[2], argv[3]);
    for (const auto& part : result)
    {
        std::cout << part << "\n";
    }

    return 0;
}

static int handle_repeat(int argc, char* argv[])
{
    string arg = argv[2];
    bool arg_is_non_negative_int = !arg.empty() && std::all_of(arg.begin(), arg.end(), ::isdigit);

    if ( argc < 4 || argc > 5 || !arg_is_non_negative_int )
    {
        std::cerr << red << "Usage: " << argv[0] << " " << argv[1] << " <count> <string> ?<separator>" << reset << "\n";
        return 1;
    }
    
    size_t count = std::stoul(arg);
    string separator = argc == 5 ? argv[4] : "";

    std::cout << strui::repeat(count, argv[3], separator) << "\n";
    return 0;
}

