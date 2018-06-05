let component = ReasonReact.statelessComponent("Readme");
let make = children => {
  ...component,
  render: _self =>
    <div>
      <h1> (ReasonReact.string({|# markdown-reason-react|})) </h1>
      <blockquote>
        (ReasonReact.string({|> Markdown to Reason React Pages|}))
      </blockquote>
      <p>
        (
          ReasonReact.string(
            {|The goal of this library is to create a CLI that will take a directory of
markdown files and then spit out those same markdown files as `reason-react`
pages.|},
          )
        )
      </p>
      <p>
        (
          ReasonReact.string(
            {|Optionally if you're just making a completely static site you can have a
directory of just markdown files and nothing else and pass a `--static` that will
generate a SPA.|},
          )
        )
      </p>
      <h2> (ReasonReact.string({|## Phases:|})) </h2>
      <ol>
        <li> (ReasonReact.string({|1.  Tokenize|})) </li>
        <li> (ReasonReact.string({|2.  AST|})) </li>
        <li> (ReasonReact.string({|3.  CodeGen|})) </li>
      </ol>
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
