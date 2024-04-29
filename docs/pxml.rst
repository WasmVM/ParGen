PXML
====

An XML-like markup language for ParGen definitions.

.. contents::
    :local:

Basic syntax
------------

* File extention: ``.pxml``
* The 1st line of pxml file should be ``<!DOCTYPE pxml>``
* The root element should be ``<pxml>`` in every pxml file, even if the files are included instead of direct used.
* Tags can be inlined as ``<tag />``
* Supported attribute value types:
    - boolean (true | false)
    - string
    - double
* Comments are enclosed with ``{%`` ``%}``
* Character ``<`` should be escaped as ``\<`` in text