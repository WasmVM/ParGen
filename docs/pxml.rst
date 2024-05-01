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
    - default : ``"Pargen"``

**Children**

Any tags and texts except for ``<pxml>``

<include>
---------

Include other PXML document to this document

**Attributes**

* src : ``[Required]`` Path of included document

<tokens>
--------

Define tokens

**Attributes**

* class : Token class name
    - default : ``"Token"``

* namespace : Namespace of token types
    - default : ``"Tokens"``

* headerFile : Path of output token header file
    - default : ``"Token.hpp"``

* sourceFile : Path of output token source file
    - default : ``"Token.cpp"``

**Children**

``<header>``, ``<token>``, ``<member>``, ``<function>``, ``<source>``

<token>
-------

Define token

**Attributes**

* name : ``[Required]`` Token name

**Children**

``<type>``, ``<member>``, ``<function>``

<header>
--------

C++ codes appending into header file

**Attributes**

* position : Appending position, ``"top"`` or ``"bottom"``
    - default : ``"top"``

* indent : Code indention
    - default : ``4``
    - ``0`` : no indention
    - negative value : keep same indention as pxml file (like HTML `<pre>`)

**Children**

C++ codes

<source>
--------

C++ codes appending into source file

**Attributes**

* position : Appending position, ``"top"`` or ``"bottom"``
    - default : ``"top"``

* indent : Code indention
    - default : ``4``
    - ``0`` : no indention
    - negative value : keep same indention as pxml file (like HTML `<pre>`)

**Children**

C++ codes

<member>
--------

Definition of class member

**Attributes**

* indent : Code indention
    - default : ``4``
    - ``0`` : no indention
    - negative value : keep same indention as pxml file (like HTML `<pre>`)

**Children**

C++ class member definition

<function>
----------

Definition of class member function

**Attributes**

* indent : Code indention
    - default : ``4``
    - ``0`` : no indention
    - negative value : keep same indention as pxml file (like HTML `<pre>`)

**Children**

C++ function definition

<type>
---------

Indicate a C++ type

**Children**

C++ type