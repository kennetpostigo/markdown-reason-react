let component = ReasonReact.statelessComponent("Readme");
let make = children => {
  ...component,
  render: _self =>
    <div>
      <img
        src="https://reasonml.github.io/img/reason.svg"
        alt="markdown-reason-react"
      />
      <a href="http://example.com" title="alpha">
        (ReasonReact.string({|"bravo"|}))
      </a>
      <sup> (ReasonReact.string({|alpha bravo|})) </sup>
      <h1> (ReasonReact.string({|# markdown-reason-react|})) </h1>
      <blockquote>
        (ReasonReact.string({|> Markdown to Reason React Pages|}))
      </blockquote>
      <blockquote>
        (ReasonReact.string({|> # markdown-reason-react|}))
      </blockquote>
      <p>
        (
          ReasonReact.string(
            {|The goal [alpha](http://example.com "bravo")
of this library is to ![markdown-reason-react](https://reasonml.github.io/img/reason.svg) create a CLI that will take a directory of
markdown files and then spit out those same markdown files as `reason-react`
pages.|},
          )
        )
      </p>
      <p>
        (
          ReasonReact.string(
            {|Optionally # if ~~you're~~ just _making_ a _completely_ static site you can have a
directory of just **markdown** files and **nothing** else and pass a `--static` that will
generate a SPA.|},
          )
        )
      </p>
      <h2> (ReasonReact.string({|## Ordered List:|})) </h2>
      <ol>
        <li> (ReasonReact.string({|1. Tokenize|})) </li>
        <li> (ReasonReact.string({|2. AST|})) </li>
        <li> (ReasonReact.string({|3. CodeGen|})) </li>
      </ol>
      <h2> (ReasonReact.string({|## Unordered List:|})) </h2>
      <ul>
        <li> (ReasonReact.string({|* Tokenize|})) </li>
        <li> (ReasonReact.string({|* AST|})) </li>
        <li> (ReasonReact.string({|* CodeGen|})) </li>
      </ul>
      <h2>
        (ReasonReact.string({|## Ordered List with nested Ordered:|}))
      </h2>
      <ol>
        <li> (ReasonReact.string({|1. Tokenize|})) </li>
        <li> (ReasonReact.string({|    1. test1|})) </li>
        <li> (ReasonReact.string({|2. AST|})) </li>
        <li> (ReasonReact.string({|    1. test2|})) </li>
        <li> (ReasonReact.string({|3. CodeGen|})) </li>
      </ol>
      <p> (ReasonReact.string({|    1. test3|})) </p>
      <h2>
        (ReasonReact.string({|## Unordered with newsted Unordered:|}))
      </h2>
      <ul>
        <li> (ReasonReact.string({|* Tokenize|})) </li>
        <li> (ReasonReact.string({|  * test1|})) </li>
        <li> (ReasonReact.string({|* AST|})) </li>
        <li> (ReasonReact.string({|  * test2|})) </li>
        <li> (ReasonReact.string({|* CodeGen|})) </li>
        <li> (ReasonReact.string({|  * test3|})) </li>
      </ul>
      <h2>
        (ReasonReact.string({|## Ordered List with nested Unordered:|}))
      </h2>
      <ol>
        <li> (ReasonReact.string({|1. Tokenize|})) </li>
        <li> (ReasonReact.string({|    * test1|})) </li>
        <li> (ReasonReact.string({|2. AST|})) </li>
        <li> (ReasonReact.string({|    * test2|})) </li>
        <li> (ReasonReact.string({|3. CodeGen|})) </li>
        <li> (ReasonReact.string({|    * test3|})) </li>
      </ol>
      <h2>
        (ReasonReact.string({|## Unordered with newsted Unordered:|}))
      </h2>
      <ul>
        <li> (ReasonReact.string({|* Tokenize|})) </li>
        <li> (ReasonReact.string({|  1. test1|})) </li>
        <li> (ReasonReact.string({|* AST|})) </li>
        <li> (ReasonReact.string({|  1. test2|})) </li>
        <li> (ReasonReact.string({|* CodeGen|})) </li>
      </ul>
      <p> (ReasonReact.string({|  1. test3|})) </p>
      <h2>
        (ReasonReact.string({|## Unordered with newsted Unordered:|}))
      </h2>
      <ul>
        <li> (ReasonReact.string({|* Tokenize|})) </li>
        <li> (ReasonReact.string({|  1. # test1|})) </li>
        <li> (ReasonReact.string({|* AST|})) </li>
        <li> (ReasonReact.string({|  1. # test2|})) </li>
        <li> (ReasonReact.string({|* CodeGen|})) </li>
        <li> (ReasonReact.string({|  1. # test3|})) </li>
      </ul>
      <h2> (ReasonReact.string({|## TODO:|})) </h2>
      <ul>
        <li> (ReasonReact.string({|* [ ] Parse Markdown|})) </li>
        <li> (ReasonReact.string({|* [ ] Parse HTML in Markdown|})) </li>
        <li> (ReasonReact.string({|* [ ] Parse YAML in Markdown|})) </li>
        <li>
          (ReasonReact.string({|* [ ] Support Components in Markdown|}))
        </li>
        <li> (ReasonReact.string({|* [ ] Generate AST|})) </li>
        <li> (ReasonReact.string({|* [ ] Codegen ReasonReact Pages|})) </li>
      </ul>
      <pre>
        <code>
          (
            ReasonReact.string(
              {|```shell
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
           markdown pages|},
            )
          )
        </code>
      </pre>
    </div>,
};
