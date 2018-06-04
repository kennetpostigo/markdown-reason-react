MarkdownReasonReact.Codegen.pipePageToFile(
  "./sample/Readme.re",
  MarkdownReasonReact.Codegen.generateCodeFromAST(
    MarkdownReasonReact.Parser.parseFileToAST("./sample/readme.md"),
    "",
    6,
  ),
);