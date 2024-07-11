# ParGen

Parser generator to generate an LALR parser with C++

[Documentation](https://wasmvm.github.io/ParGen/)

[PXML Syntax](https://wasmvm.github.io/ParGen/pxml.html)

## Prerequisite

* CMake >= 3.16

* C++ compiler with C++20 standard library

## Build

1. Run CMake

```shell
mkdir build && cd build && cmake ..
```

2. Run Make

```shell
make -j4
```

## Generate HTML documents

1. Run CMake

```shell
mkdir build && cd build && cmake ..
```

2. Run Make

```shell
make docs
```

The generated document will under `build/docs/html`

## Usage

pargen [-h | --help] [-v | --version ] [-n | --namespace ]? [-d | --debug ] [--dump_tree ] [-I? | --includes ?]... pxml_file

### Arguments

* pxml_file : Path of the main PXML file

### Options

* --help, -h : Show usage and additional help messages.

* --version, -v : Print version information.

* --namespace, -n : Override namespace of generated objects.

* --debug, -d : Open Debug mode, dump grammar, term enumeration, lexer states and parser states

* --dump_tree : Dump parse tree at runtime

* --includes, -I : Add directory for searching included PXML files
