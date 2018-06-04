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
    ++ Parser.addSpace(depth + 2)
    ++ "(ReasonReact.string({|"
    ++ s
    ++ "|}))\n"
  | None => ""
  };

let rec renderElement = (node: Parser.element, depth) =>
  Parser.(
    switch ((node.element: Parser.primitives)) {
    | Heading(1) =>
      Parser.addSpace(depth)
      ++ "<h1> "
      ++ getTextContent(node.textContent, depth)
      ++ Parser.addSpace(depth)
      ++ "</h1>\n"
    | Heading(2) =>
      Parser.addSpace(depth)
      ++ "<h2> "
      ++ getTextContent(node.textContent, depth)
      ++ Parser.addSpace(depth)
      ++ "</h2>\n"
    | Heading(3) =>
      Parser.addSpace(depth)
      ++ "<h3> "
      ++ getTextContent(node.textContent, depth)
      ++ Parser.addSpace(depth)
      ++ "</h3>\n"
    | Heading(4) =>
      Parser.addSpace(depth)
      ++ "<h4> "
      ++ getTextContent(node.textContent, depth)
      ++ Parser.addSpace(depth)
      ++ "</h4>\n"
    | Heading(5) =>
      Parser.addSpace(depth)
      ++ "<h5> "
      ++ getTextContent(node.textContent, depth)
      ++ Parser.addSpace(depth)
      ++ "</h5>\n"
    | Heading(_) =>
      Parser.addSpace(depth)
      ++ "<h6> "
      ++ getTextContent(node.textContent, depth)
      ++ Parser.addSpace(depth)
      ++ "</h6>\n"
    | Blockquote =>
      Parser.addSpace(depth)
      ++ "<blockquote> "
      ++ getTextContent(node.textContent, depth)
      ++ Parser.addSpace(depth)
      ++ "</blockquote>\n"
    | Paragraph =>
      Parser.addSpace(depth)
      ++ "<p>  "
      ++ getTextContent(node.textContent, depth)
      ++ Parser.addSpace(depth)
      ++ "</p>\n"
    | List(Ordered) =>
      Parser.addSpace(depth)
      ++ "<ol>"
      ++ listToString(node.children, depth)
      ++ Parser.addSpace(depth)
      ++ "\n"
      ++ Parser.addSpace(depth)
      ++ "</ol>\n"
    | List(Unordered) =>
      Parser.addSpace(depth)
      ++ "<ul>"
      ++ listToString(node.children, depth)
      ++ "\n"
      ++ Parser.addSpace(depth)
      ++ "</ul>\n"
    | ListItem =>
      "<li> "
      ++ getTextContent(node.textContent, depth + 2)
      ++ Parser.addSpace(depth + 2)
      ++ "</li>"
    | Code =>
      Parser.addSpace(depth)
      ++ "<pre>\n"
      ++ Parser.addSpace(depth + 2)
      ++ "<code>\n"
      ++ getTextContent(node.textContent, depth)
      ++ Parser.addSpace(depth + 2)
      ++ "</code>\n"
      ++ Parser.addSpace(depth)
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
  List.fold_left(
    (acc, curr) => acc ++ "\n" ++ Parser.addSpace(depth + 2) ++ curr,
    "",
    listOfStrings,
  );
};

let rec generateCodeFromAST = (ast: Parser.ast, page, depth) =>
  Parser.(
    switch (ast) {
    | [] =>
      statelessComponent("Readme")
      ++ makeComponent(
           Parser.addSpace(4)
           ++ "<div>\n"
           ++ page
           ++ "\n"
           ++ Parser.addSpace(4)
           ++ "</div>",
         )
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