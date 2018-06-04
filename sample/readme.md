# markdown-reason-react

> Markdown to Reason React Pages

The goal of this library is to create a CLI that will take a directory of
markdown files and then spit out those same markdown files as `reason-react`
pages.

Optionally if you're just making a completely static site you can have a
directory of just markdown files and nothing else and pass a `--static` that will
generate a SPA.

## Phases:

1.  Tokenize
2.  AST
3.  CodeGen

## TODO:

* [ ] Parse Markdown
* [ ] Parse HTML in Markdown
* [ ] Parse YAML in Markdown
* [ ] Support Components in Markdown
* [ ] Generate AST
* [ ] Codegen ReasonReact Pages

```shell
                                 MARKDOWN-TO-REASON-REACT



SYNOPSIS
       markdown-to-reason-react [OPTION]... DIRECTORY

DESCRIPTION
       markdown-to-reason-react takes a directory of markdown files
       and returns a directory of reason-react pages

ARGUMENTS
       DIRECTORY
           input directories

OPTIONS
       -static
           It will generate a single page application from the directory of
           markdown pages
```
