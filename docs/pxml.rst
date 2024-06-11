PXML
****

An XML-like markup language for ParGen definitions.

.. contents::
    :local:

Format
======

* File extention: ``.pxml``
* The 1st line of pxml file should be ``<!DOCTYPE pxml>``
* The root element should be ``<pxml>`` in every pxml file, even if the files are included instead of direct use.
* Tags can be inlined by using ``/>``
* Supported attribute value types:
    - boolean (true | false)
    - string
    - double 
* Comments are enclosed with ``{%`` ``%}``, can be nested
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

<pxml>
======

The root element of PXML document

**Attributes**

* namespace <string> : The outmost namespace for generated lexer/parser
    - default : ``"Pargen"``

**Children**

Any tags and texts except for ``<pxml>``

<include>
=========

Include other PXML document to this document

**Attributes**

* src <string> : ``[Required]`` Path of included document

<tokens>
========

Define tokens

**Attributes**

* class <string> : Token class name
    - default : ``"Token"``

* namespace <string> : Namespace of token types
    - default : ``"Tokens"``

* headerFile <string> : Path of output token header file
    - default : ``"Token.hpp"``

* sourceFile <string> : Path of output token source file
    - default : ``"Token.cpp"``

**Children**

``<header>``, ``<token>``, ``<member>``, ``<function>``, ``<source>``, ``<include>``

<token>
=======

Define token

**Attributes**

* name <string> : ``[Required]`` Token name

**Children**

``<type>``, ``<member>``, ``<function>``, ``<include>``

<header>
========

C++ codes appending into header file

**Attributes**

* position <"top"|"bottom">: Appending position
    - default : ``"top"``

* indent <number>: Code indention
    - default : ``4``
    - ``0`` : no indention
    - negative value : keep same indention as pxml file (like HTML `<pre>`)

**Children**

C++ codes

<source>
========

C++ codes appending into source file

**Attributes**

* position <string> : Appending position, ``"top"`` or ``"bottom"``
    - default : ``"top"``

* indent <number> : Code indention
    - default : ``4``
    - ``0`` : no indention
    - negative value : keep same indention as pxml file (like HTML `<pre>`)

**Children**

C++ codes

<member>
========

Definition of class member

**Attributes**

* indent <number> : Code indention
    - default : ``4``
    - ``0`` : no indention
    - negative value : keep same indention as pxml file (like HTML `<pre>`)

**Children**

C++ class member definition

<function>
==========

Definition of class member function

**Attributes**

* indent <number> : Code indention
    - default : ``4``
    - ``0`` : no indention
    - negative value : keep same indention as pxml file (like HTML `<pre>`)

**Children**

C++ function definition

<type>
======

Indicate a C++ type

**Children**

C++ type

<lexer>
======

Define lexer

A special rule without any attributes can specify custom end-of-file rule.

Only one end-of-file is allowed in lexer.

**Attributes**

* class <string> : Token class name
    - default : ``"Token"``

* namespace <string> : Namespace of token types
    - default : ``"Tokens"``

* headerFile <string> : Path of output token header file
    - default : ``"Token.hpp"``

* sourceFile <string> : Path of output token source file
    - default : ``"Token.cpp"``

* return <string> : Return type of get()
    - default : ``Token``

**Children**

``<rule>``, ``<group>``, ``<include>``, ``<header>``, ``<member>``, ``<function>``, ``<source>``

<rule>
======

Define a rule in lexer

**Attributes**

* id <string> : A unique id for <use>, can only be lower/upper case alphabetic, digits and _

* pattern <string> : Token match pattern, support the following grammar:

    Characters:

        - alphabetic: a-z, A-Z

        - underscore: _

        - space

        - punctuators: ``~``, `````, ``!``, ``@``, ``#``, ``%``, ``&``, ``=``, ``:``, ``"``, ``'``, ``<``, ``>``, ``/``

        - digits: 0-9

        - escape characters:

            + ``\t`` : horizontal tab

            + ``\r`` : return

            + ``\v`` : vertical tab

            + ``\f`` : line feed

            + ``\n`` : new line

            + hexadecimal character : like ``\x0a``, should be 2 digits

            + ``\\``, ``\?``, ``\^``, ``\$``, ``\(``, ``\)``, ``\*``, ``\+``, ``\-``, ``\{``, ``\}``, ``\|``, ``\.``, ``\,`` : punctuators

        - character class:

            + ``\d`` : [0-9]

            + ``\D`` : NOT [0-9]

            + ``\w`` : [0-9a-zA-Z]

            + ``\W`` : NOT [0-9a-zA-Z]

            + ``\s`` : [ \\t\\r\\v\\f\\n]

            + ``\S`` : NOT [ \\t\\r\\v\\f\\n]
        
            + ``\a`` : [a-zA-Z]

            + ``\A`` : NOT [a-zA-Z]
        
    Ranges
            
        - range: like ``[0-9]``

    OR operation: 

        Example:
        
        ``(lhs|rhs)``: ``lhs`` or ``rhs``

    Group: 

        Example:
        
        ``(lhs)?``: one or zero ``lhs``

    Repeat: 

        - ``?``: one or zero times

        - ``+``: one or more times

        - ``*``: zero or more times

        - ``{N}``: ``N`` times (``N`` is an integer)

        - ``{N,}``: ``N`` or more times (``N`` is an integer)

        - ``{N, M}``: ``N`` to ``M`` times (``N``, ``M`` are integers)

    Wildcard:
        - ``.``: any supported character

* push <string> : State name to push into stack

* pop : Pop current group from stack

* more : Consume the matched text for further $$

If both push and pop specified, stack will pop current group then push new group. 

**Children**

C++ codes that may return a token.

The following replacement variables can be used in the codes:

* _text : The matched text, from current pattern and previous ``more``

* _pos : The location of matched text

<group>
=======

Define a group in lexer

**Attributes**

* name <string> : ``[Required]`` Group name

**Children**

``<rule>``, ``<include>``, ``<use>``

<use>
======

Use a rule in lexer

**Attributes**

* id <string> : ``[Required]`` The rule name to use