open Types;

let statelessComponent = filename =>
  "let component = ReasonReact.statelessComponent(\"" ++ filename ++ "\");\n";

let makeComponent = elements =>
  "let make = children => {\n  ...component,\n  render: (_self) => {\n"
  ++ elements
  ++ "\n  }\n}";

let getTextContent = (tc, depth) =>
  switch (tc) {
  | Some(s) =>
    "\n"
    ++ Utils.addSpace(depth + 2)
    ++ "(ReasonReact.string({|"
    ++ s
    ++ "|}))\n"
  | None => ""
  };

let rec renderElement = (node: element, depth) =>
  Parser.(
    switch ((node.element: primitives)) {
    | Heading(1) =>
      "<h1> " ++ getTextContent(node.textContent, depth) ++ "</h1>\n"
    | Heading(2) =>
      "<h2> " ++ getTextContent(node.textContent, depth) ++ "</h2>\n"
    | Heading(3) =>
      "<h3> " ++ getTextContent(node.textContent, depth) ++ "</h3>\n"
    | Heading(4) =>
      "<h4> " ++ getTextContent(node.textContent, depth) ++ "</h4>\n"
    | Heading(5) =>
      "<h5> " ++ getTextContent(node.textContent, depth) ++ "</h5>\n"
    | Heading(_) =>
      "<h6> " ++ getTextContent(node.textContent, depth) ++ "</h6>\n"
    | Blockquote =>
      "<blockquote> "
      ++ getTextContent(node.textContent, depth)
      ++ "</blockquote>\n"
    | Paragraph =>
      "<p>  " ++ getTextContent(node.textContent, depth) ++ "</p>\n"
    | List(Ordered) =>
      "<ol>" ++ listToString(node.children, depth) ++ "\n" ++ "</ol>\n"
    | List(Unordered) =>
      "<ul>" ++ listToString(node.children, depth) ++ "\n" ++ "</ul>\n"
    | ListItem =>
      "<li> " ++ getTextContent(node.textContent, depth + 2) ++ "</li>"
    | Code =>
      "<pre>\n"
      ++ "<code>\n"
      ++ getTextContent(node.textContent, depth)
      ++ "</code>\n"
      ++ "</pre>"
    | Break
    | Emphasis
    | Strong
    | Delete
    | InlineCode
    | Table
    | TableRow
    | TableCell
    | ThematicBreak
    | Link
    | Image
    | Footnote
    | LinkReference
    | ImageReference
    | FootnoteReference
    | Definition
    | FootnoteDefinition => ""
    }
  )
and listToString = (ls, depth) => {
  let listOfStrings = List.map(el => renderElement(el, depth), ls);
  List.fold_left((acc, curr) => acc ++ "\n" ++ curr, "", listOfStrings);
};

let rec generateCodeFromAST = (ast: ast, page, depth) =>
  Parser.(
    switch (ast) {
    | [] =>
      statelessComponent("Readme")
      ++ makeComponent("<div>\n" ++ page ++ "\n" ++ "</div>")
    | [hd] =>
      generateCodeFromAST([], page ++ renderElement(hd, depth), depth)
    | [hd, ...tl] =>
      generateCodeFromAST(tl, page ++ renderElement(hd, depth), depth)
    }
  );

let pipePageToFile = (file, page) => {
  let fd = open_out(file);
  Printf.fprintf(fd, "%s", page);
};