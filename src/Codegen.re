open Types;

let statelessComponent = filename =>
  "let component = ReasonReact.statelessComponent(\"" ++ filename ++ "\");\n";

let makeComponent = elements =>
  "let make = children => {\n  ...component,\n  render: (_self) => {\n"
  ++ elements
  ++ "\n  }\n}";

let getTextContent = tc =>
  switch (tc) {
  | Some(s) => "\n" ++ "(ReasonReact.string({|" ++ s ++ "|}))\n"
  | None => ""
  };

let renderText = s => "\n" ++ "(ReasonReact.string({|" ++ s ++ "|}))\n";

let getRawTextContent = tc =>
  switch (tc) {
  | Some(s) => s
  | None => ""
  };

let rec renderElement = (node: element) =>
  Parser.(
    switch ((node.element: primitive)) {
    | Heading(1) => "<h1>" ++ getTextContent(node.textContent) ++ "</h1>\n"
    | Heading(2) => "<h2>" ++ getTextContent(node.textContent) ++ "</h2>\n"
    | Heading(3) => "<h3>" ++ getTextContent(node.textContent) ++ "</h3>\n"
    | Heading(4) => "<h4>" ++ getTextContent(node.textContent) ++ "</h4>\n"
    | Heading(5) => "<h5>" ++ getTextContent(node.textContent) ++ "</h5>\n"
    | Heading(_) => "<h6>" ++ getTextContent(node.textContent) ++ "</h6>\n"
    | Blockquote =>
      "<blockquote>" ++ getTextContent(node.textContent) ++ "</blockquote>\n"
    | Paragraph => "<p>" ++ getTextContent(node.textContent) ++ "</p>\n"
    | List(Ordered) =>
      "<ol>" ++ listToString(node.children) ++ "\n" ++ "</ol>\n"
    | List(Unordered) =>
      "<ul>" ++ listToString(node.children) ++ "\n" ++ "</ul>\n"
    | ListItem => "<li>" ++ getTextContent(node.textContent) ++ "</li>"
    | Code =>
      "<pre>\n"
      ++ "<code>"
      ++ getTextContent(node.textContent)
      ++ "</code>\n"
      ++ "</pre>\n"
    | Link =>
      let meta =
        String.split_on_char(' ', getRawTextContent(node.textContent));
      let text = List.hd(meta);
      let href = List.nth(meta, 1);
      "<a href=\"" ++ href ++ "\"" ++ ">" ++ renderText(text) ++ "</a>\n";

    | Image =>
      let meta =
        String.split_on_char(' ', getRawTextContent(node.textContent));
      let alt = List.hd(meta);
      let src = List.nth(meta, 1);

      "<img src=\"" ++ src ++ "\" alt=\"" ++ alt ++ "\" />\n";

    | Footnote => "<sup>" ++ getTextContent(node.textContent) ++ "</sup>\n"
    | Null
    | Break
    | Emphasis
    | Strong
    | Delete
    | InlineCode
    | Table
    | TableRow
    | TableCell
    | ThematicBreak
    | LinkReference
    | ImageReference
    | FootnoteReference
    | Definition
    | FootnoteDefinition => ""
    }
  )
and listToString = ls => {
  let listOfStrings = List.map(el => renderElement(el), ls);
  List.fold_left((acc, curr) => acc ++ "\n" ++ curr, "", listOfStrings);
};

let rec generateCodeFromAST = (ast: ast, page) =>
  Parser.(
    switch (ast) {
    | [] =>
      statelessComponent("Readme")
      ++ makeComponent("<div>\n" ++ page ++ "\n" ++ "</div>")
    | [hd] => generateCodeFromAST([], page ++ renderElement(hd))
    | [hd, ...tl] => generateCodeFromAST(tl, page ++ renderElement(hd))
    }
  );

let pipePageToFile = (file, page) => {
  let formattedCode =
    Lexing.from_string(page)
    |> Reason_toolchain.RE.implementation_with_comments
    |> Reason_toolchain.RE.print_implementation_with_comments(
         Format.str_formatter,
       )
    |> Format.flush_str_formatter;

  let fd = open_out(file);
  Printf.fprintf(fd, "%s", formattedCode);
};