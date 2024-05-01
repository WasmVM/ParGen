PXML
****

An XML-like markup language for ParGen definitions.

.. contents::
    :local:

Basic syntax
============

* File extention: ``.pxml``
* The 1st line of pxml file should be ``<!DOCTYPE pxml>``
* The root element should be ``<pxml>`` in every pxml file, even if the files are included instead of direct use.
* Tags can be inlined by using ``/>``
* Supported attribute value types:
    - boolean (true | false)
    - string
    - double 
* Comments are enclosed with ``{%`` ``%}``
* Character ``<`` should be escaped as ``\<`` in text

Example:

.. code-block:: pxml

    <!DOCTYPE pxml>
    {% comment %}
    <pxml>
        <include src="test.pxml" />
        <tokens class="Token" namespace="TokenType" headerFile="Token.hpp">
            {% header file definitions %}
            <header indent=0 position="top">
                #include \<string>
                #include \<cstddef>
                #include \<unordered_set>
            </header>
        </tokens>
    </pxml>

Tags
====

<pxml>
------

The root element of PXML document

**Attributes**

* namespace : The outmost namespace for generated lexer/parser
    - default : ``Pargen``

<include>
---------

Include other PXML document to this document

**Attributes**

* src : ``[Required]`` Path of included document

<tokens>
---------

Define tokens

**Attributes**

* class : Token class name
    - default : ``Token``

* namespace : Namespace of token types
    - default : ``Tokens``

* headerFile : Path of output token header file
    - default : ``Token.hpp``

* sourceFile : Path of output token source file
    - default : ``Token.cpp``