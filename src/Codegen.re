exception Element_Mismatch(string);

let statelessComponent = filename =>
  "let component = ReasonReact.statelessComponent(" ++ filename ++ ");\n";

let makeComponent = elements =>
  "let make = children => {\n  ...component,\n  render: (_self) => {\n    "
  ++ elements
  ++ "\n}";

let getTextContent = tc =>
  switch (tc) {
  | Some(s) => " ReasonReact.string(" ++ s ++ ") "
  | None => ""
  };

let listStringToString = ls =>
  List.fold_left((acc, curr) => acc ++ "\n" ++ curr, "", ls);

let rec renderElement = (node: Tokenizer.element) =>
  Tokenizer.(
    switch ((node.element: Tokenizer.primitives)) {
    | Heading(1) => "<h1> " ++ getTextContent(node.textContent) ++ "</h1>"
    | Heading(2) => "<h2> " ++ getTextContent(node.textContent) ++ "</h2>"
    | Heading(3) => "<h3> " ++ getTextContent(node.textContent) ++ "</h3>"
    | Heading(4) => "<h4> " ++ getTextContent(node.textContent) ++ "</h4>"
    | Heading(5) => "<h5> " ++ getTextContent(node.textContent) ++ "</h5>"
    | Heading(_) => "<h6> " ++ getTextContent(node.textContent) ++ "</h6>"
    | Blockquote =>
      "<blockquote> " ++ getTextContent(node.textContent) ++ "</blockquote>"
    | Paragraph => "<p>  " ++ getTextContent(node.textContent) ++ "</p>"
    | List(Ordered) =>
      "<ol>\n"
      ++ listStringToString(
           List.map(el => renderElement(el), node.children),
         )
      ++ " </ol>"
    | List(Unordered) =>
      "<ul>\n"
      ++ listStringToString(
           List.map(el => renderElement(el), node.children),
         )
      ++ "\n</ul>"
    | ListItem => "<li> " ++ getTextContent(node.textContent) ++ "\n</li>"
    | Code =>
      "<pre> <code>" ++ getTextContent(node.textContent) ++ "</code> </pre>"
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
  );

let renderParagraph = (node: Tokenizer.element) =>
  Tokenizer.(
    switch ((node.element: Tokenizer.primitives)) {
    | Paragraph => "<h1>" ++ getTextContent(node.textContent) ++ "</h1>"
    | _ =>
      raise(
        Element_Mismatch("Expected Paragraph, but received another element."),
      )
    }
  );

let rec generateCodeFromAST = (ast: Tokenizer.ast, page, depth) => {
  let elements = "";

  Tokenizer.(
    switch (ast) {
    | [] => elements
    | [hd] => elements
    | [hd, ...tl] => elements
    }
  )
  |> ignore;
};

let pipePageToFile = (file, page) => {
  let fd = open_out(file);
  Printf.fprintf(fd, "%s", page);
};