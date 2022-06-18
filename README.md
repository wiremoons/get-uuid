[![MIT licensed](https://img.shields.io/badge/license-MIT-blue.svg)](https://raw.githubusercontent.com/hyperium/hyper/master/LICENSE) [![CodeQL](https://github.com/wiremoons/get-uuid/actions/workflows/codeql-analysis.yml/badge.svg)](https://github.com/wiremoons/get-uuid/actions/workflows/codeql-analysis.yml) [![get-uuid-build](https://github.com/wiremoons/get-uuid/actions/workflows/get-uuid-build.yml/badge.svg)](https://github.com/wiremoons/get-uuid/actions/workflows/get-uuid-build.yml)

# get-uuid
CLI app to generate a random Universally Unique Identifier (UUID).

# Original program use case
The application was created as I needed to add a UUID to each record of a 18,000+ record database. I needed to generate the UUIDs quickly in a format I could 'cut and paste' the output of into a JSON database export, before re-populating the database with the additional UUID field, and all the prior existing data. This was carried out as part of a 'record clean up' exercise on the database.

## Executing the program

The application is command line application that is run from a terminal program on *macOS*, *Linux*, or *Windows*. Example of the basic output from executing the program `get-uuid` is as below.

```console
% get-uuid
2ED52F7C-ED45-4854-8B42-12A156C15DB0

% get-uuid -n 5
2BEA8AFA-59EC-48BD-9A78-37E32D353C35
9541E2FD-6EB0-433A-93E9-7E37A186CB5B
BBCB9541-1A50-4C44-BEA6-6C9E3F42E2D0
82F51F40-6FF6-40B7-A46D-BDE3FFE1A31E
018BFBE0-F48E-4D0C-AB44-7BCF496FDD28

% get-uuid -j -n 5
"uuid": "4C7F1E3C-8F2B-43DA-BE1B-4775A291F1CB", 
"uuid": "7815BA01-E681-4C25-B758-5B4EB09A76E2", 
"uuid": "3BFFFC89-6221-4F65-972F-CE6B35A30CBC", 
"uuid": "E9C5C928-5F9D-4BC9-BD83-834CECFD74DE", 
"uuid": "B638976D-E729-45F8-984C-09AD2D5F2CE0", 

```

## Build

A C++ compiler is required to build `get-uuid`. 

- `cmake` is recommended to perform the build.
- `vcpkg` is recommended to perform the config and package management. 


In order to build using `vcpkg` and `cmake`, clone this repo and then run:

```console
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

The resulting program is in located the `./bin/` sub-directory.

To detect and use `vcpkg` the `cmake` process looks for the environment variable `VCPKG_ROOT`. Set this to the location of `vcpkg` installation. For assistance wiht installing 'vcpkg' see: [Get started with vcpkg](https://vcpkg.io/en/getting-started.html).
```
# Most Unix (Linux, macOS, etc):
export VCPKG_ROOT=~/.vcpkg
```

## Library Dependencies

The following C++ libraries are included by `vcpkg` or `cmake` and used by `get-uuid`:

- [argpass by @p-ranav](https://github.com/p-ranav/argparse) - command line argument parser for modern C++;
- [fmt by @fmtlib](https://github.com/fmtlib/fmt) - fast and safe alternative to C stdio and C++ iostreams;
- [libuuid](https://sourceforge.net/projects/libuuid/) - a Linux OS only additional dependency.


## License

The `get-uuid` application is provided under the _MIT open source license_. A copy
of the MIT license file is [here](./LICENSE).
