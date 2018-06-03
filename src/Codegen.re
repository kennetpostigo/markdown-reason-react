let statelessComponent = filename =>
  "let component = ReasonReact.statelessComponent(" ++ filename ++ ");\n";

let makeComponent = elements =>
  "let make = children => {\n...component,\nrender: (_self) => {\n"
  ++ elements
  ++ "\n}";

/* Codegen */

let generateCodeFromAST = ast => "TODO";