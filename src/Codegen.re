let statelessComponent = filename =>
  "let component = ReasonReact.statelessComponent(" ++ filename ++ ");\n";

let makeComponent = elements =>
  "let make = children => {\n  ...component,\n  render: (_self) => {\n"
  ++ elements
  ++ "\n}";

let getTextContent = (tc, depth) =>
  switch (tc) {
  | Some(s) =>
    "\n"
    ++ Tokenizer.addSpace(depth + 2)
    ++ "ReasonReact.string(\""
    ++ s
    ++ "\")\n"
  | None => ""
  };

let rec renderElement = (node: Tokenizer.element, depth) =>
  Tokenizer.(
    switch ((node.element: Tokenizer.primitives)) {
    | Heading(1) =>
      Tokenizer.addSpace(depth)
      ++ "<h1> "
      ++ getTextContent(node.textContent, depth)
      ++ Tokenizer.addSpace(depth)
      ++ "</h1>\n"
    | Heading(2) =>
      Tokenizer.addSpace(depth)
      ++ "<h2> "
      ++ getTextContent(node.textContent, depth)
      ++ Tokenizer.addSpace(depth)
      ++ "</h2>\n"
    | Heading(3) =>
      Tokenizer.addSpace(depth)
      ++ "<h3> "
      ++ getTextContent(node.textContent, depth)
      ++ Tokenizer.addSpace(depth)
      ++ "</h3>\n"
    | Heading(4) =>
      Tokenizer.addSpace(depth)
      ++ "<h4> "
      ++ getTextContent(node.textContent, depth)
      ++ Tokenizer.addSpace(depth)
      ++ "</h4>\n"
    | Heading(5) =>
      Tokenizer.addSpace(depth)
      ++ "<h5> "
      ++ getTextContent(node.textContent, depth)
      ++ Tokenizer.addSpace(depth)
      ++ "</h5>\n"
    | Heading(_) =>
      Tokenizer.addSpace(depth)
      ++ "<h6> "
      ++ getTextContent(node.textContent, depth)
      ++ Tokenizer.addSpace(depth)
      ++ "</h6>\n"
    | Blockquote =>
      Tokenizer.addSpace(depth)
      ++ "<blockquote> "
      ++ getTextContent(node.textContent, depth)
      ++ Tokenizer.addSpace(depth)
      ++ "</blockquote>\n"
    | Paragraph =>
      Tokenizer.addSpace(depth)
      ++ "<p>  "
      ++ getTextContent(node.textContent, depth)
      ++ Tokenizer.addSpace(depth)
      ++ "</p>\n"
    | List(Ordered) =>
      Tokenizer.addSpace(depth)
      ++ "<ol>"
      ++ listToString(node.children, depth)
      ++ Tokenizer.addSpace(depth)
      ++ "\n"
      ++ Tokenizer.addSpace(depth)
      ++ "</ol>\n"
    | List(Unordered) =>
      Tokenizer.addSpace(depth)
      ++ "<ul>"
      ++ listToString(node.children, depth)
      ++ "\n"
      ++ Tokenizer.addSpace(depth)
      ++ "</ul>\n"
    | ListItem =>
      "<li> "
      ++ getTextContent(node.textContent, depth + 2)
      ++ Tokenizer.addSpace(depth + 2)
      ++ "</li>"
    | Code =>
      Tokenizer.addSpace(depth)
      ++ "<pre>\n"
      ++ Tokenizer.addSpace(depth + 2)
      ++ "<code>\n"
      ++ getTextContent(node.textContent, depth)
      ++ "</code>\n"
      ++ Tokenizer.addSpace(depth + 2)
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
    (acc, curr) => acc ++ "\n" ++ Tokenizer.addSpace(depth + 2) ++ curr,
    "",
    listOfStrings,
  );
};

let rec generateCodeFromAST = (ast: Tokenizer.ast, page, depth) =>
  Tokenizer.(
    switch (ast) {
    | [] =>
      statelessComponent("Readme")
      ++ makeComponent(
           Tokenizer.addSpace(4)
           ++ "<div>\n"
           ++ page
           ++ "\n"
           ++ Tokenizer.addSpace(4)
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