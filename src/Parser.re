open Types;

let parseHeading = line =>
  if (String.sub(line, 0, 2) == "# ") {
    Heading(1);
  } else if (String.sub(line, 0, 3) == "## ") {
    Heading(2);
  } else if (String.sub(line, 0, 4) == "### ") {
    Heading(3);
  } else if (String.sub(line, 0, 5) == "#### ") {
    Heading(4);
  } else if (String.sub(line, 0, 6) == "##### ") {
    Heading(5);
  } else {
    Heading(6);
  };

let parseCode = line =>
  if (String.sub(line, 0, 3) == "```") {
    Code;
  } else {
    InlineCode;
  };

let parseList = line =>
  switch (String.sub(line, 0, 2)) {
  | "* "
  | "- "
  | "+ " => List(Unordered)
  | _ =>
    try (
      {
        let _x = int_of_string(String.sub(line, 0, 1));
        if (String.sub(line, 1, 1) == ".") {
          List(Ordered);
        } else {
          Paragraph;
        };
      }
    ) {
    | Failure(_) => Paragraph
    }
  };

let parseLinkFootnote = line =>
  switch (String.sub(line, 1, 1)) {
  | "^" => Footnote
  | _ => Link
  };

let parsePrimitives = line =>
  switch (String.sub(line, 0, 1)) {
  | "" => Break
  | ">" => Blockquote
  | "#" => parseHeading(line)
  | "`" => parseCode(line)
  | "1"
  | "2"
  | "3"
  | "4"
  | "5"
  | "6"
  | "7"
  | "8"
  | "9"
  | "*"
  | "-"
  | "+" => parseList(line)
  | "[" => parseLinkFootnote(line)
  | "!" => Image
  /* | "***" => ThematicBreak */
  /* | "_" => Emphasis
     | "__" => Strong
     | "~~" => Delete */
  | exception (Invalid_argument(_e)) => Break
  | _ => Paragraph
  };

let getDirectoryFiles = directory => "TODO";
let iterDirectoryFiles = fn => "TODO";

let parseFileToAST = filename => {
  let ast: ref(ast) = ref([]);
  let startLocation = ref(1);
  let chan = open_in(filename);

  try (
    while (true) {
      let line = input_line(chan);
      let primitive = parsePrimitives(line);

      switch (primitive) {
      | Paragraph
      | Blockquote
      | Code =>
        let (el, finalLocation) =
          Ast.nodeOfMultilineElements(
            primitive,
            chan,
            line,
            startLocation^,
            startLocation^,
          );
        ast := [el, ...ast^];
        startLocation := finalLocation + 1;
      | Link =>
        let (el, finalLocation) =
          Ast.nodeOfLink(line, startLocation^, startLocation^);
        ast := [el, ...ast^];
        startLocation := finalLocation + 1;
      | Image =>
        let (el, finalLocation) =
          Ast.nodeOfImage(line, startLocation^, startLocation^);
        ast := [el, ...ast^];
        startLocation := finalLocation + 1;
      | Footnote =>
        let (el, finalLocation) =
          Ast.nodeOfFootnote(line, startLocation^, startLocation^);
        ast := [el, ...ast^];
        startLocation := finalLocation + 1;
      | List(lt) =>
        let (el, finalLocation) =
          Ast.nodeOfLists(line, chan, [], lt, startLocation^, startLocation^);
        ast := [el, ...ast^];
        startLocation := finalLocation + 1;
      | _ =>
        ast :=
          [
            {
              element: primitive,
              children: [],
              textContent: Some(line),
              location: (startLocation^, startLocation^),
            },
            ...ast^,
          ];
        startLocation := startLocation^ + 1;
      };
    }
  ) {
  | End_of_file => close_in(chan)
  };
  List.rev(ast^);
};