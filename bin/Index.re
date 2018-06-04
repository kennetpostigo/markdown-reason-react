/* MarkdownReasonReact.Codegen.pipePageToFile(
     "./sample/Readme.re",
     MarkdownReasonReact.Codegen.generateCodeFromAST(
       MarkdownReasonReact.Parser.parseFileToAST("./sample/readme.md"),
       "",
       6,
     ),
   ); */

print_string(
  MarkdownReasonReact.Parser.astToString(
    "[\n",
    MarkdownReasonReact.Parser.parseFileToAST("./sample/readme.md"),
    2,
  ),
);