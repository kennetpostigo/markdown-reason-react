![markdown-reason-react](https://reasonml.github.io/img/reason.svg)

[alpha](http://example.com "bravo")

[^alpha bravo]

# markdown-reason-react

> Markdown to Reason React Pages

> # markdown-reason-react

The goal [alpha](http://example.com "bravo")
of this library is to ![markdown-reason-react](https://reasonml.github.io/img/reason.svg) create a CLI that will take a directory of
markdown files and then spit out those same markdown files as `reason-react`
pages.

Optionally # if ~~you're~~ just _making_ a _completely_ static site you can have a
directory of just **markdown** files and **nothing** else and pass a `--static` that will
generate a SPA.

## Ordered List:

1. Tokenize
2. AST
3. CodeGen

## Unordered List:

* Tokenize
* AST
* CodeGen

## Ordered List with nested Ordered:

1. Tokenize
    1. test1
2. AST
    1. test2
3. CodeGen

    1. test3

## Unordered with newsted Unordered:

* Tokenize
  * test1
* AST
  * test2
* CodeGen
  * test3

## Ordered List with nested Unordered:

1. Tokenize
    * test1
2. AST
    * test2
3. CodeGen
    * test3

## Unordered with newsted Unordered:

* Tokenize
  1. test1
* AST
  1. test2
* CodeGen

  1. test3

## Unordered with newsted Unordered:

* Tokenize
  1. # test1
* AST
  1. # test2
* CodeGen
  1. # test3

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
