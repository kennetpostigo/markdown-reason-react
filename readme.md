![markdown-reason-react](assets/md-r-r.png)

The goal of this library is to create a CLI that will take a directory of
markdown files and then spit out those same markdown files as `reason-react`
pages.

Optionally if you're just making a completely static site you can have a
directory of just markdown files and nothing else and pass a `--static` that will
generate a SPA.

## Tasks

* [x] Parse top level elements
* [ ] Parse inline elements
* [x] Generate AST
* [x] Codegen top level elements
* [ ] Codegen inline elements
* [ ] Highlight Code Blocks
* [ ] Interpolate ReasonReact Components

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
