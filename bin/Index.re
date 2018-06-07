MarkdownReasonReact.Codegen.pipePageToFile(
  "./sample/Readme.re",
  MarkdownReasonReact.Codegen.generateCodeFromAST(
    MarkdownReasonReact.Parser.parseFileToAST("./sample/readme.md", [], 1),
    "",
  ),
);

print_string(
  MarkdownReasonReact.Ast.astToString(
    "[\n",
    MarkdownReasonReact.Parser.parseFileToAST("./sample/readme.md", [], 1),
    2,
  ),
);