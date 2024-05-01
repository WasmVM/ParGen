from sphinx.application import Sphinx
from pygments.lexer import RegexLexer
from pygments.token import *

class PxmlLexer(RegexLexer):
    name = "PXML"
    aliases = ["pxml"]
    tokens = {
        'root': [
            (r"<!DOCTYPE pxml>\n", Generic.Heading),
            (r"\{%", Comment.Multiline, 'Comment'),
            (r"\\<", Text),
            (r"<\/[a-zA-Z_]\w*", Name.Tag, 'TagTail'),
            (r"<[a-zA-Z_]\w*", Name.Tag, 'Tag'),
            (r"[^\\<{]+", Text),
            (r"[\{\n]", Text),
        ],
        'Comment': [
            (r"[^%\{\}]+", Comment.Multiline),
            (r"\n", Comment.Multiline),
            (r"\{%", Comment.Multiline, '#push'),
            (r"%\}", Comment.Multiline, '#pop'),
            (r"[%\{\}]", Comment.Multiline)
        ],
        'TagTail' : [
            (r"\{%", Comment.Multiline, 'Comment'),
            (r">", Name.Tag, '#pop'),
            (r".*\n", Name.Tag)
        ],
        'Tag' : [
            (r"\{%", Comment.Multiline, 'Comment'),
            (r"\"", String.Double, 'String'),
            (r"\/?[ \n\t\v\r]*>", Name.Tag, '#pop'),
            (r"[ \n\t\v\r]+", Name.Tag),
            (r"=", Operator),
            (r"(true|false)", Keyword.Constant),
            (r"[a-zA-Z_]\w*", Name.Attribute),
            (r"[0-9\-]+(\.[0-9]*)?([eE][\+\-]?[0-9]+)?", Number.Float)
        ],
        'String' : [
            (r"\\.", String.Double),
            (r"\"", String.Double, '#pop'),
            (r"[^\\\"]+", String.Double),
        ]
    }

def setup(app: Sphinx):
    app.add_lexer("pxml", PxmlLexer)