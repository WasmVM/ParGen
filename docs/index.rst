ParGen documentation
====================

.. toctree::
   :maxdepth: 2
   
   pxml

* :ref:`search`

``ParGen`` - Parser Generator to generate an LALR parser with C++

.. contents::
    :local:

Synopsis
--------

pargen [-h | --help] [-v | --version ] [-n | --namespace ]? [-d | --debug ] [--dump_tree ] [-I? | --includes ?]... pxml_file

Description
-----------

``ParGen`` consumes a PXML file that define the grammar, generate C++ lexer and parser

Command line arguments and options
----------------------------------

Arguments
^^^^^^^^^

pxml_file
    Path of the main PXML file

Options
^^^^^^^

--help, -h
    Show usage and additional help messages.

--version, -v
    Print version information.

--namespace, -n
    Override namespace of generated objects.

--debug, -d
    Open Debug mode, dump grammar, term enumeration, lexer states and parser states

--dump_tree
    Dump parse tree at runtime

--includes, -I
    Add directory of included files into search list
