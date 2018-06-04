MarkdownReasonReact.Codegen.pipePageToFile(
  "./sample/Readme.re",
  MarkdownReasonReact.Codegen.generateCodeFromAST(
    MarkdownReasonReact.Tokenizer.parseFileToAST("./sample/readme.md"),
    "",
    6,
  ),
);