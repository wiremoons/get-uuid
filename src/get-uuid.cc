/*
 * @file get-uuid.cc
 * @brief Generate a random Universally Unique Identifier (UUID).
 *
 * @author Simon Rowe <simon@wiremoons.com>
 * @license open-source released under "MIT License"
 * @source https://github.com/wiremoons/get-uuid
 * @date originally created: 06 June 2022
 *
 * @details Program generates a a number of stated UUID Keys and outputs
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

std::string getUuidString()
{
    uuid_t uuid;
    uuid_generate_random(uuid);

    char *str_uuid = new char[100];
    uuid_unparse(uuid, str_uuid);
    return str_uuid;
}

//////////////////////////////////////////////////////////////////////////////
//            Application entry point :  main()                             //
//////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{

    argparse::ArgumentParser program("get-uuid");
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
