/**
 * @file tp_args.hpp
 * @author Tadeusz Puźniakowski (anonymous@unknown.com)
 * @brief Simple header only arguments parsing library.
 * @version 0.1
 * @date 2022-04-21
 *
 * @copyright Copyright (c) 2022
 *
 * This library allows for simple parsing arguments in the format: argname=argvalue. It only checks the first equal sign. For example: ./a.out myarg=itsvalue
 *
 * The types are allowed for arguments:
 * @code {.c++ }
auto arguments = parse_arguments(argc, argv, {{"height","int"}});
auto height = arg(arguments, "height",0);
 * @endcode
 */
#ifndef __TP_ARGS_HPP____
#define __TP_ARGS_HPP____

#include <map>
#include <string>
#include <any>
#include <iostream>

/**
 * @brief It is in the namespace tp::args and provides just two methods - parse_arguments, and arg
 *
 */

namespace tp::args
{
/**
 * @brief prepares arguments map.
 */
auto parse_arguments = [](int argc, char **argv,
const std::map<std::string,std::string> value_types ) -> std::map<std::string,std::any> {
    using namespace std;
    map<string,any> ret;
    for (auto s : std::vector<std::string>(argv+1,argv+argc))
    {
        static const string delimiter = "=";
        auto k = s.substr(0, s.find(delimiter));
        auto v = s.erase(0, s.find(delimiter) + delimiter.length());
        try {
            if (value_types.at(k) == "int") ret[k] = stoi(v);
            else if (value_types.at(k) == "unsigned")ret[k] = (unsigned)stoul(v);
            else if (value_types.at(k) == "unsigned long")ret[k] = stoul(v);
            else if (value_types.at(k) == "float")ret[k] = stof(v);
            else if (value_types.at(k) == "double") ret[k] = stod(v);
            else if (value_types.at(k) == "bool") ret[k] = bool((v=="true") || (v=="1") || (v=="yes"));
            else ret[k] = v;
        } catch (std::out_of_range &e) {
            ret[k] = v;
            std::cerr << "WARN: unknown argument or bad type for \"" << k << "\" with value \"" << v  << "\"" << std::endl;
        }
    }
    return ret;
};

/**
 * @brief gets the value from arguments and allow for setting the default value and type is derived from this value.
 */
auto arg = [](auto arguments, auto arg_name, auto defaultval)
{
    using namespace std;
    return (arguments.count(arg_name))?any_cast<decltype(defaultval)>(arguments.at(arg_name)):defaultval;
};
}

#endif
