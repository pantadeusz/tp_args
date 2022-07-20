/**
 * @file tp_args.hpp
 * @author Tadeusz Puźniakowski
 * @brief Simple header only arguments parsing library.
 * @version 0.1
 * @date 2022-04-21
 *
 * @copyright Copyright (c) 2022
 *
 * This library allows for simple parsing arguments in the format:
 * argname=argvalue. It only checks the first equal sign. For example: ./a.out
 * myarg=itsvalue
 *
 * The types are allowed for arguments:
 * @code {.c++ }
 * auto arguments = parse_arguments(argc, argv, {{"height","int"}});
 * auto height = arg(arguments, "height",0);
 * @endcode
 * 
 * You can enable output stream for std::any by declaring
 * TP_ARGS_ENABLE_OSTREAM_ANY before including this file
 */
#ifndef __TP_ARGS_HPP____
#define __TP_ARGS_HPP____

#include <any>
#include <iostream>
#include <map>
#include <string>

/**
 * @brief It is in the namespace tp::args and provides just two methods -
 * parse_arguments, and arg. The example usage:
 * 
 * @code {.cpp}
 * int main(int argc, char **argv) {
 *     using namespace std;
 *     using namespace tp::args;
 *     auto arguments = parse_arguments(argc, argv, {{"height","int"}});
 *     auto height = arg(arguments, "height",0);
 *     std::cout <<"height " << height << std::endl;
 * }
 * @endcode
 *
 */

namespace tp::args {
/**
 * @brief Generates the arguments map that contains name-value pairs that
 * represents arguments. Each argument must be unique and only the last value
 * will be saved. For example ./programname x=1 x=2 will store only
 * arguments["x"] == 2
 *
 * @param argc number of arguments (like in main)
 * @param argv argument list with application name (like in main)
 * @param value_types map describing the expected argument names and its types
 * @param on_help callback function that is run when the CLI parameter is --help or -h
 * @return std::map<std::string,std::any>  map containing arguments and its
 * types
 */
std::map<std::string, std::any> parse_arguments(
    int argc, char **argv, const std::map<std::string, std::string> value_types,
    std::function<void(void)> on_help = []() {}) {
  using namespace std;
  map<string, any> ret;
  ret[""] = argv[0];  // program name
  for (auto s : std::vector<std::string>(argv + 1, argv + argc)) {
    if ((s == "--help") || (s == "-h")) {
      on_help();
      continue;
    }
    static const string delimiter = "=";
    auto k = s.substr(0, s.find(delimiter));
    auto v = s.erase(0, s.find(delimiter) + delimiter.length());
    try {
      if (value_types.at(k) == "int")
        ret[k] = stoi(v);
      else if (value_types.at(k) == "unsigned")
        ret[k] = (unsigned)stoul(v);
      else if (value_types.at(k) == "unsigned long")
        ret[k] = stoul(v);
      else if (value_types.at(k) == "float")
        ret[k] = stof(v);
      else if (value_types.at(k) == "double")
        ret[k] = stod(v);
      else if (value_types.at(k) == "bool")
        ret[k] = bool((v == "true") || (v == "1") || (v == "yes"));
      else
        ret[k] = v;
    } catch (std::out_of_range &e) {
      ret[k] = v;
      std::cerr << "WARN: unknown argument or bad type for \"" << k
                << "\" with value \"" << v << "\"" << std::endl;
    } catch (std::invalid_argument &) {
      std::cerr << "WARN: argument \"" << k << "\" shoud have value of type "
                << value_types.at(k) << " but had value \"" << v << "\""
                << std::endl;
    }
  }
  return ret;
}

/**
 * @brief gets the value from arguments and allow for setting the default value
 * and type is derived from this value.
 *
 * @tparam T the type of the argument
 * @param arguments map that contains pairs - param name, and then the value of
 * any type
 * @param arg_name the name of the argument
 * @param defaultval the default value that determines the type of the arg
 * @return T the value from arguments or defaultval if param not set
 */

template <typename T>
T arg(std::map<std::string, std::any> arguments, const std::string arg_name,
      T defaultval) {
  using namespace std;
  return (arguments.count(arg_name))
             ? any_cast<decltype(defaultval)>(arguments.at(arg_name))
             : defaultval;
};

}  // namespace tp::args

#ifdef TP_ARGS_ENABLE_OSTREAM_ANY
std::ostream &operator<<(std::ostream &o, std::any value) {
  using namespace std;

  if (value.type() == typeid(int)) {
    o << any_cast<int>(value);
  } else if (value.type() == typeid(float)) {
    o << any_cast<float>(value);
  } else if (value.type() == typeid(double)) {
    o << any_cast<double>(value);
  } else if (value.type() == typeid(unsigned)) {
    o << any_cast<unsigned>(value);
  } else if (value.type() == typeid(bool)) {
    o << (any_cast<bool>(value) ? "true" : "false");
  } else if (value.type() == typeid(string)) {
    o << any_cast<string>(value);
  } else
    o << "<<UNKNOWN_TYPE>>";
  return o;
}
#endif

#endif
