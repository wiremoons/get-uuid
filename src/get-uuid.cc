/*
 * @file get-uuid.cc
 * @brief Generate a random Universally Unique Identifier (UUID).
 *
 * @author Simon Rowe <simon@wiremoons.com>
 * @license open-source released under "MIT License"
 * @source https://github.com/wiremoons/get-uuid
 * @date originally created: 06 June 2022
 *
 * @details Program generates a number of stated UUID Keys and outputs
 * them in a format for pasting into a JSON file.
 * Was created to add a primary key uuid to a JSON database export file.
 * Example output:  "Key": "1540CA00-BB31-4491-84A9-981F652A6B9E",
 */

#include <iostream>
#include <locale>
#include <random>
#include <string>

#include <argparse/argparse.hpp>
#include <fmt/color.h>
#include <fmt/format.h>
#include <uuid/uuid.h>

// Function to return a random UUID as a string
std::string getUuidString()
{
    uuid_t uuid;
    uuid_generate_random(uuid);

    char *str_uuid = new char[100];
    uuid_unparse(uuid, str_uuid);
    return str_uuid;
}

// Function to return the version of the C++ compiler used to build the app
std::string const getCompilerVersion()
{
#ifdef __clang__
    return fmt::format("clang {}", __clang_version__);
#elif __GNUC__
    return fmt::format("GNU GCC {}", __VERSION__);
#elif _MSC_VER
    return = fmt::format("Microsoft {}", _MSC_FULL_VER);
#elif __MINGW64__
    return = fmt::format("mingw64 {}", __MINGW64_VERSION_MAJOR);
#else
    return = "UNKNOWN";
#endif
}

// Function to return the app build kind
std::string const getBuildType()
{
#if DEBUG
    return "Debug";
#else
    return "Release";
#endif
}

// Function to return a formatted string containing the app version details
std::string const createVersionScreen(std::string const &APP_NAME, std::string const &APP_VERSION)
{
    std::string version_output = fmt::format("\n'{}' version is: '{}'\n", APP_NAME, APP_VERSION);
    version_output.append(fmt::format("Compiled on: '{} @ {}'.\n", __DATE__, __TIME__));
    version_output.append(fmt::format("Copyright (c) 2022-2023 Simon Rowe.\n\n"));
    version_output.append(
        fmt::format("C++ source built as '{}' using compiler '{}'.\n\n", getBuildType(), getCompilerVersion()));
    version_output.append(fmt::format("Included library versions:\n"));
    version_output.append(fmt::format("- fmt version: '{}'\n", FMT_VERSION));
    version_output.append(fmt::format("\nFor licenses and further information visit:\n"
                                      "- get-uuid:      https://github.com/wiremoons/get-uuid\n"
                                      "- argparse:      https://github.com/p-ranav/argparse\n"
                                      "- fmt:           https://github.com/fmtlib/fmt\n"));
    return version_output;
}

//////////////////////////////////////////////////////////////////////////////
//            Application entry point :  main()                             //
//////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{

    const std::string APP_NAME = argv[0];
    const std::string APP_VERSION{"0.1.4"};

    argparse::ArgumentParser program("get-uuid", createVersionScreen(APP_NAME, APP_VERSION));
    program.add_argument("-j").help("Output UUID as JSON object.").default_value(false).implicit_value(true);
    program.add_argument("-n").help("Number of UUID to generate and output.").default_value(1).scan<'i', int>();

    try {
        program.parse_args(argc, argv);
    } catch (const std::runtime_error &err) {
        std::cerr << err.what() << std::endl;
        std::cerr << program;
        std::exit(1);
    }

    // number of UUID keys to produce in the loop
    auto keys = program.get<int>("-n");

    for (int i = 0; i < keys; i++) {
        if (program["-j"] == true) {
            std::cout << "\"uuid\": \"" << getUuidString() << "\", " << std::endl;
        } else {
            std::cout << getUuidString() << std::endl;
        }
    }
    return EXIT_SUCCESS;
}
